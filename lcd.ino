void init_lcd() {
  lcd.begin(16, 2);
  lcd.createChar(e, eursymbol);
  lcd.clear();
  lcd.setBacklight(HIGH);
}

void splashscreen() {
  lcd.setCursor(0, 0);
  lcd.print(ltxt_start1);
  lcd.setCursor(0, 1);
  lcd.print(ltxt_start2);
  delay(1500);
  lcd.clear();
}

void lcd_1(char* zeile) {
  if (zeile != lcd1_old) {
    lcd.setCursor(0, 0);
    lcd.print(lz);
    lcd.setCursor(0, 0);
    lcd.print(zeile);
  }
  lcd1_old = zeile;
}

void lcd_2(char* zeile) {
  if (zeile != lcd2_old) {
    lcd.setCursor(0, 1);
    lcd.print(lz);
    lcd.setCursor(0, 1);
    lcd.print(zeile);
  }
  lcd2_old = zeile;
}

/*
void lcd_2_guthaben () {
  if (account != account_old) {
    itoa(account,buff,10);
    for (i = 0; i<4; i++) {
      ltxt_account[i+9] = buff[i];  
    }
    lcd.setCursor(0, 1);
    lcd.print(lz);
    lcd.setCursor(0, 1);
    lcd.print(ltxt_account);
    lcd.print(char(e));
    account_old = account;
  }
  if (account == 0 ) {
    lcd_2("");
  }
}
*/

void rotate_lcd(int state) {
  unsigned long currentlcdMillis = millis();
   if(currentlcdMillis - lcd_prevMillis > lcd_interval) {
    switch (state) {
      case 1:     //normalbetrieb
      if (lcd_anz == 1) {
        lcd_1(s1z1_1);
        lcd_2(s1z2_1);
      } else if (lcd_anz == 2) {
        lcd_1(s1z1_2);
        lcd_2(s1z2_2);  
      } else if (lcd_anz == 3) {
        lcd_1(s1z1_3);
        lcd_2(s1z2_3);
      } else if (lcd_anz == 4) {
        lcd_1(s1z1_4);
        lcd_2(s1z2_4);
      }
      lcd_anz = lcd_anz + 1;
      if ( lcd_anz > 4 ) {lcd_anz = 1;}
      break;
      case 2:     //Produkt wählen
      if (lcd_anz == 1) {
        lcd_1(s2z1_1);
        lcd_2(s2z2_1);
      } else if (lcd_anz == 2) {
        lcd_1(s2z1_2);
        lcd_2(s2z2_2);  
      } 
      lcd_anz = lcd_anz + 1;
      if ( lcd_anz > 2 ) {lcd_anz = 1;}
      break;
    }
    lcd_prevMillis = millis();
    
   }
}

