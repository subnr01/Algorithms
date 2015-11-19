package com.example.restaurantfinder.models;

public class Deal {

	private String shortTitle, title, dealUrl, imageUrl, divisionName,
			vendorName, status;
	private String price, value;


	public Deal(String shortTitle, String title, String dealUrl,
			String imageUrl, String divisionName, String vendorName,
			String status, String price, String value) {
		super();
		this.shortTitle = shortTitle;
		this.title = title;
		this.dealUrl = dealUrl;
		this.imageUrl = imageUrl;
		this.divisionName = divisionName;
		this.vendorName = vendorName;
		this.status = status;
		this.price = price;
		this.value = value;
	}

	public String getShortTitle() {
		return shortTitle;
	}

	public Deal() {
	}

	/**
	 * Getter of the title
	 * 
	 * @return
	 */
	public String getTitle() {
		return title;
	}

	/**
	 * Getter of the Deal url
	 * 
	 * @return
	 */
	public String getDealUrl() {
		return dealUrl;
	}

	/**
	 * getter of the image url
	 * 
	 * @return
	 */
	public String getImageUrl() {
		return imageUrl;
	}

	/**
	 * getter of the division name
	 * 
	 * @return
	 */
	public String getDivisionName() {
		return divisionName;
	}

	/**
	 * getter of the vender name
	 * 
	 * @return
	 */
	public String getVendorName() {
		return vendorName;
	}

	/**
	 * Getter of the status
	 * 
	 * @return
	 */
	public String getStatus() {
		return status;
	}

	/**
	 * Getter of the price
	 * 
	 * @return
	 */
	public String getPrice() {
		return price;
	}

	/**
	 * Getter of the value
	 * 
	 * @return
	 */
	public String getValue() {
		return value;
	}

	/**
	 * Setter for each variable
	 */
	public void setTitle(String title) {
		this.title = title;
	}

	public void setDealUrl(String dealUrl) {
		this.dealUrl = dealUrl;
	}

	public void setImageUrl(String imageUrl) {
		this.imageUrl = imageUrl;
	}

	public void setDivisionName(String divisionName) {
		this.divisionName = divisionName;
	}

	public void setVendorName(String vendorName) {
		this.vendorName = vendorName;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public void setPrice(String price) {
		this.price = price;
	}

	public void setValue(String value) {
		this.value = value;
	}

}
