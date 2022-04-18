int motor_pins[8] = {3,4,5,6,7,8,9,10};
int switch_pin = 2; // Needs to be an interrupt pin
int on_pin = 11;
int motor_num = 0;
int motor_1 = 0;
int motor_2 = 0;
int start = 1;
int time_on = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Beginning Setup");
  pinMode(switch_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switch_pin),button_press,FALLING); // interrupt pin to switch which motor will buzz
  pinMode(on_pin, INPUT_PULLUP);
  for (int i = 0; i < 8; i++) {
    Serial.print("Attaching pin ");
    Serial.println(motor_pins[i]);
    pinMode(motor_pins[i], OUTPUT); // initialize all motor pins to just digital output
  }
  Serial.println("Setup Complete");
  Serial.print("Motor Pin ");
  Serial.print(motor_pins[motor_num]);
  Serial.println(" active");
}

int increment = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(on_pin) == LOW) {
    Serial.println("Motor On");
    motor_1 = (int) floor(motor_num/2.0)*2;
    motor_2 = (int) (ceil(motor_num/2.0)*2) % 8 ; // need to mod by 8 so that for a 7 we get 6 and 0

    digitalWrite(motor_pins[motor_1], HIGH);
    digitalWrite(motor_pins[motor_2], HIGH);
    delay(time_on); // leave high for half a second
    digitalWrite(motor_pins[motor_1], LOW);
    digitalWrite(motor_pins[motor_2], LOW);
  }
}

void button_press() {
  // Interrupt service routine for motor button switching
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    motor_num = (motor_num + 1) % 8;
    Serial.print("Motor Number ");
    Serial.print(motor_num);
    Serial.println(" active");
  }
  last_interrupt_time = interrupt_time;
}
