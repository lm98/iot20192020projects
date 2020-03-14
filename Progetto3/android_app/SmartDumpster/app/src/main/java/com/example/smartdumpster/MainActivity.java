package com.example.smartdumpster;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.smartdumpster.utils.C;

import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public class MainActivity extends AppCompatActivity {

    private BluetoothChannel btChannel;

    /**
     * Verifies presence of bluetooth module in the device, if so, asks for enabling.
     * Then initializes the UI.
     *
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.bluetooth.ENABLE_BT_REQUEST);
        }

        initUI();
    }

    /**
     * Initializes every button in UI with appropriate listener
     */
    private void initUI() {
        //Connect button
        findViewById(R.id.connect_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    connectToBTServer();
                } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                    bluetoothDeviceNotFound.printStackTrace();
                }
            }
        });

        //Junk buttons:

        findViewById(R.id.junk_btn_A).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "A";
                btChannel.sendMessage(message);
            }
        });

        findViewById(R.id.junk_btn_B).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "B";
                btChannel.sendMessage(message);
            }
        });

        findViewById(R.id.junk_btn_C).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "C";
                btChannel.sendMessage(message);
            }
        });
    }

    /**
     * Close the bluetooth channel
     */
    @Override
    protected void onStop() {
        super.onStop();

        btChannel.close();
    }

    /**
     * Updates Log with results from previous operations
     *
     * @param requestCode
     * @param resultCode
     * @param data
     */
    @Override
    protected void onActivityResult(final int requestCode, final int resultCode, @Nullable final Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_OK) {
            Log.d(C.APP_LOG_TAG, "Bluetooth enabled!");
        }

        if (requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_CANCELED) {
            Log.d(C.APP_LOG_TAG, "Bluetooth not enabled!");
        }
    }

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {

                ((TextView) findViewById(R.id.status_lable)).setText(String.format("Status : connected to server on device %s",
                        serverDevice.getName()));

                findViewById(R.id.connect_button).setEnabled(false);

                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener() {
                    @Override
                    public void onMessageReceived(String receivedMessage) {
                        ((TextView) findViewById(R.id.log_content)).append(String.format("> [RECEIVED from %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                receivedMessage));
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {
                        ((TextView) findViewById(R.id.log_content)).append(String.format("> [SENT to %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                sentMessage));
                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                ((TextView) findViewById(R.id.status_lable)).setText(String.format("Status : unable to connect, device %s not found!",
                        C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME));
            }
        }).execute();
    }
}
