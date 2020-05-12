package com.example.smartdumpster;

public interface DumpsterBTCommunicator {

    /**
     * Send a code String representing a message
     * @param code  Message code;
     */
    void sendCodedBTMessage(String code);
}
