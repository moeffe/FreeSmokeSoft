//Defines zu akzeptierende Scheine

//Hier werden die zu akzeptierenden Scheine des Geldscheinprüfers eingestellt
//Reihenfolge 5 EUR, 10 EUR, 20 EUR, 50 EUR, 100 EUR, 200 EUR
int mask_scheine[7] = {1,1,1,1,1,0,0};

//Preis pro Zigarette 
int preis = 10;

//Texte für das Display können bliebig verändert werden
//Startbildschirm
char ltxt_start1[17] = "FreeSmoke V 0.2 ";
char ltxt_start2[17] = "starting...     ";
char ltxt_coin[17]    = "insert note    ";
char ltxt_choose[17]  = "select product  ";
char ltxt_account[17] = "credit  :       ";
char product1_chosen[17] = "e-Zig light";
char product2_chosen[17] = "e-Zig medium";
char product3_chosen[17] = "e-Zig hard";
char product_price[17] = "costs only 10";
char please_wait[17] = "wait  ...";
char product_other[17] = "sorry, is out ";
char out_of_stock1[17] = "out of order..";
char out_of_stock2[17] = "Call: 922167959";

//Admin Menü
int adm_menu_anzhl = 6;
  char* adm[6] = {
"Stock 1: ",
"Stock 2: ",
"Stock 3: ",
"factory reset",
"statistic Reset",
"exit......"
};


//Admin Menü
int stat_menu_anzhl = 4;
  char* stat[4] = {
"sold prod 1: ",
"sold prod 2: ",
"sold prod 3: ",
"salir..."
};

int passcode[100] = {3,2,3,1,1,1};
int passcode_stat[100] = {3,3,3,1,1,1};

