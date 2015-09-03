package Util;

import java.io.*;

import Model.Automobile;
import Model.OptionSet;

public class Util {
	public Automobile buildAutoObject(String filename){
        //Reads the file and builds OptionSet array.
        String s;
        Automobile auto = new Automobile();
        OptionSet [] optionSets = new OptionSet[24];
        int setNum = 0;
        //Open the file using FileReader Object.
        File optionFile = new File(filename);
        //In a loop read a line using readLine method.
        try {
                FileReader fr = new FileReader(optionFile);
                BufferedReader br = new BufferedReader(fr);
                while ((s = br.readLine()) != null) {
	                //initial an option set with 5 options
	        		optionSets[setNum] = new OptionSet(s, 5);
	        		for(int i=0; i<5; i++) {
	        			s = br.readLine();
	        			String[] st = s.split(":"); //get the name and value
	        			int price = getPrice(st[0], st[1]);
	        			optionSets[setNum].setOption(i, st[0], price); //+":"+st[1]
	        		}
	        		setNum++;	 
	        		s = br.readLine(); //read a blank line
                }
                fr.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }        
        auto.setOptionSet(optionSets);    
        auto.setOptionSetSize(setNum); //set real optionset size
        return auto;
	}
	
	public int getPrice(String optionName, String choice) {
		if(choice.equals("selected")) {
			if(optionName.equals("Moonroof"))
				return 595;
			else
				return 350;
		}
		else if(optionName.equals("Transmission")) {
			if(choice.equals("manual"))
				return -815;
		}
		else {
			if(choice.equals("ABS")) 
				return 400;
			else if(choice.equals("ABSAT"))
				return 1625;
		}
		return 0;
	}
}
