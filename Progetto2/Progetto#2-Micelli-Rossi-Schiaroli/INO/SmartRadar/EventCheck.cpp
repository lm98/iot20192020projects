#include "EventCheck.h"
#include "MsgService.h"


void EventCheck::init(int period){
  Task::init(period);
  this -> value=0;
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
    }
    else if(msg->getContent()=="a"){
      state = AUTO;
      MsgService.sendMsg("OK");
      //auto->isActice(true);
    }else{
      value = msg->getContent().toInt();
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
  return this -> value;
}
