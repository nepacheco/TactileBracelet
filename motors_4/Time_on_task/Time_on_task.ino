//Motor and Buttons
int motor_pins[8] = {3,4,5,6,7,8,9,10};
int timer_stop_pin = 2; // Needs to be an interrupt pin
int start_button = 11;
int motor_num = 0;
int motor_1 = 0;
int motor_2 = 0;

// Timer results
long start_time = 0;
long end_time = 0;
int const num_tasks_c = 10;
int num_tasks = num_tasks_c;
float time_dur[num_tasks_c];

// States
enum states {start, run_motor, wait, pause};
states state = start;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Beginning Setup");
  // Attaching Interrupt
  pinMode(timer_stop_pin, INPUT_PULLUP);
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
//  Serial.print("Motor Pin ");
//  Serial.print(motor_pins[motor_num]);
//  Serial.println(" active");
}

int increment = 0;
void loop() {
  randomSeed(micros());
  switch (state) {
    case start:
      // Case for starting the program
      if (digitalRead(start_button) == LOW) {
        state = wait;
        num_tasks = num_tasks_c;
      }
      break;
    case wait:
      // wait for some random amount of time between 2 and 4 seconds
      delay(2000 + random(0,2000)); // delay for at least 2 seconds + some random time between 0 and 2 seconds
      state = run_motor;
      start_time = micros();
      break;
    case run_motor:
      // just run the motor
      motor_num = num_tasks % 8;
      Serial.print("Motor number ");
      Serial.print(motor_num);
      Serial.println(" active");

      motor_1 = (int) floor(motor_num/2.0)*2;
      motor_2 = (int) (ceil(motor_num/2.0)*2) % 8 ; // need to mod by 8 so that for a 7 we get 6 and 0
  
      digitalWrite(motor_pins[motor_1], HIGH);
      digitalWrite(motor_pins[motor_2], HIGH);


      state = pause;
      break;
    case pause:
      if (digitalRead(timer_stop_pin) == LOW) {
        end_time = micros(); // get time button was pressed
        // shut off the motor
        digitalWrite(motor_pins[motor_1], LOW);
        digitalWrite(motor_pins[motor_2], LOW);

       
        time_dur[num_tasks_c - num_tasks] = (end_time - start_time)/1000.0; // convert time to milliseconds
        num_tasks = num_tasks - 1; // change motor
        if (num_tasks == 0) // once we've done all 8 motors, reset the system and print the times
        { 
          state = start;
          Serial.print("Timer values: ");
          for (int i = 0; i < num_tasks_c; i++)
          {
            Serial.print(time_dur[i]);
            Serial.print(' ');
          }
          Serial.println();
        }
        else 
        { // haven't done all 8 motors so go to the next wait section
          state = wait;
        }
      }
      break;
    default:
      break;
  }
}
