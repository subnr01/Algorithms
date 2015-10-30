package com.mad.restaurantfinderrm;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;
import android.widget.TextView;
import android.widget.Toast;

import com.mad.restaurantfinderrm.library.DatabaseHandler_Saved_Restaurants;

public class Tab4Fragment extends Fragment {

	Activity a;

	ListView mFavList;
	TextView tv;

	// DB
	private SQLiteDatabase mDb;
	private Cursor mCursor;

	/**
	 * (non-Javadoc)
	 * 
	 * @see android.support.v4.app.Fragment#onCreateView(android.view.LayoutInflater,
	 *      android.view.ViewGroup, android.os.Bundle)
	 */

	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		if (container == null) {
			// We have different layouts, and in one of them this
			// fragment's containing frame doesn't exist. The fragment
			// may still be created from its saved state, but there is
			// no reason to try to create its view hierarchy because it
			// won't be displayed. Note this is not needed -- we could
			// just run the code below, where we would create and return
			// the view hierarchy; it would just never be used.
			return null;
		}
		return (LinearLayout) inflater.inflate(R.layout.tab_frag4_layout,
				container, false);
	}

	@Override
	public void onActivityCreated(Bundle savedInstanceState) {
		super.onActivityCreated(savedInstanceState);

		a = getActivity();
		mFavList = (ListView) a.findViewById(R.id.favListView);

		tv = (TextView) a.findViewById(R.id.favTextView);
	}

	SimpleCursorAdapter ca;

	@SuppressWarnings("deprecation")
	@Override
	public void onResume() {
		super.onResume();
		DatabaseHandler_Saved_Restaurants mh = new DatabaseHandler_Saved_Restaurants(
				a.getApplicationContext());
		mDb = mh.getWritableDatabase();
		mCursor = mDb.query("fav", null, null, null, null, null,
				"restaurantID desc");
		//cursor empty display error other show listview
		if(mCursor != null && mCursor.getCount() > 0){
		a.startManagingCursor(mCursor);

		int views[] = { R.id.favRestName, R.id.favRestType, };
		String cols[] = { "restaurantName", "restaurantType" };
		ca = new SimpleCursorAdapter(a.getApplicationContext(),
				R.layout.fav_list_item, mCursor, cols, views);
		mFavList.setAdapter(ca);

		mFavList.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {

				String sql = "SELECT * FROM fav WHERE _id=" + arg3;
				Cursor c = mDb.rawQuery(sql, null);
				c.moveToFirst();

				Intent i = new Intent(a.getApplicationContext(),
						RestaurantDetails.class);
				i.putExtra("ID", c.getString(c.getColumnIndex("restaurantID")));
				startActivity(i);
				a.overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
			}
		});

		mFavList.setOnItemLongClickListener(new OnItemLongClickListener() {

			public boolean onItemLongClick(AdapterView<?> arg0, View arg1,
					int pos, final long id) {

				AlertDialog.Builder alertDialog = new AlertDialog.Builder(a);

				// Setting Dialog Title
				alertDialog.setTitle("Confirm Delete");

				// Setting Dialog Message
				alertDialog.setMessage("Are you sure you want delete this?");

				// Setting Icon to Dialog
				// alertDialog.setIcon(android.R.drawable.delete);

				// Setting Positive "Yes" Button
				alertDialog.setPositiveButton("YES",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {

								// delete saved favoriate from sqlite db

								String deletesql = "DELETE FROM fav WHERE _id="
										+ id;
								mDb.execSQL(deletesql);

								ca.getCursor().requery();

								Toast.makeText(a.getApplicationContext(),
										"Restaurant removed",
										Toast.LENGTH_SHORT).show();
							}
						});

				// Setting Negative "NO" Button
				alertDialog.setNegativeButton("NO",
						new DialogInterface.OnClickListener() {
							public void onClick(DialogInterface dialog,
									int which) {
								// Write your code here to invoke NO event
								Toast.makeText(a.getApplicationContext(),
										"Cancelled", Toast.LENGTH_SHORT)
										.show();
								dialog.cancel();
							}
						});

				// Showing Alert Message
				alertDialog.show();

				return true;

			}
		});
		
		}
		else{
			tv.setVisibility(1);
		}

	}

	@Override
	public void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		// mDb.close();
	}

	@Override
	public void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		mDb.close();
	}
}
