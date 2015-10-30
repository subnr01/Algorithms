package cs2114.mazesolver;

import android.widget.TextView;
import android.widget.Button;
import sofia.graphics.ShapeView;

//-------------------------------------------------------------------------
/**
*  Tests the methods of the MazeSolverScreen class
*
*  @author  Ben Johnston (benjdj6)
*  @version 2013.03.27
*/
public class MazeSolverScreenTests
    extends student.AndroidTestCase<MazeSolverScreen>
{
    //~ Fields ................................................................

    // References to the widgets that you have in your layout. They
    // will be automatically filled in by the test class before your
    // tests run.
    private ShapeView shapeView;
    private Button drawWalls;
    private Button eraseWalls;
    private Button setStart;
    private Button setGoal;
    private Button solve;
    private TextView infoLabel;

    // This field will store the pixel width/height of a cell in the maze.
    private int cellSize;

    private Location test;


    //~ Constructors ..........................................................

    // ----------------------------------------------------------
    /**
     * Test cases that extend AndroidTestCase must have a parameterless
     * constructor that calls super() and passes it the screen/activity class
     * being tested.
     */
    public MazeSolverScreenTests()
    {
        super(MazeSolverScreen.class);
    }


    //~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Initializes the text fixtures.
     */
    public void setUp()
    {
        float viewSize =
            Math.min(getScreen().getWidth(), getScreen().getHeight());

        cellSize = Math.round(viewSize / 6);
        test = new Location(1, 0);
    }

    /**
     * Tests the drawWalls button and method
     */
    public void testDrawWalls()
    {
        click(drawWalls);
        touchDownCell(1, 0);
        assertEquals(MazeCell.WALL, getScreen().getMaze().getCell(test));

        touchMoveCell(1, 2);
        test = new Location(1, 2);
        assertEquals(MazeCell.WALL, getScreen().getMaze().getCell(test));
    }

    /**
     * Tests the erase walls button
     */
    public void testEraseWalls()
    {
        click(drawWalls);
        clickCell(1, 0);
        assertEquals(MazeCell.WALL, getScreen().getMaze().getCell(test));

        click(eraseWalls);
        clickCell(1, 0);
        assertEquals(MazeCell.UNEXPLORED, getScreen().getMaze().getCell(test));
    }

    /**
     * Tests the set start button
     */
    public void testSetStart()
    {
        click(setStart);
        clickCell(1, 0);
        assertEquals(test, getScreen().getMaze().getStartLocation());
    }

    /**
     * Tests the set goal button
     */
    public void testSetGoal()
    {
        click(setGoal);
        clickCell(1, 0);
        assertEquals(test, getScreen().getMaze().getGoalLocation());
    }

    /**
     * Tests the solve button and method
     */
    public void testSolve()
    {
        click(solve);
        assertFalse(infoLabel.getText().equals("No solution was possible."));

        getScreen().initialize();
        click(drawWalls);
        clickCell(1, 0);
        touchDownCell(0, 1);
        click(solve);
        assertEquals("No solution was possible.", infoLabel.getText());
    }


    //~ Private methods .......................................................

    // ----------------------------------------------------------
    /**
     * Simulates touching down on the middle of the specified cell in the maze.
     */
    private void touchDownCell(int x, int y)
    {
        touchDown(shapeView, (x + 0.5f) * cellSize, (y + 0.5f) * cellSize);
    }


    // ----------------------------------------------------------
    /**
     * Simulates moving the finger instantaneously to the middle of the
     * specified cell in the maze.
     */
    private void touchMoveCell(int x, int y)
    {
        touchMove((x + 0.5f) * cellSize, (y + 0.5f) * cellSize);
    }


    // ----------------------------------------------------------
    /**
     * Simulates clicking the middle of the specified cell in the maze. This is
     * equivalent to calling: touchDownCell(x, y); touchUp();
     */
    private void clickCell(int x, int y)
    {
        touchDownCell(x, y);
        touchUp();
    }
}
