package com.mad.restaurantfinderrm;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.mad.restaurantfinderrm.library.DatabaseHandler_Saved_Restaurants;
import com.mad.restaurantfinderrm.library.JSONParser;

public class RestaurantDetails extends Activity {
	//xml Nodes
	private TextView restaurantNameTV;
	private TextView restaurantType;
	private TextView addressLine1TV;
	private TextView addressLine2TV;
	private TextView addressLine3TV;
	private TextView phoneNumTV;
	private TextView emailTV;
	private TextView bioTV;
	
	//private String id;
	// Progress Dialog
    private ProgressDialog pDialog;
 
    JSONParser jsonParser = new JSONParser();
    
	//private UserFunctions userFunctions;
    
    // JSON Node names
 	private static final String TAG_RESTAURANT = "restaurant";
 	private static final String TAG_ID = "id";
 	private static final String TAG_NAME = "name";
 	private static final String TAG_TYPE = "type";
 	private static final String TAG_BIO = "bio";
 	private static final String TAG_ADDRESS1 = "addressLine1";
 	private static final String TAG_ADDRESS2 = "addressLine2";
 	private static final String TAG_ADDRESS3 = "addressLine3";
 	private static final String TAG_NUM = "contactNumber";
 	private static final String TAG_EMAIL = "email"; 	
 	private static final String TAG_URL = "url";
 	private static final String TAG_SUCCESS = "success";
 	
 	// url to make request
 	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_restaurant_details_by_id.php";
 	private static String url = "http://54.228.194.206/api/get_restaurant_details_by_id.php";

 	JSONObject json;

 	JSONArray restaurantData = null;
 	
 	String name;
 	String fullAddress;
 	
 	//DATABASE SQLITE
 	private SQLiteDatabase mDb;
 	//private Cursor mCursor;
 	String id;
 	
 	String url_menu = null;
	
 	Button viewMenu;
 	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
			setContentView(R.layout.activity_restaurant_details);
			
			//get id from selected item
			id = getIntent().getStringExtra("ID");
			
			//get reference to ui elements
			restaurantNameTV = (TextView) findViewById(R.id.restName);
			restaurantType = (TextView) findViewById(R.id.restType);
			addressLine1TV = (TextView) findViewById(R.id.tvAddress1);
			addressLine2TV = (TextView) findViewById(R.id.tvAddress2);
			addressLine3TV = (TextView) findViewById(R.id.tvAddress3);
			phoneNumTV = (TextView) findViewById(R.id.tvPhone);
			emailTV = (TextView) findViewById(R.id.tvEmail);
			bioTV = (TextView) findViewById(R.id.tvBio);
			viewMenu = (Button) findViewById(R.id.buttonMenu);
			
			//async task to retrieve data and update user interface 	
			new LoadRestaurantDetails().execute();
			
			//manage menu button if menu is not set 
			
