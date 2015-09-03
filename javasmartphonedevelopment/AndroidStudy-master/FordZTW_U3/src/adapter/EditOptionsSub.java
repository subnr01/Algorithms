package adapter;
import model.Automobile;
import scale.EditOptions;
/**
 * Used to access protected functions in class EditOptions in other package 
 * @author Jacky
 *
 */
class EditOptionsSub extends EditOptions {
	EditOptionsSub(Automobile Model, String OptionsetName,
							 String OptionName, float newprice) {
		/**
		 * call function in calss EditOptions
		 */
		super(Model, OptionsetName, OptionName, newprice);
	}

	/**
	 * call function in calss EditOptions
	 */
	EditOptionsSub(Automobile Model, String OptionsetName,
			 		String newName) {
	super(Model, OptionsetName, newName);
	}
}
