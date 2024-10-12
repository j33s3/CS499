package com.example.jessepeterson_inventory;

import android.content.Intent;
import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;

import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    // Consctruct widgets
    private EditText usernameText;
    private EditText passwordText;
    private Button loginButton;
    private Button registerButton;
    private UserDatabase userDatabase;

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

        //once text is added to the user database
        usernameText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            //enable login and register buttons
            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                loginButton.setEnabled(charSequence.length() > 0);
                registerButton.setEnabled(charSequence.length() > 0);
            }


            @Override
            public void afterTextChanged(Editable editable) {

            }
        });

    }


    //close database when exiting
    @Override
    protected void onDestroy() {
        super.onDestroy();
        userDatabase.close();
    }

}

/* TO-DO */

/**
 *
 */