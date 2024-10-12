package com.example.jessepeterson_inventory;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;


public class InventoryDatabase {
    private SQLiteDatabase db;
    private InventoryDatabaseHelper dbHelper;

    /**
     * used for opening the database
     */
    public void open() {
        db = dbHelper.getWritableDatabase();
    }

    /**
     * used for closing the database
     */
    public void close() {
        dbHelper.close();
    }


    /**
     * Constructor
     * points DB to inventory DB
     * @param context
     */
    public InventoryDatabase(Context context) {
        dbHelper = new InventoryDatabaseHelper(context);
    }

    /**
     * Adds item to database
     * @param itemName
     * @param quantity
     */
    public void addItem(String itemName, int quantity) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        ContentValues values = new ContentValues();
        //Adds item name and quantity to new document
        values.put(InventoryDatabaseHelper.COLUMN_ITEM_NAME, itemName);
        values.put(InventoryDatabaseHelper.COLUMN_QUANTITY, quantity);

        //inserts into db
        db.insert(InventoryDatabaseHelper.TABLE_INVENTORY, null, values);
        db.close();
    }

    /**
     * Finds item in inventory Db
     * and deletes it
     * @param itemName
     */
    public void removeItem(String itemName) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        //finds item in the DB and deletes it
        db.delete(InventoryDatabaseHelper.TABLE_INVENTORY, InventoryDatabaseHelper.COLUMN_ITEM_NAME + "=?", new String[]{itemName});
    }

    /**
     * Finds item in inventory DB
     * and updates the quantity
     * @param itemName
     * @param newQuantity
     */
    public void updateItemQuantity(String itemName, int newQuantity) {
        SQLiteDatabase db = dbHelper.getWritableDatabase();
        ContentValues values = new ContentValues();
        //update item quantity
        values.put(InventoryDatabaseHelper.COLUMN_QUANTITY, newQuantity);
        //set the update
        db.update(InventoryDatabaseHelper.TABLE_INVENTORY, values, InventoryDatabaseHelper.COLUMN_ITEM_NAME + "=?", new String[] {itemName});
    }

    /**
     * Returns a cursor to all items in the DB
     * @return
     */
    public Cursor getAllItems() {
        return db.query(InventoryDatabaseHelper.TABLE_INVENTORY, null, null, null, null, null, null);
    }

}


/* TO-DO */

/**
 *
 */