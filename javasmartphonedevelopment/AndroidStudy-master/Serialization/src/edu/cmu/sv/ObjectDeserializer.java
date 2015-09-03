package edu.cmu.sv;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.Iterator;

public class ObjectDeserializer {
	protected static final String SERIALIZED_FILE_NAME = "channel.ser";
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			ObjectInputStream objectInputStream = new ObjectInputStream(new FileInputStream(SERIALIZED_FILE_NAME));
			Channel channel = (Channel)objectInputStream.readObject();
			Iterator<Video> iterator = channel.getVideoClips().iterator();
			System.out.println("deseralized channel contain the following videos:");
			while(iterator.hasNext()) {
				System.out.println("-->"+((Video)iterator.next()).getName());
			}
			objectInputStream.close();
		} catch (ClassNotFoundException | IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
