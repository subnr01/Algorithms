package com.mad.restaurantfinderrm;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.util.Log;
import android.view.KeyEvent;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

@SuppressLint("SetJavaScriptEnabled")
public class MenuActivity extends Activity {

	WebView webView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_menu);
		
		//get url for menu from previous activity
		String url = getIntent().getStringExtra("url");
		Log.v("URL", url);
		webView = (WebView) findViewById(R.id.menuWebView);
		webView.canGoBack();
		WebSettings ws = webView.getSettings();
		ws.setJavaScriptEnabled(true);
		webView.setWebViewClient(new WebViewClient());
		webView.getSettings().setBuiltInZoomControls(true);
		webView.getSettings().setDisplayZoomControls(false);
		webView.getSettings().setUseWideViewPort(true);
		webView.loadUrl(url);
		
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
	    if ((keyCode == KeyEvent.KEYCODE_BACK) && webView.canGoBack()) {
	        webView.goBack();
	        return true;
	    }
	    return super.onKeyDown(keyCode, event);
	}

}

