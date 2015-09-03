package model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.LinkedHashMap;

import customerException.OptionNoElementException;
import customerException.OptionNullException;
import customerException.OptionSetIndexException;

public class Automobile implements Serializable {
	private static final long serialVersionUID = 1L;	
	private String make;
	private String model;
	private Integer basePrice;
	private ArrayList<OptionSet> optionSet; //this model has several OptionSets
	private Integer optionSetSize;
	private LinkedHashMap<String, String> Choices;
	
	/**
	 * constructors
	 */
	public Automobile(){}
	
	/**
	 * constructors
	 * @param Make : name of the maker
	 * @param Model : name of the model
	 * @param basePrice : base price of the model
	 * @param optionSetSize : the size of the optionset
	 */
	public Automobile(String Make, String Model, Integer basePrice, int optionSetSize){
		setMake(Make);
		setModel(Model); 				//model name like FordZTW
		setBasePrice(basePrice);
		setOptionSetSize(optionSetSize);
	}
		
	/**
	 * getters
	 * 
	 */
	public String getMake() {
		return this.make;
	}
	
	public String getModel() {
		return this.model;
	}
	
	public Integer getBasePrice(){
		return this.basePrice;
	}
	
	/**
	 * update optionSetSize and return
	 * @return optionSetSize
	 */
	public Integer getoptionSetSize(){
		this.optionSetSize = this.optionSet.size();
		return this.optionSetSize;
	}
	
	/**
	 * use customer exception to avoid index error
	 * @param index : index of optionset
	 * @return optionset with the index
	 */
	public OptionSet getOptionSet(int index) {
		try {
			if(index >= optionSetSize) {
				throw new OptionSetIndexException();
			}
		} catch(OptionSetIndexException e) {
			e.printSetIndexError();
			index = this.optionSet.size() - 1;
		}
		return optionSet.get(index);
	}
	
	/**
	 * To get the option set with the name 
	 * @param optionSetName
	 * @return option set
	 */
	public OptionSet getOptionSet(String optionSetName) {
		int index = -1;
		for(int i=0; i<this.getoptionSetSize(); i++) {
			if(this.optionSet.get(i).getName().equals(optionSetName)) {
				index = i;
				break;
			}
		}
		return optionSet.get(index);
	}
	
