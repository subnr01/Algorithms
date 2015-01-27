
/* 
 *
 * What does strchr do?
 *
 * Returns the first occurrence of c in the string pointed by s
 *
 *
 */


char *strchr( const char *s, int c)
{
    char *temp  = s;

    while (*temp != '\0' && *temp != (char)c)
        temp++;

    return (*temp == c ? (char *) temp : NULL);
}
