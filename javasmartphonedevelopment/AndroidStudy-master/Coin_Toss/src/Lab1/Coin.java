package Lab1;

import java.lang.Math;

public class Coin {
	private String SideUp; //indicating the side of the coin that is facing up
	
	//no-arg constructor that randomly determines the side of the coin that is facing up
	//and initializes the sideUp field accordingly
	public Coin(){
		setCoin();
	}
	
	//a void method named toss that simulates the tossing of a coin
	public void toss(){
		setCoin();
	}
	
	//randomly determine the side of the coin that is facing up
	private void setCoin() {
		int randomNum = (int)(Math.random()*10);
		if(randomNum%2 == 0) {
			SideUp = "heads";
		} else {
			SideUp = "tails";
		}
	}
	
	//return the value of the sideUp field
	public String getSideUp(){
		return SideUp;
	}
}
