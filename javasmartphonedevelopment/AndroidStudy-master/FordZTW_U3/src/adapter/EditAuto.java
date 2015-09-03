package adapter;
/**
 * EditAuto is an interface used to edit option price and optionset name with 
 * thread safty
 * @author Jacky
 * 
 */
public interface EditAuto {
	public void editOptionPrice(String ModelName, String OptionsetName, String OptionName, float newprice);
	public void editOptionSetName(String ModelName, String OptionsetName, String newName);
}
