package test;

import adapter.BuildAuto;
import adapter.CreateAuto;
import adapter.EditAuto;

public class simulator {

	protected static final String SERIALIZED_FILE_NAME = "autos.ser";
	public static void main(String[] args) {
		try{
			//create a model
			CreateAuto auto1  = new BuildAuto();
			auto1.BuildAuto("OptionSet0.txt");
			auto1.printAuto("FordZTW");
			
			//create another model
			CreateAuto auto2  = new BuildAuto();
			auto2.BuildAuto("OptionSet1.txt");
			auto2.printAuto("ToyotaLexus");
			
			//create another model
			CreateAuto auto3  = new BuildAuto();
			auto3.BuildAuto("OptionSet2.txt");
			auto3.printAuto("TeslaZ3");
			
			//two handlers to edit options
			EditAuto autoEdit1 = new BuildAuto();	
			EditAuto autoEdit2 = new BuildAuto();
			
			//two threads change the same option, in the function editOptionPrice
			//it will change 6 times with several seconds' interval, since it is 
			//synchronized, the second change will not work until the first quit!
			autoEdit1.editOptionPrice("FordZTW", "Brakes", "Standard", 100);
			autoEdit2.editOptionPrice("FordZTW", "Brakes", "Standard", 200);
			System.out.println("Two threads which change the price start to run!");
		}
		catch (Exception e){
			e.printStackTrace();
		}
	}

}
