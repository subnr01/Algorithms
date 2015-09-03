package server;

import java.util.Properties;

public interface AutoServer {
	//Accept a properties file and create an Automobile. Then add that created
	//Automobile to the LinkedHashMap.
	public void BuildAutoFromPropertiesFile(Properties props);
}
