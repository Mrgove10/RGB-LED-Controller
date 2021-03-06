// libraries
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

//custom libraries
#include <thisisatest.h>
#include <remoteCodes.h>

//webpages
#include <webpages.h>
//https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/

//defines
#define IRRecvPin D8
#define RMosfet D6
#define GMosfet D7
#define BMosfet D5

const char *ssid = "Livebox-EC80";
const char *password = "gWbj6RNW6n3mCwwD3A";

int RED = 5;
int GREEN = 5;
int BLUE = 5;

IRrecv irrecv(IRRecvPin);
ESP8266WebServer server(80); //Server on port 80

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
 * http://www.esp8266learning.com/read-and-write-to-the-eeprom-on-the-esp8266.php
 */
void save(int diyNumber)
{
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
  EEPROM.commit(); // store the data in eeprom
}

/**
 * loads a config from eprom
 */
void load(int diyNumber)
{
  EEPROM.begin(512);
  // each one has 3 byte, one pur RGB value
  switch (diyNumber)
  {
  case 1:
    RED = EEPROM.read(0);
    GREEN = EEPROM.read(1);
    BLUE = EEPROM.read(2);
    break;
  case 2:
    RED = EEPROM.read(3);
    GREEN = EEPROM.read(4);
    BLUE = EEPROM.read(5);
    break;
  case 3:
    RED = EEPROM.read(6);
    GREEN = EEPROM.read(7);
    BLUE = EEPROM.read(8);
    break;
  case 4:
    RED = EEPROM.read(9);
    GREEN = EEPROM.read(10);
    BLUE = EEPROM.read(11);
    break;
  case 5:
    RED = EEPROM.read(12);
    GREEN = EEPROM.read(13);
    BLUE = EEPROM.read(14);
    break;
  case 6:
    RED = EEPROM.read(15);
    GREEN = EEPROM.read(16);
    BLUE = EEPROM.read(17);
    break;
  default:
    break;
  }
}

/**
 * Execute the command send byh the remote
 */
void executeRemoteCommand(int hexCommand)
{
  //==========
  // CONTROL
  //==========
  //Turn on
  if (hexCommand == IR44_OFF)
  {
    changeColor(10, 10, 10);
  }

  //Turn off
  if (hexCommand == IR44_OFF)
  {
    changeColor(0, 0, 0);
  }

  //==========
  // BRIGTNESS
  //==========
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

  //==========
  // DIY CONTROL
  //==========
  //plus red
  else if (hexCommand == IR44_REDPLUS)
  {
    RED = RED + 1;
  }
  //plus green
  else if (hexCommand == IR44_GREENPLUS)
  {
    GREEN = GREEN + 1;
  }
  //plus blue
  else if (hexCommand == IR44_BLUEPLUS)
  {
    BLUE = BLUE + 1;
  }

  //minus red
  else if (hexCommand == IR44_REDMINUS)
  {
    RED = RED - 1;
  }
  //minus green
  else if (hexCommand == IR44_GREENMINUS)
  {
    GREEN = GREEN - 1;
  }
  //minus blue
  else if (hexCommand == IR44_BLUEMINUS)
  {
    BLUE = BLUE - 1;
  }

  //==========
  // DIY CONTROL SAVE
  //==========
  //DIY1
  else if (hexCommand == IR44_DIY1)
  {
    load(1);
  }
  //DIY2
  else if (hexCommand == IR44_DIY2)
  {
    load(2);
  }
  //DIY3
  else if (hexCommand == IR44_DIY3)
  {
    load(3);
  }
  //DIY4
  else if (hexCommand == IR44_DIY4)
  {
    load(4);
  }
  //DIY5
  else if (hexCommand == IR44_DIY5)
  {
    load(5);
  }
  //DIY6
  else if (hexCommand == IR44_DIY6)
  {
    load(6);
  }

  //==========
  // INDIVIDUAL COLORS
  //==========
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
  //Cyan
  else if (hexCommand == IR44_CYAN)
  {
    changeColor(0, 255, 255);
  }
  //Magenta
  else if (hexCommand == IR44_MAGENTA)
  {
    changeColor(255, 0, 255);
  }
  //Orange
  else if (hexCommand == IR44_ORANGE)
  {
    changeColor(255, 165, 0);
  }
  //Turqoise
  else if (hexCommand == IR44_TURQUOISE)
  {
    changeColor(64, 224, 208);
  }
  //Yellow
  else if (hexCommand == IR44_YELLOW)
  {
    changeColor(255, 255, 0);
  }
  //Pink
  else if (hexCommand == IR44_PINK)
  {
    changeColor(255, 192, 203);
  }
}

/**
 * /
 */
void handle_Root()
{
  Serial.println("Request : /");
  server.send(200, "text/html", HTML_index);
}

/**
 * 404
 */
void handle_NotFound()
{
  Serial.println("Request : Not found");
  server.send(404, "text/html", "404 not found");
}

/**
 * /color
 */
void handle_Color()
{
  Serial.println("Request : /color");

  // for (int i = 0; i < server.args(); i++)
  // {
  //   Serial.println(server.argName(i) + " : " + server.arg(i));
  // }

  RED = server.arg(0).toInt();
  GREEN = server.arg(1).toInt();
  BLUE = server.arg(2).toInt();

  server.send(200, "text/plain", "OK"); //Response to the HTTP request
}

/**
 * /power/on
 */
void handle_PowerOn()
{
  Serial.println("Request : /power/on");
  changeColor(25, 25, 25);
  server.send(200, "text/plain", "OK");
}

/**
 * /power/off
 */
void handle_PowerOff()
{
  Serial.println("Request : /power/off");
  changeColor(0, 0, 0);
  server.send(200, "text/plain", "OK");
}

/**
 * /current
 */
void handle_Current()
{
  Serial.println("Request : /current");
  String m = "{\"R\":" + (String)RED + ",\"G\":" + (String)GREEN + ",\"B\":" + (String)BLUE + "}";
  server.send(200, "application/json", m);
}

void setup()
{
  pinMode(RMosfet, OUTPUT);
  pinMode(GMosfet, OUTPUT);
  pinMode(BMosfet, OUTPUT);

  Serial.begin(115200);

  irrecv.enableIRIn(); // Start the receiver
  while (!Serial)      // Wait for the serial connection to be establised.
    delay(50);
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(IRRecvPin);

  Serial.print("Connecting to the Newtork");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); //IP address assigned to your ESP

  server.on("/", handle_Root); //Which routine to handle at root location
  server.on("/power/on", handle_PowerOn);
  server.on("/power/off", handle_PowerOff);
  server.on("/color", handle_Color);
  server.on("/current", handle_Current);
  server.onNotFound(handle_NotFound);

  server.begin(); // Starts the Server
  Serial.println("Web server started");
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
  server.handleClient(); //Handle client requests

  // output the colors
  analogWrite(RMosfet, RED);
  analogWrite(GMosfet, GREEN);
  analogWrite(BMosfet, BLUE);

  Serial.println(RED);
  Serial.println(GREEN);
  Serial.println(BLUE);
  Serial.println("----");
  //  thisisatest();
  delay(100);
}
