package com.mad.restaurantfinderrm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;

import org.json.JSONObject;

import android.content.Intent;
import android.graphics.Color;
import android.location.Address;
import android.location.Criteria;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;
import com.google.android.gms.maps.model.PolylineOptions;
import com.mad.restaurantfinderrm.library.DirectionsJSONParser;

public class MapActivity extends FragmentActivity implements LocationListener {

	GoogleMap map;
	ArrayList<LatLng> markerPoints;
	ArrayList<LatLng> positions;

	String address;
	String restName;

	LatLng contactLocation = null;
	LatLng myLocationLL = null;
	Address a;
	Location myLocation = null;
	Marker myMarker;
	Marker contactMarker;

	private LocationManager locationManager;
	private String provider;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_map);

		positions = new ArrayList<LatLng>();

		// Getting reference to SupportMapFragment of the activity_main
		SupportMapFragment fm = (SupportMapFragment) getSupportFragmentManager()
				.findFragmentById(R.id.map);

		// Getting Map for the SupportMapFragment
		map = fm.getMap();

		// Enable MyLocation Button in the Map
		map.setMyLocationEnabled(true);

		// get my current location
		locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);
		boolean enabledGPS = locationManager
				.isProviderEnabled(LocationManager.GPS_PROVIDER);
		//boolean enabledWiFi = locationManager
			//	.isProviderEnabled(LocationManager.NETWORK_PROVIDER);

		if (!enabledGPS) {
			Toast.makeText(this, "GPS signal not found", Toast.LENGTH_LONG)
					.show();
			// TODO
			// Intent intent = new
			// Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS);
			// startActivity(intent);

		}

		Criteria criteria = new Criteria();
		provider = locationManager.getBestProvider(criteria, false);
		myLocation = locationManager.getLastKnownLocation(provider);

		// Initialize the location fields
		if (myLocation != null) {
			Toast.makeText(this, "Selected Provider " + provider,
					Toast.LENGTH_SHORT).show();
			onLocationChanged(myLocation);
			myLocationLL = new LatLng(myLocation.getLatitude(),
					myLocation.getLongitude());
			positions.add(myLocationLL);
		} else {

			positions.add(null);
		}

		// get contacts address location
		Intent intent = getIntent();
		address = intent.getExtras().getString("address");
		Log.v("ADDRESS", address);
		restName = intent.getExtras().getString("restName");
		Log.v("ADDRESS", restName);
		String fulladdress = restName + ", " + address;
		Geocoder geocoder = new Geocoder(getApplicationContext(),
				Locale.getDefault());
		List<Address> fromLocationName = null;
		try {
			fromLocationName = geocoder.getFromLocationName(fulladdress, 1);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		if (fromLocationName != null && fromLocationName.size() > 0) {
			a = fromLocationName.get(0);
			contactLocation = new LatLng(a.getLatitude(), a.getLongitude());
			contactMarker = map.addMarker(new MarkerOptions().position(
					contactLocation).title(restName));
			contactMarker.showInfoWindow();

			positions.add(contactLocation);

			// move the camera instantly to the festival with a zoom of X.
			map.moveCamera(CameraUpdateFactory.newLatLng(contactLocation));

			map.animateCamera(CameraUpdateFactory.zoomTo(16), 2000, null);
		} else {
			positions.add(null);
		}

		// Initializing
		markerPoints = new ArrayList<LatLng>();

		if (positions.size() == 2) {
			for (LatLng position : positions) {

				// Adding new item to the ArrayList
				markerPoints.add(position);

				// Creating MarkerOptions
				MarkerOptions options = new MarkerOptions();

				// Setting the position of the marker
				options.position(position);

				/**
				 * For the start location, the color of marker is GREEN and for
				 * the end location, the color of marker is RED.
				 */
				if (markerPoints.size() == 1) {
					options.icon(BitmapDescriptorFactory
							.defaultMarker(BitmapDescriptorFactory.HUE_GREEN));
				} else if (markerPoints.size() == 2) {
					options.icon(BitmapDescriptorFactory
							.defaultMarker(BitmapDescriptorFactory.HUE_RED));
				}

				// Add new marker to the Google Map Android API V2
				map.addMarker(options);

				// Checks, whether start and end locations are captured
				if (markerPoints.size() >= 2) {
					LatLng origin = markerPoints.get(0);
					LatLng dest = markerPoints.get(1);

					// Getting URL to the Google Directions API
					String url = getDirectionsUrl(origin, dest);

					DownloadTask downloadTask = new DownloadTask();

					// Start downloading json data from Google Directions API
					downloadTask.execute(url);
				}
			}
		}
	}

	private String getDirectionsUrl(LatLng origin, LatLng dest) {

		// Origin of route
		String str_origin = "origin=" + origin.latitude + ","
				+ origin.longitude;

		// Destination of route
		String str_dest = "destination=" + dest.latitude + "," + dest.longitude;

		// Sensor enabled
		String sensor = "sensor=false";

		// Building the parameters to the web service
		String parameters = str_origin + "&" + str_dest + "&" + sensor;

		// Output format
		String output = "json";

		// Building the url to the web service
		String url = "https://maps.googleapis.com/maps/api/directions/"
				+ output + "?" + parameters;

		return url;
	}

	/** A method to download json data from url */
	private String downloadUrl(String strUrl) throws IOException {
		String data = "";
		InputStream iStream = null;
		HttpURLConnection urlConnection = null;
		try {
			URL url = new URL(strUrl);

			// Creating an http connection to communicate with url
			urlConnection = (HttpURLConnection) url.openConnection();

			// Connecting to url
			urlConnection.connect();

			// Reading data from url
			iStream = urlConnection.getInputStream();

			BufferedReader br = new BufferedReader(new InputStreamReader(
					iStream));

			StringBuffer sb = new StringBuffer();

			String line = "";
			while ((line = br.readLine()) != null) {
				sb.append(line);
			}

			data = sb.toString();

			br.close();

		} catch (Exception e) {
			Log.d("Exception while downloading url", e.toString());
		} finally {
			iStream.close();
			urlConnection.disconnect();
		}
		return data;
	}

	// Fetches data from url passed
	private class DownloadTask extends AsyncTask<String, Void, String> {

		// Downloading data in non-ui thread
		@Override
		protected String doInBackground(String... url) {

			// For storing data from web service
			String data = "";

			try {
				// Fetching the data from web service
				data = downloadUrl(url[0]);
			} catch (Exception e) {
				Log.d("Background Task", e.toString());
			}
			return data;
		}

		// Executes in UI thread, after the execution of
		// doInBackground()
		@Override
		protected void onPostExecute(String result) {
			super.onPostExecute(result);

			ParserTask parserTask = new ParserTask();

			// Invokes the thread for parsing the JSON data
			parserTask.execute(result);
		}
	}

	/** A class to parse the Google Places in JSON format */
	private class ParserTask extends
			AsyncTask<String, Integer, List<List<HashMap<String, String>>>> {

		// Parsing the data in non-ui thread
		@Override
		protected List<List<HashMap<String, String>>> doInBackground(
				String... jsonData) {

			JSONObject jObject;
			List<List<HashMap<String, String>>> routes = null;

			try {
				jObject = new JSONObject(jsonData[0]);
				DirectionsJSONParser parser = new DirectionsJSONParser();

				// Starts parsing data
				routes = parser.parse(jObject);
			} catch (Exception e) {
				e.printStackTrace();
			}
			return routes;
		}

		// Executes in UI thread, after the parsing process
		@Override
		protected void onPostExecute(List<List<HashMap<String, String>>> result) {
			ArrayList<LatLng> points = null;
			PolylineOptions lineOptions = null;
			//MarkerOptions markerOptions = new MarkerOptions();

			// Traversing through all the routes
			for (int i = 0; i < result.size(); i++) {
				points = new ArrayList<LatLng>();
				lineOptions = new PolylineOptions();

				// Fetching i-th route
				List<HashMap<String, String>> path = result.get(i);

				// Fetching all the points in i-th route
				for (int j = 0; j < path.size(); j++) {
					HashMap<String, String> point = path.get(j);

					double lat = Double.parseDouble(point.get("lat"));
					double lng = Double.parseDouble(point.get("lng"));
					LatLng position = new LatLng(lat, lng);

					points.add(position);
				}

				// Adding all the points in the route to LineOptions
				lineOptions.addAll(points);
				lineOptions.width(2);
				lineOptions.color(Color.RED);
			}

			// Drawing polyline in the Google Map for the i-th route
			map.addPolyline(lineOptions);
		}
	}

	@Override
	public void onLocationChanged(Location location) {
		LatLng coordinate = new LatLng(location.getLatitude(),
				location.getLongitude());

		// Toast.makeText(this, "Location " +
		// coordinate.latitude+","+coordinate.longitude,
		// Toast.LENGTH_LONG).show();

		if (myMarker != null) {
			// Toast.makeText(this, "!=null", Toast.LENGTH_LONG).show();
			myMarker.remove();
		}
		myMarker = map.addMarker(new MarkerOptions().position(coordinate)
				.title("Here I am!"));

		myMarker.showInfoWindow();

		// move the camera instantly to the festival with a zoom of X.
		map.moveCamera(CameraUpdateFactory.newLatLng(coordinate));

		map.animateCamera(CameraUpdateFactory.zoomTo(16), 2000, null);
	}

	@Override
	public void onProviderDisabled(String arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onProviderEnabled(String arg0) {
		// TODO Auto-generated method stub

	}

	@Override
	public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
		// TODO Auto-generated method stub

	}

}
