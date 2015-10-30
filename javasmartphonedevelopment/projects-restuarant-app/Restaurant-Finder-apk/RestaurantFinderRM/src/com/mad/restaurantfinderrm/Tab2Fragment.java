package com.mad.restaurantfinderrm;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.http.NameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.LinearLayout;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Toast;

import com.mad.restaurantfinderrm.library.JSONParser;

public class Tab2Fragment extends Fragment {
	// Progress Dialog
	private ProgressDialog pDialog;

	// creating JSON Parser object
	JSONParser jParser = new JSONParser();

	// url to make request
	// private static String url =
	// "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_deals.php";
	private static String url = "http://54.228.194.206/api/get_all_deals.php";

	// JSON Node names
	private static final String TAG_DEALS = "deals";
	private static final String TAG_ID = "id";
	private static final String TAG_DEALNAME = "dealName";
	private static final String TAG_PRICE = "price";
	private static final String TAG_DESCRIPTION = "description";
	private static final String TAG_RESTID = "restID";
	private static final String TAG_RESTNAME = "restName";
	private static final String TAG_RESTTYPE = "restType";
	private static final String TAG_LAT = "restLat";
	private static final String TAG_LNG = "restLng";
	private static final String TAG_SUCCESS = "success";

	private JSONObject json;

	JSONArray restaurantDealsData = null;

	// Hashmap for ListView
	ArrayList<HashMap<String, String>> restaurantDealsList = new ArrayList<HashMap<String, String>>();

	ListView myList;

	Activity a;

	private String[] dealID;
	private String mylat = "0.00";
	private String mylng = "0.00";

	/**
	 * (non-Javadoc)
	 * 
	 * @see android.support.v4.app.Fragment#onCreateView(android.view.LayoutInflater,
	 *      android.view.ViewGroup, android.os.Bundle)
	 */
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		if (container == null) {
			// We have different layouts, and in one of them this
			// fragment's containing frame doesn't exist. The fragment
			// may still be created from its saved state, but there is
			// no reason to try to create its view hierarchy because it
			// won't be displayed. Note this is not needed -- we could
			// just run the code below, where we would create and return
			// the view hierarchy; it would just never be used.
			return null;
		}

