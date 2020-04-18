#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

/* wifi network name */
char* ssidName = "FASTWEB-enzo-2,4";
/* WPA2 PSK password */
char* pwd = "casaenzo2017";
/* service IP address */ 
char* address = "http://*.ngrok.io";

/*
 * Questo programma invia ogni ~5 secondi un messaggio json al service
 * comunicando il peso del cassonetto, letto dal potenziometro
 */
void setup() { 
  Serial.begin(115200);                                
  WiFi.begin(ssidName, pwd);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  } 
  Serial.println("Connected: \n local IP: " + WiFi.localIP());
}

int sendData(String address, float value, String place){  
   HTTPClient http;    
   http.begin(address + "/api/data");      
   http.addHeader("Content-Type", "application/json");     
   String msg = 
    String("{ \"value\": ") + String(value) + 
    ", \"place\": \"" + place +"\" }";
   int retCode = http.POST(msg);   
   http.end();  
      
   // String payload = http.getString();  
   // Serial.println(payload);      
   return retCode;
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   

   /* read sensor */
   float value = (float) analogRead(A0) / 1023.0;
   
   /* send data */
   Serial.print("sending "+String(value)+"...");    
   int code = sendData(address, value, "home");

   /* log result */
   if (code == 200){
     Serial.println("ok");   
   } else {
     Serial.println("error");
   }
 } else { 
   Serial.println("Error in WiFi connection");   
 }
 
 delay(5000);  
 
}
