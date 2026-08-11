#include <Servo.h>

// Output GPIO Pins
int LED_0   = 21;   // Internal LED
int LED_1   = 0;    // Green LED
int LED_2   = 1;    // Red LED
int LED_3   = 2;

// Input GPIO Pins
int SW_0    = 20;   // Internal Switch
int SW_1    = 17;   // Push button
int SW_2    = 18;
int SW_3    = 19;
int SERVO_1 = 3;    // Servo lock
int POT_1   = 26;   // Potentiometer
int IR_1    = 16;   // Lid Sensor

// Object References
Servo servo_obj;

// Global Variables
int led_counter = 0;
int output_counter = 0;
bool led_state = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize output pins
  pinMode(LED_BUILTIN,  OUTPUT);
  pinMode(LED_0,        OUTPUT);
  pinMode(LED_1,        OUTPUT);
  pinMode(LED_2,        OUTPUT);
  pinMode(LED_3,        OUTPUT);

  // initialize input pins
  pinMode(SW_0,     INPUT);
  pinMode(SW_1,     INPUT);
  pinMode(SW_2,     INPUT);
  pinMode(SW_3,     INPUT);
  pinMode(SERVO_1,  INPUT);
  pinMode(POT_1,    INPUT);
  pinMode(IR_1,     INPUT);

  // initialize servo
  servo_obj.attach(SERVO_1, 700, 2400);

  // initialize serial communication
  Serial.begin(9600);
  delay(2000);
  Serial.println("Serial initialized");
}

void test_led(){

  if (led_counter > 1000){
    led_counter = 0;

    // toggles led light on/off
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state);
  }
  // adds 1 to the counter every time the function is called
  led_counter++;
}

void test_switch(){

  // if onboard button == true, illuminate onboard LED
  if (digitalRead(SW_0)){
    digitalWrite(LED_0, HIGH);
  }
  else{
    digitalWrite(LED_0, LOW);
  }

  // if pushbutton == true, illuminate LED_1
  if (digitalRead(SW_1)){
    digitalWrite(LED_1, HIGH);
  }
  else {
    digitalWrite(LED_1, LOW);
  }
}

void test_ir(){

  //if lid closed, LED_2 on, else off.
  if (!digitalRead(IR_1)) {
    digitalWrite(LED_2, HIGH);
  }
  else {
    digitalWrite(LED_2, LOW);
  }
}

void test_servo_pot(){

  // reads the value of the potentiometer (value between 0 and 1023)
  int raw_val = analogRead(POT_1);

  // scale it for use with the servo (value between 0 and 180)
  int val = map(raw_val, 0, 1023, 0, 180);

  // sets the servo position according to the scaled value
  servo_obj.write(val);

  // aproximately once a second, print values to serial
  output_counter = (output_counter + 1) % 1000;
  if(output_counter == 0){
    Serial.println("raw pot value: " + String(raw_val));
    Serial.println("map pot value: " + String(val));
  }
}

// the loop function runs over and over again forever
void loop() {

  // call test functions
  test_led();
  test_switch();
  test_servo_pot();
  test_ir();

  // sleeps for 1 millisecond
  delay(1);
}
