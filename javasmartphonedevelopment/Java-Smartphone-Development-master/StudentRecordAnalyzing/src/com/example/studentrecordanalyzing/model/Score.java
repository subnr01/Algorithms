package com.example.studentrecordanalyzing.model;

public class Score {
	private String id;
	private double q1;
	private double q2;
	private double q3;
	private double q4;
	private double q5;
	
	public Score() {
		super();
	}

	public Score(String id, double q1, double q2, double q3, double q4,
			double q5) {
		super();
		this.id = id;
		this.q1 = q1;
		this.q2 = q2;
		this.q3 = q3;
		this.q4 = q4;
		this.q5 = q5;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public double getQ1() {
		return q1;
	}

	public void setQ1(double q1) {
		this.q1 = q1;
	}

	public double getQ2() {
		return q2;
	}

	public void setQ2(double q2) {
		this.q2 = q2;
	}

	public double getQ3() {
		return q3;
	}

	public void setQ3(double q3) {
		this.q3 = q3;
	}

	public double getQ4() {
		return q4;
	}

	public void setQ4(double q4) {
		this.q4 = q4;
	}

	public double getQ5() {
		return q5;
	}

	public void setQ5(double q5) {
		this.q5 = q5;
	}

	@Override
	public String toString() {
		return "Student ID: " + id + "\nq1=" + q1 + ", q2=" + q2 + ", q3="
				+ q3 + ", q4=" + q4 + ", q5=" + q5 + 
				"\n------------------------------------------------------";
	}
}
