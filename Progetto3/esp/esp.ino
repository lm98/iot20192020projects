#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

/* wifi network name */
//char* ssidName = "FASTWEB-enzo-2,4";
char* ssidName = "Wifi";
/* WPA2 PSK password */
//char* pwd = "casaenzo2017";
char* pwd = "password";
/* service IP address */ 
char* address = "http://allco.000webhostapp.com";

void setup() { 
  Serial.begin(115200);                                
  WiFi.begin(ssidName, pwd);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  } 
  Serial.println("Connected: \n local IP: "+WiFi.localIP());
}

int sendData(String address, float value, int type){  
   HTTPClient http;    
   http.begin(address + "/dumpster/insert_weight.php");      
   http.addHeader("Content-Type", "application/json");
   String msg = "";
   
   switch(type){
    case 1:
      msg = "{ \"a\":"+ String(value) +",\"b\":" + String(0) + ",\"c\":" + String(0) +"}";
      break;
     case 2:
      msg = "{ \"a\":"+ String(0) +",\"b\":" + String(value) + ",\"c\":" + String(0) +"}";
      break;
     case 3:
      msg = "{ \"a\":"+ String(0) +",\"b\":" + String(0) + ",\"c\":" + String(value) +"}";
      break;
     default:
      msg = "Error on creating string";
      break;
   }
    
   int retCode = http.POST(msg);   
   http.end();  
      
   //String payload = http.getString();  
   //Serial.println(payload);      
   return retCode;
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   

   /* read sensor */
   float value = (float) analogRead(A0) *100 / 1023.0;
   
   /* send data */
   Serial.print("sending " + String(value) + "...");
   
   int type = 1;
   //type vale 1 se ho un rifiuto di tipo "a", 2 per "b" e 3 per "c"
   int code = sendData(address, value, type); 

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
