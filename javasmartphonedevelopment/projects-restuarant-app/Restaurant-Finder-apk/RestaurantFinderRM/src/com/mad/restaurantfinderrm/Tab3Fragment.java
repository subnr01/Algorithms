package com.mad.restaurantfinderrm;

import java.util.ArrayList;
import java.util.List;

import org.apache.http.NameValuePair;
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
import android.support.v4.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Spinner;


import com.mad.restaurantfinderrm.library.JSONParser;

public class Tab3Fragment extends Fragment {
	
	// Progress Dialog
	private ProgressDialog pDialog;
	// Progress Dialog
	private ProgressDialog pDialog2;
	// creating JSON Parser object
	JSONParser jParser = new JSONParser();
	
	//private static String url = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_restaurants.php";
	//private static String url_types = "http://192.168.0.10/~robertmcnamara/RestaurantFinderAPI/get_all_types.php";
	private static String url = "http://54.228.194.206/api/get_all_restaurants.php";
	private static String url_types = "http://54.228.194.206/api/get_all_types.php";
	
	Activity a;
	
	private JSONObject json;

	JSONArray restaurantData = null;
	JSONArray restaurantTypeData = null;
	
	private static final String TAG_RESTAURANT = "restaurant";
	private static final String TAG_ID = "id";
	private static final String TAG_NAME = "name";
	private static final String TAG_TYPE = "type";
	private static final String TAG_SUCCESS = "success";
	
	String[] rname;
	String[] rid;
	String[] type;
	
