package admin;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.location.Address;
import android.location.Geocoder;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.DatabaseHandler;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class AddRestaurantActivity extends Activity {

	UserFunctions userFunctions;

	// Progress Dialog
	private ProgressDialog pDialog;

	JSONParser jsonParser = new JSONParser();
	EditText inputName;
	EditText inputType;
	EditText inputBio;
	EditText inputAddressLine1;
	EditText inputAddressLine2;
	EditText inputAddressLine3;
	EditText inputContactNum;
	EditText inputEmail;
	EditText inputMenuUrl;

	// url to create new Restaurant

	// private static String url_create_restaurant =
	// "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/createRestaurant.php";
	private static String url_create_restaurant = "http://54.228.194.206/api/createRestaurant.php";

	// JSON Node names
	private static final String TAG_SUCCESS = "success";

	static Double lat;
	static Double lng;

	// DB
	private SQLiteDatabase mDb;
	private Cursor mCursor;
	String user_id;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_add_restaurant);

		userFunctions = new UserFunctions();

		// getting user_id
		DatabaseHandler mh = new DatabaseHandler(getApplicationContext());
		mDb = mh.getWritableDatabase();
		mCursor = mDb.query("login", null, null, null, null, null, null);

		if (mCursor != null && mCursor.getCount() > 0) {
			mCursor.moveToFirst();
			user_id = mCursor.getString(mCursor.getColumnIndex("uid"));
		}

		// Edit Text
		inputName = (EditText) findViewById(R.id.inputName);
		inputType = (EditText) findViewById(R.id.inputType);
		inputBio = (EditText) findViewById(R.id.inputBio);
		inputAddressLine1 = (EditText) findViewById(R.id.inputAddress1);
		inputAddressLine2 = (EditText) findViewById(R.id.inputAddress2);
		inputAddressLine3 = (EditText) findViewById(R.id.inputAddress3);
		inputContactNum = (EditText) findViewById(R.id.inputContactNum);
		inputEmail = (EditText) findViewById(R.id.inputEmail);
		inputMenuUrl = (EditText) findViewById(R.id.inputMenuUrl);

		// Create button
		Button btnCreateRestaurant = (Button) findViewById(R.id.btnCreateRestaurant);

		// button click event
		btnCreateRestaurant.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View view) {
				if (inputName.getText().toString().trim().contentEquals("")
						|| inputType.getText().toString().trim()
								.contentEquals("")
						|| inputBio.getText().toString().trim()
								.contentEquals("")
						|| inputAddressLine1.getText().toString().trim()
								.contentEquals("")
						|| inputAddressLine2.getText().toString().trim()
								.contentEquals("")
						|| inputContactNum.getText().toString().trim()
								.contentEquals("")
						|| inputEmail.getText().toString().trim()
								.contentEquals("")
						|| inputMenuUrl.getText().toString().trim()
								.contentEquals("")) {
					AlertDialog.Builder alertDialog = new AlertDialog.Builder(
							AddRestaurantActivity.this);

					// Setting Dialog Title
					alertDialog.setTitle("Input validation");

					// Setting Dialog Message
					alertDialog
							.setMessage("Please enter all details again,\nmaking sure they are correct");

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
				} else {
					// creating new product in background thread
					new CreateNewRestaurant().execute();
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
	 * Event Handling for Individual menu item selected Identify single menu
	 * item by it's id
	 */
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {

		switch (item.getItemId()) {
		case R.id.menu_logout:
			// logout user
			// TODO check Internet here?
			userFunctions.logoutUser(getApplicationContext());
			Intent login = new Intent(getApplicationContext(),
					LoginActivity.class);
			login.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
			startActivity(login);
			overridePendingTransition(R.anim.fade_in, R.anim.fade_out);
			// Closing dashboard screen
			finish();
			return true;
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	/**
	 * Background Async Task to Create new Restaurant
	 * */
	class CreateNewRestaurant extends AsyncTask<String, String, String> {

		/**
		 * Before starting background thread Show Progress Dialog
		 * */
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(AddRestaurantActivity.this);
			pDialog.setMessage("Creating Restaurant..");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		/**
		 * Creating Restaurant
		 * */
		protected String doInBackground(String... args) {
			String name = inputName.getText().toString();
			String type = inputType.getText().toString();
			String bio = inputBio.getText().toString();
			String addressLine1 = inputAddressLine1.getText().toString();
			String addressLine2 = inputAddressLine2.getText().toString();
			String addressLine3 = inputAddressLine3.getText().toString();
			String phoneNum = inputContactNum.getText().toString();
			String email = inputEmail.getText().toString();
			String menuUrl = inputMenuUrl.getText().toString();

			// img
			// String img = "";

			String fullAddress = name + ", " + addressLine1 + ", "
					+ addressLine2 + ", " + addressLine3;
			Geocoder geoCoder = new Geocoder(getApplicationContext());
			List<Address> addressList;
			try {
				addressList = geoCoder.getFromLocationName(fullAddress, 1);
				Address address = addressList.get(0);
				if (address.hasLatitude() && address.hasLongitude()) {
					lat = address.getLatitude();
					lng = address.getLongitude();
				}
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

			Log.v("LAT", lat.toString());
			Log.v("LNG", lng.toString());

			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			params.add(new BasicNameValuePair("name", name));
			params.add(new BasicNameValuePair("type", type));
			params.add(new BasicNameValuePair("bio", bio));
			params.add(new BasicNameValuePair("addressLine1", addressLine1));
			params.add(new BasicNameValuePair("addressLine2", addressLine2));
			params.add(new BasicNameValuePair("addressLine3", addressLine3));
			params.add(new BasicNameValuePair("contactNumber", phoneNum));
			params.add(new BasicNameValuePair("email", email));
			params.add(new BasicNameValuePair("lat", lat.toString()));
			params.add(new BasicNameValuePair("lng", lng.toString()));
			params.add(new BasicNameValuePair("url", menuUrl));
			params.add(new BasicNameValuePair("user_id", user_id));
			// getting JSON Object
			// Note that create product url accepts POST method
			JSONObject json = jsonParser.makeHttpRequest(url_create_restaurant,
					"POST", params);

			// check for success tag
			try {
				int success = json.getInt(TAG_SUCCESS);

				if (success == 1) {
					// successfully created product
					Intent i = new Intent(getApplicationContext(),
							ViewRestaurantActivity.class);
					i.putExtra("MESSAGE", "add");
					i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
					startActivity(i);
					overridePendingTransition(R.anim.slide_in_top,
							R.anim.slide_out_bottom);
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
