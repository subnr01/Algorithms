package adapter;

import scale.EditThread;
import server.AutoServer;

/**
 * BuildAuto has no line of code, all functions are implemented in proxyAutomobile
 * @author Jacky
 */
public class BuildAuto extends proxyAutomobile 
					   implements CreateAuto, UpdateAuto, EditThread, AutoServer {
	
}
