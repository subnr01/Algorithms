package Test;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.Iterator;

import Model.Automobile;
import Util.Util;

public class simulator {

	protected static final String SERIALIZED_FILE_NAME = "autos.ser";
	public static void main(String[] args) {
		Util util = new Util();
		Automobile [] autos = new Automobile[3];
		autos[0] = util.buildAutoObject("OptionSet0.txt");
		autos[0].setName("FordZTW0");
		autos[0].setBasePrice(18445);
		autos[1] = util.buildAutoObject("OptionSet1.txt");
		autos[1].setName("FordZTW1");
		autos[1].setBasePrice(18445);
		autos[2] = util.buildAutoObject("OptionSet2.txt");
		autos[2].setName("FordZTW2");
		autos[2].setBasePrice(18445);
		for(int i=0; i<3; i++) {
			autos[i].print();
			System.out.println();
		}
		try{
			//serialize Autos
			ObjectOutputStream objectOutputStream = new ObjectOutputStream(new BufferedOutputStream(new FileOutputStream(SERIALIZED_FILE_NAME)));
			objectOutputStream.writeObject(autos);
			objectOutputStream.close();
			
			//De-serialize Autos
			ObjectInputStream objectInputStream = new ObjectInputStream(new BufferedInputStream(new FileInputStream(SERIALIZED_FILE_NAME)));

			Automobile [] Autos_recon  = (Automobile [])objectInputStream.readObject();
			System.out.println("After deserialization, we get the info below:");
			
			for(int i=0; i<3; i++) {
				Autos_recon[i].print();
				System.out.println();
			}			
			objectInputStream.close();
		}
		catch (IOException | ClassNotFoundException e){
			e.printStackTrace();
		}
	}

}
