package scale;

import model.Automobile;;
public class EditOptions extends Thread{
	private Automobile Model;
	private String OptionsetName;
	private String OptionName;
	private String newName;
	private float newprice;
	
	/**
	 * To edit the price of an option
	 * @param Model : name of model
	 * @param OptionsetName : name of optionset
	 * @param OptionName : name of option
	 * @param newprice : new price of an option
	 */
	public EditOptions(Automobile Model, String OptionsetName, String OptionName, float newprice) {
		this.Model = Model;
		this.OptionsetName = OptionsetName;
		this.OptionName = OptionName;
		this.newprice = newprice;
		this.newName = null;
	}
	
	/**
	 * To edit the name of an option set
	 * @param Model : model name
	 * @param OptionsetName : old name of an optionset
	 * @param newName : new name of an optionset
	 */
	public EditOptions(Automobile Model, String OptionsetName, String newName) {
		this.Model = Model;
		this.OptionsetName = OptionsetName;
		this.newName = newName;
	}
	
	/**
	 * To edit option in a seperated thread
	 */
	public void run() {
        synchronized(Model) {
        	for(int i=0; i<6; i++) {
        		try {
					Thread.sleep((long)(2000*Math.random()));
					if(this.newName == null)
		        		Model.setOption(OptionsetName, OptionName, newprice);
		        	else
		        		Model.setOptionSet(OptionsetName, newName);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
        		Model.print();
        	}
        }
    }
}
