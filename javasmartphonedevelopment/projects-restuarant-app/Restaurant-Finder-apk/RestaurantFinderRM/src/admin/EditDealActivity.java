package admin;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.TabsViewPagerFragmentActivity;
import com.mad.restaurantfinderrm.library.DatabaseHandler;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;

public class EditDealActivity extends Activity {

	UserFunctions userFunctions;
	
	// Progress Dialog
	private ProgressDialog pDialog;
	private ProgressDialog pDialog1;

	// JSON parser class
	JSONParser jsonParser = new JSONParser();

	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_rest_by_user_id.php";
	//private static final String url_deal_details = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_deals_by_deal_id.php";
	//private static final String url_update_deal = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/update_deal.php";

	private static String url = "http://54.228.194.206/api/get_rest_by_user_id.php";
	private static final String url_deal_details = "http://54.228.194.206/api/get_all_deals_by_deal_id.php";
	private static final String url_update_deal = "http://54.228.194.206/api/update_deal.php";

	JSONObject json = null;

	// JSON Node names
	private static final String TAG_RESTAURANT = "restaurant";
	private static final String TAG_DEAL = "deals";
	private static final String TAG_ID = "id";
	private static final String TAG_NAME = "dealName";
	private static final String TAG_PRICE = "price";
	private static final String TAG_DESC = "description";
	private static final String TAG_SUCCESS = "success";

	// ui nodes
	private EditText dealNameTV;
	private Spinner restName;
	private EditText description;
	private EditText price;
	private Button edit;

	private String user_id;

	private SQLiteDatabase mDb;
	private Cursor mCursor;

	private String id;
	
