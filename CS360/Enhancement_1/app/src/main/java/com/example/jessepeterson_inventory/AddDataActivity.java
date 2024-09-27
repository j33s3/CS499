package com.example.jessepeterson_inventory;



import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;

/**
 * @author Jesse Peterson
 * 09/18/2024
 * CS360 Final Project
 * AddDataActivity
 * allows users to enter an item name and quantity into text boxes.
 * This class will read that data and add it into the inventory database
 * It will also reload the database so the dataDisplayActivity is up to date.
 */
public class AddDataActivity extends AppCompatActivity {
    // construct widgets
    private EditText itemText;
    private EditText quantityText;
    private Button saveButton;
    private InventoryDatabase inventoryDatabase;

    /**
     * initializing item components
     * @param savedInstanceState restoring previous status
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_data);

        // instantiating widgets
        itemText = findViewById(R.id.itemText);
        quantityText = findViewById(R.id.quantityText);
        saveButton = findViewById(R.id.saveButton);
        ImageButton cancelButton = findViewById(R.id.cancelButton);

        //open the inventory database
        inventoryDatabase = new InventoryDatabase(this);
        inventoryDatabase.open();


        saveButton.setOnClickListener(new View.OnClickListener() {

            /**
             * when the save button is pressed
             * add the item ot the database
             */
            @Override
            public void onClick(View view) {
                //retrieve the item name and qty from input
                String itemName = itemText.getText().toString();
                String quantityStr = quantityText.getText().toString();

                if(!itemName.isEmpty() && !quantityStr.isEmpty()) {
                    int quantity = Integer.parseInt(quantityStr);
                    if(itemName.length() < 20 && quantity < 100000) {
                        //add the item to the database
                        inventoryDatabase.addItem(itemName, quantity);

                        //sends confirmation
                        Toast.makeText(AddDataActivity.this, "Item added to inventory", Toast.LENGTH_SHORT).show();

                        //rests user input fields
                        itemText.setText("");
                        quantityText.setText("");
                    } else {
                        Toast.makeText(AddDataActivity.this, "Please enter a name under 20 characters and a quantity under 100,000", Toast.LENGTH_SHORT).show();
                    }
                } else {
                    // if a field is not filled send message
                    Toast.makeText(AddDataActivity.this, "Please enter both item name and quantity", Toast.LENGTH_SHORT).show();
                }
            }
        });

        //When item text is changed enable save button
        itemText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {} //Non-Applicable

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                //enable save button for interaction and change color
                saveButton.setEnabled(charSequence.length() > 0);
                saveButton.setTextColor(getColor(R.color.WhiteSmoke));
                saveButton.setBackgroundColor(getColor(R.color.MediumSeaGreen));
            }

            @Override
            public void afterTextChanged(Editable editable) {} //Non-Applicable
        });


        cancelButton.setOnClickListener(new View.OnClickListener() {
            /**
             * When cancel button is pressed
             * Return to DataDisplayActivity
             */
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