			final DatabaseHandler_Saved_Restaurants mh = new DatabaseHandler_Saved_Restaurants(this);
			mDb = mh.getWritableDatabase();
			
			
			//buttons events
			viewMenu.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					Intent i = new Intent(getApplicationContext(), MenuActivity.class);
					//pass the url for restaurant
					i.putExtra("url", url_menu);
					startActivity(i);
					overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);				}
			});
			
			Button viewMap = (Button) findViewById(R.id.buttonMap);
			viewMap.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					Intent i = new Intent(getApplicationContext(), MapActivity.class);
					//pass the id for restaurant
					i.putExtra("address", fullAddress);
					i.putExtra("restName", name);
					//i.putExtra("id", id);
					startActivity(i);
					overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
				}
			});	
			
			Button viewDeals = (Button) findViewById(R.id.buttonDeals);
			viewDeals.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					Intent i = new Intent(getApplicationContext(), DealsListActivity.class);
					//pass the id for restaurant
					i.putExtra("id", id);
					startActivity(i);
					overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
				}
			});
			
			final Button addFav = (Button) findViewById(R.id.buttonFavourite);
			//check if restaurant is already in database
			String sql = "SELECT * FROM fav WHERE restaurantID=" + id;
			Cursor c = mDb.rawQuery(sql, null);
			
			//c.close();
			int rowcount = c.getCount();
			if(rowcount>0){
				addFav.setText("Remove from Favourites");
			}
			else{
				addFav.setText("Add to Favourites");
			}
			addFav.setOnClickListener(new OnClickListener() {
				
				@Override
				public void onClick(View v) {
					if(addFav.getText().toString().trim().contentEquals("Add to Favourites")){
					mh.addRest(restaurantNameTV.getText().toString(), restaurantType.getText().toString(), id.toString());
					//Toast t = Toast.makeText(getApplicationContext(), "SUCCESS", Toast.LENGTH_SHORT);
					//t.show();
					addFav.setText("Remove from Favourites");
					}
					else{
						mh.deleteFav(id);
						//Toast t = Toast.makeText(getApplicationContext(), "SUCCESS", Toast.LENGTH_SHORT);
						//t.show();
						addFav.setText("Add to Favourites");
					}	
					
				}
			});
	}
    
    @Override
    protected void onPause() {
    	super.onPause();
    	mDb.close();
    }
    
    @Override
    protected void onDestroy() {
    	super.onDestroy();
    	mDb.close();
    }
    
    
    public void error(String error) {
		// Log.v("ERROR", "2");
		AlertDialog.Builder builder = new AlertDialog.Builder(
				this);

		builder.setTitle("Error");
		builder.setMessage(error);
		builder.setCancelable(false);
		builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int id) {
				// Log.v("TEST", "1");
				Intent i = new Intent(getApplicationContext(),
						TabsViewPagerFragmentActivity.class);
				startActivity(i);
				overridePendingTransition(R.anim.fade_in, R.anim.fade_out);
				finish();

			}
		});
		AlertDialog alert = builder.create();
		alert.show();
	}

    /**
	 * Background Async Task to Load all restaurant data by making
	 * HTTP Request
	 * */
	class LoadRestaurantDetails extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(RestaurantDetails.this);
			pDialog.setMessage("Loading Restaurant Details. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			params.add(new BasicNameValuePair("id", id));

			// getting JSON string from URL
			JSONObject json = jsonParser.makeHttpRequest(url, "GET", params);
			// check log cat for JSON string from URL
			//Log.v("restaurantJSON: ", json.toString());

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
					try {
						json = new JSONObject(jsonStr);
					} catch (JSONException e1) {
						// print error message to log
						e1.printStackTrace();

						error("There are no details for this restaurants");

					}

					try {
						// Checking for SUCCES TAG
						int success = json.getInt(TAG_SUCCESS);

						if (success == 1) {
							// restaurant found
							// Getting Array of restaurant
							restaurantData = json.getJSONArray(TAG_RESTAURANT);
							displayDetails(restaurantData.toString());
						} else {
							error("There are no details for this restaurants");
						}
					} catch (JSONException e) {
						error("There has been an error please try again!");
						e.printStackTrace();
					}
				}
			});
		}
	}

	
	public void displayDetails(String result) {
		JSONArray restaurantData = null;
		
		try {

			restaurantData = new JSONArray(result);

			// looping through all restaurant data
			for (int i = 0; i < restaurantData.length(); i++) {
				JSONObject rd = restaurantData.getJSONObject(i);

				// Storing each json item in variable
				String id = rd.getString(TAG_ID);
				
				name = rd.getString(TAG_NAME);
				String type = rd.getString(TAG_TYPE);
				String bio = rd.getString(TAG_BIO);
				
	            String address1 = rd.getString(TAG_ADDRESS1);
	            String address2 = rd.getString(TAG_ADDRESS2);
	            String address3 = rd.getString(TAG_ADDRESS3);
	            fullAddress = address1 + ", ";
	            
	    		if(!address2.equals("")) 
	    			fullAddress += address2 + ", ";
	    		
	    		if(!address3.equals("")) 
	    			fullAddress += address3 + ", ";
	            
	            String num = rd.getString(TAG_NUM);
	            String email = rd.getString(TAG_EMAIL);
				url_menu = rd.getString(TAG_URL);
				if(url_menu == null){
					viewMenu.setEnabled(false);
					viewMenu.setVisibility(View.INVISIBLE);
				}
				/**
				 * Updating parsed JSON data into user interface
				 * */
				this.id = id; 
				restaurantNameTV.setText(name);
				restaurantType.setText(type);
				addressLine1TV.setText(address1);
				addressLine2TV.setText(address2);
				addressLine3TV.setText(address3);
				phoneNumTV.setText(num);
				emailTV.setText(email);
				bioTV.setText(bio);
			}

		} catch (JSONException e) {
			e.printStackTrace();
			error("Error parsing json");
		}
		
	}
		
}
