package cs2114.adventure;

import java.io.PrintWriter;

// -------------------------------------------------------------------------
/**
 *  Allows the player to use items in the game.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.14
 */

public class TakeCommand extends Command
{
    /**
     * Executes the Take command allowing the player to pickup items from the
     * world.
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
                protag.pickUp(itemName, room);
                writer.println("You put the " + itemName
                    + " in your inventory");
            }
            else
            {
                writer.println("There is no " + itemName + " to take!");
            }
        }
        else
        {
            writer.println("Take what?");
        }
        return false;
    }

}
