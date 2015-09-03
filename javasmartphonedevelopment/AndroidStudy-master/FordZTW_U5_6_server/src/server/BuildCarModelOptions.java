package server;

import java.util.Properties;
import adapter.BuildAuto;

public class BuildCarModelOptions {
	public void parseCarModelOptions(Properties props) {
		AutoServer server = new BuildAuto();
		server.BuildAutoFromPropertiesFile(props);
	}
}
