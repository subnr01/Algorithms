package cs2114.adventure;

import java.io.PrintWriter;

// -------------------------------------------------------------------------
/**
 *  Prints the player's inventory contents
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.14
 */

public class InventoryCommand extends Command
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

        writer.println(protag.getBag());

        return false;
    }

}
