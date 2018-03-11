#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/* Main project file for teensy-speed-logger. 
A simple speedometer and distance logger for experiments
*/


File speed_log; // speed log file
const byte chipSelect = 10; // sd card
const byte on_off_pin = 14;
const byte hall = 8; // hall sensor
const byte resolution = 100; // how often to update state.
volatile bool on_off_switch = false;
uint32_t readTime;
const byte debounceTime = 100; // debounceing time for detector
volatile int switch_val; // switch for activating a session
//volatile bool state = false; // holds state info
volatile unsigned long last_micros; // for button debounce
volatile unsigned long lastRead; // debounce for hall sensor
const byte indicatorLed = 7; // indicator led


void setup() {

  Serial.begin(11600); 
  attachInterrupt(digitalPinToInterrupt(on_off_pin), on, RISING);
  attachInterrupt(digitalPinToInterrupt(hall), movement, CHANGE);
  pinMode(indicatorLed, OUTPUT);
  card_check();
  data_check();
  //last_micros = micros();
  digitalWrite(indicatorLed, HIGH);
  delay(1000);
  digitalWrite(indicatorLed, LOW);
  delay(1000);
  digitalWrite(indicatorLed, HIGH);
  delay(1000);
  digitalWrite(indicatorLed, LOW);
}

void loop() {
  switch_val = digitalRead(on_off_pin);
  if (switch_val== HIGH){
    digitalWrite(indicatorLed, HIGH);
    delay(resolution);
  } else {
    on_off_switch = false;
    digitalWrite(indicatorLed, LOW);
    delay(resolution);
    Serial.println("off");
  }       
} 


void on(){
  Serial.println("on called");
  on_off_switch = true;
  last_micros = micros();
  Serial.println(switch_val);
  speed_log = SD.open("speed.csv", O_CREAT | O_WRITE | O_APPEND);
  speed_log.println("----");
  speed_log.flush();
  speed_log.close();
}


// control debounce and record movement
void movement(){
  if(on_off_switch == true && (long) (micros() - lastRead) >= debounceTime * 1000){
    lastRead = micros();
    Serial.println("active");
    writeData();
  } else{
    return;
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
    speed_log.println("# Updated: 2018-03-10");
    speed_log.println("Timestamp (ms)");
    speed_log.flush();
    speed_log.close();
  }
}