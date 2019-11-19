#include "Scheduler.h"
#include "ServoMove.h"
#include "MsgService.h"

Scheduler scheduler;

#define POT A0
#define speedMin 3
#define speedMax 8

#define buttonSingle 3;
#define buttonSingle 4;
#define buttonSingle 5;

int param;
int servoSpeed = 0;
int currentSpeed = speedMin;
String result;
boolean connEnabled = false;
boolean stateEnabled = false;
boolean dirRecv=false;
boolean messageSent=false;
Msg* msg;
int distance=0;

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
  
  ServoMove *t0 = new ServoMove(6, 1);
  t0->setNewPosition(180); 
  t0->init(1000);
  scheduler.addTask(t0);

}

void loop()
{
  if(currentSpeed!=getSpeed()){
    currentSpeed=getSpeed();
  }
  //Controllo eventuale pressione pulsanti -> mettere su task
  if(buttonSingle == HIGH){
    state = SINGLE;
  }
  if(buttonManual == HIGH){
    state = MANUAL;
  }
  if(buttonAuto == HIGH){
    state = AUTO;
  }
  //Se non è ancora settata la connessione, controllo se
  //ho messaggi in arrivo TODO in inglese
  if (!connEnabled && MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    if(msg->getContent()=="ping"){
      delay(200);
      MsgService.sendMsg("pong");
    }
    connEnabled = true;
  }
  if(!stateEnabled && MsgService.isMsgAvailable()){
    if(result=="s"){
      state = SINGLE;
      MsgService.sendMsg("State setted");
    }
    else if(result=="m"){
      state = MANUAL;
      MsgService.sendMsg("State setted");
    }
    else if(result=="a"){
      state = AUTO;
      MsgService.sendMsg("State setted");
    }else{
      //Code here should not be reached!!
      //Maybe yes i should think about it
      param = result.toInt();
      MsgService.sendMsg("Value received");
    }
    /* NOT TO FORGET: message deallocation */
    delete msg;
    stateEnabled = true;
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


void setSpeed(int param){
  //TODO 
  servoSpeed = param;
}

int getSpeed(){
  return map(analogRead(POT),0,1023,3,8);
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
