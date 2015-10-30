package cs2114.restaurant;

import java.util.*;
import student.TestCase;

// -------------------------------------------------------------------------
/**
 * Tests the methods of the CircularLinkedList class.
 *
 * @author Benjamin Johnston (benjdj6)
 * @version 2013.04.03
 */

public class CircularLinkedListTest
    extends TestCase
{
    /**
     * Is the CircularLinkedList to be tested
     */
    CircularLinkedList<String> test;


    /**
     * Creates a new CircularLinkedList object
     */
    public CircularLinkedListTest()
    {
        // Empty constructor for test class
    }


    /**
     * Setup method that creates conditions for test cases. Runs before each
     * test case.
     */
    public void setUp()
    {
        test = new CircularLinkedList<String>();
    }


    /**
     * Tests the previous method of the CircularLinkedList class.
     */
    public void testAdd()
    {
        Exception occurred = null;
        try
        {
            test.getCurrent();
        }
        catch (Exception exception)
        {
            occurred = exception;
        }
        assertNotNull(occurred);
        assertTrue(occurred instanceof NoSuchElementException);
        assertEquals(
            "There are no elements in this list",
            occurred.getMessage());

        test.add("1");
        test.add("2");
        test.add("3");

        assertEquals("3", test.getCurrent());
        test.next();
        assertEquals("2", test.getCurrent());
        test.next();
        assertEquals("1", test.getCurrent());
    }


    /**
     * Tests the previous method of the CircularLinkedList class
     */
    public void testPrevious()
    {
        test.add("1");
        test.add("2");
        test.add("3");

        test.previous();
        assertEquals("1", test.getCurrent());

        test.previous();
        assertEquals("2", test.getCurrent());

        test.removeCurrent();
        test.previous();
        assertEquals("3", test.getCurrent());

        test.removeCurrent();
        test.previous();
        assertEquals("1", test.getCurrent());
    }


    /**
     * Tests the next method of the CircularLinkedList class
     */
    public void testNext()
    {
        test.next();

        test.add("1");
        test.add("2");
        test.add("3");

        test.next();
        assertEquals("2", test.getCurrent());

        test.next();
        assertEquals("1", test.getCurrent());

        test.next();
        assertEquals("3", test.getCurrent());

        test.add("4");
        test.add("5");
        test.add("6");

        test.next();
        assertEquals("5", test.getCurrent());

        test.next();
        assertEquals("4", test.getCurrent());

        test.next();
        assertEquals("3", test.getCurrent());

        test.next();
        assertEquals("2", test.getCurrent());

        test.next();
        assertEquals("1", test.getCurrent());

        test.next();
        assertEquals("6", test.getCurrent());
    }


    /**
     * Tests the clear method of the CircularLinkedList class
     */
    public void testClear()
    {
        Exception occurred = null;
        try
        {
            test.removeCurrent();
        }
        catch (Exception exception)
        {
            occurred = exception;
        }
        assertNotNull(occurred);
        assertTrue(occurred instanceof NoSuchElementException);
        assertEquals("The List is Empty", occurred.getMessage());

        test.add("1");
        test.add("2");
        test.add("3");
        test.add("4");

        assertEquals("4", test.getCurrent());
        assertEquals(4, test.size());

        test.clear();
        assertEquals(0, test.size());

        try
        {
            test.getCurrent();
        }
        catch (Exception exception)
        {
            occurred = exception;
        }
        assertNotNull(occurred);
        assertTrue(occurred instanceof NoSuchElementException);
        assertEquals(
            "There are no elements in this list",
            occurred.getMessage());


        test.add("5");
        test.removeCurrent();
        assertEquals(0, test.size());
    }

    /**
     * Tests the toString method
     */
    public void testToString()
    {
        test.add("1");
        test.add("2");
        test.add("3");
        test.add("4");

        test.next();
        assertEquals("[3, 2, 1, 4]", test.toString());
    }

    /**
     * Tests the hasNext method
     */
    public void testHasNext()
    {
        Iterator<String> iterator = test.iterator();
        assertFalse(iterator.hasNext());
        test.add("1");
        test.add("2");
        iterator = test.iterator();

        assertTrue(iterator.hasNext());
    }

    /**
     * Tests Iterator's next method.
     */
    public void testIteratorNext()
    {
        Exception occurred = null;
        try
        {
            Iterator<String> iterator = test.iterator();
            iterator.next();
        }
        catch (Exception exception)
        {
            occurred = exception;
        }
        assertNotNull(occurred);
        assertTrue(occurred instanceof NoSuchElementException);
        assertEquals("There is no next element", occurred.getMessage());

        test.add("1");
        test.add("2");
        Iterator<String> iterator = test.iterator();
        assertEquals("2", iterator.next());
        assertEquals("1", iterator.next());
    }

    /**
     * Tests the Iterator's remove method
     */
    public void testRemove()
    {
        Exception occurred = null;
        try
        {
            Iterator<String> iterator = test.iterator();
            iterator.remove();
        }
        catch (Exception exception)
        {
            occurred = exception;
        }
        assertNotNull(occurred);
        assertTrue(occurred instanceof UnsupportedOperationException);
        assertEquals("This Method is Not Supported", occurred.getMessage());
    }

}
