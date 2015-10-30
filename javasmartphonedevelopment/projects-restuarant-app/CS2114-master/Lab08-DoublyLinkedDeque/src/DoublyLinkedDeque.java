// -------------------------------------------------------------------------
/**
 * A deque implemented using a doubly-linked chain with sentinel nodes at each
 * end.
 *
 * @param <T>
 *            The type of elements contained in the deque.
 * @author Stephen Edwards and Tony Allevato
 * @author Ben Johnston (benjdj6)
 * @author Sheng Zhou(zsheng2)
 * @version 2013.03.21
 */
public class DoublyLinkedDeque<T>
    implements Deque<T>
{
    // ~ Instance/static variables .............................................

    // A reference to the sentinel node at the beginning of the deque.
    private Node<T> head;

    // A reference to the sentinel node at the end of the deque.
    private Node<T> tail;

    // The number of elements in the deque.
    private int     size;


    // ~ Constructor ...........................................................

    // ----------------------------------------------------------
    /**
     * Construct the stack.
     */
    public DoublyLinkedDeque()
    {
        size = 0;
        head = new Node<T>(null);
        tail = new Node<T>(null);
        head.join(tail);
    }


    // ~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Insert a new item at the rear (the tail) of the deque.
     *
     * @param value
     *            the item to insert.
     * @postcondition [new-contents] == [old-contents] * [value]
     */
    public void enqueueAtRear(T value)
    {
        Node<T> newTail = new Node<T>(value);
        Node<T> previous = tail.previous();
        previous.split();
        previous.join(newTail);
        newTail.join(tail);

        size++;
    }


    // ----------------------------------------------------------
    /**
     * Remove the item at the front (the head) of the deque.
     *
     * @return The item that was removed
     * @precondition |[old-contents]| > 0
     * @postcondition [old-contents] == [result] * [new-contents]
     */
    public T dequeueAtFront()
    {
        T oldHead = head.data();
        if (size <= 0)
        {
            return null;
        }

        if (size == 1)
        {
            head.split();
            size--;
            return oldHead;
        }
        head = head.split();
        size--;
        return oldHead;
    }


    // ----------------------------------------------------------
    /**
     * Insert a new item at the front (the head) of the deque.
     *
     * @param value
     *            the item to insert.
     * @postcondition [new-contents] = [value] * [old-contents]
     */
    public void enqueueAtFront(T value)
    {
        Node<T> oldHead = head;
        if (size <= 1)
        {
            tail = head;
        }
        head = new Node<T>(value);
        head.join(oldHead);
        size++;
    }


    // ----------------------------------------------------------
    /**
     * Remove the item at the rear (the tail) of the deque.
     *
     * @return The item that was removed
     * @precondition |[old-contents]| > 0
     * @postcondition [old-contents] = [new-contents] * [result]
     */
    public T dequeueAtRear()
    {
        if (size <= 0)
        {
            return null;
        }
        Node<T> newTail = tail.previous().previous();
        Node<T> oldTail = tail.previous();
        oldTail.split();
        newTail.split();
        newTail.join(tail);
        size--;
        return oldTail.data();
    }


    // ----------------------------------------------------------
    /**
     * Get the item at the front (the head) of the deque. Does not alter the
     * deque.
     *
     * @return the item at the front of the deque.
     * @precondition |[contents]| > 0
     * @postcondition [new-contents] == [old-contents] and [contents] = [result]
     *                * [rest-of-items]
     */
    public T frontItem()
    {
        if (size != 0)
        {
            return head.next().data();
        }
        return null;
    }


    // ----------------------------------------------------------
    /**
     * Get the item at the rear (the tail) of the deque. Does not alter the
     * deque.
     *
     * @return the item at the rear of the deque.
     * @precondition |[contents]| > 0
     * @postcondition [new-contents] == [old-contents] and [contents] =
     *                [rest-of-items] * [result]
     */
    public T rearItem()
    {
        if (size > 0)
        {
            return tail.previous().data();
        }
        return null;
    }


    // ----------------------------------------------------------
    /**
     * Get the number of items in this deque. Does not alter the deque.
     *
     * @return The number of items this deque contains.
     * @postcondition result = |[contents]|
     */
    public int size()
    {
        return size;
    }


    // ----------------------------------------------------------
    /**
     * Empty the deque.
     *
     * @postcondition [new-contents] = []
     */
    public void clear()
    {
        while (size > 0)
        {
            this.dequeueAtRear();
        }
    }


    // ----------------------------------------------------------
    /**
     * Returns a string representation of this deque. A deque's string
     * representation is written as a comma-separated list of its contents (in
     * front-to-rear order) surrounded by square brackets, like this:
     *
     * <pre>
     * [52, 14, 12, 119, 73, 80, 35]
     * </pre>
     * <p>
     * An empty deque is simply <code>[]</code>.
     * </p>
     *
     * @return a string representation of the deque
     */
    public String toString()
    {
        if (size == 0)
        {
            return "[]";
        }

        String output = "[";
        while (size > 1)
        {
            output += head.data().toString() + ", ";
            this.dequeueAtFront();
        }
        output += head.data().toString() + "]";
        return output;
    }
}
