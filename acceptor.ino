 void acceptor_heartbeat() {
   if (toggle == 0) {
     toggle = 1;
   } else {
     toggle = 0;
   }
   for (int i = 0; i<8; i++) {
     if (i==2) {
       message_heartbeat[2]=16 + toggle;
     } 
     if (i==3) {
       message_heartbeat[3] = scheine;
     }
     if (i==6) {
      message_heartbeat[7] = message_heartbeat[1] ^ message_heartbeat[2];
      message_heartbeat[7] = message_heartbeat[7] ^ message_heartbeat[3];
      message_heartbeat[7] = message_heartbeat[7] ^ message_heartbeat[4];
      message_heartbeat[7] = message_heartbeat[7] ^ message_heartbeat[5];
      }
     accout(message_heartbeat[i]);

    }
  if ( message_heartbeat[4] != 16)  { message_heartbeat[4] = 16;}
  /*
  Serial.flush();
  delay(500);
  int counter = 0;
  */
  #define MAX_MILLIS_TO_WAIT 1000  //or whatever
  unsigned long starttime;
  
  starttime = millis();
  
  while ( (Serial.available()<11) && ((millis() - starttime) < MAX_MILLIS_TO_WAIT) )  {
  	// hang in this loop until we either get 9 bytes of data or 1 second
  }
  if(Serial.available() < 11)  {
  	lcd_1("ERR10 CALL SERVICE");
  } else {
  	for(int n=0; n<11; n++)
     	acceptor_state[n] = Serial.read() & 0x7F; // Then: Get them.
  }

  make_status();
  if (debug_acc==1) {
    Serial.print(message_heartbeat[0]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[1]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[2]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[3]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[4]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[5]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[6]);
    Serial.print(" "); 
    Serial.print(message_heartbeat[7]);
    Serial.print(" - "); 
    out_acceptor_state();
  }
// out_acceptor_state();
 }

void out_acceptor_state() {
  for (int i = 0; i <11 ; i++) {
    Serial.print(acceptor_state[i]);
    Serial.print(" ");
  }
  Serial.println();
}

void set_message_arrays() {
  scheine = 0;
  if (mask_scheine[6] == 1) { scheine = scheine + 64;}
  if (mask_scheine[5] == 1) { scheine = scheine + 32;}
  if (mask_scheine[4] == 1) { scheine = scheine + 16;}
  if (mask_scheine[3] == 1) { scheine = scheine +  8;}
  if (mask_scheine[2] == 1) { scheine = scheine +  4;}
  if (mask_scheine[1] == 1) { scheine = scheine +  2;}
  if (mask_scheine[0] == 1) { scheine = scheine +  1;}
}

void make_status() {
  //Checksumme prüfen
  delay(200);
  for (int i = 0; i< 12;i++) {
    if (i==3) {    //Status des Scheinprüfers
     if (debug_acc == 2) {
      if ( acceptor_state[i] == STATE_IDLE) {Serial.println("Idle....");}
      if ( acceptor_state[i] == STATE_ACCEPTING) {Serial.println("Accepting....");}
      if ( acceptor_state[i] == STATE_ESCROWED) {Serial.println("Escrowed....");}
      if ( acceptor_state[i] == STATE_STACKING) {Serial.println("Stacking....");}
      if ( acceptor_state[i] == STATE_STACKED) {Serial.println("Stacked....");}
      if ( acceptor_state[i] == STATE_RETURNING) {Serial.println("Returning....");}
      if ( acceptor_state[i] == STATE_RETURNED) {Serial.println("Returned....");}
     } 
   }
  }
  if (acceptor_state[3] == STATE_ESCROWED) {    //Schein im Einzug
    add_money = 0;
    if (acceptor_state[5] == 8 ) {add_money = 5;} 
    if (acceptor_state[5] == 16 ) {add_money = 10;}
    if (acceptor_state[5] == 24 ) {add_money = 20;}
    if (acceptor_state[5] == 32 ) {add_money = 50;}
    if (acceptor_state[5] == 40 ) {add_money = 100;}
    if (acceptor_state[5] == 48 ) {add_money = 200;}
    //Schein jetzt einziehen
    message_heartbeat[4] = 32;
 
  }
  if (acceptor_state[3] == STATE_IDLE) {    //Schein im Einzug
    account = account + add_money;
    EEPROM.write(11,account);

    if (debug==1){Serial.println("ADD");};
    add_money = 0;
}
}



