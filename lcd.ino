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
