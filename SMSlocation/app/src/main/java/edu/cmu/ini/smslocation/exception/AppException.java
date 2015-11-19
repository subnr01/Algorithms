package edu.cmu.ini.smslocation.exception;

import android.util.Log;

/**
 * Created by admin on 11/18/15.
 */
public class AppException {

    private final String ERROR_TITLE = "ERROR ";// Exception Dialog Title

    // Constructor
    public AppException(String s){
        Log.e(null, ERROR_TITLE + s);// log the exception in System.out of terminal
    }

}