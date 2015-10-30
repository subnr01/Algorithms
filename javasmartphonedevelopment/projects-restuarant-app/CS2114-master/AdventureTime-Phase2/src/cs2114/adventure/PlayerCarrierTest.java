package cs2114.adventure;
import student.*;

// -------------------------------------------------------------------------
/**
 *  Tests the methods in the PlayerCarrier class
 *
 *  @author Benjamin Johnston(benjdj6)
 *  @version 2013.02.15
 */

public class PlayerCarrierTest extends student.TestCase
{
    private PlayerCarrier paul;
    private Item key;
    private RoomFilled room;

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
        key = new Item("key", 0.1);
        room = new RoomFilled("test chamber");
        room.addItem(key);
        paul.setCurrentRoom(room);
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

    /**
     * Tests the pickUp method
     */
    public void testPickUp()
    {
        Item rock = new Item("rock", 100);
        room.addItem(rock);

        paul.pickUp("key", room);
        paul.pickUp("rock", room);

        assertEquals(0.1, paul.getWeight(), 0.01);
    }

    /**
     * Tests the hasItem boolean method
     */
    public void testHasItem()
    {
        assertFalse(paul.hasItem("key"));

        paul.pickUp("key", room);

        assertTrue(paul.hasItem("key"));
    }

}
