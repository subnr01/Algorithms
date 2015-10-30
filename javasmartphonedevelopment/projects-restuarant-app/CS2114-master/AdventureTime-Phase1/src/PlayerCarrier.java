
import cs2114.adventure.Weighable;
import java.util.*;

// -------------------------------------------------------------------------
/**
 *  Represents the person playing the game, allows them to carry items.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @version 2013.02.04
 */

public class PlayerCarrier extends cs2114.adventure.Player
    implements Weighable
{
    private double currentWeight;
    private double maxWeight;
    private ArrayList<Item> inventory;

    /**
     * Creates a new PlayerCarrier object.
     */
    public PlayerCarrier()
    {
        maxWeight = 10;
        currentWeight = 0;
        inventory = new ArrayList<Item>();
    }

    /**
     * Picks up an item from the room and adds it to the inventory and
     * recalculates the currentWeight.
     * @param item is the name of the item to be picked up.
     * @param room is the room that the player is in
     */
    public void pickUp(String item, RoomFilled room)
    {
        Item newItem = room.pickUp(item);
        if (!maxedOut() && (currentWeight + newItem.getWeight()) <= maxWeight)
        {
            inventory.add(newItem);
            currentWeight = currentWeight + newItem.getWeight();
        }
    }

    /**
     * @return the weight the Player is carrying.
     */
    public double getWeight()
    {
        return currentWeight;
    }

    /**
     * Checks if the player has reached the maximum weight that
     * they can carry.
     * @return true if the current weight is greater than or equal to
     * the max weight.
     */
    public boolean maxedOut()
    {
        if (currentWeight >= maxWeight)
        {
            return true;
        }
        return false;
    }

}
