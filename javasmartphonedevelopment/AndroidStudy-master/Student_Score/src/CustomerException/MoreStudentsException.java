package CustomerException;

public class MoreStudentsException extends Exception{
	private static final long serialVersionUID = 1;
	public MoreStudentsException() {
		super();
	}
	public void printProblems()  {
		System.out.println("Students number exceeds 40, count only 40 students!!");
	}
}
