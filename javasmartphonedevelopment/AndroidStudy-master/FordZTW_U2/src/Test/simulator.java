package Test;

import Adapter.BuildAuto;
import Adapter.CreateAuto;
import Adapter.UpdateAuto;

public class simulator {

	protected static final String SERIALIZED_FILE_NAME = "autos.ser";
	public static void main(String[] args) {
		try{
			CreateAuto auto0  = new BuildAuto();
			UpdateAuto autoUpdate0 = new BuildAuto();
			auto0.BuildAuto("OptionSet0.txt");
			auto0.printAuto("FordZTW");
			
			//change the price of "Cloud 9 White Clearcoat" in Color optionSet to 100
			autoUpdate0.updateOptionPrice("FordZTW", "Color", "Cloud 9 White Clearcoat", 100);
			auto0.printAuto("FordZTW");
			
			//change the name of "Side Impact Air Bags" optionSet to "Air Bags"
			autoUpdate0.updateOptionSetName("FordZTW", "Side Impact Air Bags", "Air Bags");
			auto0.printAuto("FordZTW");
			
			//Change Choices, seems no interface to enable this test!
			
			CreateAuto auto1  = new BuildAuto();
			UpdateAuto autoUpdate1 = new BuildAuto();
			auto1.BuildAuto("OptionSet1.txt");
			auto1.printAuto("ToyotaLexus");
			
			//change the price
			autoUpdate1.updateOptionPrice("ToyotaLexus", "Transmission", "automatic", 280);
			auto1.printAuto("ToyotaLexus");
			
			//change the name of optionSet
			autoUpdate1.updateOptionSetName("ToyotaLexus", "Transmission", "Trans");
			auto1.printAuto("ToyotaLexus");
			
			//Change Choices, seems no interface to enable this test!
			
			CreateAuto auto2  = new BuildAuto();
			UpdateAuto autoUpdate2 = new BuildAuto();
			auto2.BuildAuto("OptionSet2.txt");
			auto2.printAuto("TeslaZ3");
			
			//change the price
			autoUpdate2.updateOptionPrice("TeslaZ3", "Brakes", "Standard", -300);
			auto2.printAuto("TeslaZ3");
			
			//change the name of optionSet
			autoUpdate2.updateOptionSetName("TeslaZ3", "Power Moonroof", "Moonroof");
			auto2.printAuto("TeslaZ3");
			
			//Change Choices, seems no interface to enable this test!
		}
		catch (Exception e){
			e.printStackTrace();
		}
	}

}
