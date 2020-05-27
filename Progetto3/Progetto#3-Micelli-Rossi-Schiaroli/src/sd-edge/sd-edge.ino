#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define LED_AV D0
#define LED_NAV D1
#define TRIMMER A0

float value = 0;
float oldvalue = 0;
int deposit = 0;

int sendData(float deposit) {      
   int retCode = post("{\"quantity\":"+ String(deposit) + "}","/dumpster/insert_weight.php");
   
   /*
    * If weigth is too high, post not avail state to service and switch led state
    */
   if (value >= 95){  
    setNotAvailable();
    Serial.println("Setting dumpster not available, response:" + String(post("{\"avail\":0,\"pass\":\"password\"}","/dumpster/set_availability_esp.php")));
   }
   return retCode;
}

int isAvailable() {
   if(post("","/dumpster/permission.php") == 200){
    return 1;
   } else {
    return 0;
   }
}

void setup() {
  char* ssidName = "Casa Wifi"; //Network name
  char* pwd = "penny2015"; //Wifi network password
  pinMode(LED_AV, OUTPUT);    //Dichiaro il pin D0 "AVAILABLE" in Output
  pinMode(LED_NAV, OUTPUT);    //Dichiaro il pin D1 "NOT AVAILABLE" in Output
  pinMode(TRIMMER, OUTPUT);    //Dichiaro il pin D1 "NOT AVAILABLE" in Output
  Serial.begin(115200);                                
  WiFi.begin(ssidName, pwd);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  } 
  if(isAvailable()){
    setAvailable();
  } else {
    setNotAvailable();
  }
}
   
void loop() { 
 if (WiFi.status()== WL_CONNECTED){   
   
   /* 
    *  Read value from trimmer
    */
   value = (float) analogRead(TRIMMER) * 100 / 1023.0;
   
   /*
    * Check if value has dropped from the previous one
    */
   deposit = value - oldvalue;
   
   /*
    * Check if the deposit value is > than 3 (error tolerance)
    * and if the new value is greater than 0 (plus tolerance)
    */
   if(deposit > 3 && value > 3) {
    
    /*
     * Check if service responde with HTTP response code = 200
     */
    if(isAvailable()){
      setAvailable();
      Serial.println("Deposit " + String(deposit) + "Total:" + String(value)); //Print value sent
      if (sendData(deposit) == 200){
        Serial.println("Deposit ok");   
      } else {
        Serial.println("Deposit error");
      } 
    } else {
      setNotAvailable();
      Serial.println("Dumpster not available"); 
    }
  }
  oldvalue = value; //Update value read
  delay(5000); //Wait 5 seconds for new reading
 } else { 
   Serial.println("Error in WiFi connection");   
 }
} 

/*
 * Send post message with json message msg to url address + page
 */
int post(String msg,String page){
   HTTPClient http;
   http.begin("http://allco.000webhostapp.com" + page);
   http.addHeader("Content-Type", "application/json");
   int retCode = http.POST(msg);   
   http.end();    
   return retCode;
}

/*
 * These procedures switch the state of available/not available leds
 */
void setAvailable(){
  digitalWrite(LED_AV,HIGH);
  digitalWrite(LED_NAV,LOW);
}

void setNotAvailable(){
  digitalWrite(LED_NAV,HIGH);
  digitalWrite(LED_AV,LOW); 
}
