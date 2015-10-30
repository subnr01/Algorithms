package admin;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.http.NameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.DatabaseHandler;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class ViewRestaurantActivity extends Activity {

	UserFunctions userFunctions;
	
	// Progress Dialog
	private ProgressDialog pDialog;

	// Creating JSON Parser object
	JSONParser jParser = new JSONParser();

	ArrayList<HashMap<String, String>> restList;

	// url to get all products list
	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_restaurants.php";
	private static String url = "http://54.228.194.206/api/get_all_restaurants.php";
	
	// JSON Node names
	private static final String TAG_RESTAURANT = "restaurant";
	private static final String TAG_ID = "id";
	private static final String TAG_NAME = "name";
	private static final String TAG_USERID = "user_id";
	private static final String TAG_SUCCESS = "success";

	// products JSONArray
	JSONArray restaurants = null;

	ListView lv;

	// DB
	private SQLiteDatabase mDb;
	private Cursor mCursor;
	String user_id;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_view_restaurant);

		userFunctions = new UserFunctions();
		
		// getting user_id
		DatabaseHandler mh = new DatabaseHandler(getApplicationContext());
		mDb = mh.getWritableDatabase();
		mCursor = mDb.query("login", null, null, null, null, null, null);

		if (mCursor != null && mCursor.getCount() > 0) {
			mCursor.moveToFirst();
			user_id = mCursor.getString(mCursor.getColumnIndex("uid"));
		}

		if (getIntent().getStringExtra("MESSAGE") != null) {
			if (getIntent().getStringExtra("MESSAGE").contentEquals("add")) {
				Toast.makeText(this, "Add Successful", Toast.LENGTH_LONG)
						.show();
			}
			if (getIntent().getStringExtra("MESSAGE").contentEquals("delete")) {
				Toast.makeText(this, "Delete Successful", Toast.LENGTH_LONG)
						.show();
			}
			if (getIntent().getStringExtra("MESSAGE").contentEquals("edit")) {
				Toast.makeText(this, "Update Successful", Toast.LENGTH_LONG)
						.show();
			}
		}

		// Hashmap for ListView
		restList = new ArrayList<HashMap<String, String>>();

		// Loading products in Background Thread
		new LoadAllRest().execute();

		// Get listview
		lv = (ListView) findViewById(R.id.viewRestlist);

		// listener for user clicking on lick view
		lv.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				// getting values from selected ListItem
				TextView id = (TextView) arg1.findViewById(R.id.rid);
				String rid = id.getText().toString();

				// Starting new intent
				Intent in = new Intent(getApplicationContext(),
						ManageActivity.class);
				// sending pid to next activity
				in.putExtra(TAG_ID, rid);
				startActivity(in);
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

	
	/**
	 * Background Async Task to Load all restaurants by making HTTP Request
	 * */
	class LoadAllRest extends AsyncTask<String, String, String> {

		/**
		 * Before starting background thread Show Progress Dialog
		 * */
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(ViewRestaurantActivity.this);
			pDialog.setMessage("Loading Restaurant. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		/**
		 * getting All products from url
		 * */
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			// getting JSON string from URL
			JSONObject json = jParser.makeHttpRequest(url, "GET", params);

			// Check your log cat for JSON reponse
			// Log.d("All Products: ", json.toString());

			try {
				// Checking for SUCCESS TAG
				int success = json.getInt(TAG_SUCCESS);

				if (success == 1) {
					// products found
					// Getting Array of Products
					restaurants = json.getJSONArray(TAG_RESTAURANT);

					// looping through All Products
					for (int i = 0; i < restaurants.length(); i++) {
						JSONObject c = restaurants.getJSONObject(i);

						// Storing each json item in variable
						String id = c.getString(TAG_ID);
						String name = c.getString(TAG_NAME);
						String user_idjson = c.getString(TAG_USERID);
						// creating new HashMap
						HashMap<String, String> map = new HashMap<String, String>();
						if(user_id.contentEquals(user_idjson)){
						// adding each child node to HashMap key => value
						map.put(TAG_ID, id);
						map.put(TAG_NAME, name);
						// adding HashList to ArrayList
						restList.add(map);
						}
						
					}
				} else {
					// no products found
					// Launch Add New restaurant Activity
					Intent i = new Intent(getApplicationContext(),
							AddRestaurantActivity.class);
					// Closing all previous activities
					i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					startActivity(i);
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
			// dismiss the dialog after getting all products
			pDialog.dismiss();
			// updating UI from Background Thread
			runOnUiThread(new Runnable() {
				public void run() {
					/**
					 * Updating parsed JSON data into ListView
					 * */
					ListAdapter adapter = new SimpleAdapter(
							ViewRestaurantActivity.this, restList,
							R.layout.rest_list_tem, new String[] { TAG_ID,
									TAG_NAME }, new int[] { R.id.rid,
									R.id.viewRestName });
					// updating listview
					lv.setAdapter(adapter);
					TextView tv = (TextView) findViewById(R.id.noRestTextView);
					
					if(restList.size()<1){
						tv.setVisibility(View.VISIBLE);
					}
				}
			});
			

		}

	}

}
