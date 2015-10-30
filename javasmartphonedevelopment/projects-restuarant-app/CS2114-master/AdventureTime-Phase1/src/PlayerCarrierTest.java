
import student.*;

// -------------------------------------------------------------------------
/**
 *  Tests the methods in the PlayerCarrier class
 *
 *  @author Benjamin Johnston(benjdj6)
 *  @version 2013.02.04
 */

public class PlayerCarrierTest extends student.TestCase
{
    private PlayerCarrier paul;

    /**
     * Creates a new PlayerCarrierTest object
     */
    public PlayerCarrierTest()
    {
        //Empty for test classes
    }

    /**
     * Creates the test scenario for every test method
     */
    public void setUp()
    {
        paul = new PlayerCarrier();
    }

    /**
     * Tests the getWeight method
     */
    public void testGetWeight()
    {
        assertEquals(0, paul.getWeight(), 0.01);
    }

    /**
     * Tests the maxedOut boolean
     */
    public void testMaxedOut()
    {
        assertFalse(paul.maxedOut());
    }

    public void testPickUp()
    {
        Item key = new Item("key", 5.1);
        RoomFilled room = new RoomFilled("test chamber");
        room.addItem(key);
        paul.setCurrentRoom(room);

        paul.pickUp("key", room);

        assertEquals(5.1, paul.getWeight(), 0.01);
    }

}
