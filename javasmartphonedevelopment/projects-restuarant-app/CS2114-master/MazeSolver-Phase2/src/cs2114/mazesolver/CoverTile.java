package cs2114.mazesolver;

import sofia.graphics.RectangleShape;


// -------------------------------------------------------------------------
/**
 *  A RectangularShape object that has a filled color.
 *
 *  @author Benjamin Johnston (benjdj6)
 *  @author Zak Edwards (zak279)
 *  @version Mar 7, 2013
 */

public class CoverTile
    extends RectangleShape
{
    // ----------------------------------------------------------
    /**
     * Create a new CoverTile object.
     * @param left float
     * @param top float
     * @param right float
     * @param bottom float
     */
    public CoverTile(float left, float top, float right, float bottom)
    {
        super(left, top, right, bottom);
        setFilled(true);
    }

}
