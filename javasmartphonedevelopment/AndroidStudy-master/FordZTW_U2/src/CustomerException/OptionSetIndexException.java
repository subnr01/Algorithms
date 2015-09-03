package CustomerException;

public class OptionSetIndexException extends Exception{
	private static final long serialVersionUID = 111L;
	public OptionSetIndexException() {
		super();
	}
	public void printSetIndexError()  {
		System.out.println("Index exceeds its lenth!");
	}
	public void printError3()  {
		System.out.println("Index exceeds its lenth!");
	}
}
