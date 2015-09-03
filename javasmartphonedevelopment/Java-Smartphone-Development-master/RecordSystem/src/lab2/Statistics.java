package lab2;
import lab2_interface.Interface;

public class Statistics 
	implements Interface {
	int[] lowscores = new int[5];
	int[] highscores = new int[5];
	float[] avgscores = new float[5];

	private static int numofstudents;

	public static int getNumofstudents() {
		return numofstudents;
	}

	public static void setNumofstudents(int number) {
		numofstudents = number - 1;
	}
	
	public void Title() {
		System.out.println("*******Records Analyze Results*******");
	}

	void findhigh(Student[] a) {
		System.out.printf("\nHigh Score   ");
		for (int i = 0; i < 5; i++) {
			highscores[i] = a[0].scores[i];
		}

		for (int i = 0; i < 5; i++) {
			for (int xx = 0; xx < numofstudents; xx++) {
				if (this.highscores[i] < a[xx].scores[i]) {
					this.highscores[i] = a[xx].scores[i];
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			System.out.printf("%d  ", highscores[i]);
		}
	}

	void findlow(Student[] a) {
		System.out.printf("\nLow Score   ");
		for (int i = 0; i < 5; i++) {
			lowscores[i] = a[0].scores[i];
		}

		for (int i = 0; i < 5; i++) {
			for (int xx = 0; xx < numofstudents; xx++) {
				if (this.lowscores[i] > a[xx].scores[i]) {
					this.lowscores[i] = a[xx].scores[i];
				}
			}
		}

		for (int i = 0; i < 5; i++) {
			System.out.printf("%d  ", lowscores[i]);
		}
	}

	void findavg(Student[] a) {
		System.out.printf("\nAverage   ");
		float[] sum = new float[5];

		for (int i = 0; i < 5; i++) {
			for (int xx = 0; xx < numofstudents; xx++) {
				sum[i] += a[xx].scores[i];
			}
		}
		for (int i = 0; i < 5; i++) {
			avgscores[i] = sum[i] / numofstudents;
			System.out.printf("%f  ", avgscores[i]);
		}
	}
}
