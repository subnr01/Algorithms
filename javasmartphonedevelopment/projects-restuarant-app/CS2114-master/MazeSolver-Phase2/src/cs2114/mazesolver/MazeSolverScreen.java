package cs2114.mazesolver;

import sofia.graphics.*;
import sofia.app.ShapeScreen;
import android.widget.*;

// -------------------------------------------------------------------------
/**
 * Initializes the application screen and allows for interaction with the maze.
 *
 * @author Ben Johnston(benjdj6)
 * @version 2013.03.26
 */
public class MazeSolverScreen
    extends ShapeScreen
{
    // ~ Fields ................................................................

    /**
     * Is the maze being manipulated
     */
    IMaze                 maze;
    private String        interact;
    private TextView      infoLabel;
    private CoverTile[][] tiles;
    private int           startX;
    private int           startY;
    private int           goalX;
    private int           goalY;


    // private int cellSize;

    // ~ Public methods ........................................................

    // ----------------------------------------------------------
    /**
     * Creates the maze object that the user will interact with
     */
    public void initialize()
    {
        maze = new Maze(6);
        interact = "draw";
        tiles = new CoverTile[6][6];

        float width = getWidth() / 6;
        float height = getHeight() / 6;
        width = Math.min(width, height);
        height = width;
        CoverTile cell;

        for (int i = 0; i < 6; i++)
        {
            float left = i * width;
            float right = left + width;

            for (int j = 0; j < 6; j++)
            {
                float top = j * height;
                float bottom = top + height;
                cell = new CoverTile(left, top, right, bottom);

                cell.setColor(Color.black);
                cell.setFillColor(Color.white);
                if (j == 5 && i == 5)
                {
                    cell.setFillColor(Color.blue);
                    goalX = 5;
                    goalY = 5;
                }
                else if (j == 0 && i == 0)
                {
                    cell.setFillColor(Color.green);
                    startX = 0;
                    startY = 0;
                }
                tiles[i][j] = cell;
                add(cell);
            }
        }
    }


    // ----------------------------------------------------------
    /**
     * @return the maze
     */
    public IMaze getMaze()
    {
        return maze;
    }


    /**
     * Determines the cell touched and changes it to the appropriate state
     *
     * @param x
     *            is the coordinate
     * @param y
     *            is the y coordinate
     */
    public void onTouchDown(float x, float y)
    {
        changeCell(x, y);
    }


    /**
     * Determines the cells touched and changes them to the appropriate state
     *
     * @param x
     *            is the x coordinate
     * @param y
     *            is the y coordinate
     */
    public void onTouchMove(float x, float y)
    {
        changeCell(x, y);
    }


    /**
     * Sets the current state of the interact value to draw.
     */
    public void drawWallsClicked()
    {
        interact = "draw";
    }


    /**
     * Sets the current state of the interact value to erase.
     */
    public void eraseWallsClicked()
    {
        interact = "erase";
    }


    /**
     * Sets the current state of the interact value to start.
     */
    public void setStartClicked()
    {
        interact = "start";
    }


    /**
     * Sets the current state of the interact value to goal.
     */
    public void setGoalClicked()
    {
        interact = "goal";
    }


    /**
     * Solves the maze and displays a graphical and text output of the solution.
     */
    public void solveClicked()
    {
        String solution = maze.solve();

        if (solution != null)
        {
            infoLabel.setText(solution);
        }
        else
        {
            infoLabel.setText("No solution was possible.");
        }
        showPath();
    }


    /**
     * Determines the cells touched and changes them to the appropriate state
     *
     * @param x
     *            is the x coordinate
     * @param y
     *            is the y coordinate
     */
    public void changeCell(float x, float y)
    {
        float cellSize = Math.min(getWidth(), getHeight()) / 6;

        for (int i = 0; i < 6; i++)
        {
            if (x >= cellSize * i && x < cellSize * (i + 1))
            {
                for (int j = 0; j < 6; j++)
                {
                    if (y >= cellSize * j && y < cellSize * (j + 1))
                    {
                        Location current = new Location(i, j);
                        if (interact.equals("draw"))
                        {
                            maze.setCell(current, MazeCell.WALL);
                            tiles[i][j].setFillColor(Color.black);
                            break;
                        }
                        if (interact.equals("erase"))
                        {
                            maze.setCell(current, MazeCell.UNEXPLORED);
                            tiles[i][j].setFillColor(Color.white);
                            break;
                        }
                        if (interact.equals("start"))
                        {
                            maze.setStartLocation(current);
                            tiles[startX][startY].setFillColor(Color.white);
                            tiles[i][j].setFillColor(Color.green);
                            startX = i;
                            startY = j;
                            break;
                        }
                        if (interact.equals("goal"))
                        {
                            maze.setGoalLocation(current);
                            tiles[goalX][goalY].setFillColor(Color.white);
                            tiles[i][j].setFillColor(Color.blue);
                            goalX = i;
                            goalY = j;
                            break;
                        }
                    }
                }
            }
        }
    }


    /**
     * Marks the successful path and failed paths
     */
    public void showPath()
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                Location current = new Location(i, j);
                if (!(maze.getGoalLocation().equals(current)
                    || maze.getStartLocation().equals(current)))
                {
                    if (maze.getCell(current).equals(MazeCell.FAILED_PATH))
                    {
                        tiles[i][j].setFillColor(Color.red);
                    }
                    if (maze.getCell(current).equals(MazeCell.CURRENT_PATH))
                    {
                        tiles[i][j].setFillColor(Color.yellow);
                    }
                }
            }
        }
    }

}
