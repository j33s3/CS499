package com.example.jessepeterson_inventory;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.widget.Button;
import android.widget.Toast;
import android.util.Log;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

/**
 * @author Jesse Peterson
 * 09/18/2024
 * CS360 Final Project
 * SMSPermissionActivity
 * This class is responsible for managing the SMS permission. When the user selects the bell icon
 * on the DataDisplayActivity. User can select enable SMS and it will call a system popup to ask.
 * This class also allows sending SMS by passing through a message.
 */
public class SmsPermissionActivity extends AppCompatActivity {
    private static final int SMS_PERMISSION_CODE = 1;

    /**
     * Initialize variables
     * @param savedInstanceState restoring previous status
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sms_permissions);

        // Instantiating widgets
        Button allowButton = findViewById(R.id.allowButton);
        Button denyButton = findViewById(R.id.denyButton);

        //when button is clicked it will run our method to enable sms
        allowButton.setOnClickListener(v -> enableSmsPermission());
        //when deny button is pressed it will finish/return
        denyButton.setOnClickListener(v -> finish());
    }

    /**
     * Checks if SMS is enabled
     * Enables it otherwise
     */
    private void enableSmsPermission() {
        //check if SMS is enabled
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.SEND_SMS) != PackageManager.PERMISSION_GRANTED) {
            //request access
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.SEND_SMS}, SMS_PERMISSION_CODE);
            //send test messages
            String message = "This is a test SMS notification";
            sendSmsNotification(message);
            finish();
        } else {
            Toast.makeText(this, "Already Active", Toast.LENGTH_SHORT).show();
            finish();
        }
    }

    /**
     * send message to user
     * @param message message that will be sent to the user
     */
    public void sendSmsNotification(String message) {
        String phoneNumber = "1234567890";
        String TAG = "SmsPermissionActivity";

        try {
            SmsManager smsManager = SmsManager.getDefault();
            smsManager.sendTextMessage(phoneNumber, null, message, null, null); //send message

            Log.i(TAG, "SMS sent successfully to" + phoneNumber + " with message: " + message);
        } catch (IllegalArgumentException e) {
            //Log error for invalid phone number or messaging format
            Log.e(TAG, "Invalid phone number or message format: " + e.getMessage());
        } catch (Exception e) {
            //Catch all other errors
            Log.e(TAG, "Failed to send massage due to an unexpected error: " + e.getMessage());
        }
    }
}
