package CustomerException;

public class OptionNullException extends Exception{
	private static final long serialVersionUID = 112L;
	public OptionNullException() {
		super();
	}
	public void printNullError()  {
		System.out.println("The reference is null!");
	}
}
