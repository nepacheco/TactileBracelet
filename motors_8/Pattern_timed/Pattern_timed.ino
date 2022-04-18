//Motor and Buttons
int motor_pins[8] = {3, 4, 5, 6, 7, 8, 9, 10};
int repeat_button = 2; // Needs to be an interrupt pin
int start_button = 11;
int run_time = 4000; // initial run time will actually be half this
int const num_elems = 5;
int motor_pattern[num_elems];
int pattern_vault[3][num_elems] = {{0, 6, 4, 2, 5}, {3, 2, 7, 1, 4}, {6, 1, 4, 5, 2}};

// States
enum states {wait, run_pattern};
states state = wait;


// RUN TYPE
bool random_pattern = true;
void setup() {
  Serial.begin(9600);
  Serial.println("Beginning Setup");
  //  // Attaching Interrupt
  //  pinMode(timer_stop_pin, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(timer_stop_pin),button_press,FALLING); // interrupt pin to switch which motor will buzz
  // Attach Start Button
  pinMode(repeat_button, INPUT_PULLUP);
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
      if (digitalRead(start_button) == LOW) // If we want to create a new pattern
      {
        randomSeed(micros());
        // Running a randomly generated pattern
        state = run_pattern;
        run_time = run_time / 2; //cut time in half
        gen_pattern();
      }
      else if (digitalRead(repeat_button) == LOW) // We want to repeat the previous pattern and time interval
      {
        state = run_pattern;
        gen_pattern();
      }
      break;
    case run_pattern:
      // just run the motor
      for (int i = 0; i < num_elems; i++)
      { // run the pattern
        digitalWrite(motor_pins[motor_pattern[i]], HIGH);
        delay(run_time);
        digitalWrite(motor_pins[motor_pattern[i]], LOW);
        delay(run_time);
      }
      state = wait;
      break;
    default:
      break;
  }
}

void gen_pattern() {
  if (random_pattern) // create a random pattern
  {
    for (int i = 0; i < num_elems; i++)
    {
      motor_pattern[i] = random(0, 8);
    }
  }
  else // Select a pattern from the existing ones
  {
    int vault_num = random(0, 3);
    for (int i = 0; i < num_elems; i ++)
    {
      motor_pattern[i] = pattern_vault[vault_num][i];
    }
  } // Done selecting random or predefined pattern
  /*********************************************/
  // PRRINTING PATTERN
  Serial.print("Running pattern ");
  for (int i = 0; i < num_elems; i ++) {
    Serial.print(motor_pattern[i]);
  }
  Serial.print(" At ");
  Serial.print(run_time);
  Serial.println(" milliseconds");
}
