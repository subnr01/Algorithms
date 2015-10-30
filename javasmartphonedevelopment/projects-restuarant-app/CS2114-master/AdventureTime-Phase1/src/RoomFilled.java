
import cs2114.adventure.Weighable;
import java.util.*;


// -------------------------------------------------------------------------
/**
 *  A room that contains items.
 *
 *  @author Benjamin Johnston(benjdj6)
 *  @version 2013.02.04
 */

public class RoomFilled extends cs2114.adventure.Room
    implements Weighable
{
    private ArrayList<Item> contents;

    /**
     * Creates a new RoomFilled object.
     * @param description is a description of the room
     */
    public RoomFilled(String description)
    {
        super(description);

        contents = new ArrayList<Item>();
    }

    // ----------------------------------------------------------
    /**
     * Used to access the Items Array outside of the class
     * @return an ArrayList of items in the Room.
     */
    public ArrayList<Item> items()
    {
        return contents;
    }

    /**
     * Used to add an item to the room.
     * @param thing is the item to be added to the room.
     */
    public void addItem(Item thing)
    {
        contents.add(thing);
    }

    /**
     * Moves the through the array of objects and removes the one
     * with the same name as the object given.
     *
     * @param itemName is a String of an object's name
     * @return Item if the room has the item listed
     */
    public Item pickUp(String itemName)
    {
        int i = this.checkRoom(itemName);
        if (i != -1)
        {
            Item item = contents.get(i);
            contents.remove(i);
            return item;
        }
        return null;
    }

    /**
     * Checks the array for a specified item by name.
     *
     * @param itemName is the name of the item to be searched for
     * @return the index value of the item or -1 if not in the array.
     */
    public int checkRoom(String itemName)
    {
        for (int i = 0; i < contents.size(); i++)
        {
            if (contents.get(i).getName().equals(itemName))
            {
                return i;
            }
        }
        return -1;
    }

    /**
     * @return 0 because room has no weight.
     */
    public double getWeight()
    {
        return 0;
    }

    /**
     * @return true if the room has the item listed
     */
    public boolean hasItem(String itemName)
    {
        if (this.checkRoom(itemName) != -1)
        {
            return true;
        }
        return false;
    }

}
