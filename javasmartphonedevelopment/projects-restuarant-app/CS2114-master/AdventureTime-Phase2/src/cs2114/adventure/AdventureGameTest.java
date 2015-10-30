package cs2114.adventure;
import student.*;
import student.testingsupport.PrintWriterWithHistory;

// -------------------------------------------------------------------------
/**
 *  Tests methods in the AdventureGame class
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.14
 */

public class AdventureGameTest extends student.TestCase
{
    /**
     * creates a new AdventureGameTest object
     */
    public AdventureGameTest()
    {
        //empty constructor
    }

    /**
     * Tests the AdventureGame class methods
     */
    public void testGame()
    {
        AdventureGame game = new AdventureGame();
        PrintWriterWithHistory writer = new PrintWriterWithHistory();
        game.useWriter(writer);
        assertTrue(game.interpret("quit"));
    }

}
