//Defines zu akzeptierende Scheine

//Hier werden die zu akzeptierenden Scheine des Geldscheinprüfers eingestellt
//Reihenfolge 5 EUR, 10 EUR, 20 EUR, 50 EUR, 100 EUR, 200 EUR
int mask_scheine[7] = {1,1,1,1,1,0,0};

//Preis pro Zigarette 
int preis = 10;

//Texte für das Display können bliebig verändert werden
//Startbildschirm
char ltxt_start1[17] = "FreeSmoke V 0.1 ";
char ltxt_start2[17] = "Startvorgang    ";

char ltxt_coin[17]    = "Geld einwerfen  ";
char ltxt_choose[17]  = "Produktwahl     ";
char ltxt_account[17] = "Guthaben:       ";

char product1_chosen[17] = "e-Zig light";
char product2_chosen[17] = "e-Zig medium";
char product3_chosen[17] = "e-Zig hard";

char product_price[17] = "kostet nur 10";

char please_wait[17] = "Ausgabe...";

char product_other[17] = "leider leer....";

char out_of_stock1[17] = "Ausverkauft...";
char out_of_stock2[17] = "Call: 922167959";



//Admin Menü
int adm_menu_anzhl = 4;
  char* adm[4] = {
"Stock 1: ",
"Stock 2: ",
"Stock 3: ",
"Werksreset"
};


