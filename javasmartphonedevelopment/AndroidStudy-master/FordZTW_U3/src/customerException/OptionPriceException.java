package customerException;
/**
 * deal with input price error
 * @author Jacky
 *
 */
public class OptionPriceException extends Exception{
	private static final long serialVersionUID = 111L;
	public OptionPriceException() {
		super();
	}
	public void printPriceError()  {
		System.out.println("The price for option is error!");
	}
}
