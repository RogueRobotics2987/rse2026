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

int led_counter = 0;
bool led_state = HIGH;
void test_led(){
  if (led_counter > 1000){
    led_counter = 0;
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state);
  }
  led_counter++;
}

void test_switch(){
  if (digitalRead(SW_0)){
    digitalWrite(LED_0, HIGH);
  }
  else{
    digitalWrite(LED_0, LOW);
  }

  if (digitalRead(SW_1) || !digitalRead(SW_2)){
    digitalWrite(LED_1, HIGH);
  } 
  else {
    digitalWrite(LED_1, LOW);
  }
}

void test_servo_pot(){
  int val = analogRead(POT_1);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it for use with the servo (value between 0 and 180)
  servo_obj.write(val);                  // sets the servo position according to the scaled value
}

// the loop function runs over and over again forever
void loop() {
  test_led();
  test_switch();
  test_servo_pot();
  delay(1);
}
