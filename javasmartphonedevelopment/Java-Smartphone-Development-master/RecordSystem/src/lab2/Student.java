package lab2;

public class Student {
	public int SID;
	public int scores[] = new int[5];
	public int numStu;

	public Student() {
		SID = 0;
		numStu = 0;
		for (int i = 0; i < 5; i++) {
			scores[i] = 0;
		}
	}

	public int getSID() {
		return SID;
	}

	public void setSID(int sID) {
		SID = sID;
	}

	public int[] getScores() {
		return scores;
	}

	public void setScores(int[] scores) {
		this.scores = scores;
	}
}
