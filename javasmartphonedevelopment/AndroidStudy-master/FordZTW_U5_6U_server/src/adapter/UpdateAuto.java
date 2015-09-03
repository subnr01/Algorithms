package adapter;
/**
 * UpdateAuto is an interface used to edit option price and optionset name
 * @author Jacky
 */
public interface UpdateAuto {
	public void updateOptionSetName(String Modelname, String OptionSetname, String newName);
	public void updateOptionPrice(String Modelname, String Optionname, String Option, float newprice);
}