	Spinner spinner;
	AutoCompleteTextView A;
	
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		if (container == null) {
            // We have different layouts, and in one of them this
            // fragment's containing frame doesn't exist.  The fragment
            // may still be created from its saved state, but there is
            // no reason to try to create its view hierarchy because it
            // won't be displayed.  Note this is not needed -- we could
            // just run the code below, where we would create and return
            // the view hierarchy; it would just never be used.
            return null;
        }
		return (LinearLayout)inflater.inflate(R.layout.tab_frag3_layout, container, false);
	}
	
	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);
		
		a = getActivity();
		
		spinner = (Spinner) getActivity().findViewById(R.id.searchSpinner);
		A = (AutoCompleteTextView) getActivity().findViewById(R.id.searchAutoComplete);
		
		//load autocomplete view
		new LoadRestaurantNames().execute();
		
		new LoadTypes().execute();
		
		Button searchBtn = (Button) a.findViewById(R.id.searchButton);
		searchBtn.setOnClickListener(new OnClickListener() {
		//final ViewPager p = (ViewPager) getActivity().findViewById(R.id.viewpager);
			@Override
			public void onClick(View v) {
				// TODO get user input
				if(A.getText().toString().trim().isEmpty()){
					//error
					error("Please enter a Restaurant Name",false);
				}
				else{
				String RestaurantName = A.getText().toString();
				//Log.v("SEARCH REST NAME", RestaurantName);
				
				String type = spinner.getSelectedItem().toString();
				//Log.v("SEARCH Type", type);
				//pass info to restaurant fragment
                
				Bundle bundle = new Bundle();
				bundle.putString("REST_NAME", RestaurantName);
				bundle.putString("REST_TYPE", type);
                
				//TabsViewPagerFragmentActivity test = new TabsViewPagerFragmentActivity();
				Intent i = new Intent(a, SearchResults.class);
				i.putExtras(bundle);
				startActivity(i);
				a.overridePendingTransition(R.anim.slide_in_top, R.anim.slide_out_top);
				}
			}
		});
	}
	
	class LoadRestaurantNames extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog = new ProgressDialog(a);
			pDialog.setMessage("Loading Restaurant Data. Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			//params.add(new BasicNameValuePair("id", modelID));

			// getting JSON string from URL
			JSONObject json = jParser.makeHttpRequest(url, "GET", params);
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

						error("There are no Restaurants",true);

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
							// no technical data found
							//Log.v("ERROR", "No techdata");
							// display dialog and back to dashboard
							// Log.v("ERROR", "1");
							error("There is no Restaurants data for this model!",true);
						}
					} catch (JSONException e) {
						error("There has been an error please try again!",true);
						e.printStackTrace();
					}
				}
			});
		}
	}
	
	class LoadTypes extends AsyncTask<String, String, String> {
		
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			pDialog2 = new ProgressDialog(a);
			pDialog2.setMessage("Loading Restaurant Data. Please wait...");
			pDialog2.setIndeterminate(false);
			pDialog2.setCancelable(true);
			pDialog2.show();
		}

		@Override
		protected String doInBackground(String... args) {
			// Building Parameters
			List<NameValuePair> params = new ArrayList<NameValuePair>();
			//params.add(new BasicNameValuePair("id", modelID));

			// getting JSON string from URL
			JSONObject json = jParser.makeHttpRequest(url_types, "GET", params);
			// check log cat for JSON string from URL
			//Log.v("restaurantJSON: ", json.toString());

			// return json as string to using in the user interface
			return json.toString();
		}
		
		@Override
		protected void onPostExecute(final String jsonStr) {
			// dismiss the dialog after getting all products
			pDialog2.dismiss();

			
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

						error("There are no Restaurants",true);

					}

					try {
						// Checking for SUCCES TAG
						int success = json.getInt(TAG_SUCCESS);

						if (success == 1) {
							// restaurant found
							restaurantTypeData = json.getJSONArray(TAG_RESTAURANT);
							displayTypes(restaurantTypeData.toString());
						} else {
							error("There is no Restaurants data for this model!",true);
						}
					} catch (JSONException e) {
						error("There has been an error please try again!",true);
						e.printStackTrace();
					}
				}
			});
		}
		
	}
	
	public void error(String error, boolean flag) {
		AlertDialog.Builder builder = new AlertDialog.Builder(
				a);
		// todo set icon
		builder.setTitle("Error");
		builder.setMessage(error);
		builder.setCancelable(false);
		if(flag==true){
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
		else{
			builder.setPositiveButton("OK", null);
		AlertDialog alert = builder.create();
		alert.show();
		
		}
	}

	public void displayTechData(String result) {
		// Log.v("techdata: ", "display");
		JSONArray restaurantData = null;
		
		try {
			
			restaurantData = new JSONArray(result);

			rname = new String[restaurantData.length()];
			rid = new String[restaurantData.length()];
			// looping through all technical data
			for (int i = 0; i < restaurantData.length(); i++) {
				JSONObject td = restaurantData.getJSONObject(i);

				// Storing each json item in variable
				String id = td.getString(TAG_ID);
				rid[i] = id;
				
				String name = td.getString(TAG_NAME);
				rname[i] = name;
			}

		} catch (JSONException e) {
			e.printStackTrace();
			error("Error parsing json",true);
		}

		// add to list view
		/**
		 * Updating parsed JSON data into ListView
		 * */
		 ArrayAdapter<String> adapter = new ArrayAdapter<String>(getActivity().getApplicationContext(),
	                R.layout.simplespinneritem, rname);
		    
		    A = (AutoCompleteTextView) getActivity().findViewById(R.id.searchAutoComplete);
		    A.setAdapter(adapter);
	}
	
	public void displayTypes(String result) {
		// Log.v("techdata: ", "display");
		JSONArray restaurantData = null;
		
		try {
			
			restaurantData = new JSONArray(result);

			type = new String[restaurantTypeData.length()+1];
			type[0] = "All";
			int jsonCount = 0;
			for(int i=1;i<restaurantTypeData.length()+1;i++){
				
				JSONObject td = restaurantData.getJSONObject(jsonCount);

				// Storing each json item in variable
				String types = td.getString(TAG_TYPE);
				type[i] = types;
				jsonCount++;
			}
			
			
			
		} catch (JSONException e) {
			e.printStackTrace();
			error("Error parsing json", true);
		}

		// add to list view
		/**
		 * Updating parsed JSON data into ListView
		 * */
	    ArrayAdapter<String> spinnerArrayAdapter = new ArrayAdapter<String>(
	            getActivity().getApplicationContext(), R.layout.simplespinneritem, type);
	   spinner.setAdapter(spinnerArrayAdapter);

	}
	
}


