package edu.cmu.ini.smslocation.ui;

/**
 * Subramanian Natarajan
 * snatara1
 */


import android.app.Activity;
import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import edu.cmu.ini.smslocation.R;
import edu.cmu.ini.smslocation.exception.*;




public class MainActivity extends Activity implements View.OnClickListener {

    private Button button;

    private TextView longitude;
    private TextView latitude;
    private TextView altitude;

    private LocationManager locationManager;
    private Location location;

    private String msg;

    private static final String TELENUM  = "4125571194";


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        button = (Button)findViewById(R.id.go_button);
        button.setOnClickListener(MainActivity.this);


        longitude = (TextView)findViewById(R.id.longtitude_TextView);
        latitude = (TextView)findViewById(R.id.latitute_TextView);
        altitude = (TextView)findViewById(R.id.altitude_TextView);

        locationManager = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        location = locationManager.getLastKnownLocation(locationManager.GPS_PROVIDER);


        updateLocation(location);



        locationManager.requestLocationUpdates(locationManager.GPS_PROVIDER, 0, 0, new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {

            }


            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) {
                updateLocation(locationManager.getLastKnownLocation(provider));
            }

            @Override
            public void onProviderEnabled(String provider) {

            }

            @Override
            public void onProviderDisabled(String provider) {

            }
        });
    }



    @Override
    public void onClick(View v) {
        SmsManager smsManager = SmsManager.getDefault();
       

        if (location == null){
            Toast.makeText(MainActivity.this, "No Location Service!", Toast.LENGTH_LONG).show();
        } else{
            smsManager.sendTextMessage(TELENUM,null,msg,null,null);
            Toast.makeText(MainActivity.this, "Sent to " + TELENUM, Toast.LENGTH_LONG).show();
        }
    }


    private void updateLocation(Location loc) {

        
        if(loc != null){
            StringBuilder longitude_sb = new StringBuilder();
            StringBuilder latitude_sb = new StringBuilder();
            StringBuilder altitude_sb = new StringBuilder();
            longitude_sb.append(location.getLongitude());
            latitude_sb.append(location.getLatitude());
            altitude_sb.append(location.getAltitude());
            longitude.setText(longitude_sb.toString());
            latitude.setText(latitude_sb.toString());
            altitude.setText(altitude_sb.toString());
            msg = longitude_sb.toString() + "||" +latitude_sb.toString()+ "||" + altitude_sb.toString();
        }else{
            new AppException("No Location Service!");
            Toast.makeText(this, "No Location Service!", Toast.LENGTH_SHORT).show();
        }

    }


}

