/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.11 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.4 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// you can enable debug logging to Serial at 115200
//#define REMOTEXY__DEBUGLOG  

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 62 bytes
  { 255,5,0,1,0,55,0,16,106,0,5,2,51,11,39,39,2,26,31,4,
  0,6,13,9,40,2,26,70,16,39,3,12,12,26,37,0,10,48,25,39,
  15,15,4,26,31,79,78,0,31,79,70,70,0,1,0,25,19,15,15,2,
  31,0};
  
// this structure defines all the variables and events of your control interface 
struct {

    // input variables
  int8_t joystick_1_x; // from -100 to 100  
  int8_t joystick_1_y; // from -100 to 100  
  int8_t slider_1; // =0..100 slider position
  uint8_t pushSwitch_1; // =1 if state is ON, else =0 
  uint8_t button_1; // =1 if button pressed, else =0  

  // output variables
  uint8_t led_1; // led state 0 .. 1

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////
int x;
int y;
// defines pins numbers
const int trigPin = 10; // dummy
const int echoPin = 11; // dummy
// defines variables
int ena = 4;
int in1 = 5;
int in2 = 6;
int int1_seeder = 12;
int ena_seeder = 13;
int button_click = 0;
#include <Servo.h>  

Servo servo_1;
Servo servo_2; 

void setup() 
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(int1_seeder, OUTPUT);
  pinMode(ena_seeder, OUTPUT);
  RemoteXY_Init (); 
  
  Serial.begin(9600);     
  servo_1.attach(8);
  servo_2.attach(9); 
}

void loop() 
{ 
    RemoteXY_Handler ();
    // motor driver function
    if (RemoteXY.joystick_1_x >= -70 and RemoteXY.joystick_1_x <= 70 and RemoteXY.joystick_1_y == 100){
    Serial.println("Forward");
    forward();
    }
  else if(RemoteXY.joystick_1_x >= -70 and RemoteXY.joystick_1_x <= 70 and RemoteXY.joystick_1_y == -100){
    Serial.println("Backward");
    backward();
    }
  else{
    neutral();
    } 
  // Servo function
  int ms_servo1 = RemoteXY.slider_1*20+500; 
  servo_1.writeMicroseconds(ms_servo1); 
  int ms_servo2 = RemoteXY.slider_1*20-500; 
  servo_2.writeMicroseconds(ms_servo2);
  if (RemoteXY.pushSwitch_1!=0){
    seeder_on();
  }
  else {Serial.println("SEEDER OFF");
  seeder_off();
  }
  if (RemoteXY.button_1!=0){
    button_click = 1;
  }
  else {button_click = 0;}
  if (button_click == 1){
    RemoteXY.led_1 = 1;
    }
  else{
    RemoteXY.led_1 = 0;
    }
  Serial.println(ms_servo1);
  Serial.println(ms_servo2);
}
void forward(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(ena, 200);
  }
void backward(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(ena, 200);
  }
void neutral(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(ena, 0);
  }
void seeder_on(){
  digitalWrite(int1_seeder,HIGH);
  analogWrite(ena_seeder, 150);
  }
void seeder_off(){
  digitalWrite(int1_seeder,LOW);
  analogWrite(ena_seeder, 0);
  }
