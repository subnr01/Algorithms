package client;

import java.net.*;
import java.util.Properties;
import java.io.*;

public class DefaultSocketClient extends Thread 
	   implements SocketClientInterface,
	   			  SocketClientConstants 
{
	private BufferedReader reader;
	private BufferedReader command;
	private PrintWriter writer;
	private Socket sock;
	
	public Socket getSock() {
		return sock;
	}

	public void setSock(Socket sock) {
		this.sock = sock;
	}

	private String strHost; //Host IP address
	private Properties props;
	private String models;
	
	public PrintWriter getWriter() {
		return this.writer;
	}
	
	public BufferedReader getReader() {
		return this.reader;
	}
	
	public String getStrHost() {
		return strHost;
	}

	public void setStrHost(String strHost) {
		this.strHost = strHost;
	}

	private int iPort;
	
	public int getiPort() {
		return iPort;
	}

	public void setiPort(int iPort) {
		this.iPort = iPort;
	}

	public DefaultSocketClient(String strHost, int iPort) {       
		setiPort(iPort);
		setStrHost(strHost);
		models = null;
	}	//constructor
	
	public void run(){
	   if (openConnection()){
	      handleSession();
	      closeSession();
	   }
	}//run
	
	public boolean openConnection() {
	  try {
	     sock = new Socket(this.strHost, this.iPort);                    
	  }
	  catch(IOException socketError){
	     if (DEBUG) System.err.println
	        ("Unable to connect to " + strHost);
	     return false;
	  }
	  try {
		 command = new BufferedReader(new InputStreamReader(System.in));  
	     reader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
	     writer = new PrintWriter(sock.getOutputStream(), true);
	  }
	  catch (Exception e){
	     if (DEBUG) System.err.println
	       ("Unable to obtain stream to/from " + strHost);
	     return false;
	  }
	  return true;
	}

	public void handleSession(){
		String command = "";
        String fileName = "";        
        CarModelOptionsIO CMIO = new CarModelOptionsIO();
        try {
        	String messageFromServer = "";        	
        	while(true) {
        		System.out.println("commend: s(send), q(quit), f(get all models),\n"
						+ "	c(choose model and option to show):");
        		command = this.command.readLine();
        		if(command.equals("q")) {
        			writer.println("q");
        			messageFromServer = reader.readLine();
        			System.out.println(messageFromServer);
        			break;
        		} else if(command.equals("s")) {
        			writer.println("s");
        			System.out.println("Enter Properties File Name:");
        			fileName = this.command.readLine();
        			props = CMIO.buildFromPropertiesFile(fileName);
    	        	ObjectOutputStream objectOutputStream = new ObjectOutputStream(
    	        				new BufferedOutputStream(sock.getOutputStream()));
    				objectOutputStream.writeObject(props);
    				objectOutputStream.flush();
    				messageFromServer = reader.readLine();
    				this.models = messageFromServer;
    				System.out.println("Build model success!");
        		} else if(command.equals("f")) {
        			writer.println("f");
        			System.out.println("All available models are:");
        			messageFromServer = reader.readLine();
        			this.models = messageFromServer;
    				System.out.println(messageFromServer);
        		} else if(command.equals("c")) {
        			writer.println("c");
        			/*System.out.println("All available models are:");
        			messageFromServer = reader.readLine();
        			this.models = messageFromServer;
    				System.out.println(messageFromServer);
    				System.out.println("choose one model:");
    				String modelChosen = this.command.readLine();*/
    				writer.println("FordZTW");
    				messageFromServer = reader.readLine();
    				System.out.println(messageFromServer);
    				if(messageFromServer.equals("No such Model!")) {
    					continue;
    				}
    				System.out.println("\nThe option sets are:\n");
    				messageFromServer = reader.readLine();
    				System.out.println(messageFromServer);
        		}
        	}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}       
	
	public String getAvaliableModel() {
		return this.models;
	}

    public void closeSession(){
    	try {
    	   writer = null;
    	   reader = null;
    	   command = null;
    	   sock.close();
    	}
    	catch (IOException e){
         if (DEBUG) System.err.println
          ("Error closing socket to " + strHost);
    	}
    }
    
}