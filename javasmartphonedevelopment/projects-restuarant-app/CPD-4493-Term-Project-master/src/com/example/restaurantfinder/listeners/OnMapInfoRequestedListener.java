package com.example.restaurantfinder.listeners;

import java.util.ArrayList;

import com.google.android.maps.GeoPoint;
import com.example.restaurantfinder.models.*;


public interface OnMapInfoRequestedListener {


	public GeoPoint onCenterPointRequested();

	
	public ArrayList<Restaurant> onMapInfoRequested();


	public void onRestaurantSelected(Restaurant restaurant);

	
	public ArrayList<Deal> onDealsRequested();
}
