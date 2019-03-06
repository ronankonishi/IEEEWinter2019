package com.example.ieeeremotecaregiver;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /** Called when the user taps the Patient button */
    public void redirectToPatient(View view) {
        Intent intent = new Intent(this, PatientActivity.class);
        startActivity(intent);
    }

    /** Called when the user taps the Patient button */
    public void redirectToCaregiver(View view) {
        Intent intent = new Intent(this, CaregiverActivity.class);
        startActivity(intent);
    }
}