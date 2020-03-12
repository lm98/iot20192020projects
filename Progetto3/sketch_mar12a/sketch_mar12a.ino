#include "MsgServiceBT.h"
#include "SoftwareSerial.h"
#include <Servo.h>


/*
 * Bluetooth's pin
 */
#define BT_TX 2
#define BT_RX 3

/*
 * Led's pin
 */
#define LED_1 7
#define LED_2 8
#define LED_3 9

#define servo 10

Servo my_servo;
MsgServiceBT msgService(BT_TX,BT_RX);

bool flag=false;
float timeRequested = 15;

void setup() {
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);
  pinMode(LED_3,OUTPUT);
  msgService.init();
  Serial.begin(9600);
  while(!Serial){
    Serial.print(".");
    delay(100);
  }
  Serial.println("ready!");
  my_servo.attach(servo);
}

void loop() {
   flag=false;
   if (msgService.isMsgAvailable()) {
    Msg* msg = msgService.receiveMsg();
    Serial.println(msg->getContent());    
    if (msg->getContent() == "RIFIUTO_A"){
       msgService.sendMsg(Msg("rcv"));
       digitalWrite(LED_1,HIGH);
       flag=true;
       delay(500);
    }
    else if (msg->getContent() == "RIFIUTO_B"){
       msgService.sendMsg(Msg("rcv"));
       digitalWrite(LED_2,HIGH);
       flag=true;
       delay(500);
    }
    else if (msg->getContent() == "RIFIUTO_C"){
       msgService.sendMsg(Msg("rcv"));
       digitalWrite(LED_3,HIGH);
       flag=true;
       delay(500);
    }
    else {
      msgService.sengMsg(Msg("ERRORE"));
    }
    if(flag){
      openDumpester();
      if(timeElapsed>timeRequested){
        closeDumpster();
      }
    }
    delete msg;
  }
}


void openDumpster(){
   my_servo.write(180);
}

void closeDumpster(){
  my_servo.write(0);
}

void addTime(){
  timeRequested += 15;
}
