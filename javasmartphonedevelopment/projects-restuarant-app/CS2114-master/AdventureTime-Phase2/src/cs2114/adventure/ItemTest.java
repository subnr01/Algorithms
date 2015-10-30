package cs2114.adventure;
import student.*;

// -------------------------------------------------------------------------
/**
 *  Tests the methods of the Item class.
 *
 *  @author Benjamin Johnston(benjdj6)
 *  @version 2013.02.04
 */

public class ItemTest extends student.TestCase
{
    private Item key;

    /**
     * Creates a new ItemTest object.
     */
    public ItemTest()
    {
        //Empty for test classes
    }

    /**
     * Sets up the Item object for ever test case.
     */
    public void setUp()
    {
        key = new Item("Key", 0.5);
    }

    /**
     * Tests the getName method for the Item class.
     */
    public void testGetName()
    {
        assertEquals("Key", key.getName());
    }

    /**
     * Tests the getWeight method for the Item class.
     */
    public void testGetWeight()
    {
        assertEquals(0.5, key.getWeight(), 0.01);
    }
}
