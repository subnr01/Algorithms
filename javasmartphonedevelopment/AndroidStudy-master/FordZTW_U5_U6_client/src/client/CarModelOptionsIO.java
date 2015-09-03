package client;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;

public class CarModelOptionsIO {
	
	/**
	 * Read properies objects, build and return the automobile  
	 * @param fileName
	 * @return
	 */
	public Properties buildFromPropertiesFile(String fileName) {
		FileInputStream in;
		Properties props = new Properties();
		try {
			in = new FileInputStream(fileName);
			props.load(in);
			in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return props;
	}
	
}
