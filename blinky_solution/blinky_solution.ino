//
// Hello world!
// This program will make the green and red LEDs alternate blinking once per second,
// repeating forever.
//

// These are the pins for the green and red LEDs.
int green_led_pin = 0;
int red_led_pin = 1;

// Setup all of our pins to be outputs.
// Everything inside the curly braces ({ ... }) of the setup function runs ONCE.
void setup() {
  pinMode(green_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
}

// Everything inside the curly braces ({ ... }) of the loop function runs FOREVER.
void loop() {

  // Here is our code to make the lights blink.
  // First we need to set the green LED to HIGH (on)
  digitalWrite(green_led_pin, HIGH);

  // Then we wait for 250 milliseconds (1/4 second)
  delay(250);

  // After the 250 milliseconds have elapsed, we turn the green LED off..
  digitalWrite(green_led_pin, LOW);

  // … then we wait for another 250 milliseconds
   delay(250);

  // Now, we repeat the process for the red LED
  // Turn the red LED on and wait 250 milliseconds
  digitalWrite(red_led_pin, HIGH);
  delay(250);

  // Then switch it off and wait another 250 milliseconds
  digitalWrite(red_led_pin, LOW);
  delay(250);
}
