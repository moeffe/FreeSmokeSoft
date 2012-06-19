
void turn_motor(int motor) {
  int pos;
  switch (motor) {
    case 1:
    for(pos = motor_angle_off; pos < motor_angle_on; pos +=1) {
     motor1.write(pos);           // sweep start position 
     delay(motor_speed);                            // 15ms delay for sweep
   } 
     EEPROM.write(101,account);  //Guthaben speichern
    delay(motor_delay);
    for(pos = motor_angle_on; pos > motor_angle_off; pos -=1) {
     motor1.write(pos);           // sweep start position 
     delay(motor_speed);                            // 15ms delay for sweep
   } 

    break;
    case 2:
    for(pos = motor_angle_off; pos < motor_angle_on; pos +=1) {
     motor2.write(pos);           // sweep start position 
     delay(motor_speed);                            // 15ms delay for sweep
   } 
     EEPROM.write(101,account);  //Guthaben speichern
    delay(motor_delay);
    for(pos = motor_angle_on; pos > motor_angle_off; pos -=1) {
     motor2.write(pos);           // sweep start position 
     delay(motor_speed);                            // 15ms delay for sweep
   } 

    break;
    case 3:
    for(pos = motor_angle_off; pos < motor_angle_on; pos +=1) {
     motor3.write(pos);           // sweep start position 
     delay(motor_speed);                            // 15ms delay for sweep
     EEPROM.write(101,account);  //Guthaben speichern
   } 
    delay(motor_delay);
    for(pos = motor_angle_on; pos > motor_angle_off; pos -=1) {
     motor3.write(pos);           // sweep start position 
     delay(motor_speed);                            // 15ms delay for sweep
   } 

    break;
  }
}


void init_motors() {
  pinMode(P1_MOTOR, OUTPUT); 
  pinMode(P2_MOTOR, OUTPUT); 
  pinMode(P3_MOTOR, OUTPUT); 
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  motor1.attach(P1_MOTOR);  // attaches the servo on pin 9 to the servo object 
  motor2.attach(P2_MOTOR);  // attaches the servo on pin 9 to the servo object 
  motor3.attach(P3_MOTOR);  // attaches the servo on pin 9 to the servo object 
  motor1.write(motor_angle_off);  ;  //Ausgabe
  motor2.write(motor_angle_off);  ;  //Ausgabe
  motor3.write(motor_angle_off);  ;  //Ausgabe
  
}

