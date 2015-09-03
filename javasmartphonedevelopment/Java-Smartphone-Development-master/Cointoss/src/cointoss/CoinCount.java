package cointoss;

public class CoinCount {

	public static void main(String[] args) {
	
    int tossnumber=50;
//  int tossnumber=0;
//  int tossnumber=50;
    
    int headnumber=0;
    int tailnumber=0;
    
    Coin coin = new Coin();
    
    /* Toss the Coin for "tossnumber" times */
    for(int i=0; i<tossnumber; i++) {
    	coin.toss();
    	/* 1 Represents the Heads Up, 
    	   0 Represents the Tail Up */
    	if (coin.getSideUp()) {
    		headnumber++;
    	}
    	else {
    		tailnumber++;
    	}
    }
    
    /* Print Out the Result */
    System.out.println("Number of total toss:");
    System.out.println(tossnumber);
    System.out.println("Number of times the head is facing up:");
	System.out.println(headnumber);
    System.out.println("Number of times the tail is facing up:");
    System.out.println(tailnumber);
	}
}
