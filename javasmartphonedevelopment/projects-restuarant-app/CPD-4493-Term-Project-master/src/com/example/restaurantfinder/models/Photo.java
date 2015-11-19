package com.example.restaurantfinder.models;


public class Photo {

	private String reference;
	private int width, height;

	/*
	 * Getters of fields
	 */
	public String getReference() {
		return reference;
	}

	public int getWidth() {
		return width;
	}

	public int getHeight() {
		return height;
	}


	public Photo(String reference, int width, int height) {
		super();
		this.reference = reference;
		this.width = width;
		this.height = height;
	}

}
