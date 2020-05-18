package com.example.smartdumpster;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;

import org.json.JSONException;

public class MessageFragment extends Fragment {
    private DumpsterBTCommunicator btCommunicator;

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        try {
            btCommunicator = (DumpsterBTCommunicator) context;
        } catch (ClassCastException e) {
            throw new ClassCastException(context.toString() + " must implement DumpsterBTCommunicator");
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        View v= (ViewGroup) inflater.inflate(
                R.layout.fragment_bt_communication, container, false);

        v.findViewById(R.id.aButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(btCommunicator.getTokenStatus()){
                    try {
                        btCommunicator.sendTrashType("a");
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    btCommunicator.sendCodedBTMessage("A");
                }
            }
        });

        v.findViewById(R.id.bButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(btCommunicator.getTokenStatus()){
                    try {
                        btCommunicator.sendTrashType("b");
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    btCommunicator.sendCodedBTMessage("B");
                }
            }
        });

        v.findViewById(R.id.cButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(btCommunicator.getTokenStatus()){
                    try {
                        btCommunicator.sendTrashType("c");
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    btCommunicator.sendCodedBTMessage("C");
                }
            }
        });

        v.findViewById(R.id.timeButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                btCommunicator.sendCodedBTMessage("T");
            }
        });
        return v;
    }
}
