package Lab1_2;

/**
 * @brief simulate a parking meter
 * To know the number of minutes of parking time that has been purchased
 */
public class ParkingMeter {
	private int purchasedMinutes;
	
	public ParkingMeter() {}
	
	public ParkingMeter(int purchasedMinutes) {
		setPurchasedMinutes(purchasedMinutes);
	}
	
	//getter and setter
	public int getPurchasedMinutes() {
		return purchasedMinutes;
	}
	
	public void setPurchasedMinutes(int purchasedMinutes) {
		this.purchasedMinutes = purchasedMinutes;
	}
}
