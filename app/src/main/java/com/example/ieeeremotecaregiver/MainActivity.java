package com.example.ieeeremotecaregiver;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    /** Called when the user taps the Patient button */
    public void redirectToPatient(View view) {
        Intent intent = new Intent(this, PatientPage.class);
        startActivity(intent);
    }

    /** Called when the user taps the Patient button */
    public void redirectToCaregiver(View view) {
        Intent intent = new Intent(this, CaregiverPage.class);
        startActivity(intent);
    }
}