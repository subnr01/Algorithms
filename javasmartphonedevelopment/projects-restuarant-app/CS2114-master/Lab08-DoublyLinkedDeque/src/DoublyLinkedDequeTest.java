import student.TestCase;

//-------------------------------------------------------------------------
/**
 * Tests for the {@link DoublyLinkedDeque} class.
 *
 * @author Stephen Edwards and Tony Allevato
 * @author Ben Johnston (benjdj6)
 * @author Sheng Zhou(zsheng2)
 * @version 2013.03.21
 */
public class DoublyLinkedDequeTest
    extends TestCase
{
    //~ Instance/static variables .............................................

    private Deque<String> deque;


    //~ Constructor ...........................................................

    // ----------------------------------------------------------
    /**
     * Create a new test class
     */
    public DoublyLinkedDequeTest()
    {
        // The constructor is usually empty in unit tests, since it runs
        // once for the whole class, not once for each test method.
        // Per-test initialization should be placed in setUp() instead.
    }


    //~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Creates two brand new, empty sets for each test method.
     */
    public void setUp()
    {
        deque = new DoublyLinkedDeque<String>();
    }


    /**
     * Tests the enqueueAtFront method of the DoublyLinkedDeque
     */
    public void testEnqueueAtFront()
    {
        deque.enqueueAtFront("1");
        deque.enqueueAtFront("2");
        assertEquals(2, deque.size());

    }

    /**
     * Tests the dequeueAtFront method of the DoublyLinkedDeque
     */
    public void testDequeueAtFront()
    {
        assertNull(deque.dequeueAtFront());

        deque.enqueueAtFront("1");
        deque.enqueueAtFront("2");
        deque.enqueueAtFront("3");

        assertEquals("1", deque.rearItem());

        deque.dequeueAtFront();

        assertEquals("2", deque.frontItem());

        deque.dequeueAtFront();
        deque.dequeueAtFront();

        assertEquals(0, deque.size());
    }

    /**
     * Tests the enqueueAtRear method of the DoublyLinkedDeque
     */
    public void testEnqueueAtRear()
    {
        deque.enqueueAtRear("1");
        deque.enqueueAtRear("2");
        deque.enqueueAtRear("3");
        assertEquals(3, deque.size());

        deque.dequeueAtRear();
        deque.dequeueAtRear();
        assertEquals(1, deque.size());

        deque.enqueueAtRear("4");

        assertEquals(2, deque.size());

    }

    /**
     * Tests the toString method of the DoublyLinkedDeque
     */
    public void testToString()
    {
        assertEquals("[]", deque.toString());

        deque.enqueueAtFront("1");
        deque.enqueueAtFront("2");

        assertEquals("[2, 1]", deque.toString());
    }

    /**
     * Tests the dequeueAtRear method of the DoublyLinkedDeque
     */
    public void testDequeueAtRear()
    {
        assertNull(deque.dequeueAtRear());

        deque.enqueueAtRear("1");
        deque.enqueueAtRear("2");

        assertEquals(2, deque.size());

        deque.dequeueAtRear();

        assertEquals(1, deque.size());
        assertEquals("1", deque.rearItem());
    }

    /**
     * Tests the clear method of the DoublyLinkedDeque
     */
    public void testClear()
    {
        deque.enqueueAtRear("1");
        deque.enqueueAtRear("2");

        assertEquals(2, deque.size());

        deque.clear();

        assertEquals(0, deque.size());
        assertNull(deque.frontItem());
        assertNull(deque.rearItem());
    }

}
