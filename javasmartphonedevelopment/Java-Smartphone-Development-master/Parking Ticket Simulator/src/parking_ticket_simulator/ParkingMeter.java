package parking_ticket_simulator;

public class ParkingMeter {

	public int minutesPurchased = 0;

	/* Initialize the Minutes Purchased */
	public ParkingMeter(int minutesPurchased) {
		this.minutesPurchased = minutesPurchased;
	}

	public ParkingMeter(ParkingMeter parkingmeter2) {
		minutesPurchased = parkingmeter2.minutesPurchased;
	}
}
