#include "LedControl.h"
#include <LiquidCrystal.h>                  // for lcd
#define joystickX A0
#define joystickY A1

int din = 12, clk = 11, load = 10;          //pinii in care sunt puse aceste componente ale driverului
LedControl lc = LedControl(din, clk, load, 1);

const int rs = 13, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 8;
const int butonPin = 7;                     //pin pentru butonul alb care porneste sau opreste jocul
const int lcdPin = 9;                       //pin pentru setarea luminozitatii LCD-ului
const int joystickButonPin = 2;             //pin pentru butonul joystick-ului

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int stareJoc = 0;                           //0 pentru mesaj de intampinare, 1 pt selectare nivel, 2 pentru joc, 3 pentru pierdut, 4 pentru castigat
int nivelActual = 1;                        //nivelul la care s-a ajuns cu jocul
unsigned long timpCurent;                   //pentru delay-uri etc.
unsigned long timpAnteriorMinge = 0;        //special pt minge pt a se misca independent de paleta si altele - aici paleta mi-ar fi updatat mereu timpAnterior-ul si asa mingea nu se misca decat dupa ce terminam de miscat paleta
unsigned long timpAnterior = 0;             //pentru delay-uri etc.
int xMinge, yMinge;                         //coordonatele initiale ale mingii
int directieMingeX, directieMingeY;         //vor avea valorile 1 sau -1, in functie de cum se misca mingea
int scor;
int vieti = 3;
byte pauza = false;                         //pt a putea pune pauza in timpul jocului prin apasarea butonului


byte paleta;                                //aici o sa pun paleta pt fiecare nivel
byte paleta1 = {B00111100};
byte paleta2 = {B00111000};
byte paleta3 = {B00011000};

byte nivel[7];                              //aici o sa pun ce nivel o sa joc
byte nivel1[7] = {B11100111,
                  B11000011,
                  B10000001,
                  B00000000,
                  B00000000,
                  B00000000,
                  B00000000};

byte nivel2[7] = {B11111111,
                  B11100111,
                  B11000011,
                  B10000001,
                  B00000000,
                  B00000000,
                  B00000000};

byte nivel3[7] = {B11111111,
                  B11111111,
                  B11011011,
                  B11000011,
                  B00000000,
                  B00000000,
                  B00000000};


int scorMaxim[4]   = {0,  12,  32,  58};
int dificultate[4] = {0, 155, 127, 105};

byte pierdut[8] = {B10000001,
                   B01000010,
                   B00100100,
                   B00011000,
                   B00011000,
                   B00100100,
                   B01000010,
                   B10000001};

byte castigat[8] = {B00000000,
                    B00100100,
                    B00100100,
                    B00100100,
                    B10000001,
                    B01000010,
                    B00111100,
                    B00000000};


void setup()
{
  lc.shutdown(0, false);                    // porneste matricea
  lc.setIntensity(0, 8);                    // seteaza luminozitatea (valori intre 0 si 15)
  lc.clearDisplay(0);                       // sterge ecranul matricei
  lcd.begin(16, 2);                         // seteaza nr. de linii si coloane al LCD-ului
  analogWrite(lcdPin, 80);                  //seteaza luminozitatea LCD-ului

  pinMode(butonPin, INPUT);
  pinMode(joystickButonPin, INPUT);
  
  welcome();
}

void welcome()
{
  lcd.setCursor(2, 0);
  lcd.print("BlockBreaker");
  lcd.setCursor(0, 1);
  lcd.print("START: buton alb");
}

void beforeStart()
{
  stareJoc = 1;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Nivelul  ");
  lcd.print(nivelActual);
  lcd.setCursor(0, 1);
  lcd.print("START: buton alb");

  delay(250);
}

void initializareJoc()
{
  timpCurent = millis();
  if(timpCurent - timpAnterior > 250)
  {
    timpAnterior = timpCurent;
    xMinge = 1;
    yMinge = 6;
    stareJoc = 2;
    directieMingeX = 1;
    directieMingeY = -1;
  
    if(nivelActual == 1)
    {
      for(int i = 0; i < 7; i++)
      {
        nivel[i] = nivel1[i];
      }
      paleta = paleta1;
    }
    else if(nivelActual == 2)
    {
      for(int i = 0; i < 7; i++)
      {
        nivel[i] = nivel2[i];
      }
      paleta = paleta2;
    }
    else if(nivelActual == 3)
    {
      for(int i = 0; i < 7; i++)
      {
        nivel[i] = nivel3[i];
      }
      paleta = paleta3;
    }
    
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Scor : ");
    lcd.print(scor);
    lcd.setCursor(4, 1);
    lcd.print("Vieti: ");
    lcd.print(vieti);
  
    lc.clearDisplay(0);
  
    for (int rand = 0; rand < 7; rand++)
    {
      lc.setRow(0, rand, nivel[rand]);
    }
  }
}

