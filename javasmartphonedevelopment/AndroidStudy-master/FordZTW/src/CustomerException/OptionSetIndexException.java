package CustomerException;

public class OptionSetIndexException extends Exception{
	private static final long serialVersionUID = 111L;
	public OptionSetIndexException() {
		super();
	}
	public void printProblems()  {
		System.out.println("OptionSet Index exceeds its lenth!");
	}
}
