#include "EventCheck.h"
#include "MsgService.h"
#include "ManualMode.h"
#include "SingleMode.h"
#include "AutoMode.h"
#include "Scheduler.h"

extern ManualMode *manualTask;
extern SingleMode *singleTask;
extern AutoMode *autoTask;
extern Scheduler* scheduler;

void EventCheck::init(int period){
  Task::init(period);
  this -> value = 0;
  this -> valueReceived = false;
}

void EventCheck::tick(){
  if(MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();
    if(msg->getContent()=="s"){
      state = SINGLE;
      MsgService.sendMsg("OK");
    }
    else if(msg->getContent()=="m"){
      state = MANUAL;
      MsgService.sendMsg("OK");
      manualTask->setActive(true);
    }
    else if(msg->getContent()=="a"){
      state = AUTO;
      MsgService.sendMsg("OK");    
    }else{
      value = msg->getContent().toInt();
      valueReceived = true;
      MsgService.sendMsg("OK");
    }
    /* NOT TO FORGET: message deallocation */
    delete msg;
  }else{
    if(digitalRead(BUTTON_SINGLE) == HIGH){
      Serial.println("sm");
      manualTask->shutDown();
      autoTask->shutDown();
      singleTask->setActive(true);
    }
    if(digitalRead(BUTTON_MANUAL) == HIGH){
      Serial.println("mm");
      singleTask->shutDown();
      autoTask->shutDown();
      manualTask->setActive(true);
    }
    if(digitalRead(BUTTON_AUTO)== HIGH){
      Serial.println("am");
      manualTask->shutDown();
      singleTask->shutDown();
      autoTask->setActive(true);
    }
  }
}

int EventCheck::getValue(){
  valueReceived = false;
  return this -> value;
}

bool EventCheck::isValueAvailable(){
  return this -> valueReceived;
} 