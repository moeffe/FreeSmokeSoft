#include "defines.h"
#include "user.h"


#include <EEPROM.h>
#include <Servo.h>
// include the library code:
#include "Wire.h"
#include "LiquidCrystal.h"

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);

byte outB;
int e = 0;
int checksum = B00000000;

uint8_t eursymbol[8] = {
    B01111,
    B10000,
    B11110,
    B10000,
    B11110,
    B10000,
    B01111,
  };


Servo motor1;  // create servo object to control a servo 
Servo motor2;  // create servo object to control a servo 
Servo motor3;  // create servo object to control a servo 
  
void setup() {
 Serial.begin(9600);
// Serial2.begin(9600);
// Serial2.begin(9600);
 // UCSR1C = 0x24;
 init_product_led();        //Leds initialisieren
 init_product_button();     //Buttons initialisieren
 set_message_arrays();      //Nachrichten Scheinprüfer vorbereiten
 init_lcd();                //Display initialisieren
 init_motors();             //Servos initialisieren
 splashscreen();            //Startbildschirm

 read_eeprom();
 if (stock1 == 255 || stock2 == 255 || stock3 == 255 ) { //neuer Automat-alles zurücksetzen
   reset_eeprom; 
   read_eeprom;
 }

  stock1 = 10;
  stock2 = 10;
  stock3 = 10;
  
 //Debug-Ausgaben initialisierung
 if (debug==1) {Serial.println("FreeSmoke 1.0.....Init done.");}
 if (debug==1) {
   Serial.print("Guthaben: ");
   Serial.print(account);
   Serial.print(" - Stock1: ");
   Serial.print(stock1);
   Serial.print("Guthaben: ");
   Serial.print(" - Stock2: ");
   Serial.print(stock2);
   Serial.print(" - Stock3: ");
   Serial.println(stock3);
   
 }
}

void loop() {
  
  
  if (adm_state == 0) {             //Verkaufsbetrieb
    //check_standby(); 
    if (stock1 == 0 && stock2 == 0 && stock3 == 0) {
    active = 0;
    } else {
      acceptor_heartbeat();          //Scheinprüfer
    }
      
    get_keystate();                //Buttons abfragen
    sell_product_or_tell_price();  //Produkt verkaufen oder Infos anzeigen
    //  delay(100);                    // nicht ändern
 
    
  } else {                        //Administration
    menue_adm();                  //Admin-Menü
    get_keystate();               //Buttons abfragen
    adm_action();                 //Änderungen bei Tastendruck
    delay(30);                    //nicht ändern
  }
}
