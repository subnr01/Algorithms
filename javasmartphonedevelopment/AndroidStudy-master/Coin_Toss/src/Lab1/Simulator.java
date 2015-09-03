package Lab1;

public class Simulator {
	public static void main(String argv[]){
		Coin coinX = new Coin();
		int headsUpNum = 0, tailsUpNum = 0; 
		System.out.println("Initially facing up:" + coinX.getSideUp());
		//toss 20 times
		for(int index = 0; index < 20; index++){
			coinX.toss();
			System.out.println("Currently facing up:" + coinX.getSideUp());
			if(coinX.getSideUp() == "heads") {
				headsUpNum++;
			} else {
				tailsUpNum++;
			}	
		}
		//display
		System.out.println("heads up: "+headsUpNum+" times and "+"tails up: "+tailsUpNum+" times");
	}
}
