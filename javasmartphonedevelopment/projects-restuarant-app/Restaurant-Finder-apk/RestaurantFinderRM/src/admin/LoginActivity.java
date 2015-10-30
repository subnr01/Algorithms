package admin;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.ConnectionDetector;
import com.mad.restaurantfinderrm.library.DatabaseHandler;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class LoginActivity extends Activity {
	// flag for Internet connection status
	private Boolean isInternetPresent = false;

	// Connection detector class
	ConnectionDetector cd;

	// Progress Dialog
	private ProgressDialog pDialog;
	
	private EditText inputEmail;
	private EditText inputPassword;
	private TextView errorMessage;
	private Button registerButton;
	private Button loginButton;
	
	// variable for storing activities data
	private String email;
	private String password;
	
	//flag variable
	private String success;
	
	// JSON Response node names
	private static String KEY_SUCCESS = "success";
	private static String KEY_UID = "id";
	private static String KEY_NAME = "name";
	private static String KEY_EMAIL = "email";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_login);

		// creating connection detector class instance
		cd = new ConnectionDetector(getApplicationContext());
				
		// import all assets
		inputEmail = (EditText) findViewById(R.id.loginEmail);
		inputPassword = (EditText) findViewById(R.id.loginPassword);
		errorMessage = (TextView) findViewById(R.id.login_error);
		registerButton = (Button) findViewById(R.id.btnLinkToRegisterScreen);
		loginButton = (Button) findViewById(R.id.btnLogin);

		// link to register screen
		registerButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(getApplicationContext(),
						RegisterActivity.class);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_right,
						R.anim.slide_out_left);
				finish();
			}
		});
		
		//testing
		inputEmail.setText("rm2948@ymail.com");
		inputPassword.setText("1234");
		
		//proccess the user login
		loginButton.setOnClickListener(new OnClickListener() {
			/*
			 * Error handling first check for Internet connection and the
			 * check for valid user data
			 */
			@Override
			public void onClick(View v) {
				/*
				 * Error handling first check for Internet connection and the
				 * check for valid user data
				 */
				
				isInternetPresent = cd.isConnectingToInternet();
				
				if(isInternetPresent){
					// make HTTP requests
					// call async task to process login
					new LoginUser().execute();
				}
					else {
						// Internet connection is not present
						// Ask user to connect to Internet
						showAlertDialog(
								LoginActivity.this,
								"No Internet Connection",
								"You don't have a internet connection.\nPlease connect and try again.",
								false);
				}
				}

		});
	}
	
	@SuppressWarnings("deprecation")
	public void showAlertDialog(Context context, String title, String message,
			Boolean status) {
		AlertDialog alertDialog = new AlertDialog.Builder(context).create();

		// Setting Dialog Title
		alertDialog.setTitle(title);

		// Setting Dialog Message
		alertDialog.setMessage(message);

		// Setting alert dialog icon
		// alertDialog.setIcon((status) ? R.drawable.success : R.drawable.fail);

		// Setting OK Button
		alertDialog.setButton("OK", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
			}
		});

		// Showing Alert Message
		alertDialog.show();
	}

	// async task to login user
	class LoginUser extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {

			super.onPreExecute();
			// set up dialog
			pDialog = new ProgressDialog(LoginActivity.this);
			pDialog.setMessage("Checking Details... Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();

			// get activity data
			email = inputEmail.getText().toString();
			password = inputPassword.getText().toString();
			
		}
		
		@Override
		protected String doInBackground(String... params) {
			
			UserFunctions userFunction = new UserFunctions();
			
			JSONObject json = userFunction.loginUser(email, password);
			
			try {
				if (json.getString(KEY_SUCCESS) != null) {
					//errorMessage.setText("");
					String res = json.getString(KEY_SUCCESS);
					if (Integer.parseInt(res) == 1) {
						// user successfully logged in
						// Store user details in SQLite Database
						DatabaseHandler db = new DatabaseHandler(
								getApplicationContext());
						JSONObject json_user = json.getJSONObject("user");

						// Clear all previous data in database
						userFunction.logoutUser(getApplicationContext());
						db.addUser(json_user.getString(KEY_NAME),
								json_user.getString(KEY_EMAIL),
								json.getString(KEY_UID));

						success = "success";
					} else {
						// Error in login
						// errorMessage.setText("Incorrect username/password");
						String errorMessage = "Incorrect username/password";
						return errorMessage;
					}
				}
			} catch (JSONException e) {
				e.printStackTrace();
			}

			return success;
		}

		@Override
		protected void onPostExecute(final String result) {
			//Log.v("Return value: ", result);
			// dismiss the dialog after getting all products
			pDialog.dismiss();
			// updating UI from Background Thread
			runOnUiThread(new Runnable() {
				public void run() {
					if (result == "success") {
						// start intent
						Intent i = new Intent(getApplicationContext(),
								AdminActivity.class);
						startActivity(i);
						overridePendingTransition(R.anim.slide_in_top,
								R.anim.slide_out_top);
						finish();

					} else {
						// error
						errorMessage.setText("Incorrect username/password");
					}
				}

			});
		}

	}
	}
	
	

