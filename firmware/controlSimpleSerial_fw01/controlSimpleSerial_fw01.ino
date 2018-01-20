#include <SoftwareSerial.h>
#include "RB_RoboClaw_SimpleSerial.h"

#define BTN_STOP 2
#define BTN_REVERSE 3

#define LED_FORWARD 5
#define LED_BACKWARD 6
#define LED_STOP 9

#define SERIAL_RX 11
#define SERIAL_TX 12

#define POT_LEFT A0
#define POT_RIGHT A1

const uint32_t roboClaw_serial_timeout = 10000;

//See limitations of Arduino SoftwareSerial
SoftwareSerial roboClaw_serial(SERIAL_RX, SERIAL_TX);
RoboClawSimpleSerial roboclaw(&roboClaw_serial, roboClaw_serial_timeout);

#define address 0x80

int pot_left_val;
int pot_right_val;
bool set_backward = false;
const int btn_pot_reverse_min_val = 10;
int btn_stop_val = 0;

void setup()
{
  //Open Serial and roboclaw serial ports
  Serial.begin(9600);
  roboclaw.begin(38400);

  Serial.println("\n\tRoboclaw - init");
  Serial.print("\taddr: ");
  Serial.println(address);
  Serial.print("\ttimeout: ");
  Serial.println(roboClaw_serial_timeout);
  Serial.println();

  pinMode(LED_FORWARD, OUTPUT);
  pinMode(LED_BACKWARD, OUTPUT);

  pinMode(LED_STOP, OUTPUT);

  pinMode(BTN_STOP, INPUT_PULLUP);
  pinMode(BTN_REVERSE, INPUT_PULLUP);
}

int pot_left_min_val = 189;
int pot_left_max_val = 880;
int pot_right_min_val = 186;
int pot_right_max_val = 880;

void loop()
{
  // just for debuging with ArduinoLearningKitStarter
  //pot_left_min_val = 0;
  //pot_right_min_val = 0;

  pot_left_val = abs(analogRead(POT_LEFT) / 8 - pot_left_min_val);
  //pot_right_val = map(abs(analogRead(POT_RIGHT) / 8 - pot_right_min_val), 0, 1023, 0, 128);
  
  pot_left_val = abs(map(analogRead(POT_LEFT), pot_left_min_val, pot_left_max_val, 0, 127))/2;
  pot_right_val = abs(map(analogRead(POT_RIGHT), pot_right_min_val, pot_right_max_val, 0, 127))/2;

  //pot_right_val = analogRead(POT_RIGHT);
  //pot_left_val = analogRead(POT_LEFT);
  //pot_left_val = pot_right_val; // TODO - hack - we have just one pot control

  btn_stop_val = digitalRead(BTN_STOP);

  if ((pot_left_val < btn_pot_reverse_min_val)
      && (pot_right_val < btn_pot_reverse_min_val))
  {
    if (digitalRead(BTN_REVERSE) == true)
      set_backward = false;
    else
      set_backward = true;
  }

  if (btn_stop_val == true)
  {
    roboclaw.ForwardM1(address, 0);
    roboclaw.ForwardM2(address, 0);
  }
  else
  {
    if (set_backward == false)
    {
      roboclaw.ForwardM1(address, pot_left_val);
      roboclaw.BackwardM2(address, pot_right_val);
    }
    else
    {
      roboclaw.BackwardM1(address, pot_left_val);
      roboclaw.ForwardM2(address, pot_right_val);
    }
  }

  digitalWrite(LED_BACKWARD, LOW);
  digitalWrite(LED_BACKWARD, LOW);
  digitalWrite(LED_BACKWARD, LOW);
  if (set_backward == true)
  {
    digitalWrite(LED_BACKWARD, HIGH); // blue led
  }
  else
  {
    digitalWrite(LED_FORWARD, HIGH); // green led
  }
  if (btn_stop_val == true)
  {
    digitalWrite(LED_STOP, HIGH); // red led
  }
  Serial.print("POT_LEFT: ");
  Serial.print(pot_left_val);
  Serial.print("  POT_RIGHT: ");
  Serial.print(pot_right_val);
  Serial.print("  REVERSE (BLUE): ");
  Serial.print(set_backward);
  Serial.print("  STOP (RED): ");
  Serial.print(btn_stop_val);
  Serial.println();
  delay(40);
}




















