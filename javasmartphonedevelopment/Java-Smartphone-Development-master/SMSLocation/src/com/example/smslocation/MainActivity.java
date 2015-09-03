package com.example.smslocation;

import android.app.Activity;
import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class MainActivity extends Activity {
	private static final long MINIMUM_DISTANCE_CHANGE_FOR_UPDATES = 0; 															// Meters
	private static final long MINIMUM_TIME_BETWEEN_UPDATES = 1000; 
	private static final String Phone_Number = "4129999999";

	private LocationManager locationmanager;
	private Button mButton;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		mButton = (Button) findViewById(R.id.Button);
		locationmanager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);

		locationmanager.requestLocationUpdates(
				LocationManager.GPS_PROVIDER,
				MINIMUM_TIME_BETWEEN_UPDATES,
				MINIMUM_DISTANCE_CHANGE_FOR_UPDATES, 
				new MyLocationListener());

		mButton.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				messageLocation(Phone_Number);
			}
		});
	}

	protected void messageLocation(String number) {
		Location location = locationmanager.getLastKnownLocation(LocationManager.GPS_PROVIDER);

		if (location != null) {
			String message = String.format(
					"Current Location \n Longitude: %1$s \n Latitude: %2$s",
					location.getLongitude(), location.getLatitude());
			
			SmsManager smsManager = SmsManager.getDefault();
			smsManager.sendTextMessage(number, null, message, null, null);
			
			Toast.makeText(MainActivity.this, message + 
			"\n\nYou have successfully sent your location to " 
			+ number, Toast.LENGTH_LONG).show();
		}
	}

	private class MyLocationListener implements LocationListener {
		@Override
		public void onLocationChanged(Location location) {
			String message = String.format(
					"Update Location \n Longitude: %1$s \n Latitude: %2$s",
					location.getLongitude(), location.getLatitude());
			Toast.makeText(MainActivity.this, message, Toast.LENGTH_LONG)
					.show();
		}

		@Override
		public void onStatusChanged(String s, int i, Bundle b) {
			Toast.makeText(MainActivity.this, "Provider status changed",
					Toast.LENGTH_LONG).show();
		}

		@Override
		public void onProviderDisabled(String s) {
			Toast.makeText(MainActivity.this,
					"Provider disabled by the user. GPS turned off",
					Toast.LENGTH_LONG).show();
		}

		@Override
		public void onProviderEnabled(String s) {
			Toast.makeText(MainActivity.this,
					"Provider enabled by the user. GPS turned on",
					Toast.LENGTH_LONG).show();
		}
	}
}
