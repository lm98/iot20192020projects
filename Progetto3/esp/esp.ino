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

int flag = 0;
float value = 0;
float oldvalue = 0;


int sendData(String address, float value) {  
   HTTPClient http;    
   String msg = "";

   if ( value >= 95 && flag == 0) { //SET DUMPSTER NOT AVAILABLE
    http.begin(address + "/dumpster/set_availability_esp.php");
    Serial.print("Setting dumpster not available");
    flag = 1;
    msg = "{avail:0,pass:password}";
    setNAval(); //Turn on leds
   }
   else if (flag == 1){ //SET DUMPSTER AVAILABLE
    http.begin(address + "/dumpster/set_availability_esp.php");
    Serial.print("Setting dumpster available");
    flag = 0;
    msg = "{avail:1,pass:password}";
    setAval(); //Turn on leds
   }else{ //SEND WEIGHT
    http.begin(address + "/dumpster/insert_weight.php");
    msg = "{ \"quantity\":"+ String(value) + "}"; 
   }
   
   http.addHeader("Content-Type", "application/json");
   int retCode = http.POST(msg);   
   http.end();    
   return retCode;
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
  Serial.println("Connected: \n local IP: " + WiFi.localIP());
  setAval();
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   
  
   value = (float) analogRead(A0) * 100 / 1023.0; //read sensor from 0 to 100 kilos
   
   if((value < oldvalue - 3 || value > oldvalue + 3) && value -oldvalue  > 2 ){ //Control if the weight is changed with a threshold of 3 kilos

    Serial.print("sending " + String(value - oldvalue) + "..."); //Print value sent
   
    int code = sendData(address, value); //send data

    /* log result */
    if (code == 200){
      Serial.println("ok");   
    } else {
      Serial.println("error");
    }
  }
  oldvalue = value;
  delay(5000);  
 }
 else { 
   Serial.println("Error in WiFi connection");   
 }
} 


void setAval(){
  digitalWrite(LED_AV,HIGH);
  digitalWrite(LED_NAV,LOW);
}

void setNAval(){
  digitalWrite(LED_NAV,HIGH);
  digitalWrite(LED_AV,LOW);
}
