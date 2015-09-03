package server;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;

import adapter.BuildAuto;

public class Server implements Runnable{
	private ServerSocket ListenSocket;
	private Socket socket;
	private Integer port;
	private Properties props;
	
	public Server(Integer port) {
		this.port = port;
	}
	
	public void run() {
		try {
			ListenSocket = new ServerSocket(this.port);
			socket = ListenSocket.accept();
			
			BuildCarModelOptions BCMO = new BuildCarModelOptions();
			PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
	        BufferedReader br = new BufferedReader(
					new InputStreamReader(
							socket.getInputStream()));
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
						out.println("Build model success!");
					}
					else if(messageFromClient.equals("f")) {
						BuildAuto autos = new BuildAuto();
						out.println(autos.getAllAutos());
					} 
					else if(messageFromClient.equals("c")) {
						BuildAuto autos = new BuildAuto();
						out.println(autos.getAllAutos());
						String modelChosen = br.readLine();
						String modelInfor = autos.modelToString(modelChosen);
						out.println(modelInfor);
						if(modelInfor.equals("No such Model!")) {
							continue;
						}						
						out.println(autos.listOptionSet(modelChosen));
					}
				}
			}
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void main(String[] argvs){
		Server server = new Server(Integer.parseInt(argvs[0]));
		Thread thread = new Thread(server);
		thread.start();
		System.out.println("Server is up...");
	}
}
