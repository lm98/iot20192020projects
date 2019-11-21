#include "EventCheck.h"
#include "MsgService.h"
#include "ManualMode.h"
#include "SingleMode.h"
#include "AutoMode.h"

extern ManualMode *manualTask;
extern SingleMode *singleTask;
extern AutoMode *autoTask;

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
      state = SINGLE;
    }
    if(digitalRead(BUTTON_MANUAL) == HIGH){
      state = MANUAL;
    }
    if(digitalRead(BUTTON_AUTO)== HIGH){
      state = AUTO;
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