package cs2114.adventure;
import java.util.Scanner;
import student.*;
import student.testingsupport.PrintWriterWithHistory;

// -------------------------------------------------------------------------
/**
 *  Tests the read command in multiple scenarios
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.15
 */

public class ReadCommandTest extends student.TestCase
{
    private RoomFilled room;
    private Item note;
    private Item hairpin;
    private PlayerCarrier protag;

    /**
     * Creates a new ReadCommandTest object
     */
    public ReadCommandTest()
    {
        //empty constructor for test class
    }

    /**
     * Sets up the test scenario before each test method
     */
    public void setUp()
    {
        room = new RoomFilled("testchamber");
        note = new Item("note", 0.5);
        hairpin = new Item("hairpin", 1.0);
        protag = new PlayerCarrier();

        room.addItem(note);
        room.addItem(hairpin);
        protag.setCurrentRoom(room);
    }

    /**
     * tests the ReadCommand class with note
     */
    public void testReadCommandNote()
    {
        protag.pickUp("note", room);

        ReadCommand command = new ReadCommand();
        command.readArguments(new Scanner("note"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("-Your FORMER Lab Rat"));
    }

    /**
     * tests the ReadCommand class with hairpin
     */
    public void testReadCommandHairpin()
    {
        protag.pickUp("hairpin", room);

        ReadCommand command = new ReadCommand();
        command.readArguments(new Scanner("hairpin"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("You can't read a hairpin" +
        		" are you crazy?"));
    }

    /**
     * tests the ReadCommand class with object not in inventory
     */
    public void testReadCommandNothing()
    {
        protag.pickUp("hairpin", room);

        ReadCommand command = new ReadCommand();
        command.readArguments(new Scanner("note"));

        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        command.execute(protag, writer);

        assertTrue(writer.getHistory().contains("You don't have that item"));
    }

}
