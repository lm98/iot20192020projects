#include <Servo.h>
#include "SoftwareSerial.h"
#include "MsgServiceBT.h"

/*
 * Define led,bluetoot serial and servo pins
 */
#define LED_1 7
#define LED_2 8
#define LED_3 9
#define motorPos 10
#define RX 3
#define TX 2

MsgServiceBT msgService(TX, RX);

Servo motor;
String message;
unsigned long delta;
int state = 0;
int garbageState = 0;// 0 -> close, 1 -> open
unsigned long timeInterval = 15000; //Set the limit of available time 

void setup() {
  msgService.init();
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  motor.attach(motorPos);
  Serial.begin(9600); //set baud rate
  while (!Serial) {}
  Serial.println("ready to go.");
}

void loop() {
  if (msgService.isMsgAvailable()) {
    Msg* msg = msgService.receiveMsg();
    Serial.println(msg->getContent());
    if (msg->getContent() == "A") {
      if (state != 1) {
        state = 1;
        control(LED_1);
      }
    }
    else  if (msg->getContent() == "B") {
      if (state != 2) {
        state = 2;
        control(LED_2);
      }
    }
    else if (msg->getContent() == "C") {
      if (state != 3) {
        state = 3;
        control(LED_3);
      }
    }
    else if (msg->getContent() == "T") {
      delta = millis();
    }
    delete msg;
  }
  if (millis() - delta > timeInterval) {
      if(garbageState==1){
        closeGarbage();
        garbageState = 0;
      }
  }
}

void openGarbage() {
  motor.attach(motorPos);
  for (int pos = 0; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    motor.write(pos);                        // tell servo to go to position in variable 'pos'
    delay(15);                               // waits 15ms for the servo to reach the position
  }
  motor.detach();
  delta = millis();
}

void closeGarbage() {
  motor.attach(motorPos);
  for (int pos = 180; pos >= 0; pos -= 1) {  // goes from 180 degrees to 0 degrees
    motor.write(pos);                        // tell servo to go to position in variable 'pos'
    delay(15);                               // waits 15ms for the servo to reach the position
  }
  turnOff(LED_1);
  turnOff(LED_2);
  turnOff(LED_3);
  motor.detach();
  state=0;
}

void turnOn(int led) {
  digitalWrite(led, HIGH);
}

void turnOff(int led) {
  digitalWrite(led, LOW);
}

/*
 *  If the can is available, turn the led and open the garbage
 */
void control(int led){
  if(garbageState==0){
    turnOn(led);
    delta = millis();
    openGarbage();
    garbageState = 1;
  }
}
