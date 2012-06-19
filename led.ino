
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
