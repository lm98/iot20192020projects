#include "Scheduler.h"
#include "ServoMove.h"
#include "MsgService.h"

Scheduler scheduler;

int param;
int servoSpeed = 0;
String result;

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
 // t1->setNewPosition(0);
 // t1->init(3000);
  scheduler.addTask(t0);
//  scheduler.addTask(t1);
}

void loop()
{
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    result = msg->getContent();
    if(result=="s"){
      state = SINGLE;
    }
    else if(result=="m"){
      state = MANUAL;
    }
    else if(result=="a"){
      state = AUTO;
    }else{
      param = result.toInt();
    }

    //delay(200);
    
    //INVIO DATI 
    MsgService.sendMsg("Pong"); 
    /* NOT TO FORGET: message deallocation */
    delete msg;
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