	/**
	 * To find option set with the name
	 * @param OptionSetName
	 * @return option set
	 */
	public OptionSet findOptionSet(String OptionSetName) {
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet.get(i).getName().equals(OptionSetName)) {
				return optionSet.get(i);
			}
		}
		return null;
	}
	
	/**
	 * To find option with the set name and option name
	 * @param OptionSetName : set name
	 * @param OptionName : option name
	 * @return Option
	 */
	public OptionSet.Option findOption(String OptionSetName, String OptionName) {
		OptionSet optionset = findOptionSet(OptionSetName);
		OptionSet.Option option = optionset.getOption(OptionName); //inner class
		return option;
	}
	
	/**
	 * setters
	 * 
	 */
	public void setMake(String make) { 
		this.make = make; // model name
	}
	
	public void setModel(String model) { 
		this.model = model; // model name
	}
	
	public void setBasePrice(Integer basePrice){
		this.basePrice = basePrice; // base price
	}
	
	public void setOptionSetSize(int optionSetSize) {
		this.optionSetSize = optionSetSize;
		this.optionSet = new ArrayList<OptionSet>(optionSetSize);
		for(int i=0; i<optionSetSize; i++) {
			OptionSet os = new OptionSet();
			this.optionSet.add(os);
		}
	}
	
	public void setOptionSet(String name, Integer index) {
		OptionSet optionset = this.getOptionSet(index);
		optionset.setName(name);
	}
	
	public void setOptionSet(String name, String newName) {
		int index = -1;
		for(int i=0; i<this.getoptionSetSize(); i++) {
			if(this.optionSet.get(i).getName().equals(name)) {
				index = i;
				break;
			}
		}
		if(index != -1)
			setOptionSet(newName, index);
	}
	
	public void setOption(String OptionSetName, String optionName, float price) {
		OptionSet optionset = findOptionSet(OptionSetName);
		optionset.setOption(optionName, price);
	}
	
	/**
	 * To delete the option set with the name
	 * @param OptionSetName
	 */
	public void deleteOptionSet(String OptionSetName) {
		int index = -1;
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet.get(i).getName().equals(OptionSetName)) {
				index = i;
			}
		}
		if(index != -1) {
			for(int i=index; i<this.optionSet.size(); i++) {
				this.optionSet.set(i, this.optionSet.get(i+1));
			}
			optionSetSize = optionSetSize - 1;
		}
	}
	
	/**
	 * To delete the option with set name and option name
	 * @param OptionSetName
	 * @param OptionName
	 */
	public void deleteOption(String OptionSetName, String OptionName) {
		OptionSet optionSet = null;
		OptionSet.Option option = null;
		for(int i=0; i<this.getoptionSetSize(); i++) {
			if(this.optionSet.get(i).getName().equals(OptionSetName)) {
				optionSet = this.optionSet.get(i);
			}
		}
		if(optionSet != null) {
			for(int i=0; i<optionSet.getOptionSize(); i++) {
				option = optionSet.getOption(OptionName);
				this.optionSet.remove(option);
			}
		}
	}
	
	/**
	 * To update optionset with an index
	 * @param optionset : new option set
	 * @param index : the option set with this index will be updated
	 */
	public void updateOptionSet(OptionSet optionset, int index) {
		try {
			if(index >= optionSetSize) {
				throw new OptionSetIndexException();
			}
			else {
				this.optionSet.set(index, optionset);
			}
		} catch(OptionSetIndexException e) {
			e.printSetIndexError();
		}
	}
		
	/**
	 * To update option with an optionset index
	 * @param option : new option
	 * @param optionSetIndex : optionset with this index will be updated
	 */
	public void updateOption(OptionSet.Option option, int optionSetIndex) {
		OptionSet optionset;
		OptionSet.Option optionT;
		try {
			if(optionSetIndex >= optionSetSize) {
				throw new OptionSetIndexException();
			}
			else {
				optionset = this.optionSet.get(optionSetIndex);
				optionT = optionset.getOption(option.getName());
				optionset.setOption(optionT.getName(), optionT.getPrice());
			}
		} catch(OptionSetIndexException e) {
			e.printSetIndexError();
		}
	}
	
	
	/**
	 * to print all the OptionSets and Options with their price in the model
	 */
	public void print() {
		StringBuffer str = new StringBuffer();
		str.append("Make ");
		str.append(this.getMake());
		str.append(" Model ");		
		str.append(this.getModel());
		str.append("'s base price is ");
		str.append(this.getBasePrice());
		System.out.println(str);
		str.setLength(0);
		str.append("Total price is: ");
		str.append(this.getTotalPrice());
		System.out.println(str);
		System.out.println("end of print----------\n\n");
	}
	
	/**
	 * set default choice to each optionSet
	 */
	public void setDefaultChoices() {
		this.Choices = new LinkedHashMap<String, String>();
		//set default choices to the first option of each optionSet
		for(int i=0; i<this.getoptionSetSize(); i++) {
			this.Choices.put(this.optionSet.get(i).getName(), this.optionSet.get(i).getOption(0).getName());
		}
	}
	
	/**
	 * set choice to an optionSet
	 * @param setName : name of the option set
	 * @param optionName : name of the option
	 */

	public void setOptionChoice(String setName, String optionName) {
		if(this.Choices.containsKey(setName)) {
			this.Choices.put(setName, optionName);
		}
		else {
			try{
				throw new OptionNoElementException();
			} catch(OptionNoElementException e) {
				e.printNoElementError();
			}
		}
	}
	
	/**
	 * To get the name of the chosen option for an option set
	 * @param setName : name of option set
	 * @return option name
	 */
	public String getOptionChoice(String setName) {
		String optionName = null;
		if(this.Choices.containsKey(setName)) {
			optionName = this.Choices.get(setName);
		}
		else {
			try {
				throw new OptionNullException();
			} catch(OptionNullException e) {
				e.printNullError();
			}
		}
		return optionName;
	}
	
	/**
	 * To get the price of a chosen option for an option set
	 * @param setName : name of the option set
	 * @param optionName : name of the option
	 * @return price of the option
	 */
	public Float getOptionChoicePrice(String setName, String optionName) {
		OptionSet.Option option = null;
		
		if(optionName != null)
			option = this.findOptionSet(setName).getOption(optionName);
		
		if(option != null)
			return option.getPrice();
		else
			return 0f;
	}
	
	/**
	 * To get the total price of the chosen options
	 * @return total price
	 */
	public Float getTotalPrice() {
		Float price = (Float)(float)this.basePrice;
		for(int i=0; i<this.getoptionSetSize(); i++) {
			price += getOptionChoicePrice(this.getOptionSet(i).getName(), getOptionChoice(this.getOptionSet(i).getName()));
		}
		return price;
	}
}
