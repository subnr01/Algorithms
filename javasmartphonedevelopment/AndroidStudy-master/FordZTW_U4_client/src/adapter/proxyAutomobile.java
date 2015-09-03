package adapter;
import java.util.LinkedHashMap;

import customerException.OptionFileFormatException;
import model.*;
import scale.EditOptions;
import util.Util;
/**
 * proxyAutomobile is used to implement the functions defined in the interfaces like
 * CreateAuto, EditAuto and UpdateAuto
 * @author Jacky
 */
public abstract class proxyAutomobile {
	private static LinkedHashMap<String, Automobile> models;
	
	/**
	 * To build Automobile object based on different fileType
	 * @param fileName
	 * @param fileType
	 */
	public void BuildAuto(String fileName, String fileType) {
		Util util = new Util();
		try {
			if(fileType.equals("properties")) {
				
			}
			else if(fileType.equals("txt")) {
				Automobile a1 = util.buildAutoObject(fileName);
				if(models == null) {
					models = new LinkedHashMap<String, Automobile>();
				}
				if(!models.containsKey(a1.getModel())) {
					models.put(a1.getModel(), a1);
				}
			}
			else {
				throw new OptionFileFormatException();
			}
		}
		catch (OptionFileFormatException e) {
        	e.printFileFormatError();
        }
	}
	
	/**
	 * Accept a properties file and create an Automobile. 
	 * Then add that created Automobile to the LinkedHashMap.
	 * @param fileName : file name of the properties file
	 */
	public void BuildAutoFromPropertiesFile(String fileName) {
		Util util = new Util();
		Automobile a1 = util.buildAutoObjectFromPropertiesFile(fileName);
		if(models == null) {
			models = new LinkedHashMap<String, Automobile>();
		}
		if(!models.containsKey(a1.getModel())) {
			models.put(a1.getModel(), a1);
		}
	}
	
	/**
	 * To print auto information
	 * @param Modelname : Model's name
	 */
	public void printAuto(String Modelname){
		if(models.containsKey(Modelname)) {
			models.get(Modelname).print();
		}
	}
	
	/**
	 * To update optionset's name
	 * @param Modelname : Model's name
	 * @param OptionSetname : optionset's old name
	 * @param newName : optionset's new name
	 */
	public void updateOptionSetName(String Modelname, String OptionSetname, String newName){
		Automobile auto = models.get(Modelname);
		auto.setOptionSet(OptionSetname, newName);
		
	}
	
	/**
	 * To update option's price
	 * @param Modelname : Model's name
	 * @param OptionSetname : optionset's old name
	 * @param Option : option's name
	 * @param newprice : option's new price
	 */
	public void updateOptionPrice(String Modelname, String OptionSetname, String Option, float newprice){
		Automobile auto = models.get(Modelname);
		auto.setOption(OptionSetname, Option, newprice);
	}
	
	/**
	 * To update option's price with thread safty
	 * @param ModelName : Model's name
	 * @param OptionsetName : optionset's old name
	 * @param OptionName : option's name
	 * @param newprice : option's new price
	 */
	public void editOptionPrice(String ModelName, String OptionsetName, String OptionName, float newprice) {
		EditOptions editOptions = new EditOptions(models.get(ModelName), OptionsetName, OptionName, newprice);
		editOptions.start();
	}
	
	/**
	 * To update optionset's name with thread safty
	 * @param ModelName : Model's name
	 * @param OptionsetName : optionset's old name
	 * @param newName : optionset's new name
	 */
	public void editOptionSetName(String ModelName, String OptionsetName, String newName) {
		EditOptions editOptions = new EditOptions(models.get(ModelName), OptionsetName, newName);
		editOptions.start();
	}
	
}
