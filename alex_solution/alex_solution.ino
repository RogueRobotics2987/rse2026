#include <Servo.h>

int LED_0 = 21;
int LED_1 = 0;
int LED_2 = 1;
int LED_3 = 2;

int SW_0 = 20;
int SW_1 = 16;
int SW_2 = 17;
int SW_3 = 18;
int SW_4 = 19;

int SERVO_1 = 3;
Servo servo_obj;

// Define open/closed positions
const int CLOSED_POS = 0;
const int OPEN_POS = 90;


int POT_1 = 26;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize output pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  // initialize input pins
  pinMode(SW_0, INPUT); // external pushbotton
  pinMode(SW_1, INPUT); // IR sensor
  pinMode(SW_2, INPUT);
  pinMode(SW_3, INPUT);
  pinMode(SW_4, INPUT);
  pinMode(POT_1, INPUT);

  // initialize servo
  servo_obj.attach(SERVO_1);
  servo_obj.write(CLOSED_POS);
}

int read_pot(){
    int val = analogRead(POT_1);
    return map(val, 0, 123, 0, 180);
}

bool test_pot_value (int target_low, int target_high){
    if (digitalRead(SW_0)){
        int  = read_pot();
        if (pot > target_low && pot < target_high){
            return true
        }
    }
    return false
}

void lock_lid(){
    servo_obj.write(OPEN_POS);
}

void unlock_lid(){
    servo_obj.write(OPEN_POS);
}

bool test_lid_open(){
    return digitalRead(SW_1)
}

int next_state(){
    digitalWrite(LED_1, HIGH);
    delay(250);
    digitalWrite(LED_1, LOW);
    return state + 1;
}

int reset_state(){
    for(int i = 0; i < 3; i++ ){
        digitalWrite(LED_1, HIGH);
        delay(100);
        digitalWrite(LED_1, LOW);
    }

    return 0;
}


// the loop function runs over and over again forever
void loop() {

  int state = 0;

  // state 0 -> 1 - first combo
  if (state == 0 && test_pot_value(45, 90)){
    state = next_state();
  // state 1 -> 2 - second combo
  } else if (state == 1 && test_pot_value(90, 180)){
    state = next_state();
  // state 2 -> 3 - third combo
  } else if (state == 2 && test_pot_value(90, 180)){
    state = next_state();
  // state 3 -> 4 - unlock state
  } else if (state == 3){
    state = next_state();
    unlock_lid();
  // state 4 -> 5 - lid closed
  } else if (state == 4 && !test_lid_open()){
    lock_lid();
    state = next_state();
    state = 0;
  }




  test_led();
  test_switch();
  test_servo_pot();
  delay(1);
}
