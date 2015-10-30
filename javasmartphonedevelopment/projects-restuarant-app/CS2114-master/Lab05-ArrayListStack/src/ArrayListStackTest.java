import java.util.EmptyStackException;
import student.TestCase;

//-------------------------------------------------------------------------
/**
 * Tests for the {@link ArrayListStack} class.
 *
 * @author Benjamin Johnston (benjdj6)
 * @author David Butenhoff (eolxe)
 * @version 2013.02.21
 */
public class ArrayListStackTest
    extends TestCase
{
    //~ Instance/static variables .............................................

    private ArrayListStack<String> stack;


    //~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Creates a brand new, empty stack for each test method.
     */
    public void setUp()
    {
        stack = new ArrayListStack<String>();
    }


    /**
     * Tests the push method
     */
    public void testPush()
    {
        try
        {
            stack.top();
            fail("ExceptionMessage");
        }
        catch (EmptyStackException e)
        {
            assertNull(e.getMessage());
        }

        assertTrue(stack.isEmpty());
        stack.push("Item 1");
        assertFalse(stack.isEmpty());
        assertEquals("Item 1", stack.top());
        stack.push("Item 2");
        assertEquals(2, stack.size());
        assertEquals("Item 2", stack.top());
    }

    /**
     * Tests the pop method
     */
    public void testPop()
    {
        try
        {
            stack.pop();
            fail("ExceptionMessage");
        }
        catch (EmptyStackException e)
        {
            assertNull(e.getMessage());
        }

        stack.push("Item 1");
        stack.pop();
        assertTrue(stack.isEmpty());
    }

    /**
     * Tests the size method
     */
    public void testSize()
    {
        assertTrue(stack.isEmpty());
        stack.push("Item 1");
        assertEquals(1, stack.size());
        stack.push("Item 2");
        assertEquals(2, stack.size());
    }

}
