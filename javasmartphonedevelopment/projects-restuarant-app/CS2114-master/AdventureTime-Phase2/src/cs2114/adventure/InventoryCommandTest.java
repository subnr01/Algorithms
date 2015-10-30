package cs2114.adventure;
import student.*;
import student.testingsupport.PrintWriterWithHistory;

// -------------------------------------------------------------------------
/**
 *  Tests the InventoryCommand class
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.15
 */

public class InventoryCommandTest extends student.TestCase
{
    private RoomFilled room;
    private Item key;
    private Item note;
    private PlayerCarrier protag;

    /**
     * creates new InventoryCommandTest object
     */
    public InventoryCommandTest()
    {
        //empty constructor
    }

    /**
     * Sets up the test scenario before each test method
     */
    public void setUp()
    {
        room = new RoomFilled("testchamber");
        key = new Item("key", 0.5);
        note = new Item("note", 1.0);
        protag = new PlayerCarrier();

        room.addItem(key);
        room.addItem(note);
        protag.setCurrentRoom(room);
        protag.pickUp("key", room);
        protag.pickUp("note", room);
    }

    /**
     * tests the InventoryCommand class
     */
    public void testInventoryCommand()
    {
        InventoryCommand command = new InventoryCommand();

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("You have: key, note"));
    }

}
