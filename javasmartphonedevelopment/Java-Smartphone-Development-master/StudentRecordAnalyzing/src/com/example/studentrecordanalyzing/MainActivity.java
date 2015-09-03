package com.example.studentrecordanalyzing;

import java.util.List;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

import com.example.studentrecordanalyzing.model.Score;
import com.example.studentrecordanalyzing.sqlite.MySQLiteHelper;

public class MainActivity extends Activity {

	EditText mEditID;
	EditText mEditQ1;
	EditText mEditQ2;
	EditText mEditQ3;
	EditText mEditQ4;
	EditText mEditQ5;
	EditText mEditDelete;
	Button showButton;
	Button addButton;
	Button deleteButton;
	Button analyzeButton;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		showButton = (Button) findViewById(R.id.showButton);
		addButton = (Button) findViewById(R.id.addButton);
		deleteButton = (Button) findViewById(R.id.deleteButton);
		analyzeButton = (Button) findViewById(R.id.analyzeButton);

		mEditID = (EditText) findViewById(R.id.EditTextID);
		mEditQ1 = (EditText) findViewById(R.id.EditTextQ1);
		mEditQ2 = (EditText) findViewById(R.id.EditTextQ2);
		mEditQ3 = (EditText) findViewById(R.id.EditTextQ3);
		mEditQ4 = (EditText) findViewById(R.id.EditTextQ4);
		mEditQ5 = (EditText) findViewById(R.id.EditTextQ5);
		mEditDelete = (EditText) findViewById(R.id.EditTextDelete);

		final MySQLiteHelper db = new MySQLiteHelper(this);

		showButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				Intent intent = new Intent(MainActivity.this,
						ShowActivity.class);
				startActivity(intent);
			}
		});

		addButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {

				AlertDialog alertDialog = new AlertDialog.Builder(
						MainActivity.this).create();
				alertDialog.setTitle("Message:");

				try {
					db.addScore(new Score(mEditID.getText().toString(), Double
							.parseDouble(mEditQ1.getText().toString()), Double
							.parseDouble(mEditQ2.getText().toString()), Double
							.parseDouble(mEditQ3.getText().toString()), Double
							.parseDouble(mEditQ4.getText().toString()), Double
							.parseDouble(mEditQ5.getText().toString())));
					mEditID.setText("");
					mEditQ1.setText("");
					mEditQ2.setText("");
					mEditQ3.setText("");
					mEditQ4.setText("");
					mEditQ5.setText("");

					alertDialog.setMessage("Successfully added");
					alertDialog.setButton("OK",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog,
										int which) {
								}
							});
					alertDialog.show();
				} catch (Exception e) {
					alertDialog.setMessage(e.toString());
					alertDialog.setButton("OK",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog,
										int which) {
								}
							});
					alertDialog.show();
				}
			}
		});

		deleteButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				AlertDialog alertDialog = new AlertDialog.Builder(
						MainActivity.this).create();
				alertDialog.setTitle("Message:");
				
				db.deleteRecords(mEditDelete.getText().toString());
				
				mEditDelete.setText("");
				alertDialog.setMessage("Successfully deleted");
				alertDialog.setButton("OK",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
							}
						});
				alertDialog.show();
			}
		});
		
		analyzeButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {

				List<Score> list = db.getAllScores();
				double[] highscores = new double[5];
				double[] lowscores = new double[5];
				double[] avgscores = new double[5];

				for (int i = 0; i < list.size(); i++) {
					Score cur = list.get(i);
					double q1 = cur.getQ1();
					double q2 = cur.getQ2();
					double q3 = cur.getQ3();
					double q4 = cur.getQ4();
					double q5 = cur.getQ5();

					highscores[0] = Math.max(highscores[0], q1);
					highscores[1] = Math.max(highscores[1], q2);
					highscores[2] = Math.max(highscores[2], q3);
					highscores[3] = Math.max(highscores[3], q4);
					highscores[4] = Math.max(highscores[4], q5);

					lowscores[0] = Math.min(lowscores[0], q1);
					lowscores[1] = Math.min(lowscores[1], q2);
					lowscores[2] = Math.min(lowscores[2], q3);
					lowscores[3] = Math.min(lowscores[3], q4);
					lowscores[4] = Math.min(lowscores[4], q5);

					avgscores[0] += q1;
					avgscores[1] += q2;
					avgscores[2] += q3;
					avgscores[3] += q4;
					avgscores[4] += q5;
				}

				for (int i = 0; i < 5; i++) {
					avgscores[i] /= (1.00 * list.size());
				}

				AlertDialog alertDialog = new AlertDialog.Builder(
						MainActivity.this).create();
				alertDialog.setTitle("Message:");

				String msg = String
						.format("\t\tQ1\tQ2\tQ3\tQ4\tQ5\nHigh\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\nLow\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\nAvg\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f",
								highscores[0], highscores[1], highscores[2],
								highscores[3], highscores[4], lowscores[0],
								lowscores[1], lowscores[2], lowscores[3],
								lowscores[4], avgscores[0], avgscores[1],
								avgscores[2], avgscores[3], avgscores[4]);
				alertDialog.setMessage(msg);
				alertDialog.setButton("OK",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
							}
						});
				alertDialog.show();
			}
		});
	}
}