		return (LinearLayout) inflater.inflate(R.layout.tab_frag2_layout,
				container, false);

	}

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);

		a = getActivity();
				
		myList = (ListView) a.findViewById(R.id.dealsListView);
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	@Override
	public void onStart() {
		super.onStart();
	}

	@Override
	public void onResume() {
		super.onResume();
			// load list view
			new LoadDeals().execute();
		
	}

	// in miles
	public static double distFrom(double lat1, double lng1, double lat2,
			double lng2) {
		double earthRadius = 3958.75;
		double dLat = Math.toRadians(lat2 - lat1);
		double dLng = Math.toRadians(lng2 - lng1);
		double sindLat = Math.sin(dLat / 2);
		double sindLng = Math.sin(dLng / 2);
		double a = Math.pow(sindLat, 2) + Math.pow(sindLng, 2)
				* Math.cos(Math.toRadians(lat1))
				* Math.cos(Math.toRadians(lat2));
		double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
		double dist = earthRadius * c;

		return dist;
	}
	
	
	/**
	 * Background Async Task to Load all deals by making HTTP Request
	 * */
	class LoadDeals extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(a);
			pDialog.setMessage("Loading Restaurant Deals Data. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();

			// getting JSON string from URL
			JSONObject json = jParser.makeHttpRequest(url, "GET", params);
			// check log cat for JSON string from URL
			Log.v("restaurantDealsJSON: ", json.toString());

			// return json as string to using in the user interface
			return json.toString();
		}

		@Override
		protected void onPostExecute(final String jsonStr) {
			// dismiss the dialog after getting all products
			pDialog.dismiss();

			// updating UI from Background Thread
			a.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					/**
					 * Updating parsed JSON data into listview
					 * */
					try {
						json = new JSONObject(jsonStr);
					} catch (JSONException e1) {
						// print error message to log
						e1.printStackTrace();

						error("There are no Deals");

					}

					try {
						// Checking for SUCCES TAG
						int success = json.getInt(TAG_SUCCESS);

						if (success == 1) {
							// restaurant found

							// Getting Array of restaurant

							restaurantDealsData = json.getJSONArray(TAG_DEALS);
							displayDeals(restaurantDealsData.toString());
						} else {
							// no technical data found
							// Log.v("ERROR", "No techdata");
							// display dialog and back to dashboard
							// Log.v("ERROR", "1");
							error("There is no Deals available!");
						}
					} catch (JSONException e) {
						error("There has been an error please try again!");
						e.printStackTrace();
					}
				}
			});
		}
	}

	public void error(String error) {
		// Log.v("ERROR", "2");
		AlertDialog.Builder builder = new AlertDialog.Builder(a);
		// Log.v("ERROR", "3");
		// todo set icon
		builder.setTitle("Error");
		builder.setMessage(error);
		builder.setCancelable(false);
		builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int id) {
				// Log.v("TEST", "1");
				Intent i = new Intent(a.getApplicationContext(),
						TabsViewPagerFragmentActivity.class);

				startActivity(i);
				a.overridePendingTransition(R.anim.fade_in, R.anim.fade_out);
				a.finish();

			}
		});
		AlertDialog alert = builder.create();
		alert.show();
	}

	public void displayDeals(String result) {
		// Log.v("techdata: ", "display");
		JSONArray restaurantDealsData = null;

		try {
			restaurantDealsList.clear();

			restaurantDealsData = new JSONArray(result);

			dealID = new String[restaurantDealsData.length()];
			// looping through all technical data
			for (int i = 0; i < restaurantDealsData.length(); i++) {
				JSONObject td = restaurantDealsData.getJSONObject(i);

				// Storing each json item in variable
				String id = td.getString(TAG_ID);
				dealID[i] = id;

				String name = td.getString(TAG_DEALNAME);
				String price = td.getString(TAG_PRICE);
				String description = td.getString(TAG_DESCRIPTION);
				String restaurantID = td.getString(TAG_RESTID);
				String restaurantName = td.getString(TAG_RESTNAME);
				String restaurantType = td.getString(TAG_RESTTYPE);
				String lat = td.getString(TAG_LAT);
				String lng = td.getString(TAG_LNG);

				Log.v("lat", lat);
				Log.v("lng", lng);
				/**
				 * get current location
				 */
				LocationManager mlocManager = (LocationManager) a
						.getSystemService(Context.LOCATION_SERVICE);

				LocationListener mlocListener = new MyLocationListener(lat, lng);
				mlocManager.requestLocationUpdates(
						LocationManager.GPS_PROVIDER, 0, 0, mlocListener);

				Log.v("myLat", mylat);
				Log.v("myLng", mylng);
				// Creating new HashMap
				HashMap<String, String> map = new HashMap<String, String>();

				// adding each child node to HashMap key => value
				map.put(TAG_ID, id);
				map.put(TAG_DEALNAME, name);
				map.put(TAG_PRICE, price);
				map.put(TAG_DESCRIPTION, description);
				map.put(TAG_RESTID, restaurantID);
				map.put(TAG_RESTNAME, restaurantName);
				map.put(TAG_RESTTYPE, restaurantType);
				map.put(TAG_LAT, lat);
				map.put(TAG_LNG, lng);

				if (Double.parseDouble(mylat) != 0.00
						&& Double.parseDouble(mylng) != 0.00) {
					Double dist = distFrom(Double.parseDouble(lat),
							Double.parseDouble(lng), Double.parseDouble(mylat),
							Double.parseDouble(mylng));
					// formating distance
					DecimalFormat twoDigits = new DecimalFormat("0.00");
					map.put("LOCATION", twoDigits.format(dist) + " miles");
				} else {
					map.put("LOCATION", "Please wait....");
				}

				// adding HashMap to ArrayList
				restaurantDealsList.add(map);
			}

		} catch (JSONException e) {
			e.printStackTrace();
			error("Error parsing json");
		}

		// add to list view
		/**
		 * Updating parsed JSON data into ListView
		 * */
		ListAdapter adapter = new SimpleAdapter(a, restaurantDealsList,
				R.layout.deals_list_item, new String[] { TAG_DEALNAME,
						"LOCATION", TAG_RESTNAME, TAG_RESTTYPE }, new int[] {
						R.id.dealName, R.id.dealLocation, R.id.restaurantName,
						R.id.type });
		// updating listview
		myList.setAdapter(adapter);
		// handling user click list item
		myList.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				// start the next activity - Restaurant Details
				Intent i = new Intent(a.getApplicationContext(),
						DealDetails.class);
				i.putExtra("ID", dealID[arg2]);
				startActivity(i);
				a.overridePendingTransition(R.anim.slide_in_right,
						R.anim.slide_out_left);
			}

		});
	}

	/* Class My Location Listener */
	public class MyLocationListener implements LocationListener {
		double lat;
		double lng;

		public MyLocationListener(String lat, String lng) {
			this.lat = Double.parseDouble(lat);
			this.lng = Double.parseDouble(lng);
		}

		@Override
		public void onLocationChanged(Location loc) {
			mylat = "" + loc.getLatitude();
			mylng = "" + loc.getLongitude();

		}

		@Override
		public void onProviderDisabled(String provider) {
			Toast.makeText(a.getApplicationContext(), "Gps Disabled",
					Toast.LENGTH_SHORT).show();
		}

		@Override
		public void onProviderEnabled(String provider) {
			Toast.makeText(a.getApplicationContext(), "Gps Enabled",
					Toast.LENGTH_SHORT).show();
		}

		@Override
		public void onStatusChanged(String provider, int status, Bundle extras) {

		}
	}
}
