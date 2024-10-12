package com.example.jessepeterson_inventory;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class UserDatabase {
    private SQLiteDatabase db;
    private final UserDatabaseHelper dbHelper;
    SessionManager session = SessionManager.getInstance();

    /**
     * Instantiate user database
     * @param context gives access to resources, system services, and databases
     */
    public UserDatabase(Context context) {
        dbHelper = new UserDatabaseHelper(context);
    }

    /**
     * open database
     */
    public void open() {
        db = dbHelper.getWritableDatabase();
    }

    /**
     * close database
     */
    public void close() {
        dbHelper.close();
    }

    /**
     * adds a user to the database
     * @param username username input
     * @param password password input
     * @return true if user created, false if not
     */
    public boolean addUser(String username, String password) {
        ContentValues values = new ContentValues();
        //adds username and password to DB
        values.put(UserDatabaseHelper.COLUMN_USERNAME, username);
        values.put(UserDatabaseHelper.COLUMN_PASSWORD, password);

        values.put(UserDatabaseHelper.COLUMN_THEME, session.getTheme());
        values.put(UserDatabaseHelper.COLUMN_SMS_QTY, session.getSms_Qty());
        values.put(UserDatabaseHelper.COLUMN_SMS_DELETE, session.getSms_Delete());



        long result = db.insert(UserDatabaseHelper.TABLE_USERS, null, values);
        return result != -1;
    }

    /**
     * checks if a user exists in the database
     * @param username username input
     * @param password password input
     * @return boolean true if exist false if not
     */
    public boolean userExists(String username, String password) {
        String[] columns = {UserDatabaseHelper.COLUMN_ID};
        String selection = UserDatabaseHelper.COLUMN_USERNAME + "= ? AND " + UserDatabaseHelper.COLUMN_PASSWORD + " = ?";
        String[] selectionArgs = {username, password};
        //scans database searching for mass
        Cursor cursor = db.query(UserDatabaseHelper.TABLE_USERS, columns, selection, selectionArgs, null, null, null);

        int cursorCount = cursor.getCount();
        cursor.close();

        return cursorCount > 0;
    }


    public void updateSettings(String username, int theme, int qty, int del) {
        open();
        ContentValues values = new ContentValues();

        values.put(UserDatabaseHelper.COLUMN_THEME, theme);
        values.put(UserDatabaseHelper.COLUMN_SMS_QTY, qty);
        values.put(UserDatabaseHelper.COLUMN_SMS_DELETE, del);


        db.update(UserDatabaseHelper.TABLE_USERS, values, UserDatabaseHelper.COLUMN_USERNAME + " =?", new String[]{username});
        close();
    }


    /**
     * Retrieves settings from the database
     * @return int array settings [theme, sms qty, sms delete]
     */
    public int[] getSettings() {
        //query to find settings
        String selectQuery = " SELECT " + UserDatabaseHelper.COLUMN_THEME + ", " + UserDatabaseHelper.COLUMN_SMS_QTY + ", " + UserDatabaseHelper.COLUMN_SMS_DELETE + " FROM " + UserDatabaseHelper.TABLE_USERS + " WHERE " + UserDatabaseHelper.COLUMN_USERNAME + " = ?";
        Cursor cursor = db.rawQuery(selectQuery, new String[]{session.getUsername()});

        int[] settings = new int[3];

        if(cursor.moveToFirst()) {

            // Get settings into settings array
            settings[0] = cursor.getInt(cursor.getColumnIndexOrThrow(UserDatabaseHelper.COLUMN_THEME));
            settings[1] = cursor.getInt(cursor.getColumnIndexOrThrow(UserDatabaseHelper.COLUMN_SMS_QTY));
            settings[2] = cursor.getInt(cursor.getColumnIndexOrThrow(UserDatabaseHelper.COLUMN_SMS_DELETE));

        }

        //Wrap up function
        cursor.close();
        db.close();
        return settings;


    }

}

