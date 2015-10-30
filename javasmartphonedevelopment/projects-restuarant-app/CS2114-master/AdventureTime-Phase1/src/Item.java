
import cs2114.adventure.Weighable;

// -------------------------------------------------------------------------
/**
 * Item object that contains methods that all items share.
 *
 * @author Benjamin Johnston(benjdj6)
 * @version 2013.02.04
 */

public class Item
    implements Weighable
{

    private String name;
    private double weight;

    /**
     * Creates a new Item object.
     * @param name is the name of the item
     * @param weight is the weight of the item.
     */
    public Item(String name, double weight)
    {
        this.name = name;
        this.weight = weight;
    }

    /**
     * @return the weight of the item
     */
    public double getWeight()
    {
        return weight;
    }

    /**
     * @return the name of the item
     */
    public String getName()
    {
        return name;
    }

}
