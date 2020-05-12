package com.example.smartdumpster;

import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public interface DumpsterBTCommunicator {

    void connectToBTServer() throws BluetoothDeviceNotFound;

    /**
     * Send a code String representing a message
     * @param code  Message code;
     */
    void sendCodedBTMessage(String code);
}
