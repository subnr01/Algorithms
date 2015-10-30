package cs2114.adventure;
import java.util.Scanner;
import student.*;
import student.testingsupport.PrintWriterWithHistory;

// -------------------------------------------------------------------------
/**
 *  Tests the UseCommand class
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.15
 */

public class UseCommandTest extends student.TestCase
{
    private RoomFilled room1;
    private RoomFilled room2;
    private Item key;
    private Item rat;
    private PlayerCarrier protag;

    /**
     * creates new UseCommandTest object
     */
    public UseCommandTest()
    {
        //empty constructor
    }

    /**
     * Sets up the test scenario before each test method
     */
    public void setUp()
    {
        room1 = new RoomFilled("testchamber");
        room2 = new RoomFilled("in a dirty kitchen. You hear " +
                "scratching noises from a locked cabinet.");
        key = new Item("key", 0.5);
        rat = new Item("rat", 1.5);
        protag = new PlayerCarrier();

        room1.addItem(key);
        room2.addItem(rat);
        protag.setCurrentRoom(room1);
    }

    /**
     * tests the UseCommand class without key in inventory
     */
    public void testUseCommandNoKey()
    {
        UseCommand command = new UseCommand();
        command.readArguments(new Scanner("key"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("You don't have this item."));
    }

    /**
     * tests the UseCommand class with key in wrong room
     */
    public void testUseCommandWrongRoom()
    {
        protag.pickUp("key", room1);
        UseCommand command = new UseCommand();
        command.readArguments(new Scanner("key"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("Try using this in another " +
        		"room"));
    }

    /**
     * tests the UseCommand class with key in the right room
     */
    public void testUseCommandRightRoom()
    {
        protag.pickUp("key", room1);
        protag.setCurrentRoom(room2);

        UseCommand command = new UseCommand();
        command.readArguments(new Scanner("key"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("Congratualtions! You caught " +
        		"the rat! You win!"));
    }

}
