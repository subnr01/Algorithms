
import java.util.ArrayList;
import java.util.EmptyStackException;

//-------------------------------------------------------------------------
/**
 * An implementation of the stack data type that adapts an ArrayList to
 * store its contents.
 *
 * This is a PARTIAL IMPLEMENTATION that needs completion.
 *
 * @param <T> the type of elements stored in the stack
 *
 * @author Tony Allevato (authored class skeleton)
 * @author Benjamin Johnston (benjdj6)
 * @version 2013.03.05
 */
public class ArrayListStack<T> implements SimpleStack<T>
{
	//~ Instance/static variables ............................................

	ArrayList<T> contents;


	//~ Constructors .........................................................

	// ----------------------------------------------------------
	/**
	 * Creates new ArrayListStack object
	 */
	public ArrayListStack()
	{
        contents = new ArrayList<T>();
	}


	//~ Methods ..............................................................

	// ----------------------------------------------------------
	/**
     * Pushes the specified item onto the top of the stack.
     *
     * @param item the item to push onto the stack
     */
	public void push(T item)
	{
        contents.add(item);
	}


	// ----------------------------------------------------------
	/**
     * Pops an item off the top of the stack.
     *
     * @throws EmptyStackException if the stack is empty
     */
	public void pop()
	{
	    if (this.isEmpty())
        {
            throw new EmptyStackException();
        }
        contents.remove(contents.size() - 1);
	}


	// ----------------------------------------------------------
	/**
     * Gets the item at the top of the stack.
     *
     * @return the item at the top of the stack
     * @throws EmptyStackException if the stack is empty
     */
	public T top()
	{
        if (this.isEmpty())
        {
            throw new EmptyStackException();
        }
        return contents.get(contents.size() - 1);
	}


	// ----------------------------------------------------------
	/**
     * Gets the number of items in the stack.
     *
     * @return the number of items in the stack
     */
	public int size()
	{
        return contents.size();
	}


	// ----------------------------------------------------------
	/**
     * Gets a value indicating whether the stack is empty.
     *
     * @return true if the stack is empty, otherwise false
     */
	public boolean isEmpty()
	{
        return contents.size() == 0;
	}
}
