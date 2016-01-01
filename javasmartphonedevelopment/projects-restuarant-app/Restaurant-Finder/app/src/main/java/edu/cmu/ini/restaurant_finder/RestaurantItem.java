package edu.cmu.ini.restaurant_finder;

import com.google.android.maps.OverlayItem;

import edu.cmu.ini.restaurant_finder.R;
import edu.cmu.ini.restaurant_finder.models.*;
import edu.cmu.ini.restaurant_finder.listeners.*;
import edu.cmu.ini.restaurant_finder.authentication.*;

public class RestaurantItem extends OverlayItem{
	
	Restaurant restaurant;
	public RestaurantItem(Restaurant restaurant) {
		super(restaurant.getCoordinates(), restaurant.getName(), restaurant.getAddress());
		// TODO Auto-generated constructor stub
		this.restaurant = restaurant;
	}
	
	public Restaurant getRestaurant() {
		return restaurant;
	}

}
