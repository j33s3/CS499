package com.example.jessepeterson_inventory;

import android.content.Context;

import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class InventoryDatabaseHelper extends SQLiteOpenHelper{
    // Inventory data and final vars
    private static final String DATABASE_NAME = "inventoryDatabase.db";
    private static final int DATABASE_VERSION = 1;

    public static final String TABLE_INVENTORY = "inventory";
    public static final String COLUMN_ID = "_id";
    public static final String COLUMN_ITEM_NAME = "item";
    public static final String COLUMN_QUANTITY = "quantity";

    public InventoryDatabaseHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    /**
     * creates the db
     * @param db
     */
    @Override
    public void onCreate(SQLiteDatabase db) {
        String CREATE_INVENTORY_TABLE = "CREATE TABLE " + TABLE_INVENTORY + " ("
                + COLUMN_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                + COLUMN_ITEM_NAME + " TEXT, "
                + COLUMN_QUANTITY + " INTEGER)";
        db.execSQL(CREATE_INVENTORY_TABLE);
    }

    /**
     * updgrades the DB
     * @param db
     * @param oldVersion
     * @param newVersion
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_INVENTORY);
        onCreate(db);
    }
}

/* TO-DO */

/**
 *
 */