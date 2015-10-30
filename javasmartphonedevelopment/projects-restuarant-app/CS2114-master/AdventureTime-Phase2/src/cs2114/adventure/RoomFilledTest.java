package cs2114.adventure;
import student.*;

// -------------------------------------------------------------------------
/**
 *  Tests methods for the RoomFilled class.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.14
 */

public class RoomFilledTest extends student.TestCase
{
    private RoomFilled room;
    private Item key;

    /**
     * Creates a new RoomFilledTest object.
     */
    public RoomFilledTest()
    {
        // Constructor empty for unit test, initialization in setUp()
    }

    /**
     * Sets up the RoomFilled object for every test case.
     */
    public void setUp()
    {
        key = new Item("Key", 0.5);
        room = new RoomFilled("Lobby");
        room.addItem(key);
    }

    /**
     * Tests that the checkRoom method can properly return the index number
     * of an item identified by its name.
     */
    public void testCheckRoom()
    {
        assertEquals(0, room.checkRoom("Key"));
    }

    /**
     * Checks that the RoomFilled object has no weight.
     */
    public void testGetWeight()
    {
        assertEquals(0.0, room.getWeight(), .01);
    }

    /**
     * Tests the pickUp method making sure that it removes
     * the object from the array.
     */
    public void testPickUp()
    {
        room.pickUp("Key");
        assertEquals(-1, room.checkRoom("Key"));
        assertNull(room.pickUp("rocks"));
    }

}
