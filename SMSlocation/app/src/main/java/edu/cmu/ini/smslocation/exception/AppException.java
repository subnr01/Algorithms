package edu.cmu.ini.smslocation.exception;

import android.util.Log;

/**
 * Subramanian Natarajan
 * snatara1
 */


public class AppException {

    private final String ERROR_TITLE = "ERROR ";

    // Constructor
    public AppException(String s){
        Log.e(null, ERROR_TITLE + s);
    }

}