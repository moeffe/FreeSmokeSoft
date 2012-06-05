
void init_product_led() {
pinMode(P1_LED, OUTPUT); 
pinMode(P2_LED, OUTPUT); 
pinMode(P3_LED, OUTPUT); 

digitalWrite(P1_LED, LOW);   // set the LED off
digitalWrite(P2_LED, LOW);   // set the LED off
digitalWrite(P3_LED, LOW);   // set the LED off


}

void led_blink() {
  unsigned long currentMillis = millis();
   if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == 0)
      ledState = 1;
    else
      ledState = 0;

    // set the LED with the ledState of the variable:
    if (stock1 > 0) {digitalWrite(P1_LED, ledState);} else {digitalWrite(P1_LED, LOW);};
    if (stock2 > 0) {digitalWrite(P2_LED, ledState);} else {digitalWrite(P2_LED, LOW);};
    if (stock3 > 0) {digitalWrite(P3_LED, ledState);} else {digitalWrite(P3_LED, LOW);};

  }
}

void led_reset() {
      ledState = 0;
    digitalWrite(P1_LED, 0);
    digitalWrite(P2_LED, 0);
    digitalWrite(P3_LED, 0);
 
}

void init_product_button() {
pinMode(P1_BUTTON, INPUT); 
pinMode(P2_BUTTON, INPUT); 
pinMode(P3_BUTTON, INPUT); 
//Pull-Ups on
digitalWrite(P1_BUTTON, HIGH);
digitalWrite(P2_BUTTON, HIGH);
digitalWrite(P3_BUTTON, HIGH);


}

void get_keystate() {
  p1_oldstate = p1_actstate;
  p2_oldstate = p2_actstate;
  p3_oldstate = p3_actstate;
   
  p1_actstate = digitalRead(P1_BUTTON);
  p2_actstate = digitalRead(P2_BUTTON);
  p3_actstate = digitalRead(P3_BUTTON);
  

  if (debug == 1) {
    if (p1_oldstate == 0 && p1_actstate == 1) {Serial.println("Button1 released");}
    if (p2_oldstate == 0 && p2_actstate == 1) {Serial.println("Button2 released");}
    if (p3_oldstate == 0 && p3_actstate == 1) {Serial.println("Button3 released");}

    if (p1_oldstate == 1 && p1_actstate == 0) {Serial.println("Button1 pushed");}
    if (p2_oldstate == 1 && p2_actstate == 0) {Serial.println("Button2 pushed");}
    if (p3_oldstate == 1 && p3_actstate == 0) {Serial.println("Button3 pushed");}
    
  }
  if (p1_oldstate == 1 && p1_actstate == 0) {pushed = 1;}
  if (p2_oldstate == 1 && p2_actstate == 0) {pushed = 2;}
  if (p3_oldstate == 1 && p3_actstate == 0) {pushed = 3;}
    
  
}

void reset_eeprom() {
//Guthaben
EEPROM.write(101,0);   //Guthaben
EEPROM.write(201,0);   //stock1
EEPROM.write(202,0);   //stock2
EEPROM.write(203,0);   //stock3
 
}

void write_eeprom() {
//Guthaben
EEPROM.write(101,account);   //Guthaben
EEPROM.write(201,stock1);   //stock1
EEPROM.write(202,stock2);   //stock2
EEPROM.write(203,stock3);   //stock3
 
}

void read_eeprom () {
 account = EEPROM.read(101);  //Lesen Guthaben aus EEPROM
 stock1 = EEPROM.read(201);
 stock2 = EEPROM.read(202);
 stock3 = EEPROM.read(203);
}

