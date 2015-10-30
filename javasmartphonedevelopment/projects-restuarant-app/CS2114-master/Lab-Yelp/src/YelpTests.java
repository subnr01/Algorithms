import student.TestCase;


// -------------------------------------------------------------------------
/**
 *  Tests the methods of the Yelp class.
 *
 *  @author Ben Johnston (benjdj6)
 *  @version 2013.04.06
 */

public class YelpTests
    extends TestCase
{
    private Yelp test;

    /**
     * Creates a new YelpTests object
     */
    public YelpTests()
    {
        //empty constructor
    }

    /**
     * Sets up the test scenario
     */
    public void setUp()
    {
        test = new Yelp();
    }

    /**
     * Tests the processbusinesses method
     */
    public void testProcessBusinesses()
    {
        test.processBusinesses();
        assertEquals(1, test.perfectBusinesses().size());
    }

}
