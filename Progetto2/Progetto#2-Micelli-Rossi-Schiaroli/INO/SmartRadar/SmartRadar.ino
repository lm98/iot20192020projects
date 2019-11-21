#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "MsgService.h"
#include "EventCheck.h"
#include "SingleMode.h"
#include "ManualMode.h"
#include "AutoMode.h"

//NB VALUTARE DI CANCELLARE LE CLASSI DI SONAR (BASTA IL TASK)

//Macros
#define POT A0
#define SERVO 6
#define SPEED_MIN 3
#define SPEED_MAX 8
#define PIR_PIN 2
#define ECHO_PIN 3
#define TRIG_PIN 4
#define CALIBRATION_TIME_SEC 10
#define BUTTON_SINGLE 9
#define BUTTON_MANUAL 10
#define BUTTON_AUTO 11

//Define scheduler
Scheduler scheduler;

//Define Tasks
ServoMove *servoTask;
SonarScan *sonarTask;
EventCheck *eventTask;
ManualMode *manualTask;
AutoMode *autoTask;
SingleMode *singleTask;

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
  scheduler.init(150); //Scheduler initialize
  state = MANUAL; // Starting modality
  MsgService.init(); //Initialize message receiving from serial

  //Pin Input
  pinMode(POT,INPUT);
  pinMode(BUTTON_SINGLE,INPUT);
  pinMode(BUTTON_MANUAL,INPUT);
  pinMode(BUTTON_AUTO,INPUT);

  //Pin output
  pinMode(SERVO,OUTPUT);
  
  //Setting event checker task
  eventTask = new EventCheck();
  eventTask->init(150);
  eventTask->setActive(true);
  scheduler.addTask(eventTask);

  //Setting manual mode task
  manualTask = new ManualMode();
  manualTask->init(1500);
  manualTask->setActive(false);
  scheduler.addTask(manualTask);

  //Setting single mode task
  autoTask = new AutoMode();
  autoTask->init(1500);
  autoTask->setActive(false);
  scheduler.addTask(autoTask);

  //Setting auto mode task
  singleTask = new SingleMode(PIR_PIN);
  singleTask->init(1500);
  singleTask->setActive(false);
  scheduler.addTask(singleTask);

  //Setting servo movement task
  servoTask = new ServoMove(SERVO, 18); //Second param = 1
  servoTask->init(450);
  servoTask->setActive(false);
  scheduler.addTask(servoTask);
  
  //Setting sonar scanning scan
  sonarTask = new SonarScan(TRIG_PIN,ECHO_PIN);
  sonarTask->init(450);
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

void syncronize(){
  if (MsgService.isMsgAvailable()){
  Msg* msg = MsgService.receiveMsg();
    if(msg->getContent() == "ping"){
      delay(200);
      MsgService.sendMsg("pong");
    }
    connEnabled = true;
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
