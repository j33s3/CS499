package com.example.jessepeterson_inventory;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import android.view.View;
import android.view.ViewGroup;
import android.widget.GridLayout;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

public class DataDisplayActivity extends AppCompatActivity {
    // Construct widgets
    private Button addButton;
    private GridLayout gridLayout;
    private InventoryDatabase inventoryDatabase;
    private ImageButton smsButton;


    /**
     * initialize DataDisplayAcivity
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_data_display);

        //Open the inventory database
        inventoryDatabase = new InventoryDatabase(this);
        inventoryDatabase.open();

        // Instantiate widgets
        addButton = findViewById(R.id.addButton);
        smsButton = findViewById(R.id.smsButton);
        gridLayout = findViewById(R.id.gridLayout);

        // load data
        loadInventoryItems();


        /**
         * when add item button is pressed
         * send user to screen for adding items
         */
        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // send user to screen for adding item
                Intent intent = new Intent(DataDisplayActivity.this, AddDataActivity.class);
                startActivity(intent);
            }
        });

        /**
         * When the SMS button is pressed
         * Send user permission request screen
         */
        smsButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // send user to permission request screen
                Intent intent = new Intent(DataDisplayActivity.this, SmsPermissionActivity.class);
                startActivity(intent);
            }
        });
    }


    /**
     * when returning from adding items
     * Reload inventory
     */
    @Override
    protected void onResume() {
        super.onResume();
        //reload inventory
        loadInventoryItems();
    }

    /**
     * Loads each item from the inventory db into grid
     */
    private void loadInventoryItems() {
        gridLayout.removeAllViews();

        Cursor cursor = inventoryDatabase.getAllItems();

        if(cursor != null && cursor.moveToFirst()) {
        do {
            String itemName = cursor.getString(cursor.getColumnIndexOrThrow(InventoryDatabaseHelper.COLUMN_ITEM_NAME));
            int quantity = cursor.getInt(cursor.getColumnIndexOrThrow(InventoryDatabaseHelper.COLUMN_QUANTITY));

            addInventoryRow(itemName, quantity);

        } while (cursor.moveToNext());
            cursor.close();
        }
    }

    /**
     * Adds each component the grid
     * @param name
     * @param quantity
     */
    private void addInventoryRow(String name, int quantity) {

        // adding the text for item name
        TextView itemName = new TextView(this);
        itemName.setText(name);
        itemName.setTextColor(getColor(R.color.WhiteSmoke));
        itemName.setPadding(4, 4, 4, 4);
        itemName.setTextSize(15.0f);
        GridLayout.LayoutParams itemNameParams = new GridLayout.LayoutParams(); //Creating the Layout Parameters
        itemNameParams.width = 0;
        itemNameParams.height = ViewGroup.LayoutParams.WRAP_CONTENT;
        itemNameParams.columnSpec = GridLayout.spec(0, 1, 1f);
        itemName.setLayoutParams(itemNameParams);
        gridLayout.addView(itemName);

        // Adding the text for the item quantity
        TextView quantityText = new TextView(this);
        quantityText.setText(String.valueOf(quantity));
        quantityText.setTextColor(getColor(R.color.WhiteSmoke));
        quantityText.setPadding(4, 4, 4, 4);
        quantityText.setTextSize(15.0f);
        GridLayout.LayoutParams quantityParams = new GridLayout.LayoutParams(); //Creating the Layout Parameters
        quantityParams.width = 0;
        quantityParams.height = ViewGroup.LayoutParams.WRAP_CONTENT;
        quantityParams.columnSpec = GridLayout.spec(1, 1, 1f);
        quantityText.setLayoutParams(quantityParams);
        gridLayout.addView(quantityText);

        // Adding button for incrementing item quantities
        ImageButton incrementButton = new ImageButton(this);
        incrementButton.setImageResource(android.R.drawable.ic_input_add);
        incrementButton.setBackgroundColor(getColor(R.color.Background));
        incrementButton.setColorFilter(getColor(R.color.MediumSeaGreen));
        incrementButton.setScaleX(1.2f);
        incrementButton.setScaleY(1.2f);
        incrementButton.setPadding(4, 4, 4, 4);
        GridLayout.LayoutParams incremenetButtonParams = new GridLayout.LayoutParams(); //Creating the Layout Parameters
        incremenetButtonParams.width = 0;
        incremenetButtonParams.height = ViewGroup.LayoutParams.WRAP_CONTENT;
        incremenetButtonParams.columnSpec = GridLayout.spec(2, 1, 0.33f);
        incrementButton.setLayoutParams(incremenetButtonParams);
        gridLayout.addView(incrementButton);

        // Adding a button for decrementing item quantities
        ImageButton decrementButton = new ImageButton(this);
        decrementButton.setImageResource(android.R.drawable.button_onoff_indicator_off);
        decrementButton.setBackgroundColor(getColor(R.color.Background));
        decrementButton.setColorFilter(getColor(R.color.MediumSeaGreen));
        decrementButton.setScaleX(0.6f);
        decrementButton.setScaleY(0.8f);
        decrementButton.setPadding(4, 37, 4, 4);
        GridLayout.LayoutParams decrementButtonParams = new GridLayout.LayoutParams(); //Creating the Layout Parameters
        decrementButtonParams.width = 0;
        decrementButtonParams.height = ViewGroup.LayoutParams.WRAP_CONTENT;
        decrementButtonParams.columnSpec = GridLayout.spec(3, 1, 0.33f);
        decrementButton.setLayoutParams(decrementButtonParams);
        gridLayout.addView(decrementButton);

        // Adding a button for deleting items
        ImageButton deleteButton = new ImageButton(this);
        deleteButton.setImageResource(android.R.drawable.ic_delete);
        deleteButton.setBackgroundColor(getColor(R.color.Background));
        deleteButton.setColorFilter(getColor(R.color.MediumSeaGreen));
        deleteButton.setPadding(4, 4, 4, 4);
        GridLayout.LayoutParams deleteButtonParams = new GridLayout.LayoutParams(); //Creating the Layout Parameters
        deleteButtonParams.width = 0;
        deleteButtonParams.height = ViewGroup.LayoutParams.WRAP_CONTENT;
        deleteButtonParams.columnSpec = GridLayout.spec(4, 1, 0.33f);
        deleteButton.setLayoutParams(deleteButtonParams);
        gridLayout.addView(deleteButton);

        /**
         * When the increment button is pressed
         * Will update the database an reload
         */
        incrementButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view) {
                int newQuantity = quantity + 1;
                //Try adding item to database
                try {
                    inventoryDatabase.updateItemQuantity(name, newQuantity);
                    loadInventoryItems();
                    Toast.makeText(DataDisplayActivity.this, String.format("%s incremented", name), Toast.LENGTH_SHORT).show();
                } catch (Exception e) {
                    Toast.makeText(DataDisplayActivity.this, e.toString(), Toast.LENGTH_SHORT).show();
                    Toast.makeText(DataDisplayActivity.this, "Error Incrementing", Toast.LENGTH_SHORT).show();
                }
            }
        });

        /**
         * When the decrement button is pressed
         * Will update the database and reload
         */
        decrementButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int newQuantity = quantity - 1;
                if(newQuantity >= 0) { //ensure that the new number wont be negative
                    try {
                        inventoryDatabase.updateItemQuantity(name, newQuantity);
                        loadInventoryItems();
                        Toast.makeText(DataDisplayActivity.this, String.format("%s decremented", name), Toast.LENGTH_SHORT).show();
                    } catch (Exception e) {
                        Toast.makeText(DataDisplayActivity.this, e.toString(), Toast.LENGTH_SHORT).show();
                        Toast.makeText(DataDisplayActivity.this, "Error Decrementing", Toast.LENGTH_SHORT).show();
                    }
                }
                // if the quantity is zero and user has SMS perms
                if(newQuantity == 0) {
                    if (ContextCompat.checkSelfPermission(DataDisplayActivity.this, Manifest.permission.SEND_SMS) == PackageManager.PERMISSION_GRANTED) {
                        SmsPermissionActivity sms = new SmsPermissionActivity();
                        //send notification that the item stock is low
                        sms.sendSmsNotification(String.format("Your item \"%s\" has reached a quantity of 0 units", name));
                    }
                }
            }
        });

        /**
         * When the delete button is pressed
         * will delete item from the database and reload
         */
        deleteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                    //Try to delete the item
                try {
                    inventoryDatabase.removeItem(name);
                    loadInventoryItems();
                    Toast.makeText(DataDisplayActivity.this, "deleted", Toast.LENGTH_SHORT).show();

                } catch (Exception e) {
                    Toast.makeText(DataDisplayActivity.this, e.toString(), Toast.LENGTH_SHORT).show();
                    Toast.makeText(DataDisplayActivity.this, "Error deleting item", Toast.LENGTH_SHORT).show();
                }
            }
        });
    }


    //upon exiting, close inventory DB
    @Override
    protected void onDestroy() {
        super.onDestroy();
        inventoryDatabase.close();
    }
}

/* TO-DO */

/**
 *
 */
