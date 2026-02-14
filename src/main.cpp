/* ****************************************************************************************
  PondProbe_v4
  ****************************************************************************************
  Board Driver: ESP8266 Ver 3.1.2
  Board: WiFi Kit 8 
  Upload speed 57600
  CPU frequency 80MHz

  SCL Pin D1 (GPIO 5)
  SDA pin D2 (GPIO 4)

  I2C Scanning...
  I2C device found at address 0x3C  !  OLED
  I2c device found at address 0x29  !  VL53L0X 

  ****************************************************************************************
*/

#include <Arduino.h>

#include <Wire.h>               //I2C communication Library for the VL53L0X sensor
#include <Adafruit_VL53L0X.h>   //I2C Library for the VL53L0X sensor

#include <OneWire.h>            //Communication Library to Connect DS18B20 Temperature sensor 
#include <DallasTemperature.h>  //DS18B20 Temperature sensor Library

#include "SSD1306Ascii.h"       // OLEAD display library
#include "SSD1306AsciiWire.h"   // OLEAD display library

#include <ESP8266WiFi.h>        //WiFi Library
#include <ThingSpeak.h>         //ThingSpeak IoT library



// --- Definitions ---
#define ONE_WIRE_BUS 0   // put DS18B20 on GPIO 0 - digital pin D3
#define I2C_ADDRESS 0x3C
#define OLED_RESET 16   
#define POND_SDA 4      // GPIO 4 - Physical D2 Label
#define POND_SCL 5      // GPIO 5 - Physical D1 Label



//(Change to your specific data)
const char* ssid          = "your ssid";
const char* password = "Your password";

// ThingSpeak information (Change to your specific data)
unsigned long channelID = 012345;
const char* readAPIKey = "G1G1G1G1G1G1G1G1";
const char* writeAPIKey = "C2C2C2C2C2C2C2C2";


// --- Global Objects ---
WiFiClient client; 
SSD1306AsciiWire oled; // New Lightweight Object
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// --- Helper Variables ---
unsigned long lastUpdateTime = 0;
const unsigned long postingInterval = 300000; 
int Tcount = 1;
long WaterLevel;

void connectWiFi() {
  oled.clear();
  oled.setFont(System5x7);
  

  for (int attempt = 1; attempt < 5; attempt++) {
    if (WiFi.status() != WL_CONNECTED) {
      oled.setCursor(0, 1);
      oled.print("Connecting WiFi ... ");
      oled.print(attempt);
      WiFi.begin(ssid, password); 
      delay(7000);
    } else {
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
      oled.clear();
      oled.setCursor(0, 1);
      oled.println("WiFi Connected !");
      delay(2000);
      ThingSpeak.begin(client);
  } else {
      oled.clear();
      oled.setCursor(0, 1);
      oled.println("WiFi Not Found !");
      delay(2000);
  }
}

int ObtainWaterLevel() { 
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);
  int reading = measure.RangeMilliMeter;

  if (measure.RangeStatus == 4 || reading <= 0) return 0;
  return reading;
}

void setup() {
  Serial.begin(9600);
  
// Reset Heltec Screen
  pinMode(OLED_RESET, OUTPUT);
  digitalWrite(OLED_RESET, LOW);
  delay(100);
  digitalWrite(OLED_RESET, HIGH);

  Wire.begin(POND_SDA, POND_SCL); 
 // The warning occurs because the library disables its AVR-specific 400kHz shortcut for the ESP8266, 
 // safely defaulting to 100kHz while allowing you to manage speed via the standard Wire library instead.

  oled.begin(&Adafruit128x32, I2C_ADDRESS);
  oled.setFont(System5x7); // Using a small font for the borders
  oled.clear();

  if (!lox.begin()) {
    Serial.println(F("VL53L0X Failed"));
  } else {
    lox.setMeasurementTimingBudgetMicroSeconds(50000);
  }

  sensors.begin();
  connectWiFi();
}

void loop() {
  WaterLevel = ObtainWaterLevel();
  sensors.requestTemperatures(); 
  
  double DS18B20_Sensor0 = sensors.getTempCByIndex(0) + 1.4; // +1.4 is calibration factor for sensor 0
//  double DS18B20_Sensor1 = sensors.getTempCByIndex(1) - 1.5; // -1.5 is calibration factor for for sensor 1
//  double DS18B20_Sensor2 = sensors.getTempCByIndex(2) + 0.2; // +0.2 is calibration factor for sensor 2  
//  double DS18B20_Sensor3 = sensors.getTempCByIndex(3) - 1.6; // -1.6 is calibration factor for sensor 3  

  // --- Display Data ---
// TOP BORDER
  oled.setFont(System5x7);

  oled.setCursor(0, 0);
  oled.print("---------------------");

// MIDDLE DATA ROW
  oled.setCursor(0, 1);
  oled.set2X(); // Make the text big

  // Create a temporary string to hold our display text
  String displayStr = "";

// Change Tcount to 5 is other three Temperature sensors are connected   
if (Tcount == 2) {
      displayStr = "Lvl: " + String(WaterLevel) + "mm";
  } else {
      displayStr = "T" + String(Tcount) + ": ";
      double val = 0;
      if (Tcount == 1)      val = DS18B20_Sensor0;
//      else if (Tcount == 2) val = DS18B20_Sensor1;  // if sensor1 is present
//      else if (Tcount == 3) val = DS18B20_Sensor2;  // if sensor2 is present
//      else if (Tcount == 4) val = DS18B20_Sensor3;  // if sensor3 is present
      
      displayStr += String(val, 1) + " C"; 
  }

  // PADDING LOGIC:
  // We need to make sure the string is always the same length 
  // to "wipe" previous text and reach the right-side wall.
  // In 2X mode, about 10-11 characters fit between walls.
  while(displayStr.length() < 10) {
      displayStr += " "; 
  }

  oled.print(displayStr);
  oled.set1X();    // Back to normal size

  // BOTTOM BORDER
  oled.setCursor(0, 3);
  oled.print("---------------------");

  // --- ThingSpeak Logic ---
  if (millis() - lastUpdateTime >= postingInterval) {      
      lastUpdateTime = millis();
      ThingSpeak.setField(1, (float)WaterLevel);
      ThingSpeak.setField(2, (float)DS18B20_Sensor0);
//      ThingSpeak.setField(3, (float)DS18B20_Sensor1);  // if sensor1 is present
//      ThingSpeak.setField(4, (float)DS18B20_Sensor2);  // if sensor2 is present
//      ThingSpeak.setField(5, (float)DS18B20_Sensor3);  // if sensor3 is present
      ThingSpeak.writeFields(channelID, writeAPIKey);
  }

  // if the other three sensors are present
  //  Tcount = (Tcount >= 5) ? 1 : Tcount + 1;
  //
  Tcount = (Tcount >= 2) ? 1 : Tcount + 1;
  delay(2000); 
}