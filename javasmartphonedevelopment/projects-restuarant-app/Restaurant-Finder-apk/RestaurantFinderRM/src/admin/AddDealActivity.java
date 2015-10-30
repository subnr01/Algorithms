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
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.TabsViewPagerFragmentActivity;
import com.mad.restaurantfinderrm.library.DatabaseHandler;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class AddDealActivity extends Activity {

	UserFunctions userFunctions;

	private EditText dealNameTV;
	private Spinner restName;
	private EditText description;
	private EditText price;
	private Button add;

	// Progress Dialog
	private ProgressDialog pDialog;

	// Creating JSON Parser object
	private JSONParser jParser = new JSONParser();
	private JSONParser jsonParser = new JSONParser();


	// url to get all products list
	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_rest_by_user_id.php";
	//private static String url_create_deal = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/create_new_deal.php";
	private static String url = "http://54.228.194.206/api/get_rest_by_user_id.php";
	private static String url_create_deal = "http://54.228.194.206/api/create_new_deal.php";
	
	// JSON Node names
	private static final String TAG_RESTAURANT = "restaurant";
	private static final String TAG_ID = "id";
	private static final String TAG_NAME = "name";
	private static final String TAG_SUCCESS = "success";

	
	private JSONObject json;
	JSONObject obj;

	private JSONArray restaurantData = null;

	private String[] restaurant_array;
	private String[] restaurantID;
	
	private String user_id;

	private SQLiteDatabase mDb;
	private Cursor mCursor;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_add_deal);

		userFunctions = new UserFunctions();
		
		// load spinner
		// first get user_id
		DatabaseHandler mh = new DatabaseHandler(getApplicationContext());
		mDb = mh.getWritableDatabase();
		mCursor = mDb.query("login", null, null, null, null, null, null);

		if (mCursor != null && mCursor.getCount() > 0) {
			mCursor.moveToFirst();
			user_id = mCursor.getString(mCursor.getColumnIndex("uid"));
		}
		// make a request to get restaurant with user_id;
		new LoadRest().execute();

		// get reference to ui elements
		dealNameTV = (EditText) findViewById(R.id.inputDealName);
		restName = (Spinner) findViewById(R.id.dealRestNameSpinner);
		description = (EditText) findViewById(R.id.inputDealDescription);
		price = (EditText) findViewById(R.id.inputDealPrice);
		add = (Button) findViewById(R.id.btnCreateDeal);

		add.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// insert async task
				if(dealNameTV.getText().toString().trim().contentEquals("")
						|| description.getText().toString().trim().contentEquals("")
						|| price.getText().toString().trim().contentEquals("")){
					AlertDialog.Builder alertDialog = new AlertDialog.Builder(AddDealActivity.this);

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
					new CreateDeal().execute();
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
	 * Background Async Task to Load all technical data for a model by making
	 * HTTP Request
	 * */
	class LoadRest extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(AddDealActivity.this);
			pDialog.setMessage("Loading Restaurants. Please wait...");
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
			JSONObject json = jParser.makeHttpRequest(url, "GET", params);
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

	public void error(String error) {
		// Log.v("ERROR", "2");
		AlertDialog.Builder builder = new AlertDialog.Builder(AddDealActivity.this);
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
				
				// set transition
				Toast.makeText(getApplicationContext(), "You clicked on OK",
						Toast.LENGTH_SHORT).show();

			}
		});
		AlertDialog alert = builder.create();
		alert.show();
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
						.getString(TAG_NAME);
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
	
	/**
     * Background Async Task to Create new Restaurant
     * */
    class CreateDeal extends AsyncTask<String, String, String> {
 
        /**
         * Before starting background thread Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(AddDealActivity.this);
            pDialog.setMessage("Creating Deal..");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(true);
            pDialog.show();
        }
 
        /**
         * Creating Restaurant
         * */
        protected String doInBackground(String... args) {
        	//Log.v("TEST", "1");
            String nameStr = dealNameTV.getText().toString();
           // Log.v("TEST NAME", nameStr);
            //Log.v("TEST", "2");
            String priceStr = price.getText().toString();
            //Log.v("TEST price", priceStr);
            //Log.v("TEST", "3");
            String descriptionStr = description.getText().toString();
           // Log.v("TEST des", descriptionStr);
           // Log.v("TEST rid", restaurantID[restName.getSelectedItemPosition()]);
          //  Log.v("TEST uid", user_id);
            
            
            
            
            // Building Parameters
            List<NameValuePair> params1 = new ArrayList<NameValuePair>();
            params1.add(new BasicNameValuePair("user_id", user_id));
            params1.add(new BasicNameValuePair("restaurantID", restaurantID[restName.getSelectedItemPosition()].toString()));
            params1.add(new BasicNameValuePair("dealName", nameStr));
            params1.add(new BasicNameValuePair("price", priceStr));
            params1.add(new BasicNameValuePair("description", descriptionStr));
            Log.v("URL", url_create_deal);
            
            // getting JSON Object
            // Note that create product url accepts POST method
            obj = jsonParser.makeHttpRequest(url_create_deal,
                    "GET", params1);
            
            // check log cat fro response
 
            // check for success tag
            try {
                int success = obj.getInt(TAG_SUCCESS);
 
                if (success == 1) {
                    // successfully created product
                    Intent i = new Intent(getApplicationContext(), ViewRestaurantActivity.class);
                    i.putExtra("MESSAGE", "add");
                    i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                    startActivity(i);
                    overridePendingTransition(R.anim.slide_in_right,
    						R.anim.slide_out_left);
                    // closing this screen
                    finish();
                } else {
                    // failed to create product
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
            // dismiss the dialog once done
            pDialog.dismiss();
        }
 
    }
	

}
