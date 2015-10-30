package cs2114.adventure;
import java.util.Scanner;
import student.*;
import student.testingsupport.PrintWriterWithHistory;

// -------------------------------------------------------------------------
/**
 *  Tests the TakeCommand class
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.14
 */

public class TakeCommandTest extends student.TestCase
{
    private RoomFilled room;
    private Item key;
    private PlayerCarrier protag;

    /**
     * creates new TakeCommandTest object
     */
    public TakeCommandTest()
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
     * tests the TakeCommand class
     */
    public void testTakeCommand()
    {
        TakeCommand command = new TakeCommand();
        command.readArguments(new Scanner("key"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("You put the key"
            + " in your inventory"));
    }

}
