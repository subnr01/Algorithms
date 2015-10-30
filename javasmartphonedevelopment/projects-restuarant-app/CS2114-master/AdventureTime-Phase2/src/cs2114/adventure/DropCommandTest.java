package cs2114.adventure;
import java.util.Scanner;
import student.*;
import student.testingsupport.PrintWriterWithHistory;

// -------------------------------------------------------------------------
/**
 *  Tests the DropCommand class
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.15
 */

public class DropCommandTest extends student.TestCase
{
    private RoomFilled room;
    private Item key;
    private PlayerCarrier protag;

    /**
     * creates new DropCommandTest object
     */
    public DropCommandTest()
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
        protag = new PlayerCarrier();

        room.addItem(key);
        protag.setCurrentRoom(room);
    }

    /**
     * tests the DropCommand class
     */
    public void testDropCommand()
    {
        DropCommand command = new DropCommand();
        command.readArguments(new Scanner("key"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("You took the key " +
        		"out of your inventory"));
    }

}
