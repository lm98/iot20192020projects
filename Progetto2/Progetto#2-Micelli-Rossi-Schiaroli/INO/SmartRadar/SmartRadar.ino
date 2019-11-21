#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "MsgService.h"
#include "EventCheck.h"

//Macros
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

//Define scheduler
Scheduler scheduler;

//Define Tasks
ServoMove *servoTask;
SonarScan *sonarTask;
EventCheck *eventTask;

//Define variables
int servoSpeed = 0;
int currentSpeed = SPEED_MIN;
int value;
boolean connEnabled = false;
boolean stateEnabled = false;
boolean dirRecv = false;
boolean messageSent = false;
boolean rightPosition = false;
float precValue;
float distance;

//Define objects
Msg* msg;

//Define different state enumeration
enum modality {
  SINGLE,
  MANUAL,
  AUTO
} state;

void setup()
{
  Serial.begin(9600); //Begin serial communication with 9600 baud
  scheduler.init(100); //Scheduler initialize
  state = MANUAL; // Starting modality
  MsgService.init(); //Initialize message receiving from serial

  //Pin Input
  pinMode(PIR_PIN,INPUT);
  pinMode(POT,INPUT);
  pinMode(BUTTON_SINGLE,INPUT);
  pinMode(BUTTON_MANUAL,INPUT);
  pinMode(BUTTON_AUTO,INPUT);
  pinMode(TRIG_PIN,INPUT);

  //Pin output
  pinMode(ECHO_PIN,OUTPUT);
  pinMode(SERVO,OUTPUT);
  
  //Setting event checker task
  eventTask = new EventCheck();
  eventTask->init(250);
  eventTask->setActive(true);
  scheduler.addTask(eventTask);

  //Setting servo movement task
  servoTask = new ServoMove(SERVO, 1);
  servoTask->init(200);
  servoTask->setActive(false);
  scheduler.addTask(servoTask);
  
  //Setting sonar scanning scan
  sonarTask = new SonarScan(TRIG_PIN,ECHO_PIN);
  sonarTask->init(250);
  sonarTask->setActive(false);
  scheduler.addTask(sonarTask);
  
  }

void loop(){
  if(connEnabled==false){
    syncronize();
  }
//  switch(state){
//    case SINGLE:
//        //Setto velocità in base a param
//        /**
//         * scheduler.shutDownAllTasks();
//         * scheduler.activateTask(giustoTask);
//         */
//      break;
//      case MANUAL:
//         
//         //Move to the last setted position
//         if(stateEnabled  && connEnabled){
//            moveToPosition();
//            if(t0->getReached()==true){
//              rightPosition=true;
//            }
//         }
//         
//         //Send console object distance
//         if(rightPosition){       
//                setScan(true);//Start scan
//                precValue = 0;
//                distance = t1->getDistance();
//                if(precValue != distance){
//                  MsgService.sendMsg(String("MANUAL") + " " + String(value) + " " + String(distance));  
//                  precValue = t1->getDistance();
//                }
//         }
//      break;
//      case AUTO:
//        //Setto velocità in base a param
//        /**
//         * scheduler.shutDownAllTasks();
//         * scheduler.activateTask(giustoTask);
//         * ...
//         */
//      default:
//      break;
//  }
  scheduler.schedule();
}

void setSpeed(int current){
  int newer = map(analogRead(POT),0,1023,3,8);
  if(current!=newer){
    current=newer;
  }
}

void setScan(bool value){
  sonarTask->setActive(value);
}

void syncronize(){
  if (MsgService.isMsgAvailable()){
  Msg* msg = MsgService.receiveMsg();
    if(msg->getContent() == "ping"){
      MsgService.sendMsg("pong");
    }
    connEnabled = true;
  }
}

void moveToPosition(){
  if(MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    value = msg->getContent().toInt();
    MsgService.sendMsg("OK");
    servoTask->setActive(true);
    servoTask->setNewPosition(value);
  }
}


//
//  //Controllo presenza con pir -> mettere su task
//  if (digitalRead(PIR_PIN) == HIGH){
//    //Serial.println("detected!");
//    //Segnalo presenza in qualche modo  
//  }

/*
  Serial communication rules:

  Manual message param:
    Sending: <MANUAL> <angle> <distance>
    Receive: <direction> 

  Single message param:
    Sending: <SINGLE> <angle> and <distance>
      Ps. there can be several line sented over serial
    Receiving: <Speed value>

  Auto message param:
    Sending: <angle> <distance>
      or <alarm> <value> value can be alarmTrue/False
      or TrackingTrue/False
      or TrackingTrue + distance
    Receiving: <Value>
      User can change servo speed with specified value
*/
