package com.example.jessepeterson_inventory;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.widget.Button;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

public class SmsPermissionActivity extends AppCompatActivity {
    private static final int SMS_PERMISSION_CODE = 1;
    // constructing widgets
    private Button allowButton;
    private Button denyButton;

    /**
     * Intialize variables
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sms_permissions);

        // Instantiating widgets
        allowButton = findViewById(R.id.allowButton);
        denyButton = findViewById(R.id.denyButton);

        //enable Sms
        allowButton.setOnClickListener(v -> enableSmsPermission());
        //return
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
     * @param message
     */
    public void sendSmsNotification(String message) {
        String phoneNumber = "1234567890";

        try {
            SmsManager smsManager = SmsManager.getDefault();
            smsManager.sendTextMessage(phoneNumber, null, message, null, null); //send message
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

/* TO-DO */

/**
 *
 */