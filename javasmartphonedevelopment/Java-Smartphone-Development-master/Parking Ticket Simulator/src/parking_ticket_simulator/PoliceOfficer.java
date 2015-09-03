package parking_ticket_simulator;

public class PoliceOfficer {

	public String name;
	public int badgeNumber;
	public double fine = 0.00;

	private ParkedCar parkedcar;
	private ParkingMeter parkingmeter;
	private ParkingTicket parkingticket;

	/* Initialize the Info of Police Officer */
	public PoliceOfficer(String name, int badgeNumber, ParkedCar parkedcar,
			ParkingMeter parkingmeter) {
		this.name = name;
		this.badgeNumber = badgeNumber;
		this.parkedcar = new ParkedCar(parkedcar);
		this.parkingmeter = new ParkingMeter(parkingmeter);
	}

	public PoliceOfficer(PoliceOfficer policeofficer2) {
		name = policeofficer2.name;
		badgeNumber = policeofficer2.badgeNumber;
	}

	public void examine() {
		if ((parkedcar.minutes - parkingmeter.minutesPurchased) > 0) {
			if ((parkedcar.minutes - parkingmeter.minutesPurchased) < 60) {
				fine = 25.00;
			} else {
				fine = 25.00 + 10 * (int) ((parkedcar.minutes - parkingmeter.minutesPurchased) / 60);
			}
		}
	}
}
