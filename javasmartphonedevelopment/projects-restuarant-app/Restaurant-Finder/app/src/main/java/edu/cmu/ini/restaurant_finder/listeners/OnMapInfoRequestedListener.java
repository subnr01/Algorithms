package edu.cmu.ini.restaurant_finder.listeners;

import java.util.ArrayList;

import com.google.android.maps.GeoPoint;

import edu.cmu.ini.restaurant_finder.models.*;


/**
 * OnMapInfoRequestedListener This is the interface bridges the tab host
 * activity and the map/list fragment
 * 
 * @author Shenghao Huang
 * 
 */
public interface OnMapInfoRequestedListener {

	/**
	 * Called when the center point request
	 * 
	 * @return
	 */
	public GeoPoint onCenterPointRequested();

	/**
	 * Called when map info is requested
	 * 
	 * @return
	 */
	public ArrayList<Restaurant> onMapInfoRequested();

	/**
	 * Called when the user selected a restaurant.
	 * 
	 * @param restaurant
	 *            is the restaurant selected, it can be null if the user choose
	 *            to let the program decide the restaurant
	 */
	public void onRestaurantSelected(Restaurant restaurant);

	/**
	 * Get the deal associated with the current restaurant selection
	 * 
	 * @return
	 */
	public ArrayList<Deal> onDealsRequested();
}
