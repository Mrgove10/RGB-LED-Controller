#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

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
 * Turnf off the led strip
 */
void off()
{
  changeColor(0, 0, 0);
}

/**
 * Execute the command send byh the remote
 */
void executeRemoteCommand(int hexCommand)
{
  if (hexCommand == IR44_OFF)
  {
    // Turn off
    off();
  }
  if (hexCommand == IR44_RED)
  {
    changeColor(255, 0, 0);
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
