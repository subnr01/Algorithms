package admin;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.AdapterView.OnItemClickListener;

public class ManageDealsListActivty extends Activity {
	
	UserFunctions userFunctions;
	
	private String id;

	// Progress Dialog
	private ProgressDialog pDialog;

	// creating JSON Parser object
	JSONParser jParser = new JSONParser();

	// url to make request
	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_deals_by_id.php";
	private static String url = "http://54.228.194.206/api/get_all_deals_by_id.php";

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
	
	private String[] dealID;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_deals_list);
		
		userFunctions = new UserFunctions();
		
		Button add = (Button) findViewById(R.id.buttonAddDeal);
		add.setVisibility(View.VISIBLE);
		
		id = getIntent().getStringExtra("id");
		
		myList = (ListView) findViewById(R.id. restDealListView);
		
		new LoadDeals().execute();
		
		add.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(getApplicationContext(), AddDealActivity.class);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_top,
						R.anim.slide_out_top);	
			}
		});
		
	}


	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.menu, menu);
		return true;
	}

	/*
	 * Event Handling for Individual menu item selected
     * Identify single menu item by it's id
     * */
    @Override
    public boolean onOptionsItemSelected(MenuItem item)
    {
 
        switch (item.getItemId())
        {
        case R.id.menu_logout:
        	//logout user
        	//TODO check Internet here? 
        	userFunctions.logoutUser(getApplicationContext());
            Intent login = new Intent(getApplicationContext(), LoginActivity.class);
            login.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
            startActivity(login);
            overridePendingTransition(R.anim.fade_in,
					R.anim.fade_out);
            // Closing dashboard screen
            finish();
            return true; 
        default:
            return super.onOptionsItemSelected(item);
        }
    }    

	
	
	/**
	 * Background Async Task to Load all deals by making
	 * HTTP Request
	 * */
	class LoadDeals extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(ManageDealsListActivty.this);
			pDialog.setMessage("Loading Restaurant Deals. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			Log.v("id", id);
			params.add(new BasicNameValuePair("id", id));

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
			runOnUiThread(new Runnable() {
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
		AlertDialog.Builder builder = new AlertDialog.Builder(
				ManageDealsListActivty.this);
		// Log.v("ERROR", "3");
		builder.setTitle("Error");
		builder.setMessage(error);
		builder.setCancelable(false);
		builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int id) {
				// Log.v("TEST", "1");
				Intent i = new Intent(getApplicationContext(),
						ViewRestaurantActivity.class);
				i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
				startActivity(i);
				overridePendingTransition(R.anim.fade_in,
						R.anim.fade_out);
				finish();

			}
		});
		AlertDialog alert = builder.create();
		alert.show();
	}

	public void displayDeals(String result) {
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
		ListAdapter adapter = new SimpleAdapter(getApplicationContext(),
				restaurantDealsList, R.layout.deals_list_item, new String[] {
						TAG_DEALNAME, TAG_RESTNAME, TAG_RESTTYPE }, new int[] {
						R.id.dealName, R.id.restaurantName, R.id.type });
		// updating listview
		myList.setAdapter(adapter);
		//handling user click list item
		myList.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				//start the next activity - Restaurant Details
				Intent i = new Intent(getApplicationContext(), ManageDealDetails.class);
				i.putExtra("ID", dealID[arg2]);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_right,
						R.anim.slide_out_left);
			}
		
		});
	}

}
