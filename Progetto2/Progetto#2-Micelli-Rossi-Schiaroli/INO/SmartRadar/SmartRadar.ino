#include "Scheduler.h"
#include "SlowBlink.h"

#define RX 0 //Receiving
#define TX 1 //Transmitting

Scheduler scheduler;

String inputString = "";     // a String to hold incoming data
bool stringComplete = false; // whether the string is complete
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
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  Task *t0 = new SlowBlink(13);
  t0->init(100);
  scheduler.addTask(t0);
}

void loop()
{
  scheduler.schedule();
  state = MANUAL;

  if (stringComplete)
  {
    //Serial.println(inputString);
    inputString = ""; // to clear string
    stringComplete = false;
  }

  //Leo non piangere quando vedrai questo:
  switch (state)
  {

  case SINGLE:
    servoSpeed = param;
    break;

  case MANUAL:
    //Move to direction <param>
    break;

  case AUTO:
    servoSpeed = param;
    break;

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
      or <alarm> <value>
      value can be alarmTrue/False
      or TrackingTrue/False
      or TrackingTrue + distance
    Receiving: <Value>
      User can change servo speed with specified value
*/

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Serial.println("Ho ricevuto");
    Serial.println(inChar);
    switch (inChar)
    {
    case 's':
      state = SINGLE;
      break;
    case 'm':
      state = MANUAL;
      break;
    case 'a':
      state = AUTO;
      break;
    case '\n':
      stringComplete = true;
      break;
    default: // Every digit is a byte
      /*param = Serial.parseInt(' ');
      if(param==0)
      {
        Serial.print("Error reading from stream");
      }*/
      break;
    }
  }
}
