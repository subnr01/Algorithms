package admin;

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
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.DatabaseHandler_Saved_Restaurants;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class ManageActivity extends Activity {
	
	UserFunctions userFunctions;
	
	// xml Nodes
	private TextView restaurantNameTV;
	private TextView restaurantType;
	private TextView addressLine1TV;
	private TextView addressLine2TV;
	private TextView addressLine3TV;
	private TextView phoneNumTV;
	private TextView emailTV;
	private TextView bioTV;

	// private String id;
	// Progress Dialog
	private ProgressDialog pDialog;

	JSONParser jsonParser = new JSONParser();

	// private UserFunctions userFunctions;

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
	private static final String TAG_SUCCESS = "success";

	// url to make request
	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_restaurant_details_by_id.php";
	//private static String url_delete_rest = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/delete_restaurants_by_id.php";
	private static String url = "http://54.228.194.206/api/get_restaurant_details_by_id.php";
	private static String url_delete_rest = "http://54.228.194.206/api/delete_restaurants_by_id.php";
	
	JSONObject json;

 	JSONArray restaurantData = null;
 	
 	String name;
 	String fullAddress;
 	
 	//DATABASE SQLITE
 	private SQLiteDatabase mDb;
 	//private Cursor mCursor;
 	String id;
 	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_manage);
		
		userFunctions = new UserFunctions();
		
		//get id from selected item
		id = getIntent().getStringExtra("id");
		
		//get reference to ui elements
		restaurantNameTV = (TextView) findViewById(R.id.manageRestName);
		restaurantType = (TextView) findViewById(R.id.manageRestType);
		addressLine1TV = (TextView) findViewById(R.id.mantvAddress1);
		addressLine2TV = (TextView) findViewById(R.id.mantvAddress2);
		addressLine3TV = (TextView) findViewById(R.id.mantvAddress3);
		phoneNumTV = (TextView) findViewById(R.id.mantvPhone);
		emailTV = (TextView) findViewById(R.id.mantvEmail);
		bioTV = (TextView) findViewById(R.id.mantvBio);
		
		//async task to retrieve data and update user interface 	
		new LoadRestaurantDetails().execute();
		final DatabaseHandler_Saved_Restaurants mh = new DatabaseHandler_Saved_Restaurants(this);
		mDb = mh.getWritableDatabase();
		
		Button editBtn = (Button) findViewById(R.id.buttonEdit);
		editBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent in = new Intent(getApplicationContext(), EditRestaurantActivity.class);
				in.putExtra(TAG_ID, id);
				startActivity(in);
				overridePendingTransition(R.anim.slide_in_top,
						R.anim.slide_out_top);	
			}
		});
		
		Button deleteBtn = (Button) findViewById(R.id.buttonDelete);
		deleteBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// deleting restaurant in background thread
                new DeleteRestaurant().execute();
			}
		});
		
		Button manageDealsBtn = (Button) findViewById(R.id.buttonManageDeals);
		manageDealsBtn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(getApplicationContext(), ManageDealsListActivty.class);
				i.putExtra(TAG_ID, id);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_right,
						R.anim.slide_out_left);	
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

	
	
	@Override
    protected void onPause() {
    	// TODO Auto-generated method stub
    	super.onPause();
    	mDb.close();
    }
	
    @Override
    protected void onDestroy() {
    	// TODO Auto-generated method stub
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
    
    /**
	 * Background Async Task to Load all restaurant data by making
	 * HTTP Request
	 * */
	class LoadRestaurantDetails extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(ManageActivity.this);
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
	            String num = rd.getString(TAG_NUM);
	            String email = rd.getString(TAG_EMAIL);

				
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

	/*****************************************************************
     * Background Async Task to Delete Product
     * */
    class DeleteRestaurant extends AsyncTask<String, String, String> {
 
        /**
         * Before starting background thread Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(ManageActivity.this);
            pDialog.setMessage("Deleting Restaurant...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(true);
            pDialog.show();
        }
 
        /**
         * Deleting product
         * */
        protected String doInBackground(String... args) {
 
            // Check for success tag
            int success;
            try {
                // Building Parameters
                List<NameValuePair> params = new ArrayList<NameValuePair>();
                params.add(new BasicNameValuePair("id", id));
 
                // getting product details by making HTTP request
                JSONObject json = jsonParser.makeHttpRequest(
                        url_delete_rest, "POST", params);
 
                // check your log for json response
                //Log.d("Delete Product", json.toString());
 
                // json success tag
                success = json.getInt(TAG_SUCCESS);
                if (success == 1) {
                    // product successfully deleted
                	Intent i = new Intent(getApplicationContext(), ViewRestaurantActivity.class);
                    i.putExtra("MESSAGE", "delete");
                    i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    startActivity(i);
                    overridePendingTransition(R.anim.slide_in_right,
    						R.anim.slide_out_left);		
                    finish();

                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
 
            return null;
        }
 
        /**
         * After completing background task Dismiss the progress dialog
         * **/
        protected void onPostExecute(String file_url) {
            // dismiss the dialog once product deleted
            pDialog.dismiss();
 
        }
 
    }
}
