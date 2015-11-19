package com.example.restaurantfinder;

import com.google.android.maps.OverlayItem;


import com.example.restaurantfinder.models.*;


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
