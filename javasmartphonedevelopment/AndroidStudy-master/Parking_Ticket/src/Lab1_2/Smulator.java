package Lab1_2;

import java.util.ArrayList;

public class Smulator {

	public static void main(String[] argv) {
		ArrayList<ParkingTicket> List = new ArrayList<ParkingTicket>();
		ParkedCar[] car ;
		car = new ParkedCar[4];
		car[0] = new ParkedCar("Toyota", "Corolla", "Black", "XYZ1234", 160);
		car[1] = new ParkedCar("Honda", "Civic", "Red", "IJK4321", 180);
		car[2] = new ParkedCar("Audi", "Q7", "White", "ABCD123", 30);
		car[3] = new ParkedCar("Audi", "X5", "Purple", "518516QQ", 95);
		
		ParkingMeter[] meter;
		meter = new ParkingMeter[4];
		meter[0] = new ParkingMeter(50);
		meter[1] = new ParkingMeter(120);
		meter[2] = new ParkingMeter(0);
		meter[3] = new ParkingMeter(100);
		
		PoliceOfficer[] police;
		police = new PoliceOfficer[4];
		police[0] = new PoliceOfficer("Jacky", "XYZ911");
		police[1] = new PoliceOfficer("Tom", "XYZ008");
		police[2] = new PoliceOfficer("Jason", "XYZ119");
		police[3] = new PoliceOfficer("Joy", "XYZ333");
		
		for(int i=0; i<4; i++){
			ParkingTicket ticket = police[i].issueTicket(car[i], meter[i]);
			if(ticket != null){
				List.add(ticket);
			}
		}
		
		System.out.println("ticket number:" + List.size() + '\n');
		for(ParkingTicket t : List){
			t.report();
		}
	}

}
