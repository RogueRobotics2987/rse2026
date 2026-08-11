#include <Servo.h>

int LED_0 = 21;
int LED_1 = 0;
int LED_2 = 1;
int LED_3 = 2;

int SW_0 = 20;
int SW_1 = 17;
int SW_2 = 18;
int SW_3 = 19;
int IR_1 = 16;

int SERVO_1 = 3;
Servo servo_obj;

int POT_1 = 26;

int loop_state = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize output pins
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(LED_0, OUTPUT);
  digitalWrite(LED_0, HIGH);
  pinMode(LED_1, OUTPUT); // external LED
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  // initialize input pins
  pinMode(SW_0, INPUT);
  pinMode(SW_1, INPUT); // external push button
  pinMode(SW_2, INPUT);
  pinMode(SW_3, INPUT);
  pinMode(IR_1, INPUT); // prox sensor

  pinMode(POT_1, INPUT);

  // initialize servo
  servo_obj.attach(SERVO_1);
  servo_obj.write(0);
}

bool test_combination(int combo){
  int pot_val = analogRead(POT_1);            // reads the value of the potentiometer (value between 0 and 1023)

  int direction;

  if (pot_val > 511){ // right
    direction = 0;
  } else { // left
    direction = 1;
  }

  if (digitalRead(SW_1) && direction == combo){
    return true;
  } else{
    return false;
  }
}

void next_state(){
  loop_state = loop_state + 1;
  digitalWrite(LED_1, HIGH);
  delay(350);
  digitalWrite(LED_1, LOW);
}
void reset_state(){
  loop_state = 0;
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
  delay(100);
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
  delay(100);
  digitalWrite(LED_2, HIGH);
  delay(100);
  digitalWrite(LED_2, LOW);
  delay(100);
}

int shake_counter = 0;

// the loop function runs over and over again forever
void loop() {
  if (!digitalRead(SW_2)){
    shake_counter++;
  } else{
    shake_counter = 0;
  }
  if (shake_counter > 1000){
    shake_counter = 0;
    loop_state = 3;
  }

  if (loop_state == 0){
    if (digitalRead(SW_1)){
      if (test_combination(0)){
        next_state();
      } else{
        reset_state();
      }
    }
  } else if (loop_state == 1){
    if (digitalRead(SW_1)){
      if (test_combination(1)){
        next_state();
      } else{
        reset_state();
      }
    }
  } else if (loop_state == 2){
    if (digitalRead(SW_1)){
      if (test_combination(0)){
        next_state();
      } else{
        reset_state();
      }
    }
  } else if (loop_state == 3){
    servo_obj.write(180);
    loop_state = loop_state + 1;
    delay(500);
    digitalWrite(LED_1, HIGH);
  } else if (loop_state == 4){
    if (digitalRead(IR_1)){
      loop_state = loop_state + 1;
      delay(1000);
    }
  } else if (loop_state == 5){
    if (!digitalRead(IR_1)){
      loop_state = 0;
      digitalWrite(LED_2, HIGH);
      delay(250);
      digitalWrite(LED_2, LOW);
      delay(1000);
      digitalWrite(LED_1, LOW);
      servo_obj.write(0);

    }
  }

  // debugging button & led
  if (digitalRead(SW_0) == true){
    digitalWrite(LED_0, HIGH);
  } else{
    digitalWrite(LED_0, LOW);
  }

  delay(1);
}
