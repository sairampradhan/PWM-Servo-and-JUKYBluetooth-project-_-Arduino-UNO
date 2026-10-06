// Code for Robot - Creator : Sairam Pradhan //
// CopyRight - James Bruton for seamless signal processing of the PWM signals given by receiver to arduino
const int Relay_1_In1 = 4; //Relay1_In1 pin
const int Relay_1_In2 = 5; //Relay1_In2 pin
const int Relay_2_In1 = 6; //Relay2_In1 pin
const int Relay_2_In2 = 7; //Relay2_In2 pin
volatile unsigned long pwm_ch1;
volatile unsigned long pwm_ch2;
volatile boolean done_1;
unsigned long start_1;
volatile boolean done_2;
unsigned long start_2;
unsigned long currentMillis_1;
unsigned long currentMillis_2;

long previousMillis_1 = 0;    // set up timers
long interval_1 = 20;        // time constant for timers
long previousMillis_2 = 0;    // set up timers
long interval_2 = 20;        // time constant for timers

void setup() {
  pinMode(2, INPUT);//ch1 
  attachInterrupt(0, timeit_1, CHANGE);
  pinMode(3, INPUT);//ch2
  attachInterrupt(1, timeit_2, CHANGE);
  pinMode(Relay_1_In1, OUTPUT); //Relay1_In1
  pinMode(Relay_1_In2, OUTPUT); // Relay1_In2
  pinMode(Relay_2_In1, OUTPUT); //Relay2_In1
  pinMode(Relay_2_In2, OUTPUT); // Relay2_In2
  
  Serial.begin(9600);

}

void timeit_1() { //ch1
    if (digitalRead(2) == HIGH) {
      start_1 = micros();
    }
    else {
      pwm_ch1 = micros() - start_1;
      done_1 = true;
    }
  }
  
void timeit_2() { //ch2
    if (digitalRead(3) == HIGH) {
      start_2 = micros();
    }
    else {
      pwm_ch2 = micros() - start_2;
      done_2 = true;
    }
  }


void loop() {

  currentMillis_1 = millis(); //ch1
  if (currentMillis_1 - previousMillis_1 >= interval_1) {  //start timed event
      previousMillis_1 = currentMillis_1;
      
      if (!done_1)
          return;
      //Serial.println ("PWM VALUE CH1: ");                         
      //Serial.println (pwm_ch1);
      //delay(500);
      done_1 = false;      

  } // end of timed event _ 1

  currentMillis_2 = millis(); //ch2
  if (currentMillis_2 - previousMillis_2 >= interval_2) {  //start timed event
      previousMillis_2 = currentMillis_2;
      
      if (!done_2)
          return;
      //Serial.println ("PWM VALUE CH2: ");                         
      //Serial.println (pwm_ch2);
      //delay(500);
      done_2 = false;      

  } // end of timed event _ 2
  
  // Void Function(s):
  
  // Forward (conditional)
  if (pwm_ch2 > 1550 and pwm_ch1 < 1562 and pwm_ch1 > 1458){
    forward();
    Serial.println("Status: Forward");
  }
  // Forward right
  else if (pwm_ch2 > 1550 and pwm_ch1 > 1562){
    forward_right();
    Serial.println("Status: Forward Right");
    }
  // Forward left
  else if (pwm_ch2 > 1550 and pwm_ch1 < 1458){
    forward_left();
    Serial.println("Status: Forward Left");
    }
  // Reverse
  else if (pwm_ch2 < 1426){
    backward();
    Serial.println("Status: Reverse");
  }
  // Left
  else if (pwm_ch1 < 1458){
    left();
    Serial.println("Status: Left");
  }
  //Right
  else if (pwm_ch1 > 1562){
    right();
    Serial.println("Status: Right");
  }
  //Neutral
  else{
    neutral();
    Serial.println("Status: Neutral");
  }
}
// Void Function Defined
void forward(){ // Forward
  digitalWrite(Relay_1_In1, HIGH); // OFF
  digitalWrite(Relay_1_In2, LOW); // ON
  digitalWrite(Relay_2_In1, HIGH); //OFF
  digitalWrite(Relay_2_In2, LOW); //ON
}
void forward_left(){ // Forward left
  digitalWrite(Relay_1_In1, HIGH); // OFF
  digitalWrite(Relay_1_In2, HIGH); // OFF 
  digitalWrite(Relay_2_In1, LOW); //ON
  digitalWrite(Relay_2_In2, HIGH); //OFF
}
void forward_right(){ // Forward right
  digitalWrite(Relay_1_In1, HIGH); // OFF
  digitalWrite(Relay_1_In2, HIGH); // OFF 
  digitalWrite(Relay_2_In1, HIGH); //OFF
  digitalWrite(Relay_2_In2, LOW); //ON
}
void backward(){ // Backward
  digitalWrite(Relay_1_In1, LOW); // ON
  digitalWrite(Relay_1_In2, HIGH); // OFF
  digitalWrite(Relay_2_In1, LOW); // ON
  digitalWrite(Relay_2_In2, HIGH); // OFF
}
void left(){ // Left
  digitalWrite(Relay_1_In1, HIGH); // OFF
  digitalWrite(Relay_1_In2, LOW); // ON
  digitalWrite(Relay_2_In1, LOW); // ON
  digitalWrite(Relay_2_In2, HIGH); // OFF
}
void right(){ // Right
  digitalWrite(Relay_1_In1, LOW); // ON
  digitalWrite(Relay_1_In2, HIGH); // OFF
  digitalWrite(Relay_2_In1, HIGH); // OFF
  digitalWrite(Relay_2_In2, LOW); // ON
}
void neutral(){ // Neutral
  digitalWrite(Relay_1_In1, HIGH); //OFF
  digitalWrite(Relay_1_In2, HIGH); //OFF
  digitalWrite(Relay_2_In1, HIGH); //OFF
  digitalWrite(Relay_2_In2, HIGH); //OFF
}
