



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
        delay(400);      
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
        EEPROM.write(21,stock1);
        write_eeprom_stat(1);
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
        EEPROM.write(22,stock2);
        write_eeprom_stat(2);
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
        EEPROM.write(23,stock3);
        write_eeprom_stat(3);
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
      delay(200);  //Produktausgabe
      }
    }
 } else {
 //nicht aktiv
     lcd_1(out_of_stock1);  //Geldeinwerfen
     lcd_2(out_of_stock2);  //Geldeinwerfen
     init_product_led();  
     if (account != 0 ) {
     EEPROM.write(11,0);
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
    case 4:
    lcd_1(adm[4]);
    lcd_2("");    
    break;
    case 5:
    lcd_1(adm[5]);
    lcd_2("");    
    break;
    
  }
}

void adm_action() {
  if (pushed > 0) {
     lcd_2("");
     switch (pushed) {
     case 1:
      adm_menu = adm_menu + 1;
      if ( adm_menu > 5 ) {
        adm_menu = 0;
      }
      break;
     case 2:   //PLUS
      if (adm_menu == 0) {stock1 = stock1 + 1; write_eeprom(); read_eeprom(); itoa(stock1,buff,10); lcd_2(""); lcd_2(buff); }
      if (adm_menu == 1) {stock2 = stock2 + 1; write_eeprom(); read_eeprom(); itoa(stock2,buff,10); lcd_2(""); lcd_2(buff); }
      if (adm_menu == 2) {stock3 = stock3 + 1; write_eeprom(); read_eeprom(); itoa(stock3,buff,10); lcd_2(""); lcd_2(buff); }
      break;
     case 3:   //MINUS
      if (adm_menu == 0) {stock1 = stock1 - 1; write_eeprom(); read_eeprom(); itoa(stock1,buff,10); lcd_2(""); lcd_2(buff); }
      if (adm_menu == 1) {stock2 = stock2 - 1; write_eeprom(); read_eeprom(); itoa(stock2,buff,10); lcd_2(""); lcd_2(buff); }
      if (adm_menu == 2) {stock3 = stock3 - 1; write_eeprom(); read_eeprom(); itoa(stock3,buff,10); lcd_2(""); lcd_2(buff); }
      if (adm_menu == 3) {      //Werksreset
        reset_eeprom();
        read_eeprom();
        reset_eeprom_stat();
        lcd_2("RESET...");
        delay(500);
      }
      if (adm_menu == 4) {      //Statistik reset
        reset_eeprom_stat();
        lcd_2("RESET...");
        delay(500);
      }
      if (adm_menu == 5) {      //zurueck
        clear_keylog();
        adm_state = 0;
        delay(500);
        adm_menu = 0;
      }
      break;
   }
  pushed = 0;
  }
}


//Statistik Menü
void menue_stat() {
  read_eeprom_stat();
  switch (stat_menu) {
    case 0:            //Stock1
    lcd_1(stat[0]);
    itoa(vend1,buff,10);
    lcd_2(buff);    
    break;
    case 1:
    lcd_1(stat[1]);
    itoa(vend2,buff,10);
    lcd_2(buff);    
    break;
    case 2:
    lcd_1(stat[2]);
    itoa(vend3,buff,10);
    lcd_2(buff);    
    break;
    case 3:
    lcd_1(stat[3]);
    lcd_2("");
    break;
  }
}
//Statistik Aktionen
void stat_action() {
  if (pushed > 0) {
    lcd_2("");
    switch (pushed) {
     case 1:
      stat_menu = stat_menu + 1;
      if ( stat_menu > 3 ) {
        stat_menu = 0;
      }
      break;
     case 2:   //PLUS
     // do nothing
     break;
     case 3:   //MINUS
      if (stat_menu == 3) {      //zurueck
        clear_keylog();
        adm_state = 0;
        delay(500);
        stat_menu = 0;
      }
      break;
   }
     
  pushed = 0;
  }
}

//reset Guthaben und Stock
void reset_eeprom() {
  EEPROM.write(11,0);   //Guthaben
  EEPROM.write(21,0);   //stock1
  EEPROM.write(22,0);   //stock2
  EEPROM.write(23,0);   //stock3
}

//schreiben Guthaben und Stock
void write_eeprom() {
  EEPROM.write(11,account);   //Guthaben
  EEPROM.write(21,stock1);   //stock1
  EEPROM.write(22,stock2);   //stock2
  EEPROM.write(23,stock3);   //stock3
}

//lesen Guthaben und Stock
void read_eeprom () {
 account = EEPROM.read(11);  //Lesen Guthaben aus EEPROM
 stock1 = EEPROM.read(21);
 stock2 = EEPROM.read(22);
 stock3 = EEPROM.read(23);
}


//Statistik-Funktionen

//reset statistic
void reset_eeprom_stat() {
  EEPROM.write(31,0);   //stock1
  EEPROM.write(32,0);   //stock2
  EEPROM.write(33,0);   //stock3
}

//statistic schreiben
void write_eeprom_stat(int type) {
   switch (type) {
    case 1:
      vend1 = EEPROM.read(31) + 1;
      EEPROM.write(31,vend1);   //vend1
      break;
    case 2:
      vend2 = EEPROM.read(32) + 1;
      EEPROM.write(32,vend2);   //vend2
      break;
    case 3:
      vend3 = EEPROM.read(33) + 1;
      EEPROM.write(33,vend3);   //vend3
      break;
  }
}

//reset statistic
void read_eeprom_stat () {
 vend1 = EEPROM.read(31);
 vend2 = EEPROM.read(32);
 vend3 = EEPROM.read(33);
}


