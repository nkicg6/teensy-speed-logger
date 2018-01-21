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
volatile unsigned long last_micros; // for button debounce
const int debounceTime = 80; // debounceing time for on-off button


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
    delay(resolution);
  } else {
    if (state == false){
      //Serial.print(millis()); Serial.print(", "); Serial.print("0");Serial.println("\n");
      delay(resolution);
    }  else {
      Serial.print(millis()); Serial.print(", "); Serial.print("1");Serial.println("\n");
      state = false;
    } 
  }
}


void on_off(){
  if((long) (micros() - last_micros) >= debounceTime * 1000){
    on_off_switch =! on_off_switch;
    last_micros = micros();
    Serial.println("state change");
  }
}




void movement(){
  state = true;
  
}

