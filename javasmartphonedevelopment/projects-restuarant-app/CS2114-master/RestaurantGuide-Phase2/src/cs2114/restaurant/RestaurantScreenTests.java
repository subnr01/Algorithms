package cs2114.restaurant;

import android.content.Intent;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RatingBar;
import android.widget.TextView;

// -------------------------------------------------------------------------
/**
 * Tests the methods in the RestaurantScreen class.
 *
 * @author Ben Johnston (benjdj6)
 * @version 2013.04.14
 */
public class RestaurantScreenTests
    extends student.AndroidTestCase<RestaurantScreen>
{
    // ~ Fields ................................................................

    private EditText  searchField;
    private TextView  restaurantName;
    private RatingBar ratingBar;
    private Button    next;
    private Button    previous;
    private Button    viewMap;


    // ~ Constructors ..........................................................

    // ----------------------------------------------------------
    /**
     * Test cases that extend AndroidTestCase must have a parameterless
     * constructor that calls super() and passes it the screen/activity class
     * being tested.
     */
    public RestaurantScreenTests()
    {
        super(RestaurantScreen.class);
    }


    // ~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Initializes the text fixtures.
     */
    public void setUp()
    {
        enterText(searchField, "Blacksburg, VA");
    }


    /**
     * Tests that the app works properly when search terms are entered.
     */
    public void testBusinessSearchCompleted()
    {
        assertEquals(4.5, ratingBar.getRating(), 0.01);
    }

    /**
     * Tests the next button
     */
    public void testNextClicked()
    {
        click(next);
        assertEquals(4.0, ratingBar.getRating(), 0.01);
        assertEquals("Sub Station II", restaurantName.getText());
    }

    /**
     * Tests the previous button
     */
    public void testPreviousClicked()
    {
        click(previous);
        assertEquals(5.0, ratingBar.getRating(), 0.01);
        assertEquals("Lyric Theatre", restaurantName.getText());
    }

    /**
     * Tests the viewMap button
     */
    public void testViewMap()
    {
        prepareForUpcomingActivity(Intent.ACTION_VIEW);
        click(viewMap);
    }

    /**
     * Tests that the application can disable buttons.
     */
    public void testChangeButtonStates()
    {
        getScreen().changeButtonStates();
        assertFalse(viewMap.isEnabled());
    }
}
