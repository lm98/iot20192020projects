#include "SlowBlink.h"

SlowBlink::SlowBlink(int ledPin) {
  this->ledPin = ledPin;
}

void SlowBlink::init(int period) {
  Task::init(period);
  led = new Led(ledPin);
  state = OFF;
}

void SlowBlink::tick() {
  switch(state) {
    case OFF:
      led->switchOn();
      state = ON;
      break;

    case ON:
      led->switchOff();
      state = OFF;
      break;
  }
}
