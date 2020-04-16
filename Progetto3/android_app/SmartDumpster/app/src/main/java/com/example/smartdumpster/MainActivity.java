package com.example.smartdumpster;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonArrayRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity {
    RequestQueue requestQueue;
    TextView tokenStatusView;
    /**
     * Token Request tag
     */
    private final static String TAG = "TOKEN_REQUEST";
    /**
     * Token serves as a permission to open the physical dumpster
     */
    private JSONObject token;
    private boolean hasToken;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        hasToken = false;

        findViewById(R.id.requestTokenButton).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!hasToken) {
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
    }

    /**
     * Creates the request for the token
     */
    private void createTokenRequest() {
        requestQueue = Volley.newRequestQueue(this);
        String url = "http://localhost/dumpster/permission.php";
        JsonArrayRequest jsonArrayRequest = new JsonArrayRequest
                (Request.Method.GET, url, null, new Response.Listener<JSONArray>() {
                    @Override
                    public void onResponse(JSONArray response) {
                        try {
                            token = response.getJSONObject(0);
                            setTokenStatus(true);
                        } catch (JSONException e) {
                            e.printStackTrace();
                            setTokenStatus(false);
                        }
                    }
                }, new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        Log.d("LAB", error.toString());
                    }
                });
        jsonArrayRequest.setTag(TAG);

        // Add the request to the RequestQueue.
        requestQueue.add(jsonArrayRequest);
    }

    private void setTokenStatus(boolean tokenObtained){
       if(tokenObtained){
           hasToken = true;
           tokenStatusView.setText(R.string.tokenOk);
       } else {
           hasToken = false;
           tokenStatusView.setText(R.string.tokenNok);
       }
    }
}
