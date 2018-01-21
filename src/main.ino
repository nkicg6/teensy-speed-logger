#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/* Main project file for teensy-speed-logger. 
A simple speedometer and distance logger for experiments
*/

File speed_log; // speed log file
const int chipSelect = 10; // sd card
const int on_off_pin = 14;
const int hall = 8; // hall sensor
const int resolution = 100; // how often to update state. 
uint32_t readTime;
volatile bool on_off_switch = false; // switch for activating a session
//volatile bool state = false; // holds state info
volatile unsigned long last_micros; // for button debounce
volatile unsigned long lastRead; // debounce for hall sensor
const int debounceTime = 100; // debounceing time for on-off button
const int indicatorLed = ;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(on_off_pin), on_off, RISING);
  attachInterrupt(digitalPinToInterrupt(hall), movement, CHANGE);
  card_check();
  data_check();
}

void loop() {
  if (on_off_switch == false){
    delay(resolution);
  } else {
    delay(resolution);
  }       
} 

void on_off(){
  if((long) (micros() - last_micros) >= debounceTime * 1000){
    on_off_switch =! on_off_switch;
    last_micros = micros();
    speed_log = SD.open("speed.csv", O_CREAT | O_WRITE | O_APPEND);
    speed_log.println("----");
    speed_log.flush();
    speed_log.close();
    Serial.println("state change");
  }
}


// control debounce and record movement
void movement(){
  if((long) (micros() - lastRead) >= debounceTime * 1000){
    lastRead = micros();
    writeData();
  }
}

// write to the SD card every movement
void writeData(){
  speed_log = SD.open("speed.csv", O_CREAT | O_WRITE | O_APPEND);
  speed_log.println(millis());
  speed_log.flush();
  speed_log.close();
}


// verify SD card attached
void card_check(){
  Serial.println("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
}


void data_check(){
  Serial.print("checking for speed loggin file");
  if (SD.exists("speed.csv")) {
    Serial.println("file exists");
  } else {
    Serial.print("doesnt exist, creating now");
    speed_log = SD.open("speed.csv", FILE_WRITE);
    Serial.print("printing file header");
    speed_log.println("# Speed logger");
    speed_log.println("# Author: Nick George");
    speed_log.println("# Contact: nicholas.m.george@ucdenver.edu");
    speed_log.println("# Updated: 2018-01-21");
    speed_log.println("Timestamp (ms)");
    speed_log.close();
  }
}