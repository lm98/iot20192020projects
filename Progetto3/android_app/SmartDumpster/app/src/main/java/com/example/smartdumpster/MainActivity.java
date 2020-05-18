package com.example.smartdumpster;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.example.smartdumpster.utils.C;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;

public class MainActivity extends AppCompatActivity implements DumpsterBTCommunicator{
    private RequestQueue requestQueue;
    private BluetoothChannel btChannel;
    private boolean hasToken = false;

    /**
     * Token Request tag
     */
    private final String TAG = "SMART_DUMPSTER";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.bluetooth.ENABLE_BT_REQUEST);
        }

        findViewById(R.id.requestTokenButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!hasToken){
                    createTokenRequest();
                }
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();

        // Cancel token request
        if (requestQueue != null) {
            requestQueue.cancelAll(TAG);
        }
        // Close bluetooth channel
        if(btChannel != null){
            btChannel.close();
        }
    }

    /**
     * Creates the request for the token
     */
    private void createTokenRequest() {
        requestQueue = Volley.newRequestQueue(this);
        String url = "https://allco.000webhostapp.com/dumpster/permission.php";

        StringRequest stringRequest = new StringRequest(
                Request.Method.GET,
                url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        hasToken = true;
                        showMessageToast("Token Acquired!");
                        showBTFragment();
                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        hasToken = false;
                        showMessageToast("Token Denied!");
                    }
                });

        stringRequest.setTag(TAG);
        requestQueue.add(stringRequest);
    }

    /**
     * Send the trash to deposit type
     */
    @Override
    public void sendTrashType(String type) throws JSONException {
        
        requestQueue = Volley.newRequestQueue(this);
        String url = "https://allco.000webhostapp.com/dumpster/set_trash_type.php";

        JSONObject jBody = new JSONObject();
        jBody.put("type", type);

        Log.d(TAG, "sendTrashType: "+type);

        JsonObjectRequest stringRequest = new JsonObjectRequest(
                Request.Method.POST,
                url,
                jBody,
                new Response.Listener<JSONObject>() {
                    @Override
                    public void onResponse(JSONObject response) {
                        Log.d(TAG, "onResponse: "+response.toString());
                    }
                },
                new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        showBTFragment();
                        Log.d(TAG, "Error Response code: " + error.getMessage());
                    }
                });

        stringRequest.setTag(TAG);
        requestQueue.add(stringRequest);
        cancelToken();
    }

    @Override
    public boolean getTokenStatus() {
        return hasToken;
    }

    @Override
    public void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {
                showBTMessageFragment();
                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener() {
                    @Override
                    public void onMessageReceived(String receivedMessage) {
                        Log.d(TAG, "onMessageReceived: "+receivedMessage);
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {
                        Log.d(TAG, "onMessageReceived: "+sentMessage);
                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                Log.d(TAG, "onConnectionCanceled: unable to connect to device");
            }
        }).execute();
    }

    public void showBTFragment(){
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        //fragmentManager.popBackStack("BACKSTACK_BASE", FragmentManager.POP_BACK_STACK_INCLUSIVE);
        transaction.replace(R.id.fragment_bt_container, new BTFragment());
        transaction.commit();
    }

    public void showBTMessageFragment(){
        FragmentManager fragmentManager = getSupportFragmentManager();
        FragmentTransaction transaction = fragmentManager.beginTransaction();
        //fragmentManager.popBackStack("BACKSTACK_BASE", FragmentManager.POP_BACK_STACK_INCLUSIVE);
        transaction.replace(R.id.fragment_bt_message_container, new MessageFragment());
        transaction.commit();
    }

    @Override
    public void sendCodedBTMessage(String code){
        if(hasToken){
            btChannel.sendMessage(code);
            cancelToken(); //Decommentare questa riga per fare in modo che 1 token valga 1 solo deposito
        } else {
            showMessageToast("Token expired!");
        }
    }

    private void showMessageToast(String msg){
        Context context = getApplicationContext();
        int duration = Toast.LENGTH_SHORT;
        Toast toast = Toast.makeText(context, msg, duration);
        toast.show();
    }

    private void cancelToken(){
        this.hasToken = false;
        showMessageToast("You don't have token anymore");
    }
}
