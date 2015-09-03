package customerException;
/**
 * deal with the "No Element" error 
 * @author Jacky
 *
 */
public class OptionNoElementException extends Exception{
	private static final long serialVersionUID = 111L;
	public OptionNoElementException() {
		super();
	}
	public void printNoElementError()  {
		System.out.println("Element miss!");
	}
}