void atiPierdut()
{
  for(int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, pierdut[i]);
  }

  timpCurent = millis();

  if (timpCurent - timpAnterior > 250)
  {
    timpAnterior = timpCurent;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Ati pierdut!");
    lcd.setCursor(4, 1);
    lcd.print("Scor : ");
    lcd.print(scor);
  }
}

void maiAvetiSanse()
{
  timpCurent = millis();

  if (timpCurent - timpAnterior > 250)
  {
    timpAnterior = timpCurent;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vieti ramase:  ");
    lcd.print(vieti - 1);
    lcd.setCursor(0, 1);
    lcd.print("CONTIN:buton alb");
  }
}

void atiCastigat()
{
  nivelActual++;

  for(int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, castigat[i]);
  }

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Bravo! Urmeaza");
  lcd.setCursor(2, 1);
  lcd.print("Nivelul  ");
  lcd.print(nivelActual);

  delay(3000);

  beforeStart();
}

void atiCastigatJocul()
{
  for(int i = 0; i < 8; i++)
  {
    lc.setRow(0, i, castigat[i]);
  }

  timpCurent = millis();
  if (timpCurent - timpAnterior > 250)
  {
    timpAnterior = timpCurent;
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Felicitari");
    lcd.setCursor(0, 1);
    lcd.print("Ati castigat tot");
    lcd.print(nivelActual);
  }
}

void joaca()
{
  if(scorMaxim[nivelActual] == scor)
  {
    stareJoc = 4;
  }

  timpCurent = millis();
  
  miscareMinge();
  miscarePaleta();
}

void miscareMinge()
{
  lc.setRow(0, yMinge, (1 << xMinge) | nivel[yMinge]);

  if (timpCurent - timpAnteriorMinge > dificultate[nivelActual])
  {
    timpAnteriorMinge = timpCurent;

    lc.setRow(0, yMinge - directieMingeY, 0 | nivel[yMinge - directieMingeY]);

    if(xMinge == 0 && directieMingeX == -1)
    {
      directieMingeX = 1;
    }
    else if(xMinge == 7 && directieMingeX == 1)
    {
      directieMingeX = -1;
    }

    if(yMinge == 0 && directieMingeY == -1)
    {
      directieMingeY = 1;
    }
    else if(yMinge == 6 && directieMingeY == 1)
    {
      if((1 << xMinge) & paleta)
      {
        directieMingeY = -1;
      }
      else
      {
        stareJoc = 3;
      }
    }
    
    if(yMinge + directieMingeY >= 0 && yMinge + directieMingeY < 7 && ((1 << (xMinge)) & nivel[yMinge + directieMingeY]))
    {
      nivel[yMinge + directieMingeY] = nivel[yMinge + directieMingeY] ^ (1 << (xMinge));
      lc.setRow(0, yMinge + directieMingeY, nivel[yMinge + directieMingeY]);
      scor++;
      directieMingeY *= -1;

      if(yMinge + directieMingeY >= 0 && yMinge + directieMingeY < 7 && ((1 << (xMinge + directieMingeX)) & nivel[yMinge + directieMingeY]))
      {
        nivel[yMinge + directieMingeY] = nivel[yMinge + directieMingeY] ^ (1 << (xMinge + directieMingeX));
        lc.setRow(0, yMinge + directieMingeY, nivel[yMinge + directieMingeY]);
        scor++;
        directieMingeY *= -1;
        directieMingeX *= -1;
      }

      if(yMinge + directieMingeY >= 0 && yMinge + directieMingeY < 7 && ((1 << (xMinge + directieMingeX)) & nivel[yMinge + directieMingeY]))
      {
        nivel[yMinge + directieMingeY] = nivel[yMinge + directieMingeY] ^ (1 << (xMinge + directieMingeX));
        lc.setRow(0, yMinge + directieMingeY, nivel[yMinge + directieMingeY]);
        scor++;
        directieMingeY *= -1;
        directieMingeX *= -1;
      }
    }
    else if(yMinge + directieMingeY >= 0 && yMinge + directieMingeY < 7 && ((1 << (xMinge + directieMingeX)) & nivel[yMinge + directieMingeY]))
    {
      nivel[yMinge + directieMingeY] = nivel[yMinge + directieMingeY] ^ (1 << (xMinge + directieMingeX));
      lc.setRow(0, yMinge + directieMingeY, nivel[yMinge + directieMingeY]);
      scor++;
      directieMingeY *= -1;
      directieMingeX *= -1;
      
    }

    if(xMinge == 0 && directieMingeX == -1)
    {
      directieMingeX = 1;
    }
    else if(xMinge == 7 && directieMingeX == 1)
    {
      directieMingeX = -1;
    }

    if(yMinge == 0 && directieMingeY == -1)
    {
      directieMingeY = 1;
    }
    else if(yMinge == 6 && directieMingeY == 1)
    {
      if((1 << xMinge) & paleta)
      {
        directieMingeY = -1;
      }
      else
      {
        stareJoc = 3;
      }
    }

    xMinge += directieMingeX;
    yMinge += directieMingeY;

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Scor : ");
    lcd.print(scor);
    lcd.setCursor(4, 1);
    lcd.print("Vieti: ");
    lcd.print(vieti);
    
  }
  else lc.setRow(0, yMinge - directieMingeY, 0 | nivel[yMinge - directieMingeY]);
}

