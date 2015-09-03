package Util;

import java.io.*;

import CustomerException.OptionFileFormatException;
import CustomerException.OptionPriceException;
import Model.Automobile;

public class Util {
	public Automobile buildAutoObject(String filename){
        //Reads the file and builds OptionSet array.
        String s;
        Automobile auto = new Automobile();
        int setNum = 0;
        
        //Open the file using FileReader Object.
        try {
        	if(!filename.contains(".txt")) {
        		throw new OptionFileFormatException();
        	}
        	File optionFile = new File(filename);
    		//In a loop read a line using readLine method.
            FileReader fr = new FileReader(optionFile);
            @SuppressWarnings("resource")
			BufferedReader br = new BufferedReader(fr);
            br.readLine();
            s = br.readLine();
            auto.setMake(s);
            br.readLine();
            s = br.readLine();
            auto.setModel(s);
            br.readLine();
            s = br.readLine();
            auto.setBasePrice(Integer.parseInt(s));
            s = br.readLine(); //size of the optionSet
            auto.setOptionSetSize(Integer.parseInt(s)); //set optionSet size
            while ((s = br.readLine()) != null) {
            	String optionSetName = s;
            	auto.setOptionSet(optionSetName, setNum); //set the name of optionSet
            	s = br.readLine();
            	while(s != null && s.length() != 0) {
            		boolean hasPrice = s.contains("$");
            		if(!hasPrice) {
            			String optionName = s;
            			auto.setOption(optionSetName, optionName, 0);
            		} else {
            			int index = s.indexOf("$");            			
            			String optionName = s.substring(0, index);
            			String price = s.substring(index+1, s.length());
            			int priceInt = Integer.parseInt(price);
            			if(priceInt > auto.getBasePrice() || priceInt < 0-auto.getBasePrice()) {
            				throw new OptionPriceException();
            			}
            			auto.setOption(optionSetName, optionName, priceInt);
            		}
            		s = br.readLine();
            	}
        		setNum++;	 
            }
            fr.close();
        }
        catch (OptionFileFormatException e) {
        	e.printFileFormatError();
        }
        catch (OptionPriceException e) {
        	e.printPriceError();
        }
        catch(Exception e){
            e.printStackTrace();
        }        
        auto.setDefaultChoices();
        return auto;
	}
}
