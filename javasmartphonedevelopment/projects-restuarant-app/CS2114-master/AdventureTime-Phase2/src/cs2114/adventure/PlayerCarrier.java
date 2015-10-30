package cs2114.adventure;

import cs2114.adventure.Weighable;
import java.util.*;

// -------------------------------------------------------------------------
/**
 * Represents the person playing the game, allows them to carry items.
 *
 * @author Benjamin Johnston (benjdj6)
 * @version 2013.02.14
 */

public class PlayerCarrier
    extends cs2114.adventure.Player
    implements Weighable
{
    private double          currentWeight;
    private double          maxWeight;
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
     *
     * @param item
     *            is the name of the item to be picked up.
     * @param room
     *            is the room that the player is in
     */
    public void pickUp(String item, RoomFilled room)
    {
        Item newItem = room.pickUp(item);
        if (!maxedOut() && (currentWeight + newItem.getWeight()) <= maxWeight)
        {
            inventory.add(newItem);
            currentWeight += newItem.getWeight();
        }
    }


    /**
     * Removes an item from the inventory and adds it to the currentroom
     *
     * @param item
     *            is the name of the item.
     * @param room
     *            is the room the player is in.
     */
    public void drop(String item, RoomFilled room)
    {
        for (int i = 0; i < inventory.size(); i++)
        {
            if (inventory.get(i).toString().equals(item))
            {
                room.addItem(inventory.get(i));
                currentWeight -= inventory.get(i).getWeight();
                inventory.remove(i);
                break;
            }
        }
    }


    /**
     * @return a string of the contents of the player's inventory
     */
    public String getBag()
    {
        String str = "You have: ";
        if (inventory.size() == 0)
        {
            str += "nothing";
            return str;
        }
        for (int i = 0; i < inventory.size(); i++)
        {
            if (i > 0)
            {
                str += ", ";
            }
            str += inventory.get(i).getName();

        }
        return str;
    }


    /**
     * @return the weight the Player is carrying.
     */
    public double getWeight()
    {
        return currentWeight;
    }


    /**
     * Checks if the player has reached the maximum weight that they can carry.
     *
     * @return true if the current weight is greater than or equal to the max
     *         weight.
     */
    public boolean maxedOut()
    {
        if (currentWeight >= maxWeight)
        {
            return true;
        }
        return false;
    }


    /**
     * @return true if item is in inventory
     * @param thing
     *            is the item being searched for.
     */
    public boolean hasItem(String thing)
    {
        for (int i = 0; i < inventory.size(); i++)
        {
            if (inventory.get(i).getName().equals(thing))
            {
                return true;
            }
        }
        return false;
    }

}
