/** @file console.c
 *  @brief A console driver.
 *
 *  This file contains the implementation of key functions for console
 *  which are mostly declared in 'p1kern.h'.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *  @bug No know bugs.
 */

#include <console.h>
#include <x86/asm.h>
#include <ctype.h>

#define DEFAULT_COLOR (FGND_GREEN | BGND_BLACK )

#define CONSOLE_GET_CHAR(ROW, COL) \
    (*(char *)( CONSOLE_MEM_BASE + 2*((ROW)*CONSOLE_WIDTH + (COL))))
#define CONSOLE_GET_COLOR(ROW, COL) \
    (*(char *)( CONSOLE_MEM_BASE + 2*((ROW)*CONSOLE_WIDTH + (COL)) + 1))

/* encapsulation of drawing on console */
#define CONSOLE_WRITE(ROW, COL, CH, COLOR) \
{ \
    CONSOLE_GET_CHAR(ROW, COL) = (CH); \
    CONSOLE_GET_COLOR(ROW, COL) = (COLOR); \
}

/* encapsulation of erase; use whitespace */
#define CONSOLE_ERASE_CHAR(ROW, COL, COLOR) \
  CONSOLE_WRITE(ROW, COL, ' ', COLOR)


static int curs_row;
static int curs_col;
static int curs_hidden;
static int term_color;

static void put_char(char ch);
static void scrolldown(int lines);
static void newline();
static void cursor_change();


/********* Function Implementation *********/
void
init_console()
{
    curs_hidden = 0;
    curs_row = 0;
    curs_col = 0;
    term_color = DEFAULT_COLOR;

    clear_console();

    cursor_change();
}

/** @brief put the character onto the console
 *
 *  It will print the character to the place of cursor.
 *  Then check if it's the end of line and move cursor to newline
 *  logically.
 *
 *  @param ch character to be printed
 *  @return Void.
 */
static void
put_char(char ch)
{
    CONSOLE_WRITE(curs_row, curs_col, ch, term_color);
    curs_col ++;
    if ( curs_col  == CONSOLE_WIDTH ) {
        newline();
    }
}

/** @brief move cursor to newline logically
 *
 *  Move to newline. Then check if it's the last line of the console and
 *  scrool down the console by one line.
 *
 *  @return Void.
 */
static void
newline()
{
    curs_col = 0;
    curs_row ++;
    if(curs_row == CONSOLE_HEIGHT) {
        scrolldown(1);
    }
}

/** @brief reset cursor to the beginning of line
 *
 *  @return Void.
 */
static void
carrige()
{
    curs_col = 0;
}

/** @brief remove the previous character from cursor place.
 *
 *  Move cursor backwards one space and overwrite that place with
 *  whitespace.
 *
 *  @return Void.
 */
static void
backspace()
{
    if( curs_col > 0){
        curs_col --;
        CONSOLE_ERASE_CHAR(curs_row, curs_col, term_color);
    }
}

/** @brief scroll down the console screen.
 *
 *  Copy the lines in bottom onto upper place.
 *  Wipe out the bottom lines.
 *  Move the cursor logically.
 *
 *  @param lines the lines to be scrolled down.
 *  @return Void.
 */
static void
scrolldown(int lines)
{
    int i, j;
    char t;

    /*
     *  n lines overall, m lines to scroll down
     *  (n-m) lines left to show on top of the screen
     *  m lines cleared with whitespaces in the bottom
     */
    for (i = 0; i < CONSOLE_HEIGHT - lines; i++) {
        for(j = 0; j < CONSOLE_WIDTH; j++) {
            t = CONSOLE_GET_CHAR(i + lines, j);
            CONSOLE_WRITE(i, j, t, term_color);
        }
    }
    for (i = CONSOLE_HEIGHT - lines; i < CONSOLE_HEIGHT; i++){
        for(j = 0; j < CONSOLE_WIDTH; j++){
            CONSOLE_ERASE_CHAR(i, j, term_color);
        }
    }

    curs_row = (curs_row - lines >= 0)? curs_row - lines: 0 ;
}

/** @brief check if the row and col are valid values.
 *
 *  row and col values must be within the console boundary.
 *
 *  @param row Row value.
 *  @param col Column value.
 *  @return 1 if valid; 0 if not.
 */
static int
valid_row_col(row, col)
{
    return !(row < 0 || row >= CONSOLE_HEIGHT ||
            col < 0 || col >= CONSOLE_WIDTH );
}

/** @brief Change the cursor to new place on console
 *
 *  Use IO ports to write new coordinate values to cursor device.
 *
 *  @return Void.
 */
static void
cursor_change()
{
    int offset = curs_row * CONSOLE_WIDTH + curs_col;

    outb( CRTC_IDX_REG, CRTC_CURSOR_LSB_IDX );
    outb( CRTC_DATA_REG, offset & 0xFF );
    outb( CRTC_IDX_REG, CRTC_CURSOR_MSB_IDX );
    outb( CRTC_DATA_REG, (offset >> 8) & 0xFF );
}


/******** Functions below are declared in 'p1kern.h' ********/
int
putbyte( char ch )
{
    switch (ch) {
    case '\n':
        newline();
        break;
    case '\r':
        carrige();
        break;
    case '\b':
        backspace();
        break;
    default :
        put_char(ch);
    }

    /* change the cursor after printing the char */
    if ( ! curs_hidden )
        cursor_change();

    return 0;
}

void
putbytes( const char *s, int len )
{
    int i;

    if ( len <= 0 || !s )  return;

    for (i = 0; i < len; i++) {
        putbyte(s[i]);
    }
}

int
set_term_color( int color )
{
    /* check if color value is valid */
    if ( color & ~0xFF )
        return -1;

    term_color = color;

    return 0;
}

void
get_term_color( int *color )
{
    *color = term_color;
}

int
set_cursor( int row, int col )
{
    /*
     * wrapper for cursor_change() function.
     * do a lot of checking here before call cursor_change().
     */
    if(!valid_row_col(row, col))
        return -1;

    curs_row = row;
    curs_col = col;

    if(!curs_hidden) {
        cursor_change();
    }

    return 0;
}

void
get_cursor( int *row, int *col )
{
    *row = curs_row;
    *col = curs_col;
}

void
hide_cursor()
{
    if( ! curs_hidden ){
        curs_hidden = 1;

        /* move cursor out of console */
        outb( CRTC_IDX_REG, CRTC_CURSOR_MSB_IDX );
        outb( CRTC_DATA_REG, 0xFF );
    }
}

void
show_cursor()
{
    if( curs_hidden ) {
        curs_hidden = 0;
        cursor_change();
    }
}

void
clear_console()
{
    scrolldown(CONSOLE_HEIGHT);
}

void
draw_char( int row, int col, int ch, int color )
{
    if( ! valid_row_col(row, col) || ! isprint(ch) || (color & ~0xFF ))
        return ;

    CONSOLE_WRITE(row, col, ch, color);
}

char
get_char( int row, int col )
{
    return CONSOLE_GET_CHAR(row, col);
}
