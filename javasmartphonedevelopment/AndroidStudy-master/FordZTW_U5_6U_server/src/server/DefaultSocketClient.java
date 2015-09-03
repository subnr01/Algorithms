package server;

import java.net.*;
import java.util.Properties;
import java.io.*;

import model.Automobile;
import adapter.BuildAuto;

public class DefaultSocketClient extends Thread 
	   implements SocketClientInterface,
	   			  SocketClientConstants 
{
	private BufferedReader br;
	private PrintWriter out;
	private ServerSocket ListenSocket;
	private Socket socket;
	private Integer port;
	private Properties props;

	private int iPort;
	
	public int getiPort() {
		return iPort;
	}
	
	public void setiPort(int iPort) {
		this.iPort = iPort;
	}

	public DefaultSocketClient(int iPort) {       
		setiPort(iPort);
	}	//constructor
	
	public void run(){
	   if (openConnection()){
	      handleSession();
	      closeSession();
	   }
	} //run
	
	public boolean openConnection() {
		try {
			ListenSocket = new ServerSocket(this.getiPort());
			socket = ListenSocket.accept();                    
		}
		catch(IOException socketError){
			if (DEBUG) System.err.println
	        	("Unable to connect to port " + this.port);
			return false;
		}
		try {
			out = new PrintWriter(socket.getOutputStream(), true);
	        br = new BufferedReader(new InputStreamReader(
								  socket.getInputStream()));
		}
		catch (Exception e) {
			if (DEBUG) System.err.println
				("Unable to obtain stream to/from " + this.port);
			return false;
		}
		return true;
	}

	public void handleSession() {
		BuildCarModelOptions BCMO = new BuildCarModelOptions();
		try {
			while(true) {
				String messageFromClient = br.readLine();
				if(messageFromClient != null) {
					if(messageFromClient.equals("q")) {
						out.println("Server is down!");
						System.out.println("quit");
						break;
					}
					else if(messageFromClient.equals("s")) {
						ObjectInputStream in = new ObjectInputStream(
								new BufferedInputStream(socket.getInputStream()));
						props = (Properties)in.readObject();
						BCMO.parseCarModelOptions(props);
						BuildAuto autos = new BuildAuto();
						out.println(autos.getAllAutos());
					}
					else if(messageFromClient.equals("f")) {
						BuildAuto autos = new BuildAuto();
						out.println(autos.getAllAutos());
					} 
					else if(messageFromClient.equals("c")) {
						String modelName = br.readLine();
						BuildAuto autos = new BuildAuto();
						Automobile auto = autos.getAuto(modelName);
						ObjectOutputStream objectOutputStream = new ObjectOutputStream(
    	        				new BufferedOutputStream(socket.getOutputStream()));
						objectOutputStream.writeObject(auto);
						objectOutputStream.flush();
					}
				}
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
	}       

    public void closeSession() {
    	try {
    	   br = null;
    	   out = null;
    	   ListenSocket.close();
    	   socket.close();
    	}
    	catch (IOException e) {
         if (DEBUG) System.err.println
          ("Error closing socket to port " + port);
    	}
    }
    
}