package util;


import java.io.*;
import java.util.*;

import lab2.Statistics;
import lab2.Student;

public class Util {

	public static Student[] readFile(String filename, Student[] lab2) {

		String line2 = null;

		int number = 0;
		int numStudents = 0;
		String[] record = new String[500];
		int[][] matrix = new int[100][6];
		int[] ID = new int[100];

		try {
			FileReader file = new FileReader(filename);
			BufferedReader buff = new BufferedReader(file);
			boolean eof = false;
			while (!eof) {
				String line = buff.readLine();

				if (line == null) {
					eof = true;
				} else {
					line2 = line;
					System.out.println(line);
				}
				StringTokenizer st = new StringTokenizer(line2);
				while (st.hasMoreTokens()) {
					record[number] = st.nextToken();
					number++;
				}
			}

			numStudents = (number / 6) - 1;

			for (int i = 0; i < numStudents; i++) {
				for (int j = 0; j < 5; j++) {
					matrix[i][j] = Integer.parseInt(record[6 * i + 7 + j]);
					ID[i] = Integer.parseInt(record[6 * i + 6]);
				}
			}

			buff.close();

		} catch (IOException e) {
			System.out.println("Error -- " + e.toString());
		}

		Statistics.setNumofstudents(numStudents);

		lab2 = new Student[40];

		for (int i = 0; i < numStudents; i++) {
			lab2[i] = new Student();
		}

		for (int i = 0; i < numStudents; i++) {
			lab2[i].setScores(matrix[i]);
		}

		for (int i = 0; i < numStudents; i++) {
			lab2[i].setSID(ID[i]);
		}
		return lab2;
	}
}