void miscarePaleta()
{
  
  int X = map(analogRead(joystickX), 0, 1023, 1, 18);
  int Y = map(analogRead(joystickY), 0, 1023, 1, 18);

  if(X >= 13)
  {
    if(nivelActual == 1 && paleta > 15 || nivelActual == 2 && paleta > 7 || nivelActual == 3 && paleta > 3)
    {
      if(X >= 17 && timpCurent - timpAnterior > 50)
      {
        timpAnterior = timpCurent;
        paleta = paleta >> 1;
      }
      else if(X >= 15 && timpCurent - timpAnterior > 90)
      {
        timpAnterior = timpCurent;
        paleta = paleta >> 1;
      }
      else if(timpCurent - timpAnterior > 215)
      {
        timpAnterior = timpCurent;
        paleta = paleta >> 1;
      }
    }
  }
  else if(X <= 6)
  {
    if(nivelActual == 1 && paleta < 240 || nivelActual == 2 && paleta < 224 || nivelActual == 3 && paleta < 192)
    {
      if(X <= 2 && timpCurent - timpAnterior > 50)
      {
        timpAnterior = timpCurent;
        paleta = paleta << 1;
      }
      else if(X <= 4 && timpCurent - timpAnterior > 90)
      {
        timpAnterior = timpCurent;
        paleta = paleta << 1;
      }
      else if(timpCurent - timpAnterior > 215)
      {
        timpAnterior = timpCurent;
        paleta = paleta << 1;
      }
    }
  }

  lc.setRow(0, 7, paleta);
}

void loop()
{
  int stareButon = digitalRead(butonPin);

  if (stareJoc == 0)
  {
    if (stareButon == HIGH)
    {
      beforeStart();
    }
  }
  else if (stareJoc == 1)
  {
    if (stareButon == HIGH)
    {
      initializareJoc();
    }
  }
  else if (stareJoc == 2)
  {
    if (pauza == false)
      joaca();

    timpCurent = millis();
    if (timpCurent - timpAnterior > 250 && stareButon == HIGH)
    {
      timpAnterior = timpCurent;
      
      if (pauza == true)
        pauza = false;
      else
        pauza = true;
    }
  }
  else if (stareJoc == 3)
  {
    if (vieti == 1)
    {
      atiPierdut();
      if (stareButon == HIGH)
      {
        nivelActual = 1;
        scor = 0;
        vieti = 3;
        lc.clearDisplay(0);
        beforeStart();
      }
    }
    else
    {
      maiAvetiSanse();
      if (stareButon == HIGH)
      {
        vieti--;
        stareJoc = 2;
        timpAnterior = millis();
        xMinge = 1;
        yMinge = 6;
        directieMingeX = 1;
        directieMingeY = -1;
      }
    }
  }
  else
  {
    if (nivelActual == 3)
    {
      atiCastigatJocul();
      if (stareButon == HIGH)
      {
        nivelActual = 1;
        scor = 0;
        vieti = 3;
        lc.clearDisplay(0);
        beforeStart();
      }
    }
    else
    {
      atiCastigat();
      if (stareButon == HIGH)
      {
        initializareJoc();
      }
    }
  }
}

