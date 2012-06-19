
void get_keystate() {
  p1_oldstate = p1_actstate;
  p2_oldstate = p2_actstate;
  p3_oldstate = p3_actstate;
  p1_actstate = digitalRead(P1_BUTTON);
  p2_actstate = digitalRead(P2_BUTTON);
  p3_actstate = digitalRead(P3_BUTTON);
  if (p1_oldstate == 1 && p1_actstate == 0) {pushed = 1;ins_keylog(1);}    
  if (p2_oldstate == 1 && p2_actstate == 0) {pushed = 2; ins_keylog(2);}
  if (p3_oldstate == 1 && p3_actstate == 0) {pushed = 3; ins_keylog(3);}
  //zurücksetzen nach Zeitablauf
  if (millis() - start_keylog_time > keylog_reset_time && adm_state == 0) {
    clear_keylog();
  }
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

//keylog reset
void clear_keylog(){
  keycount = 0;
  for (int i=0;i<100;i++) {
    keylog[i] = 0;
  }
}

//keylog schreiben
void ins_keylog(int value) {
  start_keylog_time = millis();
  if (adm_state == 0) {
 
    keylog[keycount] = value;
    keycount = keycount + 1;
  }
  
}
