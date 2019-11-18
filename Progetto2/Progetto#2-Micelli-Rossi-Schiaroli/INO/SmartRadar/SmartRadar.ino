#include "Scheduler.h"
#include "SlowBlink.h"
#include "MsgService.h"

Scheduler scheduler;

int param;
int servoSpeed = 0;

enum service_type
{
  SINGLE,
  MANUAL,
  AUTO
} state;

void setup()
{
  Serial.begin(9600);
  scheduler.init(100);

  MsgService.init();
  Task *t0 = new SlowBlink(13);
  t0->init(100);
  scheduler.addTask(t0);
}

void loop()
{
  if (MsgService.isMsgAvailable()) {
    Msg* msg = MsgService.receiveMsg();
    /*    
    if (msg->getContent() == "ping"){
       delay(500);
       MsgService.sendMsg("pang");
    }*/
    String result = msg->getContent();
    if(result=="s"){
      state = SINGLE;
    }
    else if(result=="m"){
      state = MANUAL;
    }
    else if(result=="a"){
      state = AUTO;
    }else{
      int valueRcv= result.toInt();
    }
    
    //INVIO DATI 
    MsgService.sendMsg("Autodistruzione avviata, madonna imbalsamata"); 
    /* NOT TO FORGET: message deallocation */
    delete msg;
  }
  scheduler.schedule();
  switch(state){
    case SINGLE:
        digitalWrite(13,LOW);
        digitalWrite(12,HIGH);
      break;
      case MANUAL:
      digitalWrite(13,HIGH);
      digitalWrite(12,HIGH);
      break;
      case AUTO:
        digitalWrite(12,LOW);
        digitalWrite(13,HIGH);
      default:
      break;
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
