#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define LED_AV D0
#define LED_NAV D1

/* wifi network name */
//char* ssidName = "FASTWEB-enzo-2,4";
char* ssidName = "Wifi";

/* WPA2 PSK password */
//char* pwd = "casaenzo2017";
char* pwd = "password";

/* service IP address */ 
char* address = "http://allco.000webhostapp.com";

HTTPClient http;
int flag = 0;
float value = 0;
float oldvalue = 0;

int sendData(float value) {      
   String msg = "{ \"quantity\":"+ String(value) + "}";
   http.begin(address + String("/dumpster/insert_weight.php"));
   http.addHeader("Content-Type", "application/json");
   int retCode = http.POST(msg);   
   http.end();
   if (value >= 95){  
    setNAvail();
    postNotAvail();
   }    
   return retCode;
}

int isAvailable() {     
   http.begin(address + String("/dumpster/permission.php"));
   http.addHeader("Content-Type", "application/json");
   int retCode = http.POST("");   
   http.end();    
   if(retCode == 200){
    setAvail();
    flag = 1;
   } else if (retCode == 418) {
    setNAvail();
    flag = 0;
   } else {
    Serial.println("Error asking dumpster state");
   }
   
  return flag;
}

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
  Serial.println("\nConnected: \n local IP: " + WiFi.localIP());
  if(isAvailable()){
    setAvail();
  } else {
    setNAvail();
  }
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   
    
   value = (float) analogRead(A0) * 100 / 1023.0; //read sensor from 0 to 100 kilos
   
   if((value < oldvalue - 3 || value > oldvalue + 3) && value > 3) { //Control if the weight is changed with a threshold of 3 kilos

    Serial.print("sending " + String(value - oldvalue) + "..."); //Print value sent
    if(isAvailable()){
    
    int code = sendData(value - oldvalue); //send data
       
    if (code == 200){
      Serial.println("ok");   
    } else {
      Serial.println("error");
    } 
   } 
  }
  oldvalue = value;
  delay(5000);  
 } else { 
   Serial.println("Error in WiFi connection");   
 }
} 

void setAvail(){
  digitalWrite(LED_AV,HIGH);
  digitalWrite(LED_NAV,LOW);
}

void setNAvail(){
  digitalWrite(LED_NAV,HIGH);
  digitalWrite(LED_AV,LOW); 
}

int postNotAvail(){    
   String msg = "{avail:0,pass:password}";
   http.begin(address + String("/dumpster/set_availability_esp.php"));
   http.addHeader("Content-Type", "application/json");
   int retCode = http.POST(msg);   
   http.end();    
   return retCode;
}
