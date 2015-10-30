package cs2114.mazesolver;
import student.TestCase;

// -------------------------------------------------------------------------
/**
 *  Tests the methods of the Location class.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.03.02
 */

public class LocationTest extends TestCase
{
    private Location a;
    private Location b;

    /**
     * Creates a new LocationTest object
     */
    public LocationTest()
    {
        //empty constructor for test class
    }

    /**
     * Sets up the test scenario before each testcase
     */
    public void setUp()
    {
        a = new Location(0, 0);
        b = new Location(1, 1);
    }

    /**
     * Tests the toString method of Location
     */
    public void testToString()
    {
        assertEquals("(0, 0)", a.toString());
    }

    /**
     * Tests the east method of Location
     */
    public void testEast()
    {
        assertEquals("(1, 0)", a.east().toString());
    }

    /**
     * Tests the west method of Location
     */
    public void testWest()
    {
        assertEquals("(0, 1)", b.west().toString());
    }

    /**
     * Tests the north method of Location
     */
    public void testNorth()
    {
        assertEquals("(1, 0)", b.north().toString());
    }

    /**
     * Tests the south method of Location
     */
    public void testSouth()
    {
        assertEquals("(1, 2)", b.south().toString());
    }

    /**
     * Tests the x method of Location
     */
    public void testX()
    {
        assertEquals(1, b.x());
    }

    /**
     * Tests the y method of Location
     */
    public void testY()
    {
        assertEquals(1, b.y());
    }

    /**
     * Tests the equals boolean method of the Location class
     */
    public void testEquals()
    {
        assertFalse(a.equals(b));
    }

}
