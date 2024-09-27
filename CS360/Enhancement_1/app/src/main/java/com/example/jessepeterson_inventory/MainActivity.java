package com.example.jessepeterson_inventory;

import android.content.Intent;
import android.content.res.Resources;
import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.app.AppCompatDelegate;

import android.se.omapi.Session;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

/**
 * @author Jesse Peterson
 * 09/18/2024
 * CS360 Final Project
 * MainActivity
 * This class is the starting point for the user. This is where the user will login to the system.
 * It manages the login and create new account buttons. It uses the UserDatabase class to execute its database querries
 */
public class MainActivity extends AppCompatActivity {
    // Construct widgets
    private EditText usernameText;
    private EditText passwordText;
    private TextView loginButton;
    private TextView registerButton;
    private UserDatabase userDatabase;

    // settings from the current session
    SessionManager session = SessionManager.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_login); //Login Screen

        // Instantiate Widgets
        usernameText = findViewById(R.id.username);
        passwordText = findViewById(R.id.password);
        loginButton = findViewById(R.id.loginButton);
        registerButton = findViewById(R.id.registerButton);

        //Open user database
        userDatabase = new UserDatabase(this);
        userDatabase.open();


        //When login button is pressed
        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //read the current user pwd text
                String username = usernameText.getText().toString();
                String password = passwordText.getText().toString();

                //if the user exists in the lightSQL db continue
                if (userDatabase.userExists(username, password)) {
                    Toast.makeText(MainActivity.this, "Login Successful", Toast.LENGTH_SHORT).show();
                    session.setUsername(username);
                    loadSettings();
                    //create intent pointing to the DataDisplayActivity
                    Intent intent = new Intent(MainActivity.this, DataDisplayActivity.class);
                    startActivity(intent);
                    finish();
                } else {
                    //if user not exist send error message
                    Toast.makeText(MainActivity.this, "Invalid username or password", Toast.LENGTH_SHORT).show();
                }
            }
        });

        // When new user button is pressed
        registerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //read the current user pwd text
                String username = usernameText.getText().toString();
                String password = passwordText.getText().toString();

                //adds the user to the database
                if (userDatabase.addUser(username, password)) {
                    Toast.makeText(MainActivity.this, "User Registered", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "Registration Failed", Toast.LENGTH_SHORT).show();
                }
            }
        });

        // Once text is added to the user database
        usernameText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {} //Non-Applicable

            //enable login and register buttons
            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                //enables buttons and changes their background colors
                loginButton.setBackgroundColor(getColor(R.color.MediumSeaGreen));
                loginButton.setTextColor(getColor(R.color.WhiteSmoke));
                loginButton.setEnabled(charSequence.length() > 0);
                registerButton.setBackgroundColor(getColor(R.color.MediumSeaGreen));
                registerButton.setTextColor(getColor(R.color.WhiteSmoke));
                registerButton.setEnabled(charSequence.length() > 0);
            }


            @Override
            public void afterTextChanged(Editable editable) {} //Non-Applicable
        });
    }


    /**
     * Loads settings into global session variables
     */
    private void loadSettings() {
        // settings from the database
        int[] settings = userDatabase.getSettings();

        // setting the settings for the session
        // theme 1 = Light, 0 = dark
        // smsqty any number
        // sms delete 1 = True, 0 = False
        session.setTheme(settings[0] == 1);
        session.setSms_Qty(settings[1]);
        session.setSms_Delete(settings[2] == 1);

        //set the theme
        if(session.getTheme()) {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_NO);
        } else {
            AppCompatDelegate.setDefaultNightMode(AppCompatDelegate.MODE_NIGHT_YES);
        }

    }

    //close database when exiting
    @Override
    protected void onDestroy() {
        super.onDestroy();
        userDatabase.close();
    }

}