package cs2114.adventure;

import java.io.PrintWriter;

// -------------------------------------------------------------------------
/**
 *  Allows the player to read signs and notes in the game
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 14.02.2013
 */

public class ReadCommand extends Command
{

    /**
     * Executes the Read command allowing the player to read signs and notes.
     * @param player represents the person playing the game
     * @param writer is the output console
     * @return false
     */
    public boolean execute(Player player, PrintWriter writer)
    {
        PlayerCarrier protag = (PlayerCarrier) player;

        if (hasSecondWord())
        {
            String itemName = getSecondWord();

            if (itemName.equals("note") && protag.hasItem("note"))
            {
                writer.println("After having worked for you for many years");
                writer.println("I have decided to take my leave, good luck");
                writer.println("finding me.");
                writer.println("-Your FORMER Lab Rat");
            }
            else if (protag.hasItem(itemName))
            {
                writer.println("You can't read a " + itemName +
                    " are you crazy?");
            }
            else
            {
                writer.println("You don't have that item");
            }
        }
        else
        {
            writer.println("Read what?");
        }
        return false;
    }

}