	private JSONArray restaurantData = null;
	private String[] restaurant_array;
	private String[] restaurantID;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_add_deal);

		userFunctions = new UserFunctions();
		
		// first get user_id
		DatabaseHandler mh = new DatabaseHandler(getApplicationContext());
		mDb = mh.getWritableDatabase();
		mCursor = mDb.query("login", null, null, null, null, null, null);

		if (mCursor != null && mCursor.getCount() > 0) {
			mCursor.moveToFirst();
			user_id = mCursor.getString(mCursor.getColumnIndex("uid"));
		}

		// get reference to ui elements
		dealNameTV = (EditText) findViewById(R.id.inputDealName);
		restName = (Spinner) findViewById(R.id.dealRestNameSpinner);
		description = (EditText) findViewById(R.id.inputDealDescription);
		price = (EditText) findViewById(R.id.inputDealPrice);

		// getting product details from intent
		Intent i = getIntent();

		// getting product id (pid) from intent
		id = i.getStringExtra(TAG_ID);
		new LoadRest().execute();
		edit = (Button) findViewById(R.id.btnCreateDeal);
		edit.setText("Update Deal");

		// Getting complete product details in background thread
		new GetDealDetails().execute();

		edit.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if(dealNameTV.getText().toString().trim().contentEquals("")
						|| description.getText().toString().trim().contentEquals("")
						|| price.getText().toString().trim().contentEquals("")){
					AlertDialog.Builder alertDialog = new AlertDialog.Builder(EditDealActivity.this);

					// Setting Dialog Title
					alertDialog.setTitle("Input validation");

					// Setting Dialog Message
					alertDialog.setMessage("Please enter all details again,\nmaking sure they are correct");

					// Setting Icon to Dialog
					// alertDialog.setIcon(android.R.drawable.delete);

					// Setting Positive "Yes" Button
					alertDialog.setPositiveButton("OK",
							new DialogInterface.OnClickListener() {
								public void onClick(DialogInterface dialog,
										int which) {
									dialog.cancel();
								}
							});

					// Showing Alert Message
					alertDialog.show();
				}
				else{
					// insert async task
					new SaveDealDetails().execute();
				}
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
	 * Background Async Task to Get complete deal details
	 * */
	class GetDealDetails extends AsyncTask<String, String, String> {

		/**
		 * Before starting background thread Show Progress Dialog
		 * */
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog1 = new ProgressDialog(EditDealActivity.this);
			pDialog1.setMessage("Loading Deal details. Please wait...");
			pDialog1.setIndeterminate(false);
			pDialog1.setCancelable(true);
			pDialog1.show();
		}

		/**
		 * Getting product details in background thread
		 * */
		protected String doInBackground(String... args) {

			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			params.add(new BasicNameValuePair("id", id));

			// getting product details by making HTTP request
			// Note that product details url will use GET request
			JSONObject json = jsonParser.makeHttpRequest(url_deal_details,
					"GET", params);

			return json.toString();
		}

		/**
		 * After completing background task Dismiss the progress dialog
		 * **/
		protected void onPostExecute(final String jsonStr) {
			// dismiss the dialog once got all details
			pDialog1.dismiss();

			// updating UI from Background Thread
			runOnUiThread(new Runnable() {
				@Override
				public void run() {
					try {
						json = new JSONObject(jsonStr);
					} catch (JSONException e1) {
						// print error message to log
						e1.printStackTrace();

						// error("There are no details for this restaurants");

					}

					try {
						// Checking for SUCCES TAG
						int success = json.getInt(TAG_SUCCESS);
						if (success == 1) {
							// successfully received rest details
							JSONArray restObj = json
									.getJSONArray(TAG_DEAL); // JSON Array

							// get first rest object from JSON Array
							JSONObject rest = restObj.getJSONObject(0);

							// DEAL with this id found
							// Edit Text set data
							dealNameTV.setText(rest.getString(TAG_NAME));
							price.setText(rest.getString(TAG_PRICE));
							description.setText(rest.getString(TAG_DESC));
							restName.setSelection(Integer.parseInt(rest.getString(TAG_RESTAURANT)));
							
							
						} else {
							// deal with id not found
						}
					} catch (JSONException e) {
						e.printStackTrace();
					}
				}
			});
		}
	}
	
	/**
     * Background Async Task to  Save restaurant Details
     * */
    class SaveDealDetails extends AsyncTask<String, String, String> {
 
        /**
         * Before starting background thread Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(EditDealActivity.this);
            pDialog.setMessage("Saving Deal ...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(true);
            pDialog.show();
        }
 
        /**
         * Saving product
         * */
        protected String doInBackground(String... args) {
 
        	String nameStr = dealNameTV.getText().toString();
        	//String restid = restName.getSe
        	String priceStr = price.getText().toString();
        	String descriptionStr = description.getText().toString();
            
            // Building Parameters
        	List<NameValuePair> params = new ArrayList<NameValuePair>();
            params.add(new BasicNameValuePair("id", id));
            params.add(new BasicNameValuePair("restaurantID", restaurantID[restName.getSelectedItemPosition()].toString()));
            params.add(new BasicNameValuePair("dealName", nameStr));
            params.add(new BasicNameValuePair("price", priceStr));
            params.add(new BasicNameValuePair("description", descriptionStr));
            
            
            // sending modified data through http request
            // Notice that update product url accepts POST method
            JSONObject json = jsonParser.makeHttpRequest(url_update_deal,
                    "POST", params);
 
            // check json success tag
            try {
                int success = json.getInt(TAG_SUCCESS);
 
                if (success == 1) {
                    // successfully updated
                    Intent i = new Intent(getApplicationContext(), ViewRestaurantActivity.class);
                    i.putExtra("MESSAGE", "edit");
                    i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    startActivity(i);
                    overridePendingTransition(R.anim.slide_in_right,
    						R.anim.slide_out_left);
                    finish();
                } else {
                    // failed to update product
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
            // dismiss the dialog once product uupdated
            pDialog.dismiss();
        }
    }
    
    public void error(String error) {
		// Log.v("ERROR", "2");
		AlertDialog.Builder builder = new AlertDialog.Builder(EditDealActivity.this);
		// Log.v("ERROR", "3");
		// todo set icon
		builder.setTitle("Error");
		builder.setMessage(error);
		builder.setCancelable(false);
		builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int id) {
				// Log.v("TEST", "1");
				Intent i = new Intent(getApplicationContext(),
						TabsViewPagerFragmentActivity.class);
				overridePendingTransition(R.anim.fade_in,
						R.anim.fade_out);
				i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
				startActivity(i);
				finish();

			}
		});
		AlertDialog alert = builder.create();
		alert.show();
	}

	/**
	 * Background Async Task to Load rests names in spinner
	 * HTTP Request
	 * */
	class LoadRest extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(EditDealActivity.this);
			pDialog.setMessage("Loading Deals. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			params.add(new BasicNameValuePair("id", user_id));

			// getting JSON string from URL
			JSONObject json = jsonParser.makeHttpRequest(url, "GET", params);
			// check log cat for JSON string from URL
		//	Log.v("restaurantJSON USER ID: ", json.toString());

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

						error("There are no Restaurants");

					}

					try {
						// Checking for SUCCES TAG
						int success = json.getInt(TAG_SUCCESS);

						if (success == 1) {
							// restaurant found
							// Getting Array of restaurant
							restaurantData = json.getJSONArray(TAG_RESTAURANT);
							displayTechData(restaurantData.toString());
						} else {

							error("There is no Restaurants data for this model!");
						}
					} catch (JSONException e) {
						error("There has been an error please try again!");
						e.printStackTrace();
					}
				}
			});
		}
	}
	
	public void displayTechData(String result) {
		// Log.v("techdata: ", "display");
		JSONArray restaurantData = null;
		
		try {
			
			restaurantData = new JSONArray(result);
			//Log.v("TEST json", restaurantData.toString());
			restaurant_array = new String[restaurantData.length()];
			restaurantID = new String[restaurantData.length()];
			// 
			for (int i = 0; i < restaurantData.length(); i++) {
				restaurant_array[i] = restaurantData.getJSONObject(i)
						.getString("name");
				restaurantID[i] = restaurantData.getJSONObject(i)
						.getString(TAG_ID);
			}


			// setting model adapter
			ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
					android.R.layout.simple_spinner_item, restaurant_array);
			adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
			restName.setAdapter(adapter);
			//restName.setSelection(1);
	
		} catch (JSONException e) {
			e.printStackTrace();
			error("Error parsing json");
		}

	}
	
}
