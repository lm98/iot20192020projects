package com.example.smartdumpster;

import org.json.JSONException;

import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public interface DumpsterBTCommunicator {

    void connectToBTServer() throws BluetoothDeviceNotFound;

    /**
     * Send a code String representing a message
     * @param code  Message code;
     */
    void sendCodedBTMessage(String code);

    void sendTrashType(String type) throws JSONException;

    boolean getTokenStatus();
}
