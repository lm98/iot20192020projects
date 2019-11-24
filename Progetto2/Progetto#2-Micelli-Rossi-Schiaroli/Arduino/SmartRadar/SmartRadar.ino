#include "Scheduler.h"
#include "ServoMove.h"
#include "SonarScan.h"
#include "MsgService.h"
#include "EventCheck.h"
#include "SingleMode.h"
#include "ManualMode.h"
#include "AutoMode.h"
#include "SlowBlink.h"
#include "SleepMode.h"


//Macros
#define POT_PIN 14
#define LED_A_PIN 8
#define LED_D_PIN 7
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
#define N 18

//Define scheduler
Scheduler scheduler;

//Define Tasks
EventCheck *eventTask;
ManualMode *manualTask;
AutoMode *autoTask;
SingleMode *singleTask;
ServoMove *servoTask;
SonarScan *sonarTask;
SlowBlink *ledATask;
SlowBlink *ledDTask;
SleepMode *sleepTask;

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
  MANUAL,
  SINGLE,
  AUTO
} state;

void setup()
{
  Serial.begin(9600); //Begin serial communication with 9600 baud
  scheduler.init(150); //Scheduler initialize
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
  scheduler.addTask(manualTask);

  //Setting auto mode task
  autoTask = new AutoMode(D_NEAR, D_FAR, POT_PIN);
  autoTask->init(1500);
  scheduler.addTask(autoTask);

  //Setting single mode task
  singleTask = new SingleMode(PIR_PIN, POT_PIN);
  singleTask->init(1500);
  scheduler.addTask(singleTask);

  //Setting servo movement task
  servoTask = new ServoMove(SERVO, N); //Second param = 1
  servoTask->init(450);
  scheduler.addTask(servoTask);
  
  //Setting sonar scanning task
  sonarTask = new SonarScan(TRIG_PIN,ECHO_PIN);
  sonarTask->init(450);
  scheduler.addTask(sonarTask);

  //Setting alarm led task
  ledATask = new SlowBlink(LED_A_PIN);
  ledATask->init(150);
  scheduler.addTask(ledATask);  //Setting alarm led task
 
  //Setting detection led task
  ledDTask = new SlowBlink(LED_D_PIN);
  ledDTask->init(150);
  scheduler.addTask(ledDTask);

  //Setting sleeping mode task
  sleepTask = new SleepMode();
  sleepTask->init(300);
  scheduler.addTask(sleepTask);


}

void loop(){

  scheduler.schedule();
}