package cs2114.adventure;

import java.io.PrintWriter;

// -------------------------------------------------------------------------
/**
 *  Allows the player to drop an item into the current room.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.15
 */

public class DropCommand extends Command
{

    /**
     * Executes the drop command allowing the player to drop items from their
     * inventory.
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

            RoomFilled room = (RoomFilled) protag.getCurrentRoom();
            if (room.hasItem(itemName))
            {
                protag.drop(itemName, room);
                writer.println("You took the " + itemName
                    + " out of your inventory");
            }
            else
            {
                writer.println("There is no " + itemName + " to drop!");
            }
        }
        else
        {
            writer.println("Drop what?");
        }
        return false;
    }

}
