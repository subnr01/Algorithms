package parking_ticket_simulator;

public class Test {

	public static void main(String[] args) {

		/* Different Parked Time Test Cases */
		ParkedCar parkedcar = new ParkedCar("Telsa", "S", "Silver", "PA0108",
				90);
		// ParkedCar parkedcar = new ParkedCar("Telsa", "S", "Silver", "PA0108",
		// 60);
		// ParkedCar parkedcar = new ParkedCar("Telsa", "S", "Silver", "PA0108",
		// 90);
		// ParkedCar parkedcar = new ParkedCar("Telsa", "S", "Silver", "PA0108",
		// 120);
		// ParkedCar parkedcar = new ParkedCar("Telsa", "S", "Silver", "PA0108",
		// 360);

		/* Different Purchased Parking Time Test Cases */
		ParkingMeter parkingmeter = new ParkingMeter(0);
		// ParkingMeter parkingmeter = new ParkingMeter(30);
		// ParkingMeter parkingmeter = new ParkingMeter(60);
		// ParkingMeter parkingmeter = new ParkingMeter(90);
		// ParkingMeter parkingmeter = new ParkingMeter(120);

		PoliceOfficer policeofficer = new PoliceOfficer("John Edwin",
				2009010498, parkedcar, parkingmeter);

		policeofficer.examine();

		/* Check If There IS A Fine, If Yes Print It out */
		if (policeofficer.fine != 0) {
			ParkingTicket parkingticket = new ParkingTicket(policeofficer.fine,
					parkedcar, parkingmeter, policeofficer);
			System.out.println(parkingticket.toString());
			System.out.println(parkedcar.toString());
			System.out.println(parkingticket.toString2());
		}
	}
}
