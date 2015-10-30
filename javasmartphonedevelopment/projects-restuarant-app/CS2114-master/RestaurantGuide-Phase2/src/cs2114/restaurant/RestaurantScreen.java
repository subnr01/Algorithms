package cs2114.restaurant;

import sofia.content.ContentViewer;
import android.net.Uri;
import android.widget.Button;
import android.widget.RatingBar;
import android.widget.TextView;
import android.widget.EditText;
import sofia.widget.ImageView;
import realtimeweb.yelp.BusinessQuery;
import realtimeweb.yelp.BusinessSearch;
import realtimeweb.yelp.Business;
import realtimeweb.yelp.SearchResponse;
import realtimeweb.yelp.exceptions.BusinessSearchException;
import realtimeweb.yelp.BusinessSearchListener;
import sofia.app.Screen;

// -------------------------------------------------------------------------
/**
 * Allows the user to search for Yelp data and displays the appropriate outputs.
 *
 * @author Ben Johnston (benjdj6)
 * @version 2013.04.14
 */
public class RestaurantScreen
    extends Screen
    implements BusinessSearchListener
{
    // ~ Fields ................................................................

    private CircularLinkedList<Business> results;
    private BusinessSearch               bus;
    private EditText                     searchField;
    private TextView                     restaurantName;
    private TextView                     numRatings;
    private RatingBar                    ratingBar;
    private Button                       next;
    private Button                       previous;
    private Button                       viewMap;
    private ImageView                    imageView;


    // ~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Initializes the fields used by other methods.
     */
    public void initialize()
    {
        results = new CircularLinkedList<Business>();
        bus = BusinessSearch.getInstance();
    }


    /**
     * Performs a search with the text input into the text box
     */
    public void searchFieldEditingDone()
    {
        String location = searchField.getText().toString();
        bus.searchBusinesses(
            new BusinessQuery(location),
            new BusinessSearchGUIAdapter(this));
    }


    /**
     * Adds the returned businesses to a circularlinkedlist
     *
     * @param result
     *            is the list of businesses
     */
    public void businessSearchCompleted(SearchResponse result)
    {
        results.clear();
        for (Business biz : result.getBusinesses())
        {
            results.add(biz);
        }
        if (results.size() != 0)
        {
            updateInfo();
        }
    }


    /**
     * Updates imageviews, textviews, and other outputs.
     */
    public void updateInfo()
    {
        if (results.getCurrent().getImageUrl() == null)
        {
            imageView.setImageURI(null);
        }
        else
        {
            imageView
                .setImageURI(Uri.parse(results.getCurrent().getImageUrl()));
        }
        ratingBar.setRating(results.getCurrent().getRating());
        restaurantName.setText(results.getCurrent().getName());
        numRatings.setText(results.getCurrent().getReviewCount() + " ratings");
    }


    /**
     * Moves the list to the next node.
     */
    public void nextClicked()
    {
        results.next();
        updateInfo();
    }


    /**
     * Moves the list to the previous node.
     */
    public void previousClicked()
    {
        results.previous();
        updateInfo();
    }


    /**
     * Opens a web page showing the current location on google maps
     */
    public void viewMapClicked()
    {
        double longitude = results.getCurrent().getLocation().getLongitude();
        double latitude = results.getCurrent().getLocation().getLatitude();

        new ContentViewer(Uri.parse("http://maps.google.com/maps?q=" + latitude
            + "," + longitude)).start(this);
    }


    /**
     * Disables all buttons if the search fails.
     *
     * @param result
     *            is the exception message
     */
    public void businessSearchFailed(BusinessSearchException result)
    {
        if (viewMap.isEnabled())
        {
            changeButtonStates();
        }
    }


    /**
     * Changes the state of buttons to the opposite of the current state.
     */
    public void changeButtonStates()
    {
        if (viewMap.isEnabled())
        {
            viewMap.setEnabled(false);
            next.setEnabled(false);
            previous.setEnabled(false);
        }
        else
        {
            viewMap.setEnabled(true);
            next.setEnabled(true);
            previous.setEnabled(true);
        }
    }
}
