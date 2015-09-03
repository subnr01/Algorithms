package customerException;
/**
 * deal with input file format error
 * @author Jacky
 *
 */
public class OptionFileFormatException extends Exception{
	private static final long serialVersionUID = 111L;
	public OptionFileFormatException() {
		super();
	}

	public void printFileFormatError()  {
		System.out.println("It is not a txt file!");
	}
}
