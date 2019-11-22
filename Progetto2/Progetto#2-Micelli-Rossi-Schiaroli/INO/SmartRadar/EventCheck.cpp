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
    }
    else if(msg->getContent()=="m"){
     state = MANUAL;
    }
    else if(msg->getContent()=="a"){
      state = AUTO;  
    }else{
      value = msg->getContent().toInt();
      valueReceived = true;
      MsgService.sendMsg("val");
    }
    /* NOT TO FORGET: message deallocation */
    delete msg;
    
  }else{
    if(digitalRead(BUTTON_SINGLE) == HIGH){
      state = SINGLE;

      /* Notify Console */
      Serial.println("c s");
    }
    if(digitalRead(BUTTON_MANUAL) == HIGH){
      state = MANUAL;

      /* Notify Console */
      Serial.println("c m");
    }
    if(digitalRead(BUTTON_AUTO)== HIGH){
      state = AUTO;

      /* Notify Console */
      Serial.println("c a");
    }
  }

    switch(state){
      case SINGLE:
        manualTask->shutDown();
        autoTask->shutDown();
        singleTask->setActive(true);
      break;

      case MANUAL:
        singleTask->shutDown();
        autoTask->shutDown();
        manualTask->setActive(true); 
      break;

      case AUTO:
        manualTask->shutDown();
        singleTask->shutDown();
        autoTask->setActive(true);
      break;    
    }

}

int EventCheck::getValue(){
  valueReceived = false;
  return this -> value;
}

bool EventCheck::isValueAvailable(){
  return this -> valueReceived;
} 