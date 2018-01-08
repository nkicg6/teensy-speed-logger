# 1 "/var/folders/3k/6kg_n29d06d4c8rysy068w1c0000gn/T/tmpXY4oIC"
#include <Arduino.h>
# 1 "/Users/Nick/personal_projects/teensy-speed-logger/src/main.ino"
#include <Arduino.h>
#include <SPI.h>




const int log_interval = 1000;
const int on_off_pin = 14;
const int hall = 8;
const int resolution = 10;
uint32_t readTime;
volatile bool on_off_switch = false;
volatile bool state = false;
void setup();
void loop();
void on_off();
void movement();
#line 16 "/Users/Nick/personal_projects/teensy-speed-logger/src/main.ino"
void setup() {

Serial.begin(9600);
Serial.println("Begin!");
 attachInterrupt(digitalPinToInterrupt(on_off_pin), on_off, RISING);
 attachInterrupt(digitalPinToInterrupt(hall), movement, CHANGE);

}

void loop() {

  if (on_off_switch == false){
    Serial.println("Not strated");
    delay(resolution);
} else{
    if (state == false){
Serial.print(millis()); Serial.print(", "); Serial.print("0");Serial.println("\n");
    Serial.println("No trigger");
    delay(resolution);
  } else {

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