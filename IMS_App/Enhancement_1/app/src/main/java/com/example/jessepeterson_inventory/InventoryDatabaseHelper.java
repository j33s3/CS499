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
public class InventoryDatabaseHelper extends SQLiteOpenHelper{
    // Inventory data and final vars
    private static final String DATABASE_NAME = "inventoryDatabase.db";
    private static final int DATABASE_VERSION = 1;

    public static final String TABLE_INVENTORY = "inventory";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_ITEM_NAME = "item";
    public static final String COLUMN_QUANTITY = "quantity";

    /**
     * @param context gives access to resources, system services, and databases
     */
    public InventoryDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    /**
     * creates the db
     * This method is called by the parent class SQLiteOpenHelper
     * @param db SQLite database
     */
    @Override
    public void onCreate(SQLiteDatabase db) {
        //SQL command
        String CREATE_INVENTORY_TABLE = "CREATE TABLE " + TABLE_INVENTORY + " ("
                + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                + COLUMN_ITEM_NAME + " TEXT, "
                + COLUMN_QUANTITY + " INTEGER)";
        //Execute command
        db.execSQL(CREATE_INVENTORY_TABLE);
    }

    /**
     * upgrades the DB
     * This method is called by the parent class SQLiteOpenHelper
     * @param db SQLite database
     * @param oldVersion version number
     * @param newVersion version number
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        //executes command then creates database
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_INVENTORY);
        onCreate(db);
    }
}
