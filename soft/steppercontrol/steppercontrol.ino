

// pins for the stepper
const int stepPin = 3;
const int dirPin = 4;
const int enablePin = 5;


void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(stepPin, OUTPUT); 
  pinMode(dirPin, OUTPUT); 
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);

}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    //  find number of steps
    int steps = Serial.parseInt(); 
    // find direction
    int dir = Serial.parseInt(); 
    // is basically 1 or 0 in stupid way
    int stepspeed = Serial.parseInt();
    //find steps per second.
    // sentence:
    if (Serial.read() == '\n') {
      //command finished, carry it out.

      //probably backwards
      if(dir) digitalWrite(dirPin, HIGH);
      else digitalWrite(dirPin, LOW);
      for (int i=0; i<steps; i++){
        //bitbang IO to step
        digitalWrite(stepPin, HIGH);
        delay(500/stepspeed);
        digitalWrite(stepPin, LOW);
        delay(500/stepspeed);
      }


      // print the three numbers in one string as hexadecimal:
      Serial.println(steps);
      Serial.println(dir);

    }
  }
}








