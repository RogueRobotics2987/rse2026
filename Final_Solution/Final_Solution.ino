#include <Servo.h>

// Input GPIO Pins
const int LED_0   = 21;
const int LED_1   = 0;  // Green LED
const int LED_2   = 1;  // Red LED
const int LED_3   = 2;
const int POT_1   = 26; // Potentiometer
const int IR_1    = 16; // Lid Sensor

// Output GPIO Pins
const int SW_0    = 20;
const int SW_1    = 17; // Push Button
const int SW_2    = 18;
const int SW_3    = 19;
const int SERVO_1 = 3;  // Servo Lock

// Object References
Servo lock_servo;

// Global Constants
const int CLOSED_POS = 30;
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

  // Initialize servo to closed (locked) state
  lock_servo.attach(SERVO_1, 700, 2400);
  lock_servo.write(CLOSED_POS);

  // Initialize serial port
  Serial.begin(9600);
}

bool test_combination(int combo){
  // Reads value of potentiometer (value between 0 and 511)
  int pot_val = analogRead(POT_1);
  Serial.println("\tRaw Pot Value: " + String(pot_val));

  // Map potentiometer value to a value between 0 and 1
  int pot_val_mapped = map(pot_val, 0, 511, 0, 1);
  Serial.println("\tMapped Pot Value: " + String(pot_val_mapped));

  if (pot_val_mapped == combo){
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
  if(blink == true){
    digitalWrite(LED_1, HIGH);
    delay(250);
    digitalWrite(LED_1, LOW);
  }
}

void fail_state(){
  // Reset state to start
  loop_state = 0;

  /********************************************
  / Signal Failure
  / Blink LED_2 three times
  /********************************************/

  // Blink 1
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
  delay(100);

  // Blink 2
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
  delay(100);

  // Blink 3
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
  delay(100);

  // Delay before starting again
  delay(500);
}

void lid_unlock(){
  // Open lid lock
  lock_servo.write(OPEN_POS);

  // Signal successful open
  digitalWrite(LED_1, HIGH);
}

void lid_lock(){
  // Close lid lock
  lock_servo.write(CLOSED_POS);

  /********************************************
  / Signal Lock
  / Alternate blink LED_1 and LED_2 three times
  /********************************************/

  // Blink sequence 1
  digitalWrite(LED_1, HIGH);
  delay(100);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);

  // Blink sequence 2
  digitalWrite(LED_1, HIGH);
  delay(100);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);

  // Blink sequence 3
  digitalWrite(LED_1, HIGH);
  delay(100);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
}

// The loop function runs over and over again forever
void loop() {

  // Read input values
  bool push_button = digitalRead(SW_1);
  bool lid_sensor = digitalRead(IR_1);
  Serial.println("===========================================");
  Serial.println("State: " + String(loop_state));
  Serial.println("Button: " + String(push_button));
  Serial.println("Sensor: " + String(lid_sensor));

  /********************************************
  / States 0 - 2 - Check input combination.
  / Combination: 0, 1, 0 (L, R, L)
  /********************************************/

  // state 0 -> 1 - first combo
  if (loop_state == 0){
    if (push_button == 1){
      if (test_combination(0) == true){
        next_state(true);
      } else{
        fail_state();
      }
    }

  // state 1 -> 2 - second combo
  } else if (loop_state == 1){
    if (push_button == 1){
      if (test_combination(1) == true){
        next_state(true);
      } else{
        fail_state();
      }
    }

  // state 2 -> 3 - third combo
  } else if (loop_state == 2){
    if (push_button == 1){
      if (test_combination(0) == true){
        next_state(true);
      } else{
        fail_state();
      }
    }

  /********************************************
  / States 3 - 5 - Unlock and re-lock lid
  / Unlock lid on successful combination.
  / After opening, wait for lid close before locking.
  /********************************************/

  // state 3 -> 4 - unlock state
  } else if (loop_state == 3){
    next_state(false);
    lid_unlock();

  // state 4 -> 5 - lid opened
  } else if (loop_state == 4){
    if (lid_sensor == 1){
      next_state(false);
      delay(1000);
    }

  // state 5 - lid lock, reset
  } else if (loop_state == 5){
    if (lid_sensor == 0){
      delay(500);
      lid_lock();
      loop_state = 0;
    }
  }

  // Add 100ms delay to set base loop rate;
  delay(100);
}
