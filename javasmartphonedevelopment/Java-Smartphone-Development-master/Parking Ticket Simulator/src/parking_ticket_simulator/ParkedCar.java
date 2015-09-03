package parking_ticket_simulator;

public class ParkedCar {
	private String make;
	private String model;
	private String color;
	private String license;
	public int minutes = 0;

	/* Initialize the Info of the Car */
	public ParkedCar(String make, String model, String color, String license,
			int minutes) {
		this.make = make;
		this.model = model;
		this.color = color;
		this.license = license;
		this.minutes = minutes;
	}

	public ParkedCar(ParkedCar parkedcar2) {
		make = parkedcar2.make;
		model = parkedcar2.model;
		color = parkedcar2.color;
		license = parkedcar2.license;
		minutes = parkedcar2.minutes;
	}

	public String toString() {
		String str = "Parked Car's Make: " + make + "\nParked Car's Model: "
				+ model + "\nParked Car's Color: " + color
				+ "\nParked Car's License number: " + license
				+ "\nMinutes Parked: " + minutes;
		return str;
	}
}
