package com.example.jessepeterson_inventory;


/**
 * @author Jesse Peterson
 * 09/21/2024
 * CS499 Software Development Enhancement
 * SessionManager
 * This class is a singlton which is used to store variables for use in the active session
 */
public class SessionManager {

    // only instance of SessionManager singleton
    private static final SessionManager session = new SessionManager();

    // Private constructor
    private SessionManager() {

    }

    // returns the only instance
    public static SessionManager getInstance() {
        return session;
    }


    /**   Session Variables   **/
    private String USERNAME;

    private boolean THEME = false;

    private int SMS_QTY = 0;

    private boolean SMS_DELETE = false;

    /**   Getters for session variables   **/
    public String getUsername() { return USERNAME; }

    public boolean getTheme() { return THEME; }

    public int getSms_Qty() { return SMS_QTY; }

    public boolean getSms_Delete() { return SMS_DELETE; }

    /** Setters for session variables   **/
    public void setUsername(String username) { USERNAME = username; }

    public void setTheme(boolean theme) { THEME = theme; }

    public void setSms_Qty(int Sms_Qty) { SMS_QTY = Sms_Qty; }

    public void setSms_Delete(boolean Sms_Delete) { SMS_DELETE = Sms_Delete; }



}
