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

int POT_1 = 26;

int loop_state = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize output pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  // initialize input pins
  pinMode(SW_0, INPUT);
  pinMode(SW_1, INPUT);
  pinMode(SW_2, INPUT);
  pinMode(SW_3, INPUT);
  pinMode(SW_4, INPUT);
  pinMode(POT_1, INPUT);

  // initialize servo
  servo_obj.attach(SERVO_1);
}

bool test_combination(int combo){
  int pot_val = analogRead(POT_1);            // reads the value of the potentiometer (value between 0 and 1023)
  pot_val = map(val, 0, 1023, 0, 1); 

  if (digitalRead(SW_1) && pot_val == comb0){
    return true;
  } else{
    return false;
  }
}

// the loop function runs over and over again forever
void loop() {
  if (loop_state == 0){
    if (test_combination(1)){
      loop_state = loop_state + 1;
      digitalWrite(LED_1, HIGH);
      delay(250);
      digitalWrite(LED_1, LOW);
    }
  } else if (loop_state == 1){
    if (test_combination(0)){
      loop_state = loop_state + 1;
      digitalWrite(LED_1, HIGH);
      delay(250);
      digitalWrite(LED_1, LOW);
    }
  } else if (loop_state == 2){
    if (test_combination(1)){
      loop_state = loop_state + 1;
      digitalWrite(LED_1, HIGH);
      delay(250);
      digitalWrite(LED_1, LOW);
    }
  } else if (loop_state == 3){
    servo_obj.write(180);
    loop_state = loop_state + 1;
    delay(500);
  } else if (loop_state == 4){
    if (digitalRead(SW_2)){
      loop_state = loop_state + 1;
      delay(1000);
    }
  } else if (loop_state == 5){
    if (digitalRead(SW_2)){
      loop_state = 0;
      digitalWrite(LED_1, HIGH);
      delay(250);
      digitalWrite(LED_1, LOW);
      delay(1000);
    }
  }
  delay(1);
}
