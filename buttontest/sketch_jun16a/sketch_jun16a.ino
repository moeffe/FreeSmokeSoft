/*  How to set up additional interrupts in Arduino (ATMEL 328)
                              7/7/2010
Louis Van Blarigan
This code uses Pin Change interrupts to switch between two display states.
*/
/* Pin to interrupt map:
* D0-D7 = PCINT 16-23 = PCIE2 = pcmsk2
* D8-D13 = PCINT 0-5 = PCIE0 = pcmsk0
* A0-A5 (D14-D19) = PCINT 8-13 = PCIE1 = pcmsk1
*/


#define P1_LED 9
#define P2_LED 10
#define P3_LED 11

#define P1_BUTTON 8
#define P2_BUTTON 7
#define P3_BUTTON 4

/*  How to set up additional interrupts in Arduino (ATMEL 328)
                              7/7/2010
Louis Van Blarigan
This code uses Pin Change interrupts to switch between two display states.
*/
/* Pin to interrupt map:
* D0-D7 = PCINT 16-23 = PCIE2 = pcmsk2
* D8-D13 = PCINT 0-5 = PCIE0 = pcmsk0
* A0-A5 (D14-D19) = PCINT 8-13 = PCIE1 = pcmsk1
*/

#define interrupt_pin 7                 //Define Analog Pin (analog pins are 16-21)
#define interrupt_pin2 8                 //Define Analog Pin (analog pins are 16-21)
volatile int bump = 0;

void setup() {
Serial.begin(115200);

  PCICR |= (1<<PCIE2);
PCMSK2 |= (1<<PCINT23);
MCUCR = (1<<ISC01) | (1<<ISC00);
PCICR |= (1<<PCIE0);
PCMSK0 |= (1<<PCINT0);
   
  //LCD Configuration
pinMode(13, OUTPUT);
pinMode(P1_LED, INPUT);        //Make pin an input
digitalWrite(P1_LED,HIGH);   //Enable pullup resistor on Analog Pin
  
pinMode(interrupt_pin, INPUT);        //Make pin an input
pinMode(interrupt_pin2, INPUT);        //Make pin an input
digitalWrite(interrupt_pin,HIGH);   //Enable pullup resistor on Analog Pin
digitalWrite(interrupt_pin2,HIGH);   //Enable pullup resistor on Analog Pin
bump = 0;  interrupts();
}
void loop() {
  if (bump == 0) {
   digitalWrite(P1_LED,HIGH);   //Enable pullup resistor on Analog Pin

    Serial.print("?f");
Serial.print("LOW");
  }
else {
   digitalWrite(P1_LED,HIGH);   //Enable pullup resistor on Analog Pin
    Serial.print("?f");
Serial.print("HIGH");
  }
}
ISR(PCINT2_vect) {
  bump = 1;  
}
ISR(PCINT0_vect) {
  bump = 0;
}
