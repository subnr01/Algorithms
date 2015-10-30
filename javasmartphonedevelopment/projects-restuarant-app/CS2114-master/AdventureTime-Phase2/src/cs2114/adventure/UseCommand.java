package cs2114.adventure;

import java.io.PrintWriter;

/**
 *  Allows the player to use items in the game.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.15
 */

public class UseCommand extends Command
{

    /**
     * Executes the Use command allowing the player to use items in their
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

            String kitdes = "in a dirty kitchen. You hear " +
                "scratching noises from a locked cabinet.";
            if (!protag.hasItem(itemName))
            {
                writer.println("You don't have this item.");
            }
            else if (room.getShortDescription().equals(kitdes)
                && itemName.equals("key"))
            {
                protag.pickUp("rat", room);
                writer.println("Congratualtions! You caught the rat! You win!");
            }
            else if (itemName.equals("key"))
            {
                writer.println("Try using this in another room");
            }
            else
            {
                writer.println("There is no use for this item");
            }
        }
        else
        {
            writer.println("Use what?");
        }
        return false;
    }

}
