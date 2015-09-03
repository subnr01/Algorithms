package Model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.LinkedHashMap;

import CustomerException.OptionNoElementException;
import CustomerException.OptionNullException;
import CustomerException.OptionSetIndexException;

public class Automobile implements Serializable {
	private static final long serialVersionUID = 1L;	
	private String make;
	private String model;
	private Integer basePrice;
	private ArrayList<OptionSet> optionSet; //this model has several OptionSets
	private Integer optionSetSize;
	private LinkedHashMap<String, String> Choices;
	
	/*
	 * constructors
	 */
	public Automobile(){}
	
	public Automobile(String Make, String Model, Integer basePrice, int optionSetSize){
		setMake(Make);
		setModel(Model); 				//model name like FordZTW
		setBasePrice(basePrice);
		setOptionSetSize(optionSetSize);
	}
		
	//getters
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
	
	//use customer exception to avoid index error
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
	
	//finders
	public OptionSet findOptionSet(String OptionSetName) {
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet.get(i).getName().equals(OptionSetName)) {
				return optionSet.get(i);
			}
		}
		return null;
	}
	
	public OptionSet.Option findOption(String OptionSetName, String OptionName) {
		OptionSet optionset = findOptionSet(OptionSetName);
		OptionSet.Option option = optionset.getOptions(OptionName); //inner class
		return option;
	}
	
	//setters
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
	
	//delete
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
	
	//update
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
		str.append(", it includes ");
		str.append(this.getoptionSetSize());
		str.append(" optionSets:");
		System.out.println(str);
		str.setLength(0);
		for(int i=0; i<this.getoptionSetSize(); i++) {
			OptionSet os = this.getOptionSet(i);
			str.append(os.getName());
			str.append(":\n");
			str.append(os.print());
			System.out.println(str);
			str.setLength(0);
		}
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
	 * 
	 */
	public Float getOptionChoicePrice(String setName) {
		String optionName = null;
		OptionSet.Option option = null;
		if(this.Choices.containsKey(setName)) {
			optionName = this.Choices.get(setName);
			option = this.findOptionSet(setName).getOption(optionName);
		}
		if(option != null)
			return option.getPrice();
		else
			return 0f;
	}
	
	public Float getTotalPrice() {
		Float price = (Float)(float)this.basePrice;
		for(int i=0; i<this.getoptionSetSize(); i++) {
			price += getOptionChoicePrice(getOptionChoice(this.getOptionSet(i).getName()));
		}
		return price;
	}
}
