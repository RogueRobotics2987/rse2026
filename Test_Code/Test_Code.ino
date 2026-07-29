
// constants won't change. They're used here to set pin numbers:
const int switch_0 = 20;   // the number of the pushbutton pin
const int switch_1 = 19;   // the number for the pushbutton pin
const int led_0 =  21;     // the number of the LED pin
const int led_1 = A1;      // the number of the LED pin
const int sensorPin = 26;  // the number for the potentiometer pin

// variables will change:
int sensorValue = 0;       // variable to store the value coming from the sensor


void setup() {
  // initialize the LED pin as an output:
  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(switch_0, INPUT);
  pinMode(switch_1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(switch_0);
  // read the state of the pushbutton value:
  buttonState = digitalRead(switch_1);
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (switch_0 == HIGH) {
    // turn LED on:
    digitalWrite(led_0, HIGH);
  } else {
    // turn LED off:
    digitalWrite(led_0, LOW);
  }

  //check if the pushbutton is pressed. If it is, the button is LOW: 
  if (switch_1 == HIGH) {
    digitalWrite(led_1, LOW);
  // otherwise have the potentiometer blink the LED  
  } else {
  // turn the ledPin on
  digitalWrite(led_1, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(led_1, LOW);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  }
}
