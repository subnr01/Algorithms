package com.example.restaurantfinder.authentication;

import android.accounts.AbstractAccountAuthenticator;
import android.accounts.Account;
import android.accounts.AccountAuthenticatorResponse;
import android.accounts.AccountManager;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import com.example.restaurantfinder.*;


public class AccountAuthenticator extends AbstractAccountAuthenticator {
	// Authentication Service context
	private final Context mContext;

	public static final String ACCOUNT_TYPE = "edu.cmu.android.restaurant";

	public static final String AUTHTOKEN_TYPE = "edu.cmu.android.restaurant";

	public AccountAuthenticator(Context context) {
		super(context);
		mContext = context;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle addAccount(AccountAuthenticatorResponse response,
			String accountType, String authTokenType,
			String[] requiredFeatures, Bundle options) {
		final Intent intent = new Intent(mContext, LoginActivity.class);
		intent.putExtra(LoginActivity.PARAM_AUTHTOKEN_TYPE, authTokenType);
		intent.putExtra(AccountManager.KEY_ACCOUNT_AUTHENTICATOR_RESPONSE,
				response);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle confirmCredentials(AccountAuthenticatorResponse response,
			Account account, Bundle options) {
		if (options != null && options.containsKey(AccountManager.KEY_PASSWORD)) {
			final String password = options
					.getString(AccountManager.KEY_PASSWORD);
			final boolean verified = onlineConfirmPassword(account.name,
					password);
			final Bundle result = new Bundle();
			result.putBoolean(AccountManager.KEY_BOOLEAN_RESULT, verified);
			return result;
		}
		// Launch LoginActivity to confirm credentials
		final Intent intent = new Intent(mContext, LoginActivity.class);
		intent.putExtra(LoginActivity.PARAM_USERNAME, account.name);
		intent.putExtra(LoginActivity.PARAM_CONFIRMCREDENTIALS, true);
		intent.putExtra(AccountManager.KEY_ACCOUNT_AUTHENTICATOR_RESPONSE,
				response);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle editProperties(AccountAuthenticatorResponse response,
			String accountType) {
		throw new UnsupportedOperationException();
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle getAuthToken(AccountAuthenticatorResponse response,
			Account account, String authTokenType, Bundle loginOptions) {
		if (!authTokenType.equals(AUTHTOKEN_TYPE)) {
			final Bundle result = new Bundle();
			result.putString(AccountManager.KEY_ERROR_MESSAGE,
					"invalid authTokenType");
			return result;
		}
		final AccountManager am = AccountManager.get(mContext);
		final String password = am.getPassword(account);
		if (password != null) {
			final boolean verified = onlineConfirmPassword(account.name,
					password);
			if (verified) {
				final Bundle result = new Bundle();
				result.putString(AccountManager.KEY_ACCOUNT_NAME, account.name);
				result.putString(AccountManager.KEY_ACCOUNT_TYPE, ACCOUNT_TYPE);
				result.putString(AccountManager.KEY_AUTHTOKEN, password);
				return result;
			}
		}
		// the password was missing or incorrect, return an Intent to an
		// Activity that will prompt the user for the password.
		final Intent intent = new Intent(mContext, LoginActivity.class);
		intent.putExtra(LoginActivity.PARAM_USERNAME, account.name);
		intent.putExtra(LoginActivity.PARAM_AUTHTOKEN_TYPE, authTokenType);
		intent.putExtra(AccountManager.KEY_ACCOUNT_AUTHENTICATOR_RESPONSE,
				response);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public String getAuthTokenLabel(String authTokenType) {
		if (authTokenType.equals(AUTHTOKEN_TYPE)) {
			return mContext.getString(R.string.label);
		}
		return null;

	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle hasFeatures(AccountAuthenticatorResponse response,
			Account account, String[] features) {
		final Bundle result = new Bundle();
		result.putBoolean(AccountManager.KEY_BOOLEAN_RESULT, false);
		return result;
	}

	/**
	 * Validates user's password on the server
	 */
	private boolean onlineConfirmPassword(String username, String password) {
		return NetworkUtilities.authenticate(username, password,
				null/* Handler */, null/* Context */);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public Bundle updateCredentials(AccountAuthenticatorResponse response,
			Account account, String authTokenType, Bundle loginOptions) {
		final Intent intent = new Intent(mContext, LoginActivity.class);
		intent.putExtra(LoginActivity.PARAM_USERNAME, account.name);
		intent.putExtra(LoginActivity.PARAM_AUTHTOKEN_TYPE, authTokenType);
		intent.putExtra(LoginActivity.PARAM_CONFIRMCREDENTIALS, false);
		final Bundle bundle = new Bundle();
		bundle.putParcelable(AccountManager.KEY_INTENT, intent);
		return bundle;
	}

}
