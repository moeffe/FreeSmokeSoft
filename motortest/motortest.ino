//rolling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservo1;  // create servo object to control a servo 
int switch_pin = 2;


int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  pinMode(switch_pin, OUTPUT);
  digitalWrite(switch_pin, HIGH);
  myservo1.attach(3);  // attaches the servo on pin 9 to the servo object 
} 
 
void loop() 
{ 

  val = 20;
  myservo1.write(val);                  // sets the servo position according to the scaled value 0-180
  delay(4000);
  val = 160;
  myservo1.write(val);                  // sets the servo position according to the scaled value 0-180
  delay(4000);
  

  
} 
