#include <Keypad.h>
const byte ROWS = 4;
const byte COLS = 4;

byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] = {12, 13, A4, A3};

char keys[ROWS][COLS] = {
  {'ON','OFF','1','#'},
  {'B','+','2','3'},
  {'<','-','>','A'},
  {'4','5','S','P'}
};
Keypad klawiatura = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5 , 6, 7);

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel led = Adafruit_NeoPixel(8, A2, NEO_GRB + NEO_KHZ800);

#define PIR A1
#define buzzer A0
#define foto A5

volatile int stan = 1;
volatile int czasCONST = 2000;
volatile int czas = 0;
volatile int trybLED = 1;
volatile int trybPRACY = 1;
volatile int jasnosc = 30;
volatile int prog = 200;
volatile bool ON = 0;
volatile bool LEDwylacz = 1;
volatile long zapamietanyczas = 0;
volatile int kolor = 1;
volatile float R = 1;
volatile float G = 1;
volatile float B = 1;
String kolorPOKAZ;
String trybPOKAZ;


void setup() {
Serial.begin(9600);
led.begin();
led.show();
pinMode(PIR, INPUT);
pinMode(buzzer, OUTPUT);
digitalWrite(buzzer,0);
lcd.begin(16,2);
lcd.clear();

}

void loop() {
    if(stan == 1) {
      //lock screen

    lcd.setCursor(0,0);
    lcd.print("Start ||");
    lcd.setCursor(0,1);
    lcd.print("Ustawienia #");
    int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
    ON = 1;
    }
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();
    }
    if(ON == 1){
    lampa(); 
    }
    if (klawisz == '#') {
      pik();
    stan = 2;
    lcd.clear();
    }
    }
    


    if(stan == 2) {
     //<jasnosc>

    lcd.setCursor(0,0);
    lcd.print("< jasnosc >");
        int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
      ON = 1;}
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();}
    if (ON == 1){
      lampa(); }
    if (klawisz == 'A') {
      pik();
      lcd.clear();
      stan = 3; } 
      if (klawisz == 'B') {
        pik();
        lcd.clear();
        stan = 1;
      }
      if(klawisz == '>'){
        pik();
        lcd.clear();
        stan = 4;
      }
      if(klawisz == '<') {
        pik();
        lcd.clear();
        stan = 12;
      } }


     if(stan == 3) {
      //jasnosc +-

      int klawisz = klawiatura.getKey();
      long czas1 = millis();
     if(czas1 - zapamietanyczas >= 250) {
      zapamietanyczas = czas1;
      lcd.clear();
     }
      if (klawisz == '+') {
        pik();
        jasnosc = jasnosc + 10;
        if(jasnosc >= 255) {
          jasnosc = 255;
        }
      }
      if (klawisz == '-') {
        pik();
        jasnosc = jasnosc - 10;
        if (jasnosc <= 0) {
          jasnosc = 0;
        }
      }
      lcd.setCursor(0,0);
      lcd.print("jasnosc   +");
      lcd.setCursor(0,1);
      int pokazowajasnosc = map(jasnosc, 0, 255, 0, 100);
      lcd.print(pokazowajasnosc);
      lcd.setCursor(3,1);
      lcd.print("%      -");
        if(klawisz == 'B'){
          pik();
        lcd.clear();
        czas1 = 0;
        stan = 2;
      }
     }
     if(stan == 4) {
      // < czas >
      lcd.setCursor(0,0);
      lcd.print("< czas >");
      int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
      ON = 1;}
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();}
    if (ON == 1){
      lampa(); }
      if(klawisz == 'A'){
         pik();
        lcd.clear();
         stan = 5; }
      if(klawisz == 'B'){
        pik();
        lcd.clear();
        stan = 1;}
      if(klawisz == '<') {
        pik();
        lcd.clear();
        stan = 2;
      }
      if(klawisz == '>') {
        pik();
        lcd.clear();
        stan = 6;
      }
     }

     if(stan == 5) {
      // czas + -
      int klawisz = klawiatura.getKey();
      long czas1 = millis();
     if(czas1 - zapamietanyczas >= 250) {
      zapamietanyczas = czas1;
      lcd.clear();
     }
      if (klawisz == '+') {
        pik();
        czasCONST = czasCONST + 1000;
        if(czasCONST >= 10000) {
          czasCONST = 10000;
        }
      }
      if (klawisz == '-') {
        pik();
        czasCONST = czasCONST - 1000;
        if (czasCONST <= 1000) {
          czasCONST = 1000;
        }
      }
      lcd.setCursor(0,0);
      lcd.print("czas   +");
      lcd.setCursor(0,1);
      int pokazowyczas = map(czasCONST, 1, 10000, 1, 10);
      lcd.print(pokazowyczas);
      lcd.setCursor(3,1);
      lcd.print("s   -");
        if(klawisz == 'B'){
          pik();
        lcd.clear();
        czas1 = 0;
        stan = 4;
      }
     }

     if(stan == 6) {
      //  < tryb LED >
      lcd.setCursor(0,0);
      lcd.print("< tryb LED >");
    int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
      ON = 1;}
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();}
    if (ON == 1){
      lampa(); }
      if(klawisz == 'A'){
         pik();
        lcd.clear();
         stan = 7; }
      if(klawisz == 'B'){
        pik();
        lcd.clear();
        stan = 1;}
      if(klawisz == '<') {
        pik();
        lcd.clear();
        stan = 4;
      }
      if(klawisz == '>') {
        pik();
        lcd.clear();
        stan = 8;
      }
     }



      if(stan == 7) {
      // wybór LED
      int klawisz = klawiatura.getKey();
     if(klawisz == '+') {
      pik();
      trybLED = trybLED + 1;
      if(trybLED >= 5) {
        trybLED = 5;
      }
    lcd.setCursor(0,1);
    lcd.print(trybLED);
      int trybZAPAMIETAJ = trybPRACY;
      trybPRACY = 0;
      lampa();
      trybPRACY = trybZAPAMIETAJ;     
     }
     if(klawisz == '-') {
      pik();
      trybLED = trybLED - 1;
      if(trybLED <= 1) {
        trybLED = 1;
      }
    lcd.setCursor(0,1);
    lcd.print(trybLED);
    int trybZAPAMIETAJ = trybPRACY;
      trybPRACY = 0;
      lampa();
      trybPRACY = trybZAPAMIETAJ;
     }
    lcd.setCursor(0,0);
    lcd.print("tryb LED +");
    lcd.setCursor(0,1);
    lcd.print(trybLED);
    lcd.setCursor(9,1);
    lcd.print("-");
        if(klawisz == 'B'){
        pik();
        lcd.clear();
        stan = 6;
      }
    
      }


      if(stan == 8) {
        // < kolor > 
        lcd.setCursor(0,0);
        lcd.print("< kolor >");
    int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
      ON = 1;}
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();}
    if (ON == 1){
      lampa(); }
      if(klawisz == 'A'){
         pik();
        lcd.clear();
         stan = 9; }
      if(klawisz == 'B'){
        pik();
        lcd.clear();
        stan = 1;}
      if(klawisz == '<') {
        pik();
        lcd.clear();
        stan = 6;
      }
      if(klawisz == '>') {
        pik();
        lcd.clear();
        stan = 10;
      } }
      

      if(stan == 9) {
      // wybór koloru
      for(int i = 0; i < 8; i++) {
      led.setPixelColor(i, led.Color(25 * R, 25 * G, 25 * B));
      led.show();   } 
    int klawisz = klawiatura.getKey();
      lcd.setCursor(0,0);
      lcd.print("kolor          +");
      lcd.setCursor(0,1);
      lcd.print(kolorPOKAZ);
      lcd.setCursor(15,1);
      lcd.print("-");
        if(klawisz == 'B'){
        pik();
        lcd.clear();  
        wylacz();  
        stan = 8;
      }
        if(klawisz == '+') {
        kolor++;
        if(kolor > 7){
          kolor = 1;
        }
         pik();
         lcd.clear();
        }
        if(klawisz == '-') {
        kolor--;
        if(kolor < 1) {
          kolor = 7;
        }
            pik();
            lcd.clear();
        }
if(kolor == 1) { //bialy
  R = 1;
  G = 1;
  B = 1;
  kolorPOKAZ = "bialy";}
if(kolor == 2) { //czerwony
  R = 1;
  G = 0;
  B = 0;
  kolorPOKAZ = "czerwony";}
if(kolor == 3) { //żółty
  R = 1;
  G = 1;
  B = 0;
  kolorPOKAZ = "zolty";}
if(kolor == 4) { //pomarańczowy
  R = 1;
  G = 0.5;
  B = 0;
  kolorPOKAZ = "pomaranczowy";}
if(kolor == 5) { //niebieski
  R = 0;
  G = 0;
  B = 1;
  kolorPOKAZ = "niebieski";}
if(kolor == 6) { //jasny niebieski
  R = 0;
  G = 1;
  B = 1;
  kolorPOKAZ = "jasny niebieski";}
if(kolor == 7) { //zielony
  R = 0;
  G = 1;
  B = 0;
  kolorPOKAZ = "zielony";}


      }
            
      if(stan == 10) {
        // < tryb pracy >
        lcd.setCursor(0,0);
        lcd.print("< tryb pracy >");
    int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
      ON = 1;}
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();}
    if (ON == 1){
      lampa(); }
      if(klawisz == 'A'){
         pik();
        lcd.clear();
         stan = 11; }
      if(klawisz == 'B'){
        pik();
        lcd.clear();
        stan = 1;}
      if(klawisz == '<') {
        pik();
        lcd.clear();
        stan = 8;
      }
      if(klawisz == '>') {
        pik();
        lcd.clear();
        stan = 12;
      } }

      if(stan == 11){ //wybór trybu pracy
     long czas1 = millis();
     if(czas1 - zapamietanyczas >= 500) {
      zapamietanyczas = czas1;
      lcd.clear();
     }
      lcd.setCursor(0,0);
      lcd.print("uruchom jesli");
      lcd.setCursor(0,1);
      lcd.print(trybPOKAZ);
          int klawisz = klawiatura.getKey();
        if(klawisz == 'B'){
        pik();
        lcd.clear();    
        stan = 10;
      }
        if(klawisz == '+') {
        trybPRACY++;
        if(trybPRACY > 2){
          trybPRACY = 1;
        }
         pik();
         lcd.clear();
        }
        if(klawisz == '-') {
        trybPRACY--;
        if(trybPRACY < 1) {
          trybPRACY = 2;
        }
            pik();
            lcd.clear();
        }
        if(trybPRACY == 1) {
        trybPOKAZ = "ruch";
        }
        if(trybPRACY == 2) {
        trybPOKAZ = "swiatlo";
        }
        if(trybPRACY == 3) {
        trybPOKAZ = "ruch i swiatlo";
        }
      }

      if(stan == 12) {
        // <poziom aktywacji>
        lcd.setCursor(0,0);
        lcd.print(" < poziom >");
        lcd.setCursor(0,1);
        lcd.print("aktywacji LED");
    int klawisz = klawiatura.getKey();
    if (klawisz == 'S') {
      pik();
      ON = 1;}
    if (klawisz == 'P') {
      pik();
      ON = 0;
      wylacz();}
    if (ON == 1){
      lampa(); }
      if(klawisz == 'A'){
         pik();
        lcd.clear();
         stan = 13; }
      if(klawisz == 'B'){
        pik();
        lcd.clear();
        stan = 1;}
      if(klawisz == '<') {
        pik();
        lcd.clear();
        stan = 10;
      }
      if(klawisz == '>') {
        pik();
        lcd.clear();
        stan = 2;
      } }

      if(stan == 13){ //wybór poziomu aktywacji LED
     long czas1 = millis();
     if(czas1 - zapamietanyczas >= 500) {
      zapamietanyczas = czas1;
      lcd.clear();
     }
      lcd.setCursor(0,0);
      lcd.print("kliknij A by");
      lcd.setCursor(0,1);
      lcd.print("ustawic");
      lcd.setCursor(8,1);
      lcd.print(analogRead(foto));
          int klawisz = klawiatura.getKey();
        if(klawisz == 'B'){
        pik();
        lcd.clear();    
        stan = 12;
      }
      if(klawisz == 'A'){
        pik();
        prog = analogRead(foto) + 50;
      }
      Serial.println(prog);
      }


    
}
void lampa() {
if(trybPRACY == 0){
  LEDwylacz = 1;
  swiec();
}
if(trybPRACY == 1 && digitalRead(PIR) == 1) {
  LEDwylacz = 1;
  swiec();
}
if(trybPRACY == 2 && analogRead(foto) < prog) {
  LEDwylacz = 0;
  trybLED = 1;
  swiec();
  delay(150);
}
if(trybPRACY == 3 && digitalRead(PIR) == 1 && analogRead(foto) == prog) {
  LEDwylacz = 1;
  swiec();
}
if(trybPRACY == 2 && analogRead(foto) > prog) {
  wylacz();
}
}
void pik() {
  digitalWrite(buzzer,1);
  delay(100);
  digitalWrite(buzzer,0);
}   


