package cs2114.restaurant;

import java.util.*;

// -------------------------------------------------------------------------
/**
 * A circularlinkedlist that contains doublylinked nodes which are connected in
 * a circular fashion.
 *
 * @author Ben Johnston (benjdj6)
 * @version 2013.04.03
 * @param <E>
 *            is the element
 */

public class CircularLinkedList<E>
    implements CircularList<E>
{
    private Node<E> next;
    private Node<E> previous;
    private Node<E> current;
    private int     size;


    /**
     * Creates a new CircularLinkedList object
     */
    public CircularLinkedList()
    {
        size = 0;
        next = new Node<E>(null);
        previous = new Node<E>(null);
        current = new Node<E>(null);
    }


    /**
     * @return the Iterator
     */
    public Iterator<E> iterator()
    {
        return new CircularListIterator();
    }


    /**
     * Adds a node to the list and increases the size.
     *
     * @param newData
     *            is the data to be contained in the new node.
     */
    public void add(E newData)
    {
        Node<E> newNode = new Node<E>(newData);

        next = current;
        current = newNode;
        if (size == 0)
        {
            previous = newNode;
        }

        if (size == 1)
        {
            current.join(next);
            previous.join(current);
        }

        if (size > 1)
        {
            current.join(previous.split());
            previous.join(current);
        }
        size++;
    }


    /**
     * Empties the list.
     */
    public void clear()
    {
        while (size > 0)
        {
            removeCurrent();
        }
    }


    /**
     * @return the data of the current node in the list
     */
    public E getCurrent()
    {
        if (size == 0)
        {
            throw new NoSuchElementException(
                "There are no elements in this list");
        }
        else
        {
            return current.data();
        }
    }


    /**
     * Moves the current location to the next node and adjusts the values of
     * previous, next, and current accordingly.
     */
    public void next()
    {
        if (size > 1)
        {
            previous = current;
            current = next;
            next = current.next();
        }
    }


    /**
     * Moves the current location to the previous node and adjusts the values of
     * previous, next, and current accordingly.
     */
    public void previous()
    {
        if (size > 2)
        {
            current = previous;
            previous = previous.previous();
            next = current.next();
        }
        else if (size == 2)
        {
            next();
        }

    }


    /**
     * Removes the current node from the list
     *
     * @return the data contained in the removed node.
     */
    public E removeCurrent()
    {
        Node<E> temp = current;

        if (size == 0)
        {
            throw new NoSuchElementException("The List is Empty");
        }
        else if (size == 1)
        {
            current = null;
            previous = null;
            next = null;
        }
        else
        {
            previous.split();
            previous.join(current.split());
            current = next;
        }
        size--;
        if (size == 2)
        {
            next = previous;
        }
        return temp.data();
    }


    /**
     * @return the size of the list
     */
    public int size()
    {
        return size;
    }


    /**
     * @return a string containing the list's contents
     */
    public String toString()
    {
        String str = "[" + getCurrent();
        next();
        for (int i = 0; i < size - 1; i++)
        {
            str += ", " + getCurrent();
            next();
        }
        str += "]";
        return str;
    }


    /**
     * // ---------------------------------------------------------------------
     * /** Creates a new Iterator that will iterate across a CircularList.
     *
     * @author Ben Johnston (benjdj6)
     * @version 2013.04.03
     */
    private class CircularListIterator
        implements Iterator<E>
    {
        private Node<E> cur;

        private boolean run;
        private int place;


        /**
         * Creates a new CircularListIterator object.
         */
        public CircularListIterator()
        {
            cur = current;
            run = false;
            place = 0;
        }


        /**
         * @return if there is a next item in the list
         */
        public boolean hasNext()
        {
            if (place < size)
            {
                return true;
            }
            return false;
        }


        /**
         * @return the next item in the array.
         * @throws NoSuchElementException
         *             when array is empty
         */
        public E next()
        {
            if (!hasNext())
            {
                throw new NoSuchElementException("There is no next element");
            }
            else if (!run)
            {
                run = true;
                place++;
                return cur.data();
            }
            cur = cur.next();
            place++;
            return cur.data();
        }


        /**
         * @throws UnsupportedOperationException
         */
        public void remove()
        {
            throw new UnsupportedOperationException(
                "This Method is Not Supported");
        }

    }

}
