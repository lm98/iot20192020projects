package com.example.smartdumpster;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.fragment.app.Fragment;

import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public class BTFragment extends Fragment {
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
                R.layout.fragment_bt_connect, container, false);

        v.findViewById(R.id.btButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    btCommunicator.connectToBTServer();
                } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                    bluetoothDeviceNotFound.printStackTrace();
                }
            }
        });
        return v;
    }
}
