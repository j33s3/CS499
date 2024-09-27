package com.example.jessepeterson_inventory;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;
import androidx.appcompat.widget.SwitchCompat;
import androidx.core.content.ContextCompat;


/**
 * @author Jesse Peterson
 * 09/18/2024
 * CS499 Software Development Enhancement
 * SettingsActivity
 * This activity is used for managing changed to the settings screen
 */
public class SettingsActivity extends AppCompatActivity {

    private SwitchCompat themeSlider;
    private TextView smsButton;
    private EditText SMSQty;
    private SwitchCompat SMSDeleteSlider;
    private UserDatabase userDatabase;

    // settings for the current session
    SessionManager session = SessionManager.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings_display);

        //initialize new database
        userDatabase = new UserDatabase(this);
        userDatabase.open();

        // instantiate all widgets
        themeSlider = findViewById(R.id.themeSlider);
        smsButton = findViewById(R.id.smsButton);
        SMSQty = findViewById(R.id.SMSQty);
        SMSDeleteSlider = findViewById(R.id.SMSDeleteSlider);
        Button doneButton = findViewById(R.id.doneButton);

        //set the status of the widgets
        setSettingsStatus();

        // activate upon clicking them slider
        themeSlider.setOnClickListener(v -> {
            //sets session variable then changed the widget
            session.setTheme(!session.getTheme());
            themeSlider.setChecked(session.getTheme());

            //updates the theme
            if(session.getTheme()) {
                AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
            } else {
                AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
            }
        });

        smsButton.setOnClickListener(new View.OnClickListener() {
            /**
             * When the SMS button is pressed
             * Send user permission request screen
             */
            @Override
            public void onClick(View view) {
                // send user to permission request screen
                Intent intent = new Intent(SettingsActivity.this, SmsPermissionActivity.class);
                startActivity(intent);
            }
        });

        // activates upon clicking sms delete
        SMSDeleteSlider.setOnClickListener(v -> {
            //sets session variable and updates slider
            session.setSms_Delete(!session.getSms_Delete());
            SMSDeleteSlider.setChecked(session.getSms_Delete());
        });

        // activates upon clicking done
        doneButton.setOnClickListener(v -> {
            //retrieves the value in textbox
            int qty = Integer.parseInt(SMSQty.getText().toString());

            //if the value is different then current, update
            if(session.getSms_Qty() != qty) {
                session.setSms_Qty(qty);
            }
            //send values to db query handler
            userDatabase.updateSettings(session.getUsername(), (session.getTheme() ? 1 : 0), session.getSms_Qty(), (session.getSms_Delete() ? 1 : 0));

            //wrap up class
            setResult(RESULT_CANCELED);
            userDatabase.close();
            finish();
        });
    }

    /**
     * executes upon returning to class
     * Used for returning from SMS activity
     */
    @Override
    protected void onResume() {
        super.onResume();
        smsButton.setText(checkSMS() ? "Enabled" : "Disabled");
    }

    /**
     * Checks if sms permissions are enabled
     * @return true if active false if not
     */
    public boolean checkSMS() {
        return ContextCompat.checkSelfPermission(this, Manifest.permission.SEND_SMS) == PackageManager.PERMISSION_GRANTED;
    }


    /**
     * Sets the status of the widgets depending on settings
     */
    public void setSettingsStatus() {
        //retrieve settings from db
        int[] settings = userDatabase.getSettings();

        //set the widgets
        themeSlider.setChecked(settings[0] == 1);
        smsButton.setText(checkSMS() ? "Enabled" : "Disabled");
        SMSQty.setText(String.valueOf(settings[1]));
        SMSDeleteSlider.setChecked(settings[2] == 1);
    }



}
