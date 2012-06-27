int debug = 0;           //Debug-.Ausgaben einschalten
int debug_acc = 2;
int debug_key = 1;

//Defines für den Acceptor
#define accout Serial.write
//#define accinp Serial.read

#define P1_LED 9
#define P2_LED 10
#define P3_LED 11

#define P1_BUTTON 8
#define P2_BUTTON 7
#define P3_BUTTON 4

//Servomotoren
#define P1_MOTOR 3
#define P2_MOTOR 5
#define P3_MOTOR 6
#define motor_angle_off 15
#define motor_angle_on 165
#define motor_delay 800
#define motor_speed 5


//Statusbits des Scheinprüfers
#define STATE_IDLE      1
#define STATE_ACCEPTING 2
#define STATE_ESCROWED  4
#define STATE_STACKING  8
#define STATE_STACKED   16
#define STATE_RETURNING 32
#define STATE_RETURNED  64

#define lz "                " //Leerzeile LCD

int message_heartbeat[8] = {2,8,16,1,16,0,3,0}; //Grundnachricht an den Scheinprüfer

int scheine = 0;         //byte zu akzeptierende Scheine
int account = 0;         //aktuelles Guthaben
int account_old = 0;         //aktuelles Guthaben

int add_money = 0;       //zu addierendes Gutahben
char zeil[8] = "       ";//
int incB;                //eigehendes Byte
  

int acceptor_state[11];  //Nachricht vom Scheinprüfer
int toggle = 0;          //Umschalten Nachrichten an Scheinprüfer

int active = 1;
int i = 0;
char buff[4];

//LED-Blinken
long previousMillis = 0;        // will store last time LED was updated
long interval = 500;           // interval at which to blink (milliseconds)
int ledState = 0;

//Text-Rotation
long lcd_prevMillis = 0;        // will store last time LED was updated
long lcd_interval = 1500;           // interval at which to blink (milliseconds)




//Buttons
int p1_actstate = 0;
int p2_actstate = 0;
int p3_actstate = 0;
int p1_oldstate = 0;
int p2_oldstate = 0;
int p3_oldstate = 0;

int pushed = 0;

int stock1 = 0;
int stock2 = 0;
int stock3 = 0;

char* lcd1_old;
char* lcd2_old;

int adm_state = 0;
int adm_menu = 0;
int stat_menu = 0;

int keylog[100];
int keycount = 0;


long start_keylog_time = 0;
long keylog_reset_time = 6000;

int vend1 = 0;
int vend2 = 0;
int vend3 = 0;

int lcd_anz = 1;

