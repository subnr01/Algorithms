package com.example.studentrecordanalyzing;

import java.util.List;

import android.app.Activity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.example.studentrecordanalyzing.model.Score;
import com.example.studentrecordanalyzing.sqlite.MySQLiteHelper;

public class ShowActivity extends Activity{

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_show);
		
		MySQLiteHelper db = new MySQLiteHelper(this);
        List<Score> list = db.getAllScores();
        
        ListView listView = (ListView)findViewById(R.id.listView);
        ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, list); 
        listView.setAdapter(adapter);
	}
}
