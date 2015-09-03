package customerException;
/**
 * deal with input file format error
 * @author Jacky
 *
 */
public class OptionException extends Exception{
	private static final long serialVersionUID = 111L;
	private int flag;
	public OptionException() {
		super();
	}
	
	public OptionException(int flag) {
		super();
		this.setFlag(flag);
	}
	
	public void printError() {
		switch(this.flag) {
		case 0 :
			printFileFormatError();
			break;
		case 1 :
			printNoElementError();
			break;
		case 2 :
			printNullError();
			break;
		case 3 :
			printPriceError();
			break;
		case 4 :
			printSetIndexError();
			break;
		default :
					
		}
	}

	public void printFileFormatError()  {
		System.out.println("File format is not correct!");
	}
	
	public void printNoElementError()  {
		System.out.println("Element miss!");
	}
	
	public void printNullError()  {
		System.out.println("The reference is null!");
	}
	
	public void printPriceError()  {
		System.out.println("The price for option is error!");
	}
	
	public void printSetIndexError()  {
		System.out.println("Index exceeds its lenth!");
	}

	public int getFlag() {
		return flag;
	}

	public void setFlag(int flag) {
		this.flag = flag;
	}
}
