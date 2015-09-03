package com.example.studentrecordanalyzing.sqlite;

import java.util.LinkedList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import com.example.studentrecordanalyzing.model.Score;

public class MySQLiteHelper extends SQLiteOpenHelper {
	
    private static final int DATABASE_VERSION = 1;
    private static final String DATABASE_NAME = "SQliteDB";
    
    private static final String TABLE_SCORES = "scores";
    
    private static final String KEY_ID = "id";
    private static final String KEY_Q1 = "q1";
    private static final String KEY_Q2 = "q2";
    private static final String KEY_Q3 = "q3";
    private static final String KEY_Q4 = "q4";
    private static final String KEY_Q5 = "q5";
    
    private static final String[] COLUMNS = {KEY_ID,KEY_Q1,KEY_Q2, KEY_Q3, KEY_Q4, KEY_Q5};
   
	public MySQLiteHelper(Context context) {
		super(context, DATABASE_NAME, null, DATABASE_VERSION);	
	}

	@Override
	public void onCreate(SQLiteDatabase db) {
		String CREATE_RECORDS_TABLE = "CREATE TABLE scores ( " +
                "id TEXT PRIMARY KEY, " + "q1 REAL, "+ "q2 REAL, "
				+ "q3 REAL, "+ "q4 REAL, "+ "q5 REAL )";
		
		db.execSQL(CREATE_RECORDS_TABLE);
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_SCORES);
        this.onCreate(db);
	}
	
   
	public void addScore(Score score){
		SQLiteDatabase db = this.getWritableDatabase();
		 
        ContentValues values = new ContentValues();
        values.put(KEY_ID, score.getId());
        values.put(KEY_Q1, score.getQ1());
        values.put(KEY_Q2, score.getQ2());
        values.put(KEY_Q3, score.getQ3());
        values.put(KEY_Q4, score.getQ4());
        values.put(KEY_Q5, score.getQ5());
 
        db.insert(TABLE_SCORES, null, values); 
        db.close(); 
	}
	
	public Score getScore(int id){
		SQLiteDatabase db = this.getReadableDatabase();
        Cursor cursor = 
        		db.query(TABLE_SCORES, COLUMNS, " id = ?", 
                new String[] { String.valueOf(id) }, 
                null, null, null, null); 
        
        if (cursor != null) cursor.moveToFirst();
 
        Score score = new Score();
        score.setId(cursor.getString(0));
        score.setQ1(Double.parseDouble(cursor.getString(1)));
        score.setQ2(Double.parseDouble(cursor.getString(2)));
        score.setQ3(Double.parseDouble(cursor.getString(3)));
        score.setQ4(Double.parseDouble(cursor.getString(4)));
        score.setQ5(Double.parseDouble(cursor.getString(5)));

        return score;
	}
	
	// Get All Recordss
    public List<Score> getAllScores() {
        List<Score> scores = new LinkedList<Score>();
        String query = "SELECT  * FROM " + TABLE_SCORES;
 
        SQLiteDatabase db = this.getWritableDatabase();
        Cursor cursor = db.rawQuery(query, null);
        Score score = null;
        if (cursor.moveToFirst()) {
            do {
            	score = new Score();
            	score.setId(cursor.getString(0));
                score.setQ1(Double.parseDouble(cursor.getString(1)));
                score.setQ2(Double.parseDouble(cursor.getString(2)));
                score.setQ3(Double.parseDouble(cursor.getString(3)));
                score.setQ4(Double.parseDouble(cursor.getString(4)));
                score.setQ5(Double.parseDouble(cursor.getString(5)));
                scores.add(score);
            } while (cursor.moveToNext());
        }
        return scores;
    }
	
    // Deleting single Records
    public void deleteRecords(String id) {
        SQLiteDatabase db = this.getWritableDatabase();
        db.delete(TABLE_SCORES, KEY_ID+" = ?", new String[] {id});
        db.close();
    }
}
