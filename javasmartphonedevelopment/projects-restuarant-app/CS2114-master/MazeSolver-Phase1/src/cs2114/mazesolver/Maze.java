package cs2114.mazesolver;

import java.util.Stack;

// -------------------------------------------------------------------------
/**
 * Represents the maze to be navigated
 *
 * @author Benjamin Johnston (benjdj6)
 * @version 2013.03.04
 */

public class Maze
    implements IMaze
{
    private ILocation    start;
    private ILocation    goal;
    private MazeCell[][] grid;
    private int          size;


    /**
     * Creates new Maze object, sets maze size, start and goal locations all
     * cells start as unexplored
     *
     * @param size
     *            is the size of the maze
     */
    public Maze(int size)
    {
        this.size = size;
        grid = new MazeCell[size][size];
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                grid[i][j] = MazeCell.UNEXPLORED;
            }
        }
        this.setStartLocation(new Location(0, 0));
        this.setGoalLocation(new Location(size - 1, size - 1));
    }


    // ----------------------------------------------------------
    /**
     * Returns the state of the specified location
     *
     * @param location
     *            is the specificied location
     * @return the state of location
     */
    public MazeCell getCell(ILocation location)
    {
        return grid[location.x()][location.y()];
    }


    // ----------------------------------------------------------
    /**
     * @return the goal location
     */
    public ILocation getGoalLocation()
    {
        return goal;
    }


    // ----------------------------------------------------------
    /**
     * @return the starting location
     */
    public ILocation getStartLocation()
    {
        return start;
    }


    // ----------------------------------------------------------
    /**
     * Sets a new state to a location in the maze
     *
     * @param location
     *            is a specific location in the maze
     * @param cell
     *            is the state the location should be set to
     */
    public void setCell(ILocation location, MazeCell cell)
    {
        if (location.equals(goal) && cell.equals(MazeCell.WALL))
        {
            return;
        }
        else if (location.equals(start) && cell.equals(MazeCell.WALL))
        {
            return;
        }
        else
        {
            grid[location.x()][location.y()] = cell;
        }
    }


    // ----------------------------------------------------------
    /**
     * Sets the goal location
     *
     * @param location
     *            is the goal location
     */
    public void setGoalLocation(ILocation location)
    {
        if (this.getCell(location).equals(MazeCell.WALL))
        {
            this.setCell(location, MazeCell.UNEXPLORED);
        }
        goal = location;
    }


    // ----------------------------------------------------------
    /**
     * Sets the start location
     *
     * @param location
     *            is the starting location
     */
    public void setStartLocation(ILocation location)
    {
        if (this.getCell(location).equals(MazeCell.WALL))
        {
            this.setCell(location, MazeCell.UNEXPLORED);
        }
        start = location;
    }


    // ----------------------------------------------------------
    /**
     * @return size of the maze
     */
    public int size()
    {
        return size;
    }


    // ----------------------------------------------------------
    /**
     * Solves the maze and returns a string containing the solution
     *
     * @return string of the moves needed to solve the maze
     */
    public String solve()
    {
        Stack<ILocation> moves = new Stack<ILocation>();
        Stack<ILocation> soln = new Stack<ILocation>();

        String output = new String();

        moves.push(start);
        this.setCell(moves.peek(), MazeCell.CURRENT_PATH);

        while (moves.peek().x() != goal.x() || moves.peek().y() != goal.y())
        {
            ILocation current = moves.peek();
            if (current.x() < size - 1
                && this.getCell(current.east()).equals(MazeCell.UNEXPLORED))
            {
                this.setCell(current.east(), MazeCell.CURRENT_PATH);
                moves.push(current.east());
            }
            else if (current.x() > 0
                && this.getCell(current.west()).equals(MazeCell.UNEXPLORED))
            {
                this.setCell(current.west(), MazeCell.CURRENT_PATH);
                moves.push(current.west());
            }
            else if (current.y() > 0
                && this.getCell(current.north()).equals(MazeCell.UNEXPLORED))
            {
                this.setCell(current.north(), MazeCell.CURRENT_PATH);
                moves.push(current.north());
            }
            else if (current.y() < size - 1
                && this.getCell(current.south()).equals(MazeCell.UNEXPLORED))
            {
                this.setCell(current.south(), MazeCell.CURRENT_PATH);
                moves.push(current.south());
            }
            else
            {
                this.setCell(current, MazeCell.FAILED_PATH);
                moves.pop();
            }

            if (moves.empty())
            {
                return null;
            }
        }

        while (!moves.empty())
        {
            soln.push(moves.peek());
            moves.pop();
        }
        while (!soln.empty())
        {
            output = output + soln.peek().toString() + " ";
            soln.pop();
        }
        return output;
    }

}
