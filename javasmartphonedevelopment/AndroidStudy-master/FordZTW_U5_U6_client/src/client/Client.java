package client;

import java.io.BufferedReader;
import java.io.PrintWriter;

public class Client extends DefaultSocketClient {
	private static Client instance = new Client("127.0.0.1", 2014);
	
	public static Client getInstance() {
		return instance;
	}
	
	public Client(String servIp, Integer servPort) {
		super(servIp, servPort);
	}
	
	public PrintWriter getWriter() {
		return super.getWriter();
	}
	
	public BufferedReader getReader() {
		return super.getReader();
	}
	
	public void run() {
		super.run();
	}
	
	
	public static void main(String[] argvs) {
		Client client = Client.getInstance();
		client.start();
		System.out.println("Client is up...");
	}
}
