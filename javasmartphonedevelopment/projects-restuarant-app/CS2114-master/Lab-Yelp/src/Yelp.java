import realtimeweb.yelp.Business;
import realtimeweb.yelp.BusinessDataListener;
import realtimeweb.yelp.SearchResponse;
import realtimeweb.yelp.exceptions.BusinessSearchException;
import realtimeweb.yelp.BusinessSearchListener;
import java.util.*;
import realtimeweb.yelp.*;


// -------------------------------------------------------------------------
/**
 *  Retrieves and sorts list of businesses.
 *
 *  @author Ben Johnston
 *  @version 2013.04.06
 */

public class Yelp implements BusinessSearchListener, BusinessDataListener
{
    private BusinessSearch results;
    private List<Business> businesses;

    /**
     * Creates a new Yelp object
     */
    public Yelp()
    {
        results = BusinessSearch.getInstance();
    }

    /**
     * Processes the businesses returned by BusinessSearch
     */
    public void processBusinesses()
    {
        businesses = new ArrayList<Business>();
        results.searchBusinesses(new BusinessQuery("Blacksburg, VA"), this);
    }

    /**
     * Returns the businesses with a perfect rating
     * @return a list containing perfect-rated businesses
     */
    public List<Business> perfectBusinesses()
    {
        return businesses;
    }

    /**
     * Removes businesses without a perfect rating from the list.
     */
    public void businessSearchCompleted(SearchResponse result)
    {
        for (Business biz : result.getBusinesses())
        {
            if (Math.abs(biz.getRating() - 5) < 0.001)
            {
                businesses.add(biz);
                results.getBusinessData(biz, this);
            }
        }
    }

    /**
     * Does nothing
     */
    public void businessSearchFailed(BusinessSearchException arg0)
    {
        // Intentionally does nothing

    }

    /**
     * Checks if the ratings are all 5 and removes those that
     * don't meet this criteria.
     */
    public void businessDataCompleted(Business biz)
    {
        for (Review rev : biz.getReviews())
        {
            if (rev.getRating() != 5)
            {
                businesses.remove(biz);
            }
        }
    }

    /**
     * Does nothing
     */
    public void businessDataFailed(BusinessSearchException arg0)
    {
        // Intentionally does nothing
    }

}
