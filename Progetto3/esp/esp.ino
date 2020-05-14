#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define LED_AV 16
#define LED_NAV 5
/* wifi network name */
//char* ssidName = "FASTWEB-enzo-2,4";
char* ssidName = "Wifi";
/* WPA2 PSK password */
//char* pwd = "casaenzo2017";
char* pwd = "password";
/* service IP address */ 
char* address = "http://allco.000webhostapp.com";

int flag = 0;

void setup() {
  pinMode(LED_AV, OUTPUT);    //Dichiaro il pin D0 "AVAILABLE" in Output
  pinMode(LED_NAV, OUTPUT);    //Dichiaro il pin D1 "NOT AVAILABLE" in Output
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

   if ( value >= 95 && flag == 0) { //SET DUMPSTER NOT AVAILABLE
    flag = 1;
    msg = "{avail:0,pass:pass}";
    setNAval(); //Turn on leds
   }
   else if (flag == 1){ //SET DUMPSTER AVAILABLE
    flag = 0;
    msg = "{avail:1,pass:pass}";
    setAval(); //Turn on leds
   }else{
    msg = "{ \"quantity\":"+ String(value) + "}"; 
   }
   
   int retCode = http.POST(msg);   
   http.end();
   //String payload = http.getString();  
   //Serial.println(payload);      
   return retCode;
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   

   /* read sensor from 0 to 100 kilos */
   float value = (float) analogRead(A0) * 100 / 1023.0;
   
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


void setAval(){
  digitalWrite(LED_AV,HIGH);
  digitalWrite(LED_NAV,LOW);
}

void setNAval(){
  digitalWrite(LED_NAV,HIGH);
  digitalWrite(LED_AV,LOW);
}
