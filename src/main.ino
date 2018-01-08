#include <Arduino.h>
#include <SPI.h>
/* Main project file for teensy-speed-logger. 
A simple speedometer and distance logger for experiments
*/

const int log_interval = 1000; // ms between logging
const int on_off_pin = 14;
const int hall = 8; // hall sensor
const int resolution = 10; // how often to update state. 
uint32_t readTime;
volatile bool on_off_switch = false; // switch for activating a session
volatile bool state = false; // holds state info


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Begin!");
 attachInterrupt(digitalPinToInterrupt(on_off_pin), on_off, RISING);
 attachInterrupt(digitalPinToInterrupt(hall), movement, CHANGE);

}

void loop() {
    // put your main code here, to run repeatedly:
  if (on_off_switch == false){
    Serial.println("Not strated");
    delay(resolution);
} else{ 
    if (state == false){
Serial.print(millis()); Serial.print(", "); Serial.print("0");Serial.println("\n");
    Serial.println("No trigger");
    delay(resolution);
  }  else {

   Serial.print(millis()); Serial.print(", "); Serial.print("1");Serial.println("\n");
   Serial.println("Trigger");
   state = false;
}
    
}
 }

void on_off(){
  if (on_off_switch == false){
    on_off_switch = true;
    Serial.println("On!");
    readTime = millis();
}
  else{
    Serial.println("off!");
    on_off_switch = false;
    return;
}
}

void movement(){
  state = true;
  Serial.println("TRIGGER!");
  
}

