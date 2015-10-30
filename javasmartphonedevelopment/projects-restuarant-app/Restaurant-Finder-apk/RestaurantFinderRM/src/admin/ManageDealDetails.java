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
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.TabsViewPagerFragmentActivity;
import com.mad.restaurantfinderrm.library.JSONParser;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class ManageDealDetails extends Activity {

	UserFunctions userFunctions;
	
	//var for linking id to restaurant details
	String restaurantID;
	
	//xml nodes
	private TextView dealNameTV;
	private TextView restNameTV;
	private TextView descriptionTV;
	private TextView priceTV;
	
	String id;
	
	// Progress Dialog
    private ProgressDialog pDialog;
 
    JSONParser jsonParser = new JSONParser();
    
    // url to make request
 	//private static String urlDeals = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_deals_by_deal_id.php";
 	//private static String url_delete_deal = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/delete_deal_by_id.php";
 	private static String urlDeals = "http://54.228.194.206/api/get_all_deals_by_deal_id.php";
 	private static String url_delete_deal = "http://54.228.194.206/api/delete_deal_by_id.php";
    
    private JSONObject json;

 	JSONArray dealData = null;
 	

 	// JSON Node names
 	private static final String TAG_DEALS = "deals";
 	//private static final String TAG_ID = "id";
 	private static final String TAG_DEALNAME = "dealName";
 	private static final String TAG_PRICE = "price";
 	private static final String TAG_DESCRIPTION = "description";
 	private static final String TAG_RESTID = "restID";
 	private static final String TAG_RESTNAME = "restName";
 	private static final String TAG_SUCCESS = "success";
 	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_deal_details);
		
		userFunctions = new UserFunctions();

		LinearLayout ll = (LinearLayout) findViewById(R.id.llDealsButton);
		ll.setVisibility(View.VISIBLE);
		
		//getting id from selected deal
		id = getIntent().getStringExtra("ID");
		//Log.v("id", id);
		
		//getting reference to ui elements
		dealNameTV = (TextView) findViewById(R.id.dealName);
		restNameTV = (TextView) findViewById(R.id.dealRestName);
		descriptionTV = (TextView) findViewById(R.id.descriptionTV);
		priceTV = (TextView) findViewById(R.id.priceTV);
		
		new LoadDealDetails().execute();
		
		
		//reference to edit and delete buttons
		Button edit = (Button) findViewById(R.id.buttonEditDeal);
		edit.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(getApplicationContext(), EditDealActivity.class);
				i.putExtra("id", id);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_right,
						R.anim.slide_out_left);	
			}
		});
		
		Button delete = (Button) findViewById(R.id.buttonDeleteDeal);
		delete.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				new DeleteDeal().execute();
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
	class LoadDealDetails extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(ManageDealDetails.this);
			pDialog.setMessage("Deals. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			params.add(new BasicNameValuePair("id", id));
			Log.v("DEALS", id);
			// getting JSON string from URL
			JSONObject json = jsonParser.makeHttpRequest(urlDeals, "GET", params);
			// check log cat for JSON string from URL
			Log.v("restaurantDeals: ", json.toString());

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

						error("There are no info on this deal");

					}

					try {
						// Checking for SUCCES TAG
						int success = json.getInt(TAG_SUCCESS);

						if (success == 1) {
							// deal found
							// Getting Array of deals
							dealData = json.getJSONArray(TAG_DEALS);
							displayDeals(dealData.toString());
						} else {
							// no technical data found
							//Log.v("ERROR", "No techdata");
							// display dialog and back to dashboard
							// Log.v("ERROR", "1");
							error("There is no Deal data available!");
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
				ManageDealDetails.this);
		// Log.v("ERROR", "3");
		builder.setTitle("Error");
		builder.setMessage(error);
		builder.setCancelable(false);
		builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int id) {
				// Log.v("TEST", "1");
				Intent i = new Intent(getApplicationContext(),
						TabsViewPagerFragmentActivity.class);
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
			restaurantDealsData = new JSONArray(result);
			// looping through all deal data
			for (int i = 0; i < restaurantDealsData.length(); i++) {
				JSONObject td = restaurantDealsData.getJSONObject(i);
				// Storing each json item in variable
				//String id = td.getString(TAG_ID);
				String name = td.getString(TAG_DEALNAME);
				String price = td.getString(TAG_PRICE);
				String description = td.getString(TAG_DESCRIPTION);
				restaurantID = td.getString(TAG_RESTID);
				String restaurantName = td.getString(TAG_RESTNAME);
				//String restaurantType = td.getString(TAG_RESTTYPE);
				//String lat = td.getString(TAG_LAT);
				
				//String lng = td.getString(TAG_LNG);
				/**
				 * Updating parsed JSON data into user interface
				 * */
				dealNameTV.setText(name);
				restNameTV.setText(restaurantName);
				descriptionTV.setText(description);
				priceTV.setText("€" + price);
			}

		} catch (JSONException e) {
			e.printStackTrace();
			error("Error parsing json");
		}
	}
	
	/*****************************************************************
     * Background Async Task to Delete Product
     * */
    class DeleteDeal extends AsyncTask<String, String, String> {
 
        /**
         * Before starting background thread Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(ManageDealDetails.this);
            pDialog.setMessage("Deleting Deal...");
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
                        url_delete_deal, "POST", params);
 
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