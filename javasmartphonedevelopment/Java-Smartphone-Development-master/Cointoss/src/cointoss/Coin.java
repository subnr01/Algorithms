package cointoss;

public class Coin {

	private int sideUp;

	/* Simulate the Sides by Randomly Generating 0 or 1 */
    public void toss() {
    	sideUp=(int)(Math.random()*2);
    }
    
    /* Constructor */
    public Coin() {
         toss();
    }

    /* If We Randomly Generated 1, Return 1 */
    public boolean getSideUp() {
	    return (sideUp==1); 
    }
}
