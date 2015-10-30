package cs2114.mazesolver;

// -------------------------------------------------------------------------
/**
 *  Represents a location in the maze.
 *
 *  @author Benjamin Johnston
 *  @version 2013.03.02
 */

public class Location
    implements ILocation
{
    private int x;
    private int y;

    /**
     * Creates new Location object.
     * @param x is the x coordinate
     * @param y is the y coordinate
     */
    public Location(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    // ----------------------------------------------------------
    /**
     * @return a Location object east of the current location
     */
    public ILocation east()
    {
        return new Location(x + 1, y);
    }


    // ----------------------------------------------------------
    /**
     * @return a Location object north of the current location
     */
    public ILocation north()
    {
        return new Location(x, y - 1);
    }


    // ----------------------------------------------------------
    /**
     * @return a Location object south of the current location
     */
    public ILocation south()
    {
        return new Location(x, y + 1);
    }


    // ----------------------------------------------------------
    /**
     * @return a Location object west of the current location
     */
    public ILocation west()
    {
        return new Location(x - 1, y);
    }


    // ----------------------------------------------------------
    /**
     * @return the x coordinate of this object
     */
    public int x()
    {
        return x;
    }


    // ----------------------------------------------------------
    /**
     * @return the y coordinate of this object
     */
    public int y()
    {
        return y;
    }

    /**
     * @return a string containing the x and y coordinates
     */
    public String toString()
    {
        return "(" + x + ", " + y + ")";
    }

    /**
     * @param o is an object
     * @return true if o is equal to this object
     */
    public boolean equals(Object o)
    {
        if (this.toString().equals(o.toString()))
        {
            return true;
        }
        return false;
    }

}
