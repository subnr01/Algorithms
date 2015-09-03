package model;

import java.io.Serializable;
import java.util.ArrayList;

/*implement Serializable interface*/
public class OptionSet implements Serializable {
	private static final long serialVersionUID = 1L;
	/**
	 * Option is an inner class of OptionSet
	 * It is used to represent an option for the car
	 * @author Jacky
	 *
	 */
	class Option implements Serializable {
		private static final long serialVersionUID = 1L;
		private String name;
		private Float price;
		
		protected Option() {}
		
		protected Option(String name) {
			this.name = name;
		}
		
		protected Option(String name, Float price) {
			this.name = name;
			this.price = price;
		}
		
		public String getName() {
			return name;
		}
		protected void setName(String name) {
			this.name = name;
		}
		public Float getPrice() {
			return this.price;
		}
		protected void setPrice(Float price) {
			this.price = price;
		}		
		
		protected String print() {
			return this.getName() + " price:" + this.getPrice() + "\n";
		}		
	}  //end of option
	
	//properties of OptionSet
	private String name;
	private ArrayList<Option> options;
	private Integer optionSize;
	
	/**
	 * constructors
	 */
	protected OptionSet() {
		options = new ArrayList<Option>();
	}
	protected OptionSet(String name) {
		this.name = name;
		options = new ArrayList<Option>();
	}
	
	/**
	 * getter and setter of OptionSet
	 * 
	 */
	protected String getName() {
		return name;
	}
	
	protected void setName(String name) {
		this.name = name;
	}
	
	public Integer getOptionSize() {
		this.optionSize = this.options.size();
		return this.optionSize;
	}
	
	public Option getOption(int index) {
		if(index >= 0 && index < this.getOptionSize()) {
			return options.get(index);
		}
		return null;
	}	

	public ArrayList<Option> getOptions() {
		return this.options;
	}
	
	public String getOptionName(int i) {
		return this.options.get(i).getName();
	}
	
	protected void setOptionSize(Integer optionSize) {
		this.optionSize = optionSize;
	}
	
	protected void setOptions(Integer index, Option options) {
		this.options.set(index, options);
	}
	/**
	 * sets the ith Option to the specified name and price
	 * @param i : the ith option
	 * @param name : the name of the option
	 * @param price : the price of the option
	 */
	protected void setOption(String name, Float price) {
		boolean found = false;
		int index = -1;
	
		for(int i=0; i<this.options.size(); i++) {
			if(this.options.get(i).getName().equals(name)) {
				found = true;
				index = i;
				break;
			}
		}
		//if found, just change the price;
		//if not found, add the node into the ArrayList
		if(found) {
			Option o = this.options.get(index);
			o.setPrice(price);
		} else {
			Option o = new Option(name, price);
			this.options.add(o);
		}
	}
	
	/**
	 * get option by its name
	 * @param name : option name
	 * @return option
	 */
	protected Option getOption(String name) {
		int index = findOption(name);
		if(index != -1) {
			return options.get(index);
		}
		return null;
	}
	/**
	 * eturns the price of the Option based on the name
	 * @param name
	 * @return price of the option
	 */
	protected Float getOptionPrice(String name) {
		int index = findOption(name);
		if(index != -1) {
			return options.get(index).getPrice();
		}
		return -1f;
	}
	/**
	 * eturns the index of the Option based on the name
	 * @param name
	 * @return index of the option
	 */
	protected int findOption(String name) {
		for(int i=0; i<options.size(); i++) {
			if(options.get(i).getName().equals(name))
				return i;
		}
		return -1;
	}
	
	/**
	 * print info of options in an optionset
	 * @return info string of the optionset
	 */
	protected String print() {
		String str = "";
		for(int i=0; i<this.getOptionSize(); i++) {
			str += this.options.get(i).print();
		}
		return str;
	}
}
