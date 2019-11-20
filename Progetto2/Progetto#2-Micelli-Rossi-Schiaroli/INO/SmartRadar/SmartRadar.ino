#include "Scheduler.h"
#include "ServoMove.h"
#include "MsgService.h"

#define POT A0
#define SERVO 6
#define SPEED_MIN 3
#define SPEED_MAX 8
#define PIR_PIN 2
#define ECHO_PIN 3
#define TRIG_PIN 4
#define CALIBRATION_TIME_SEC 10
#define BUTTON_SINGLE 3
#define BUTTON_MANUAL 4
#define BUTTON_AUTO 5


Scheduler scheduler;
int param;
int servoSpeed = 0;
int currentSpeed = SPEED_MIN;
int distance=0;
String result;
boolean connEnabled = false;
boolean stateEnabled = false;
boolean dirRecv = false;
boolean messageSent = false;
Msg* msg;

String statement;


enum service_type
{
  SINGLE,
  MANUAL,
  AUTO
} state;

void setup()
{
  Serial.begin(9600); //Begin serial communication with 9600 baud
  scheduler.init(100); //Scheduler initialize
  state = MANUAL; // Starting mode
  MsgService.init(); 
  pinMode(PIR_PIN,INPUT);
  pinMode(POT,INPUT);
  pinMode(BUTTON_SINGLE,INPUT);
  pinMode(BUTTON_MANUAL,INPUT);
  pinMode(BUTTON_AUTO,INPUT);
  ServoMove *t0 = new ServoMove(SERVO, 1);
  t0->setNewPosition(180); 
  t0->init(1000);
  scheduler.addTask(t0);
}

void loop()
{

//  //Controllo eventuale pressione pulsanti -> mettere su task
//  if(digitalRead(BUTTON_SINGLE) == HIGH){
//    state = SINGLE;
//  }
//  if(digitalRead(BUTTON_MANUAL) == HIGH){
//    state = MANUAL;
//  }
//  if(digitalRead(BUTTON_AUTO)== HIGH){
//    state = AUTO;
//  }
//
//  //Controllo presenza con pir -> mettere su task
//  if (digitalRead(PIR_PIN) == HIGH){
//    //Serial.println("detected!");
//    //Segnalo presenza in qualche modo  
//  }


  
  //If connenction is not already setted,ì
  //I control if a connection message is  arrived
  if (connEnabled == false) {
    syncronize();
  }

  //If setting is not already setted, and connection is already made
  //I control if a setting message is  arrived
  if(stateEnabled == false && connEnabled == true){
    setState();
  }
  
  switch(state){
    case SINGLE:
        //Setto velocità in base a param
        /**
         * scheduler.shutDownAllTasks();
         * scheduler.activateTask(giustoTask);
         * ...
         */
      break;
      case MANUAL:
        //Setto direction in base a param
        /**
         * scheduler.shutDownAllTasks();
         * scheduler.activateTask(giustoTask);
         * ...
         */
         //Direziono in base al valore ricevuto


         //Elaboro risposta
         if (!dirRecv && MsgService.isMsgAvailable()) {
            Msg* msg = MsgService.receiveMsg();
            int value = msg->getContent().toInt();
            MsgService.sendMsg("OK");
            dirRecv=false;
            //Avvio movimento verso direzione value
            //Quando ho finito
            MsgService.sendMsg(String("MANUAL") + " " + String(value) + " " + String(distance));
         }
      break;
      case AUTO:
        //Setto velocità in base a param
        /**
         * scheduler.shutDownAllTasks();
         * scheduler.activateTask(giustoTask);
         * ...
         */
      default:
      break;
  }
  scheduler.schedule();
}

void setSpeed(int current){
  int newer = map(analogRead(POT),0,1023,3,8);
  if(current!=newer){
    current=newer;
  }
}

void syncronize(){
  if (MsgService.isMsgAvailable()){
  Msg* msg = MsgService.receiveMsg();
    if(msg->getContent() == "ping"){
      delay(2000);
      MsgService.sendMsg("pong");
    }
    connEnabled = true;
  }
}

void setState(){
  if(MsgService.isMsgAvailable()){
    if(msg->getContent()=="s"){
      state = SINGLE;
      MsgService.sendMsg("OK");
    }
    else if(msg->getContent()=="m"){
      state = MANUAL;
      MsgService.sendMsg("OK");
    }
    else if(msg->getContent()=="a"){
      state = AUTO;
      MsgService.sendMsg("OK");
    }else{
      MsgService.sendMsg("Error");
    }
    /* NOT TO FORGET: message deallocation */
    delete msg;
    stateEnabled = true;
  }
}
/* 
  Serial communication rules:

  Manual message param:
    Sending: <direction> <isTakingOver> <distance>
      The first is the radius between the sonar and 0, it is a value between 0 and 180 more or less
      The second is a boolean indicating if the sonar is taking over any object
      The third is the distance between object and the sonar, if it is negative indicate no object 
    Receive: <direction>

  Single message param:
    Sending: <angle> and <distance>
      For each object identified, i send <angle> and <distance>
    Receiving: <Value>
      User can change servo speed with specified value

  Auto message param:
    Sending: <angle> <distance>
      or <alarm> <value> value can be alarmTrue/False
      or TrackingTrue/False
      or TrackingTrue + distance
    Receiving: <Value>
      User can change servo speed with specified value
*/
