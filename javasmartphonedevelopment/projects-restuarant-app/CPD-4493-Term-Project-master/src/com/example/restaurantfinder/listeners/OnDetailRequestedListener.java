package com.example.restaurantfinder.listeners;

import java.util.ArrayList;

import com.example.restaurantfinder.models.*;


public interface OnDetailRequestedListener {


	public Restaurant onRestaurantRequested();

	
	public ArrayList<Deal> onDealsRequested();
}
