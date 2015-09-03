package client;

import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Properties;

public class Client extends Thread{
	private Socket socket;
	private String servIp;
	private Integer servPort;
	private Properties props;
	
	public Client(String servIp, Integer servPort) {
		this.servIp = servIp;
		this.servPort = servPort;
	}
	
	public void run() {
		try {
			socket = new Socket(servIp, servPort);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String commend = "";
        String fileName = "";        
        CarModelOptionsIO CMIO = new CarModelOptionsIO();
        try {
        	String messageFromServer = "";        	
        	PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
    		BufferedReader br = new BufferedReader(
    				new InputStreamReader(socket.getInputStream()));
        	while(true) {
        		System.out.println("commend: s(send), q(quit), f(get all models),\n"
						+ "	c(choose model and option to show):");
        		commend = in.readLine();
        		if(commend.equals("q")) {
        			out.println("q");
        			messageFromServer = br.readLine();
        			System.out.println(messageFromServer);
        			break;
        		} else if(commend.equals("s")) {
        			out.println("s");
        			System.out.println("Enter Properties File Name:");
        			fileName = in.readLine();
        			props = CMIO.buildFromPropertiesFile(fileName);
    	        	ObjectOutputStream objectOutputStream = new ObjectOutputStream(
    	        				new BufferedOutputStream(socket.getOutputStream()));
    				objectOutputStream.writeObject(props);
    				objectOutputStream.flush();
    				messageFromServer = br.readLine();
    				System.out.println(messageFromServer);
        		} else if(commend.equals("f")) {
        			out.println("f");
        			System.out.println("All available models are:");
        			messageFromServer = br.readLine();
    				System.out.println(messageFromServer);
        		} else if(commend.equals("c")) {
        			out.println("c");
        			System.out.println("All available models are:");
        			messageFromServer = br.readLine();
    				System.out.println(messageFromServer);
    				System.out.println("choose one model:");
    				String modelChosen = in.readLine();
    				out.println(modelChosen);
    				messageFromServer = br.readLine();
    				System.out.println(messageFromServer);
    				if(messageFromServer.equals("No such Model!")) {
    					continue;
    				}
    				System.out.println("\nThe option sets are:\n");
    				messageFromServer = br.readLine();
    				System.out.println(messageFromServer);
        		}
        	}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void main(String[] argvs){
		Client client = new Client(argvs[0], Integer.parseInt(argvs[1]));
		client.start();
		System.out.println("Client is up...");
	}
	
}
