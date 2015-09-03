package Model;

import java.io.Serializable;

import CustomerException.OptionSetIndexException;

public class Automobile implements Serializable {
	private static final long serialVersionUID = 1L;	
	private String name;
	private Integer basePrice;
	private OptionSet[] optionSet; //this model has several OptionSets
	private Integer optionSetSize;
	/*
	 * constructors
	 */
	public Automobile(){}
	public Automobile(String name, Integer basePrice, int optionSetSize){
		setName(name); 				//model name like FordZTW
		setBasePrice(basePrice);
		setOptionSetSize(optionSetSize);
	}
	//getters
	public String getName() {
		return name;
	}
	
	public Integer getBasePrice(){
		return this.basePrice;
	}
	
	public Integer getoptionSetSize(){
		return this.optionSetSize;
	}
	
	//use customer exception to avoid index error
	public OptionSet getOptionSet(int index) {
		try {
			if(index >= optionSetSize) {
				throw new OptionSetIndexException();
			}
		} catch(OptionSetIndexException e) {
			e.printProblems();
			index = this.optionSet.length - 1;
		}
		return optionSet[index];
	}
	
	//finders
	public OptionSet findOptionSet(String OptionSetName) {
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet[i].getName().equals(OptionSetName)) {
				return optionSet[i];
			}
		}
		return null;
	}
	
	public OptionSet.Option findOption(String OptionSetName, String OptionName) {
		OptionSet optionset = findOptionSet(OptionSetName);
		OptionSet.Option [] options = optionset.getOptions(); //inner class
		for(int i=0; i<options.length; i++) {
			if(options[i].getName().equals(OptionName)) {
				return options[i];
			}
		}
		return null;
	}
	
	//setters
	public void setName(String name) { 
		this.name = name; // model name
	}
	
	public void setBasePrice(Integer basePrice){
		this.basePrice = basePrice; // base price
	}
	
	public void setOptionSetSize(int optionSetSize) {
		this.optionSetSize = optionSetSize;
	}
	
	public void setOptionSet(OptionSet[] optionSets) {
		this.setOptionSetSize(optionSets.length);
		this.optionSet = new OptionSet[optionSetSize];
		for(int i=0; i<optionSetSize; i++) {
			this.optionSet[i] = new OptionSet();
			this.optionSet[i] = optionSets[i];
		}
		/*
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet[i] == null) {
				this.optionSet[i] = new OptionSet();
			}
			
		}*/
	}
	
	public void setOption(String OptionSetName, OptionSet.Option option) {
		OptionSet optionset = findOptionSet(OptionSetName);
		optionset.setOption(option);
	}
	
	//delete
	public void deleteOptionSet(String OptionSetName) {
		int index = -1;
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet[i].getName().equals(OptionSetName)) {
				index = i;
			}
		}
		if(index != -1) {
			for(int i=index; i<this.optionSet.length; i++) {
				this.optionSet[i] = this.optionSet[i+1];
			}
			optionSetSize = optionSetSize - 1;
		}
	}
	
	public void deleteOption(String OptionSetName, String OptionName) {
		int index = -1, optionIndex = -1;
		for(int i=0; i<optionSetSize; i++) {
			if(this.optionSet[i].getName().equals(OptionSetName)) {
				index = i;
			}
		}
		if(index != -1) {
			for(int i=0; i<this.optionSet[index].getOptionSize(); i++) {
				if(this.optionSet[index].getOptions()[i].equals(OptionName)) {
					optionIndex = i;
				}
			}
			if(optionIndex != -1) {
				for(int i=optionIndex; i<this.optionSet[index].getOptionSize(); i++) {
					this.optionSet[index].getOptions()[i] = this.optionSet[index].getOptions()[i+1];
				}
				this.optionSet[index].setOptionSize(this.optionSet[index].getOptionSize()-1);
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
				this.optionSet[index] = optionset;
			}
		} catch(OptionSetIndexException e) {
			e.printProblems();
		}
	}
		
	public void updateOption(OptionSet.Option option, int optionSetIndex) {
		OptionSet optionset;
		try {
			if(optionSetIndex >= optionSetSize) {
				throw new OptionSetIndexException();
			}
			else {
				optionset = this.optionSet[optionSetIndex];
				for(int i=0; i<optionset.getOptionSize(); i++) {
					if(optionset.getOptions()[i].getName().equals(option.getName())) {
						optionset.getOptions()[i] = option;
					}
				}
			}
		} catch(OptionSetIndexException e) {
			e.printProblems();
		}
	}
	
	/**
	 * calculate the price of the optionSet index
	 * @return
	 */
	public int getPrice(int index) {
		int additionalPrice = 0;
		//there are at most 5 different options in its optionset
		additionalPrice += optionSet[index].getOptionPrice("Color");
		additionalPrice += optionSet[index].getOptionPrice("Transmission");
		additionalPrice += optionSet[index].getOptionPrice("Brakes");
		additionalPrice += optionSet[index].getOptionPrice("SideAirBag");
		additionalPrice += optionSet[index].getOptionPrice("Moonroof");
		int price = this.getBasePrice() + additionalPrice;
		return price;
	}	
	
	//print method
	public void print() {
		StringBuffer str = new StringBuffer();
		str.append("The model ");
		str.append(this.getName());
		str.append(" includes ");
		str.append(this.getoptionSetSize());
		str.append(" optionSets:");
		System.out.println(str);
		str.setLength(0);
		for(int i=0; i<this.getoptionSetSize(); i++) {
			str.append(this.getOptionSet(i).getName());
			str.append("'s price is ").append(this.getPrice(i));		
			System.out.println(str);
			str.setLength(0);
		}
	}
		
}
