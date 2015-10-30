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
import android.widget.Toast;

import com.mad.restaurantfinderrm.R;
import com.mad.restaurantfinderrm.library.ConnectionDetector;
import com.mad.restaurantfinderrm.library.UserFunctions;

public class RegisterActivity extends Activity {

	// flag for Internet connection status
	private Boolean isInternetPresent = false;

	// Connection detector class
	ConnectionDetector cd;

	// Progress Dialog
	private ProgressDialog pDialog;

	// reference for UI elements
	private EditText name;
	private EditText email;
	private EditText password;
	private TextView error;
	private Button register;

	// variable for storing data
	private String nameStr;
	private String emailStr;
	private String passwordStr;

	// flag variable
	String success;

	// JSON Response node names
	private static String KEY_SUCCESS = "success";
	private static String KEY_ERROR = "error";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_register);

		// creating connection detector class instance
		cd = new ConnectionDetector(getApplicationContext());

		// import all assets
		name = (EditText) findViewById(R.id.registerName);
		email = (EditText) findViewById(R.id.registerEmail);
		password = (EditText) findViewById(R.id.registerPassword);
		error = (TextView) findViewById(R.id.register_error);
		register = (Button) findViewById(R.id.btnRegister);

		// button to redirect user back to the register screen
		Button toLogin = (Button) findViewById(R.id.btnLinkToLoginScreen);
		toLogin.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(getApplicationContext(),
						LoginActivity.class);
				startActivity(i);
				overridePendingTransition(R.anim.slide_in_left,
						R.anim.slide_out_right);
				finish();
			}
		});

		// register button clcik event
		register.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				/*
				 * Error handling first check for Internet connection and the
				 * check for valid user data
				 */

				// get Internet status
				isInternetPresent = cd.isConnectingToInternet();

				// check for Internet status
				if (isInternetPresent) {
					// Internet Connection is Present
					// check user input
					if (name.getText().toString().trim().isEmpty()
							|| email.getText().toString().trim().isEmpty()
							|| password.getText().toString().trim().isEmpty()) {
						// Log.v("userinput", "name error");
						error.setText("Check your Data!!".toString());
					} else {
						// make HTTP requests
						// call async task to process register
						new RegisterUser().execute();
					}
				} else {
					// Internet connection is not present
					// Ask user to connect to Internet
					showAlertDialog(
							RegisterActivity.this,
							"No Internet Connection",
							"You don't have a internet connection.\nPlease connect and try again.",
							false);
				}

			}
		});

	}
	
	// async task to register user
	class RegisterUser extends AsyncTask<String, String, String> {

		@Override
		protected void onPreExecute() {

			super.onPreExecute();
			// set up dialog
			pDialog = new ProgressDialog(RegisterActivity.this);
			pDialog.setMessage("Registering... Please wait...");
			pDialog.setIndeterminate(false);
			pDialog.setCancelable(true);
			pDialog.show();

			// get activity data
			nameStr = name.getText().toString();
			emailStr = email.getText().toString();
			passwordStr = password.getText().toString();

		}

		@Override
		protected String doInBackground(String... params) {

			UserFunctions userFunction = new UserFunctions();

			JSONObject json = userFunction.registerUser(nameStr, emailStr,
					passwordStr);

			try {
				if (json.getString(KEY_SUCCESS) != null) {
					// errorMessage.setText("");
					String res = json.getString(KEY_SUCCESS);
					String error = json.getString(KEY_ERROR);
					if (Integer.parseInt(res) == 1) {
						// user successfully registered and stored in mysql db

						// JSONObject json_user = json.getJSONObject("user");

						// Clear all previous data in database

						success = "success";

					} else if (Integer.parseInt(error) == 2) {
						// user already exists
						success = "exists";

					} else {
						// Error in login
						// errorMessage.setText("Incorrect username/password");
						String errorMessage = "Unable to register, try again";
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
			// Log.v("Return value: ", result);
			// dismiss the dialog after getting all products
			pDialog.dismiss();
			// updating UI from Background Thread
			runOnUiThread(new Runnable() {
				public void run() {
					if (result == "success") {
						// start intent
						Intent i = new Intent(getApplicationContext(),
								LoginActivity.class);

						startActivity(i);
						overridePendingTransition(R.anim.slide_in_left,
								R.anim.slide_out_right);
						finish();
						Toast t = Toast.makeText(getApplicationContext(),
								"Account Created, Please login!!",
								Toast.LENGTH_SHORT);
						t.show();

					} else if (result == "exists") {
						// start intent
						Intent i = new Intent(getApplicationContext(),
								LoginActivity.class);

						startActivity(i);
						overridePendingTransition(R.anim.slide_in_left,
								R.anim.slide_out_right);
						finish();
						Toast t = Toast.makeText(getApplicationContext(),
								"User already exists!", Toast.LENGTH_LONG);
						t.show();
					} else {
						// error
						error.setText("Unable to register, try again");
					}
				}

			});
		}

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
}
