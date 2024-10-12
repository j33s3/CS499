package com.example.jessepeterson_inventory;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;

import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;


public class AddDataActivity extends AppCompatActivity {
    private InventoryDatabaseHelper dbHelper;
    // construct widgets
    private EditText itemText;
    private EditText quantityText;
    private Button saveButton;
    private ImageButton cancelButton;
    private InventoryDatabase inventoryDatabase;

    /**
     * initializing item components
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_data);

        // instantiating widgets
        itemText = findViewById(R.id.itemText);
        quantityText = findViewById(R.id.quantityText);
        saveButton = findViewById(R.id.saveButton);
        cancelButton = findViewById(R.id.cancelButton);

        //open the inventory database
        inventoryDatabase = new InventoryDatabase(this);
        inventoryDatabase.open();

        /**
         * when the save button is pressed
         * add the item ot the databaase
         */
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //retrive the item name and qty from input
                String itemName = itemText.getText().toString();
                String quantityStr = quantityText.getText().toString();

                if(!itemName.isEmpty() && !quantityStr.isEmpty()) {
                    //add the item to the database
                    int quantity = Integer.parseInt(quantityStr);
                    inventoryDatabase.addItem(itemName, quantity);
                    Toast.makeText(AddDataActivity.this, "Item added to inventory", Toast.LENGTH_SHORT).show();

                    itemText.setText("");
                    quantityText.setText("");
                } else {
                    Toast.makeText(AddDataActivity.this, "Please enter both item name and quantity", Toast.LENGTH_SHORT).show();
                }
            }
        });

        /**
         * When item text is changed
         * enable save button
         */
        itemText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                saveButton.setEnabled(charSequence.length() > 0); //enable save button
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });

        /**
         * When cancel button is pressed
         * Return to DataDisplayActivity
         */
        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setResult(RESULT_CANCELED);
                finish();
            }
        });
    }


    // upon quiting, close DB
    @Override
    protected void onDestroy() {
        super.onDestroy();
        inventoryDatabase.close();
    }
}

/* TO-DO */

/**
 * 1. Line 21 find better placement for variable declaration.
 * DOCUMENTATION
 * 2. Fix Javadocs
 * 3. Line 26 Fix argument description
 * 4. Comments may be sparse but effectively covers function comments
 * DEFENSIVE PROGRAMMING
 * 5. No form or input validation, users can enter quantities that could break the system
 * 6.
 */
