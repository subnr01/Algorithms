package cs2114.mazesolver;
import student.TestCase;

// -------------------------------------------------------------------------
/**
 *  Tests the methods of the Maze class
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.03.04
 */

public class MazeTest extends TestCase
{
    private Maze test;
    private Location loc;

    /**
     * Creates a new MazeTest object
     */
    public MazeTest()
    {
        //empty constructor
    }

    /**
     * Set up method runs before every test case
     */
    public void setUp()
    {
        test = new Maze(6);
        loc = new Location(1, 1);
    }

    /**
     * Tests the getCell method.
     */
    public void testGetCell()
    {
        assertTrue(test.getCell(loc).equals(MazeCell.UNEXPLORED));
    }

    /**
     * Tests the getGoalLocation method
     */
    public void testGetGoalLocation()
    {
        test.setGoalLocation(loc);
        assertTrue(test.getGoalLocation().equals(loc));
    }

    /**
     * Tests the set goal location method
     */
    public void testSetGoalLocation()
    {
        test.setCell(loc, MazeCell.WALL);
        test.setGoalLocation(loc);
        assertTrue(test.getGoalLocation().equals(loc));

        ILocation gl = new Location(2, 2);
        test.setGoalLocation(gl);
        assertTrue(test.getGoalLocation().equals(gl));
    }

    /**
     * Tests the getStartLocation method.
     */
    public void testGetStartLocation()
    {
        test.setCell(loc, MazeCell.WALL);
        test.setStartLocation(loc);
        assertTrue(test.getStartLocation().equals(loc));
    }

    /**
     * Tests the setCell method of the Maze class
     */
    public void testSetCell()
    {
        test.setCell(loc, MazeCell.FAILED_PATH);
        assertEquals(MazeCell.FAILED_PATH, test.getCell(loc));

        ILocation st = new Location(0, 0);
        test.setCell(st, MazeCell.WALL);
        assertEquals(MazeCell.UNEXPLORED, test.getCell(st));

        test.setCell(st, MazeCell.CURRENT_PATH);
        assertEquals(MazeCell.CURRENT_PATH, test.getCell(st));

        test.setCell(st, MazeCell.FAILED_PATH);
        assertEquals(MazeCell.FAILED_PATH, test.getCell(st));

        test.setGoalLocation(loc);
        test.setCell(loc, MazeCell.UNEXPLORED);
        test.setCell(loc, MazeCell.WALL);
        assertEquals(MazeCell.UNEXPLORED, test.getCell(loc));

        assertEquals(6, test.size());
    }

    /**
     * Tests the solve method in the Maze class.
     */
    public void testSolve()
    {
        ILocation gl = new Location(4, 5);
        Maze ntest = new Maze(6);
        ntest.setGoalLocation(gl);
        ntest.setStartLocation(new Location(0, 1));
        ntest.setCell(loc, MazeCell.WALL);
        ntest.setCell(new Location (2, 0), MazeCell.WALL);
        ntest.setCell(new Location (0, 2), MazeCell.WALL);

        assertNull(ntest.solve());

        test.setGoalLocation(new Location(4, 4));
        test.setStartLocation(new Location(1, 1));
        test.setCell(loc, MazeCell.WALL);
        test.setCell(new Location (1, 0), MazeCell.WALL);
        test.setCell(new Location (1, 2), MazeCell.WALL);
        test.setCell(new Location (1, 4), MazeCell.WALL);
        test.setCell(new Location (1, 5), MazeCell.WALL);
        test.setCell(new Location (3, 2), MazeCell.WALL);
        test.setCell(new Location (3, 3), MazeCell.WALL);
        test.setCell(new Location (3, 4), MazeCell.WALL);
        test.setCell(new Location (3, 5), MazeCell.WALL);

        assertNotNull(test.solve());
    }

}
