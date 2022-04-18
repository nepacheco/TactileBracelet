//Motor and Buttons
int motor_pins[8] = {3,4,5,6,7,8,9,10};
int timer_stop_pin = 2; // Needs to be an interrupt pin
int start_button = 11;
int motor_num = 0;
int run_time = 1000;


// States
enum states {wait, run_motor};
states state = wait;

void setup() {
  randomSeed(micros());
  Serial.begin(9600);
  Serial.println("Beginning Setup");
//  // Attaching Interrupt
//  pinMode(timer_stop_pin, INPUT_PULLUP);
//  attachInterrupt(digitalPinToInterrupt(timer_stop_pin),button_press,FALLING); // interrupt pin to switch which motor will buzz
  // Attach Start Button
  pinMode(start_button, INPUT_PULLUP);
  // Attach each motor
  for (int i = 0; i < 8; i++) {
    Serial.print("Attaching pin ");
    Serial.println(motor_pins[i]);
    pinMode(motor_pins[i], OUTPUT); // initialize all motor pins to just digital output
  }
  Serial.println("Setup Complete");

}

void loop() {
  // put your main code here, to run repeatedly:
  switch (state) {
    case wait:
      // Case for starting the program
      if (digitalRead(start_button) == LOW) {
        // select a random motor
        state = run_motor;
        motor_num = random(0,8);
        double temp = floor(motor_num/2.0)*2;
        motor_num = temp;
        Serial.print("Running motor ");
        Serial.println(motor_num);
      }
      break;
    case run_motor:
      // just run the motor
      digitalWrite(motor_pins[motor_num], HIGH);
      delay(run_time);
      digitalWrite(motor_pins[motor_num], LOW);
      state = wait;
      break;
    default:
      break;
  }
}
