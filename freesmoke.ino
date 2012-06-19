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
 //Serial.println("FreeSmoke Init....OK");
 // UCSR1C = 0x24;
 init_product_led();        //Leds initialisieren
 init_product_button();     //Buttons initialisieren
 set_message_arrays();      //Nachrichten Scheinprüfer vorbereiten
 init_lcd();                //Display initialisieren
 init_motors();             //Servos initialisieren
 splashscreen();            //Startbildschirm

 clear_keylog();            //Tasten reset
 read_eeprom();             //Stock, Guthaben etc. lesen
 if (stock1 == 255 || stock2 == 255 || stock3 == 255 ) { //neuer Automat-alles zurücksetzen
   reset_eeprom; 
   read_eeprom;
 }
}

void loop() {
  //Betriebsmodus finden (normal, admin, statistic)
  if (memcmp(keylog, passcode,100) == 0) {
    adm_state = 1;
  } else if (memcmp(keylog, passcode_stat,100) ==0 ) {
    adm_state = 2;
  } else {
    adm_state = 0;
  }
  
    if (adm_state == 0) {                                //Verkaufsbetrieb
    if (stock1 == 0 && stock2 == 0 && stock3 == 0) {
    active = 0;                                          //ausverkauft
    } else {
      acceptor_heartbeat();                              //Scheinprüfer
    }
    get_keystate();                                      //Buttons abfragen
    sell_product_or_tell_price();                        //Produkt verkaufen oder Infos anzeigen
    //  delay(100);                                      // nicht ändern
    } else if (adm_state == 2) {                         //Statistik
    menue_stat();                                        //Statistik-Menü
    get_keystate();                                      //Buttons abfragen
    stat_action();                                       //Änderungen bei Tastendruck
    delay(30);                                           //nicht ändern
  } else {
    menue_adm();                                        //Admin-Menü
    get_keystate();                                     //Buttons abfragen
    adm_action();                                       //Änderungen bei Tastendruck
    delay(30);                                          //nicht ändern
  
  }
}
