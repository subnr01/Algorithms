package parking_ticket_simulator;

public class ParkingTicket {

	private PoliceOfficer policeofficer;
	private ParkedCar parkedcar;
	private ParkingMeter parkingmeter;

	private double fine;

	/* Initialize the Parameters in the Ticket */
	public ParkingTicket(double fine, ParkedCar parkedcar,
			ParkingMeter parkingmeter, PoliceOfficer policeofficer) {
		this.parkedcar = new ParkedCar(parkedcar);
		this.parkingmeter = new ParkingMeter(parkingmeter);
		this.policeofficer = new PoliceOfficer(policeofficer);
		this.fine = fine;
	}

	/* Content of the Ticket */
	public String toString() {
		String str = "PARKING VIOLATION\n\n" + "Illegally Parked Car Info: ";
		return str;
	}

	public String toString2() {
		String str = "Minutes Purchased: " + parkingmeter.minutesPurchased
				+ "\nAmount of the fine: " + fine + "\n\nPolice officer: "
				+ policeofficer.name + "\nBadge Number: "
				+ policeofficer.badgeNumber;
		return str;
	}
}
