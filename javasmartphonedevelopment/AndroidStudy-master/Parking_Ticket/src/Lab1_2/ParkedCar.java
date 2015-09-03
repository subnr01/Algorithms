package Lab1_2;

/**
 * @brief to simulate a parked car
 * To know the car's make, model, color, license number 
 * and number of minutes the car has been parked
 */
public class ParkedCar {
	private String make;
	private String model;
	private String color;
	private String licenseNumber;
	private int parkedMinutes;
	
	public ParkedCar() {}
	public ParkedCar(String make, String model, String color, String licenseNumber, int parkedMinutes){
		this.make = make;
		this.model = model;
		this.color = color;
		this.licenseNumber = licenseNumber;
		this.parkedMinutes = parkedMinutes;
	}
	
	public String getMake() {
		return make;
	}
	
	public void setMake(String make) {
		this.make = make;
	}
	
	public String getModel() {
		return model;
	}
	
	public void setModel(String model) {
		this.model = model;
	}
	
	public String getColor() {
		return color;
	}
	
	public void setColor(String color) {
		this.color = color;
	}
	
	public String getLicenseNumber() {
		return licenseNumber;
	}
	
	public void setLicenseNumber(String licenseNumber) {
		this.licenseNumber = licenseNumber;
	}
	
	public int getParkedMinutes() {
		return parkedMinutes;
	}
	
	public void setParkedMinutes(int parkedMinutes) {
		this.parkedMinutes = parkedMinutes;
	}
	
}