void swiec() {
  if (trybPRACY != 2) {
  pik();}
  if(trybLED == 1) {
    for(int i = 0; i < 8; i++) {
      led.setPixelColor(i, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      led.show();     
    }
    czas = czasCONST;
  }
    if(trybLED == 2) {
    for(int i = 0; i < 8; i++) {
      led.setPixelColor(i, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      delay(100);
      led.show();     
    }
    czas = czasCONST - 800;
  }
    if(trybLED == 3) {
    for(int i = 8; i >= 0; i--) {
      led.setPixelColor(i, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      delay(100);
      led.show();     
    }
    czas = czasCONST - 800;
  }
    if(trybLED == 4) {
    float intensityLevels[] = {0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.85, 1.0};

    for (int level = 0; level < 10; level++) {
    for (int i = 0; i < 8; i++) {
    int red = (int)(intensityLevels[level] * jasnosc * R);
    int green = (int)(intensityLevels[level] * jasnosc * G);
    int blue = (int)(intensityLevels[level] * jasnosc * B);
    led.setPixelColor(i, led.Color(red, green, blue));
  }
  led.show();
  delay(50);
}
czas = czasCONST - 500;
    }
    if(trybLED == 5) {
      led.setPixelColor(3, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      led.setPixelColor(4, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      delay(100);
      led.show();
      led.setPixelColor(2, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      led.setPixelColor(5, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      delay(100);
      led.show();
      led.setPixelColor(1, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      led.setPixelColor(6, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      delay(100);
      led.show();
      led.setPixelColor(0, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      led.setPixelColor(7, led.Color(jasnosc * R, jasnosc * G, jasnosc * B));
      delay(100);
      led.show();
      czas = czasCONST - 400;
    }

  if (trybPRACY == 1 || trybPRACY == 3){
  delay(czas); }
  if (trybPRACY == 0) {
    delay(1000);
  }
  if(LEDwylacz == 1){
  for(int i = 0; i < 8; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));
    led.show();
  }}
}

void wylacz() {
  for(int i = 0; i < 8; i++) {
    led.setPixelColor(i, led.Color(0, 0, 0));
    led.show();
  }
}
