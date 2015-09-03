package Lab1_2;

/**
 * @brief simulate parking tickets
 * To report the make, model, color and license number of an illegally parked car
 * Report the fine - which is $25.00 for first hour plus $10.00 for each additional hour
 * Report the name and badge number of the police officer issuing the ticket.
 */
public class ParkingTicket {
	private ParkedCar carGetTicket;
	private PoliceOfficer officerGiveTicket;
	private double fine;
	
	public ParkingTicket() {}
	
	public ParkingTicket(ParkedCar carGetTicket, PoliceOfficer officerGiveTicket, double fine) {
		this.carGetTicket = carGetTicket;
		this.officerGiveTicket = officerGiveTicket;
		this.fine = fine;
	}
	
	public ParkedCar getCarGetTicket() {
		return carGetTicket;
	}
	
	public void setCarGetTicket(ParkedCar carGetTicket) {
		this.carGetTicket = carGetTicket;
	}
	
	public PoliceOfficer getOfficerGiveTicket() {
		return officerGiveTicket;
	}
	
	public void setOfficerGiveTicket(PoliceOfficer officerGiveTicket) {
		this.officerGiveTicket = officerGiveTicket;
	}
	
	public void report() {
		System.out.println("Make:"+carGetTicket.getMake()+"\nModel:"+carGetTicket.getModel()
							+"\nColor:"+carGetTicket.getColor()+"\nLicenseNumber:"+carGetTicket.getLicenseNumber());
		System.out.println("Fine:"+this.fine);
		System.out.println("Police Name:"+this.officerGiveTicket.getName()+"\nBadge Number:"+officerGiveTicket.getBadgeNumber()+"\n");
	}
}