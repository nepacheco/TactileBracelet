//Motor and Buttons
int motor_pins[8] = {3,4,5,6,7,8,9,10};
int timer_stop_pin = 2; // Needs to be an interrupt pin
int start_button = 11;
int motor_nums[2] = {0,0};
int motor_temp = 0;
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
  randomSeed(micros());
  // put your main code here, to run repeatedly:
  switch (state) {
    case wait:
      // Case for starting the program
      if (digitalRead(start_button) == LOW) {
        // select a random motor
        state = run_motor;
        motor_temp = random(0,8);
        motor_nums[0] = (int) floor(motor_temp/2.0)*2;
        motor_nums[1] = (int) (ceil(motor_temp/2.0)*2) % 8 ; // need to mod by 8 so that for a 7 we get 6 and 0
      }
      break;
    case run_motor:
      // just run the motor
      Serial.print("Running motors ");
      Serial.print(motor_nums[0]);
      Serial.print(" and ");
      Serial.println(motor_nums[1]);
      
      digitalWrite(motor_pins[motor_nums[0]], HIGH);
      digitalWrite(motor_pins[motor_nums[1]], HIGH); 
      delay(run_time);
      digitalWrite(motor_pins[motor_nums[0]], LOW);
      digitalWrite(motor_pins[motor_nums[1]], LOW);
      
      state = wait;
      break;
    default:
      break;
  }
}
