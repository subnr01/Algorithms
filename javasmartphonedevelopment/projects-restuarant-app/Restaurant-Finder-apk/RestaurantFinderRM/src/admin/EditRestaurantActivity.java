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
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class EditRestaurantActivity extends Activity {

	UserFunctions userFunctions;
	
	// Progress Dialog
    private ProgressDialog pDialog;
 
    // JSON parser class
    JSONParser jsonParser = new JSONParser();
 
    // single product url
    //private static final String url_rest_details = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_restaurant_details_by_id.php";
    // url to update product
    //private static final String url_update_rest = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/update_restaurant.php";
 
    private static final String url_rest_details = "http://54.228.194.206/api/get_restaurant_details_by_id.php";
    private static final String url_update_rest = "http://54.228.194.206/api/update_restaurant.php";
    
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
  	
  	String id;
  	
  	 EditText inputName;
     EditText inputType;
     EditText inputBio;
     EditText inputAddressLine1;
     EditText inputAddressLine2;
     EditText inputAddressLine3;
     EditText inputContactNum;
     EditText inputEmail;
     EditText inputMenuUrl;
     
     JSONObject json = null;
     
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_add_restaurant);
		
		userFunctions = new UserFunctions();

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
		
		Button btnUpdate = (Button) findViewById(R.id.btnCreateRestaurant);
		btnUpdate.setText("Update Restaurant");
		
		// getting product details from intent
        Intent i = getIntent();
 
        // getting product id (pid) from intent
        id = i.getStringExtra(TAG_ID);
 
        // Getting complete product details in background thread
        new GetRestDetails().execute();
		
		btnUpdate.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				if(inputName.getText().toString().trim().contentEquals("")
						||inputType.getText().toString().trim().contentEquals("")
						||inputBio.getText().toString().trim().contentEquals("")
						||inputAddressLine1.getText().toString().trim().contentEquals("")
						||inputAddressLine2.getText().toString().trim().contentEquals("")
						||inputContactNum.getText().toString().trim().contentEquals("")
						||inputEmail.getText().toString().trim().contentEquals("")
						||inputMenuUrl.getText().toString().trim().contentEquals(""))
				{
					AlertDialog.Builder alertDialog = new AlertDialog.Builder(EditRestaurantActivity.this);

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
					// starting background task to update product
	                new SaveRestDetails().execute();	
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
     * Background Async Task to Get complete restaurant details
     * */
    class GetRestDetails extends AsyncTask<String, String, String> {
 
        /**
         * Before starting background thread Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(EditRestaurantActivity.this);
            pDialog.setMessage("Loading Restaurant details. Please wait...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(true);
            pDialog.show();
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
                        JSONObject json = jsonParser.makeHttpRequest(
                                url_rest_details, "GET", params);
 
                        return json.toString();
        }
 
        /**
         * After completing background task Dismiss the progress dialog
         * **/
        protected void onPostExecute(final String jsonStr) {
            // dismiss the dialog once got all details
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

         						//error("There are no details for this restaurants");

         					}

         					try {
         						// Checking for SUCCES TAG
         						int success = json.getInt(TAG_SUCCESS);
                                if (success == 1) {
                                    // successfully received rest details
                                    JSONArray restObj = json
                                            .getJSONArray(TAG_RESTAURANT); // JSON Array
         
                                    // get first rest object from JSON Array
                                    JSONObject rest = restObj.getJSONObject(0);
         
                                    // rest with this id found
                                    // Edit Text set data
                                    inputName.setText(rest.getString(TAG_NAME));
                                    inputType.setText(rest.getString(TAG_TYPE));
                                    inputBio.setText(rest.getString(TAG_BIO));
                                    inputAddressLine1.setText(rest.getString(TAG_ADDRESS1));
                                    inputAddressLine2.setText(rest.getString(TAG_ADDRESS2));
                                    inputAddressLine3.setText(rest.getString(TAG_ADDRESS3));
                                    inputContactNum.setText(rest.getString(TAG_NUM));
                                    inputEmail.setText(rest.getString(TAG_EMAIL));
                                    inputMenuUrl.setText(rest.getString(TAG_URL));
         
                                }else{
                                    // rest with id not found
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
    class SaveRestDetails extends AsyncTask<String, String, String> {
 
        /**
         * Before starting background thread Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(EditRestaurantActivity.this);
            pDialog.setMessage("Saving Restaurant ...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(true);
            pDialog.show();
        }
 
        /**
         * Saving product
         * */
        protected String doInBackground(String... args) {
 
            // getting updated data from EditTexts
        	String name = inputName.getText().toString();
            String type = inputType.getText().toString();
            String bio = inputBio.getText().toString();
            String addressLine1 = inputAddressLine1.getText().toString();
            String addressLine2 = inputAddressLine2.getText().toString();
            String addressLine3 = inputAddressLine3.getText().toString();
            String phoneNum = inputContactNum.getText().toString();
            String email = inputEmail.getText().toString();
            String url = inputMenuUrl.getText().toString();
            
            // Building Parameters
            List<NameValuePair> params = new ArrayList<NameValuePair>();
            params.add(new BasicNameValuePair("restaurantID", id));
            params.add(new BasicNameValuePair("name", name));
            params.add(new BasicNameValuePair("type", type));
            params.add(new BasicNameValuePair("bio", bio));
            params.add(new BasicNameValuePair("addressLine1", addressLine1));
            params.add(new BasicNameValuePair("addressLine2", addressLine2));
            params.add(new BasicNameValuePair("addressLine3", addressLine3));
            params.add(new BasicNameValuePair("contactNumber", phoneNum));
            params.add(new BasicNameValuePair("email", email));
            params.add(new BasicNameValuePair("url", url));
            
            
            // sending modified data through http request
            // Notice that update product url accepts POST method
            JSONObject json = jsonParser.makeHttpRequest(url_update_rest,
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
    
    
}
