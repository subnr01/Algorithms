package lab2;

import util.Util;

public class Main {
	public static void main(String[] args) {
	   
		Student lab2[] = new Student[40];

		lab2 = Util.readFile("filename.txt", lab2);
		// test cases: filename2.txt
		// test cases: filename3.txt
		// test cases: filename4.txt

		Statistics statlab2 = new Statistics();
		
        statlab2.Title();
		statlab2.findlow(lab2);
		statlab2.findhigh(lab2);
		statlab2.findavg(lab2);
	}
}
