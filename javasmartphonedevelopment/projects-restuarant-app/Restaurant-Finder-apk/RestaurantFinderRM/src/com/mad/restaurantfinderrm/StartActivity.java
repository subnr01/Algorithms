package com.mad.restaurantfinderrm;

import admin.LoginActivity;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.View;
import android.widget.Button;
import android.view.View.OnClickListener;

public class StartActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_start);
		
		Button user = (Button) findViewById(R.id.userButton);
		Button admin = (Button) findViewById(R.id.adminButton);
		
		//onclick event for button
		user.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent i = new Intent(getApplicationContext(), TabsViewPagerFragmentActivity.class);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_top,
						R.anim.slide_out_top);
			}
		});
		
		admin.setOnClickListener(new  OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent i = new Intent(getApplicationContext(), LoginActivity.class);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_top,
						R.anim.slide_out_top);
			}
		});
	}

}
