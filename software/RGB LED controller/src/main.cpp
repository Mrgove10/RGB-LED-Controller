#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <EEPROM.h>

#include "remoteCodes.h"

#define IRRecvPin D8
#define RMosfet D6
#define GMosfet D7
#define BMosfet D5

int RED = 0;
int GREEN = 0;
int BLUE = 0;

IRrecv irrecv(IRRecvPin);

decode_results results;

/**
 * Change the color of the LED strip
 * The parameters are a numebr between 0 and 255
 */
void changeColor(int red, int green, int blue)
{
  RED = red;
  GREEN = green;
  BLUE = blue;
}

/**
 * Saves a DIY setting to EEprom
 */
void save(int diyNumber)
{
  //http://www.esp8266learning.com/read-and-write-to-the-eeprom-on-the-esp8266.php
  EEPROM.begin(512);
  // each one has 3 byte, one pur RGB value
  switch (diyNumber)
  {
  case 1:
    EEPROM.write(0, RED);
    EEPROM.write(1, GREEN);
    EEPROM.write(2, BLUE);
    break;
  case 2:
    EEPROM.write(3, RED);
    EEPROM.write(4, GREEN);
    EEPROM.write(5, BLUE);
    break;
  case 3:
    EEPROM.write(6, RED);
    EEPROM.write(7, GREEN);
    EEPROM.write(8, BLUE);
    break;
  case 4:
    EEPROM.write(9, RED);
    EEPROM.write(10, GREEN);
    EEPROM.write(11, BLUE);
    break;
  case 5:
    EEPROM.write(12, RED);
    EEPROM.write(13, GREEN);
    EEPROM.write(14, BLUE);
    break;
  case 6:
    EEPROM.write(15, RED);
    EEPROM.write(16, GREEN);
    EEPROM.write(17, BLUE);
    break;
  default:
    break;
  }
  EEPROM.commit();
}

void

/**
 * Execute the command send byh the remote
 */
void executeRemoteCommand(int hexCommand)
{
  // Turn off
  if (hexCommand == IR44_OFF)
  {
    changeColor(0, 0, 0);
  }
  //Brigtness down
  else if (hexCommand == IR44_BMINUS)
  {
    RED = RED - 5;
    GREEN = GREEN - 5;
    BLUE = BLUE - 5;
  }
  //Brigtness up
  else if (hexCommand == IR44_BPLUS)
  {
    RED = RED + 5;
    GREEN = GREEN + 5;
    BLUE = BLUE + 5;
  }
  //Full red
  else if (hexCommand == IR44_RED)
  {
    changeColor(255, 0, 0);
  }
  //Full green
  else if (hexCommand == IR44_GREEN)
  {
    changeColor(0, 255, 0);
  }
  //Full blue
  else if (hexCommand == IR44_BLUE)
  {
    changeColor(0, 0, 255);
  }
  //Full white
  else if (hexCommand == IR44_WHITE)
  {
    changeColor(255, 255, 255);
  }
}

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  while (!Serial)      // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(IRRecvPin);

  pinMode(RMosfet, OUTPUT);
  pinMode(GMosfet, OUTPUT);
  pinMode(BMosfet, OUTPUT);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    // print() & println() can't handle printing long longs. (uint64_t)
    serialPrintUint64(results.value, HEX);
    executeRemoteCommand(results.value); // execute the hex
    irrecv.resume();                     // Receive the next value
  }
  // output the colors
  analogWrite(RMosfet, RED);
  analogWrite(GMosfet, GREEN);
  analogWrite(BMosfet, BLUE);
  delay(100);
}