void sell_product_or_tell_price() {
 if ( active == 1 ) {
  if (account < preis ) {   //noch nicht genug Guthaben
      lcd_1(ltxt_coin);  //Geldeinwerfen
      lcd_2_guthaben();
      led_reset();
      if (pushed > 0) {
        switch (pushed) {
        case 1:
          lcd_1(product1_chosen);
          lcd_2(product_price);
          lcd.write(e);
          break;
        case 2:
          lcd_1(product2_chosen);
          lcd_2(please_wait);
          lcd_2(product_price);
          lcd.write(e);
          break;
        case 3:
          lcd_1(product3_chosen);
          lcd_2(please_wait);
          lcd_2(product_price);
          lcd.write(e);
          break;
        }
        pushed = 0;
        delay(1300);      
      }
    } else {        //genug Guthaben
      lcd_1(ltxt_choose);  //Produkt wählen
      lcd_2_guthaben();
      led_blink();
      
      //LEDsnach Produktwahl ausschalten
      if (pushed > 0) {
      switch (pushed) {
      case 1:
        if( stock1 > 0 ) {
        lcd_1(product1_chosen);
        lcd_2(please_wait);
        stock1 = stock1 - 1;
        EEPROM.write(201,stock1);
        account = account - preis;
        pushed = 0;
        turn_motor(1);
        } else {
          lcd_1(product1_chosen);
          lcd_2(product_other);
          pushed = 0;
        }
        break;
      case 2:
        if( stock2 > 0 ) {
        lcd_1(product2_chosen);
        lcd_2(please_wait);
        stock2 = stock2 - 1;
        EEPROM.write(202,stock2);
        account = account - preis;
        pushed = 0;
        turn_motor(2);
        } else {
          lcd_1(product2_chosen);
          lcd_2(product_other);
          pushed = 0;
      }
        break;
      case 3:
        if( stock3 > 0 ) {
        lcd_1(product3_chosen);
        lcd_2(please_wait);
        stock3 = stock3 - 1;
        EEPROM.write(203,stock3);
        account = account - preis;
        pushed = 0;
        turn_motor(3);
        } else {
          lcd_1(product3_chosen);
          lcd_2(product_other);
          pushed = 0;
        }
        break;
      }
      delay(500);  //Produktausgabe
      }
    }
 } else {
 //nicht aktiv
     lcd_1(out_of_stock1);  //Geldeinwerfen
     lcd_2(out_of_stock2);  //Geldeinwerfen
     init_product_led();  
     if (account != 0 ) {
     EEPROM.write(101,0);
     }

 }
}

void menue_adm() {
  switch (adm_menu) {
    case 0:            //Stock1
    lcd_1(adm[0]);
    itoa(stock1,buff,10);
    lcd_2(buff);    
    break;
    case 1:
    lcd_1(adm[1]);
    itoa(stock2,buff,10);
    lcd_2(buff);    
    break;
    case 2:
    lcd_1(adm[2]);
    itoa(stock3,buff,10);
    lcd_2(buff);    
    break;
    case 3:
    lcd_1(adm[3]);
    lcd_2("");    
    break;
  }
}

void adm_action() {
  if (pushed > 0) {
     switch (pushed) {
     case 1:
      adm_menu = adm_menu + 1;
      if ( adm_menu > 3 ) {
        adm_menu = 0;
      }
      break;
     case 2:   //PLUS
      if (adm_menu == 0) {stock1 = stock1 + 1; write_eeprom(); read_eeprom();}
      if (adm_menu == 1) {stock2 = stock2 + 1; write_eeprom(); read_eeprom();}
      if (adm_menu == 2) {stock3 = stock3 + 1; write_eeprom(); read_eeprom();}
      break;
     case 3:   //MINUS
      if (adm_menu == 0) {stock1 = stock1 - 1; write_eeprom(); read_eeprom();}
      if (adm_menu == 1) {stock2 = stock2 - 1; write_eeprom(); read_eeprom();}
      if (adm_menu == 2) {stock3 = stock3 - 1; write_eeprom(); read_eeprom();}
      if (adm_menu == 3) {      //Werksreset
        reset_eeprom();
        read_eeprom();
        lcd_2("RESET...");
        delay(500);
      }
      break;
      
   
   }
     
  pushed = 0;
  }
}


