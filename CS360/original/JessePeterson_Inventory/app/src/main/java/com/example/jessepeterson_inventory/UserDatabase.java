package com.example.jessepeterson_inventory;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;

public class UserDatabase {
    private SQLiteDatabase db;
    private UserDatabasehelper dbHelper;

    /**
     * Instantiate user database
     * @param context
     */
    public UserDatabase(Context context) {
        dbHelper = new UserDatabasehelper(context);
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
     * @param username
     * @param password
     * @return
     */
    public boolean addUser(String username, String password) {
        ContentValues values = new ContentValues();
        //adds username and password to DB
        values.put(UserDatabasehelper.COLUMN_USERNAME, username);
        values.put(UserDatabasehelper.COLUMN_PASSWORD, password);

        long result = db.insert(UserDatabasehelper.TABLE_USERS, null, values);
        return result != -1;
    }

    /**
     * checks if a user exists in the database
     * @param username
     * @param password
     * @return
     */
    public boolean userExists(String username, String password) {
        String[] columns = {UserDatabasehelper.COLUMN_ID};
        String selection = UserDatabasehelper.COLUMN_USERNAME + "= ? AND " + UserDatabasehelper.COLUMN_PASSWORD + " = ?";
        String[] selectionArgs = {username, password};
        //scans database searching for mass
        Cursor cursor = db.query(UserDatabasehelper.TABLE_USERS, columns, selection, selectionArgs, null, null, null);

        int cursorCount = cursor.getCount();
        cursor.close();

        return cursorCount > 0;
    }

}

/* TO-DO */

/**
 *
 */