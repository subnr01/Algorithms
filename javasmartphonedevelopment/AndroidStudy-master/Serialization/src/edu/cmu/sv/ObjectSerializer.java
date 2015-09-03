package edu.cmu.sv;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;

public class ObjectSerializer {
	protected static final String SERIALIZED_FILE_NAME = "channel.ser";
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Channel channel = new Channel();
		channel.addVideo(new Video("Introduction to RMI"));
		channel.addVideo(new Video("Introduction to Java Sockets"));
		channel.addVideo(new Video("Java Threading"));
		try {
			ObjectOutputStream objectOutputStream = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(SERIALIZED_FILE_NAME)));
			objectOutputStream.writeObject(channel);
			objectOutputStream.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
