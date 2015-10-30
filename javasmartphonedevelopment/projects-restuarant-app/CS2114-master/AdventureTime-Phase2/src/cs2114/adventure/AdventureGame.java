package cs2114.adventure;

// -------------------------------------------------------------------------
/**
 * A class that creates the game scenario for the player including environment,
 * items, and commands.
 *
 * @author Benjamin Johnston(benjdj6)
 * @version 14.02.2013
 */

public class AdventureGame
    extends Game
{
    /**
     * Creates a new AdventureGame object
     */
    public AdventureGame()
    {
        super(new PlayerCarrier());
    }


    /**
     * Generates the commands that will be recognized by the game.
     */
    public void createCommands()
    {
        CommandWords commands = commandWords();
        commands.addCommand("go", new GoCommand());
        commands.addCommand("help", new HelpCommand(commands));
        commands.addCommand("quit", new QuitCommand());
        commands.addCommand("take", new TakeCommand());
        commands.addCommand("read", new ReadCommand());
        commands.addCommand("inventory", new InventoryCommand());
        commands.addCommand("drop", new DropCommand());
        commands.addCommand("use", new UseCommand());
    }


    /**
     * Generates the rooms and items, and links the rooms together. Also adds
     * the player to a room and adds items to their rooms.
     */
    public void createRooms()
    {
        // Create rooms
        RoomFilled sleepingArea =
            new RoomFilled("in a bland bedroom");
        RoomFilled lobby = new RoomFilled("in a lobby");
        RoomFilled lab = new RoomFilled("in a destroyed laboratory with a " +
        		"note");
        RoomFilled stockRoom = new RoomFilled("in a filthy stock room with" +
        		" a key on the floor");
        RoomFilled kitchen = new RoomFilled("in a dirty kitchen. You hear " +
        		"scratching noises from a locked cabinet.");
        RoomFilled outside = new RoomFilled("outdoors. The rat probably " +
        		"hasn't gotten this far.");

        // Creating items
        Item key = new Item("key", 0.2);
        Item note = new Item("note", 0.1);
        Item rat = new Item("rat", 1.5);

        // adding items to rooms
        stockRoom.addItem(key);
        lab.addItem(note);
        kitchen.addItem(rat);

        // Linking rooms together
        sleepingArea.setExit("north", lobby);
        sleepingArea.setExit("south", kitchen);

        lobby.setExit("south", sleepingArea);
        lobby.setExit("east", lab);
        lobby.setExit("west", outside);

        lab.setExit("west", lobby);
        lab.setExit("north", stockRoom);

        stockRoom.setExit("south", lab);

        outside.setExit("east", lobby);

        kitchen.setExit("north", sleepingArea);

        // putting player in starting room
        player().setCurrentRoom(sleepingArea);
    }


    /**
     * @return a message welcoming the player to the game.
     */
    public String welcomeMessage()
    {
        return "Welcome to Lab Rat!\n"
            + "Lab Rat is a new game that is still in the early stages of\n"
            + "development.\n" + "Type 'help' if you need help.";
    }

}
