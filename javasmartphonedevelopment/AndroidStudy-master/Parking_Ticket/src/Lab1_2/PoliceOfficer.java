package Lab1_2;

/**
 * @brief simulate the police officer
 * To know the name and badge number
 * To examine a parked car and parking meter object and determine 
 * whether the car's time has expired.
 * To issue a parking ticket if the car time has expired. 
 */
public class PoliceOfficer {
	private String name;
	private String badgeNumber;
	
	public PoliceOfficer() {}
	public PoliceOfficer(String name, String badgeNumber) {
		this.name = name;
		this.badgeNumber = badgeNumber;
	}
	
	//getter and setter
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getBadgeNumber() {
		return badgeNumber;
	}
	public void setBadgeNumber(String badgeNumber) {
		this.badgeNumber = badgeNumber;
	}
	
	//related to issue ticket
	public ParkingTicket issueTicket(ParkedCar car, ParkingMeter meter){
		int purchased, parked;
		purchased = examineMeter(meter);
		parked = examineCar(car);
		if(purchased - parked < 0 && parked - purchased <= 60) {
			return new ParkingTicket(car, this, 25.0);
		}
		else if(parked - purchased > 60){
			double fine = (parked - purchased)/60*10 + 25.0;
			return new ParkingTicket(car, this, fine);
		}
		return null;
	}
	
	private int examineCar(ParkedCar car){
		return car.getParkedMinutes();
	}
	
	private int examineMeter(ParkingMeter meter){
		return meter.getPurchasedMinutes();
	}
}
