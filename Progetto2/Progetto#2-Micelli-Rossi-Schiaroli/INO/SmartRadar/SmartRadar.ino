#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "MsgService.h"
#include "EventCheck.h"
#include "SingleMode.h"
#include "ManualMode.h"
#include "AutoMode.h"
#include "SlowBlink.h"

//NB VALUTARE DI CANCELLARE LE CLASSI DI SONAR (BASTA IL TASK)

//Macros
#define POT_PIN 14
#define LED_PIN 8
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
#define D_NEAR 0.3
#define D_FAR 0.8

//Define scheduler
Scheduler scheduler;

//Define Tasks
EventCheck *eventTask;
ManualMode *manualTask;
AutoMode *autoTask;
SingleMode *singleTask;
ServoMove *servoTask;
SonarScan *sonarTask;
SlowBlink *ledTask;

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
  //manualTask->setActive(true); // On program start, it begins in manual mode
  scheduler.addTask(manualTask);

  //Setting auto mode task
  autoTask = new AutoMode(D_NEAR, D_FAR);
  autoTask->init(1500);
  scheduler.addTask(autoTask);

  //Setting single mode task
  singleTask = new SingleMode(PIR_PIN, POT_PIN);
  singleTask->init(1500);
  scheduler.addTask(singleTask);

  //Setting servo movement task
  servoTask = new ServoMove(SERVO, 18); //Second param = 1
  servoTask->init(450);
  scheduler.addTask(servoTask);
  
  //Setting sonar scanning scan
  sonarTask = new SonarScan(TRIG_PIN,ECHO_PIN);
  sonarTask->init(450);
  scheduler.addTask(sonarTask);

  //Setting alarm led task
  ledTask = new SlowBlink(LED_PIN);
  ledTask->init(450);
  scheduler.addTask(ledTask);
  }

void loop(){
  
  if(connEnabled==false){
    syncronize();
  }
  
  scheduler.schedule();
}

void syncronize(){
  if (MsgService.isMsgAvailable()){

    Msg* msg = MsgService.receiveMsg();
    if(msg->getContent() == "ping"){
      delay(200);
      MsgService.sendMsg("pong");
    }
    state = MANUAL;
    connEnabled = true;
  }
}

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
