package com.example.jessepeterson_inventory;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * @author Jesse Peterson
 * 09/18/2024
 * CS360 Final Project
 * InventoryDatabaseHelper
 * This class is responsible for creating the database and upgrading whenever new versions are presented.
 * The class holds the outline for the SQLite database structure. The parent class also hold
 * functionality for the database setup.
 */
public class UserDatabaseHelper extends SQLiteOpenHelper{
    //Database info
    private static final String DATABASE_NAME = "userDatabase.db";
    private static final int DATABASE_VERSION = 1;

    public static final String TABLE_USERS = "users";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_USERNAME = "username";
    public static final String COLUMN_PASSWORD = "password";
    // user settings
    public static final String COLUMN_THEME = "theme";
    public static final String COLUMN_SMS_QTY = "sms_qty";
    public static final String COLUMN_SMS_DELETE = "sms_delete";

    /**
     * Constructor, calls super
     * @param context gives access to resources, system services, and databases
     */
    public UserDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    /**
     * Creates the DB
     * @param db SQLite database
     */
    @Override
    public void onCreate(SQLiteDatabase db) {
        //sql command
        String CREATE_USERS_TABLE = "CREATE TABLE " + TABLE_USERS + " ("
                + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                + COLUMN_USERNAME + " TEXT, "
                + COLUMN_PASSWORD + " TEXT, "
                + COLUMN_THEME + " INTEGER, "
                + COLUMN_SMS_QTY + " INTEGER, "
                + COLUMN_SMS_DELETE + " INTEGER)";
        //executes command
        db.execSQL(CREATE_USERS_TABLE);
    }

    /**
     * updates the DB
     * @param db SQLite database
     * @param oldVersion version number
     * @param newVersion version number
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        //executes command and creates db
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_USERS);
        onCreate(db);
    }
}
