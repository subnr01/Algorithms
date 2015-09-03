package server;

public class Server extends DefaultSocketClient {
		
	public Server(Integer servPort) {
		super(servPort);
	}
	
	public void run() {
		super.run();
	}
	
	public static void main(String[] argvs){
		Server server = new Server(Integer.parseInt(argvs[0]));
		Thread thread = new Thread(server);
		thread.start();
		System.out.println("Server is up...");
	}
}