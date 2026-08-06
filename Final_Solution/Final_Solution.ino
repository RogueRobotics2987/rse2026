#include <Servo.h>

// Input GPIO Pins
const int LED_0 = 21;
const int LED_1 = 0;
const int LED_2 = 1;
const int LED_3 = 2;
const int POT_1 = 26;
const int IR_1 = 16;

// Output GPIO Pins
const int SW_0 = 20;
const int SW_1 = 17;
const int SW_2 = 18;
const int SW_3 = 19;
const int SERVO_1 = 3;

// Object handles
Servo servo_obj;

// Global Constants
const int CLOSED_POS = 0;
const int OPEN_POS = 90;

// Global Variables
int loop_state = 0;

// The setup function runs once when you press reset or power the board
void setup() {
  // Initialize output pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  // Initialize input pins
  pinMode(SW_0, INPUT);
  pinMode(SW_1, INPUT);
  pinMode(SW_2, INPUT);
  pinMode(SW_3, INPUT);
  pinMode(IR_1, INPUT);
  pinMode(POT_1, INPUT);

  // Initialize servo
  servo_obj.attach(SERVO_1, 1000, 2400);
  servo_obj.write(CLOSED_POS);

  // Initialize serial port
  Serial.begin(9600);
}

bool test_combination(int combo){
  // Reads value of potentiometer (value between 0 and 1023)
  int pot_val = analogRead(POT_1);
  Serial.println("Raw Pot Value: " + String(pot_val));

  // Map potentiometer value to a value
  // between 0 and 1
  pot_val = map(pot_val, 0, 511, 0, 1);
  if (pot_val == combo){
    return true;
  } else{
    return false;
  }
}

void next_state(bool blink){
  // Increment state to next value
  loop_state = loop_state + 1;

  // Signal success state
  // Blink LED_1 once
  if(blink){
    digitalWrite(LED_1, HIGH);
    delay(250);
    digitalWrite(LED_1, LOW);
  }
}

void fail_state(){
  // Reset state to start
  loop_state = 0;

  // Signal failure state
  // Blink LED_2 three times
  for(int i = 0; i < 3; i++){
    digitalWrite(LED_2, HIGH);
    delay(100);
    digitalWrite(LED_2, LOW);
    delay(100);
  }
  delay(500);
}

void lid_unlock(){
  // Open lid lock
  servo_obj.write(OPEN_POS);

  // Signal successful open
  digitalWrite(LED_1, HIGH);
}

void lid_lock(){
  // Close lid lock
  servo_obj.write(CLOSED_POS);

  // Signal Lock
  for(int i = 0; i < 3; i++){
    digitalWrite(LED_1, HIGH);
    delay(100);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
    delay(100);
    digitalWrite(LED_2, LOW);
  }
}

// The loop function runs over and over again forever
void loop() {

  // Read input values
  int push_button = digitalRead(SW_1);
  int lid_sensor = digitalRead(IR_1);
  Serial.println("===========================================");
  Serial.println("State: " + String(loop_state));
  Serial.println("Button: " + String(push_button));
  Serial.println("Sensor: " + String(lid_sensor));

  // state 0 -> 1 - first combo
  if (loop_state == 0){
    if (push_button){
      if (test_combination(0)){
        next_state(true);
      } else{
        fail_state();
      }
    }
  // state 1 -> 2 - second combo
  } else if (loop_state == 1){
    if (push_button){
      if (test_combination(1)){
        next_state(true);
      } else{
        fail_state();
      }
    }
  // state 2 -> 3 - third combo
  } else if (loop_state == 2){
    if (push_button){
      if (test_combination(0)){
        next_state(true);
      } else{
        fail_state();
      }
    }
  // state 3 -> 4 - unlock state
  } else if (loop_state == 3){
    next_state(false);
    lid_unlock();
  // state 4 -> 5 - lid opened
  } else if (loop_state == 4){
    if (lid_sensor){
      next_state(false);
      delay(1000);
    }
  // state 5 - lid lock, reset
  } else if (loop_state == 5){
    if (!lid_sensor){
      delay(1000);
      lid_lock();
      loop_state = 0;
    }
  }
  delay(1);
}
