
#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>
#include <SeeedTouchScreen.h>

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3 

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3 

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3 

#endif

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM);

int stage = 1;
int tweets = 0;
int evolutions = 0;
// int duration = millis();
int key = 0;
int petX = 100;
int petY = 0;
unsigned long previousMillis = 0;
const long interval = 500;

boolean CrimeA = false;
boolean RiskyA = false;
boolean UselessA = false;
boolean TrustA = false;
boolean SafeA = false;
boolean UsefulA = false;

boolean CrimeB = false;
boolean RiskyB = false;
boolean UselessB = false;
boolean TrustB = false;
boolean SafeB = false;
boolean UsefulB = false;

boolean evolveA = false;
boolean evolveAA = false;
boolean evolveB = false;
boolean evolveBB = false;

int tweetsCrime = 0;
int tweetsRisky = 0;
int tweetsUseless = 0;
int tweetsTrust = 0;
int tweetsSafe = 0;
int tweetsUseful = 0;


void setup(void)
{
  Serial.begin(9600);
  TFT_BL_ON;      // turn on the background light
  Tft.TFTinit();  // init TFT library

}

void loop(void)
{

  petSetup();

}




//------------------------------------------------
// -------------- Pet Set Up Stages --------------
//------------------------------------------------


void petSetup() {
  updateStage();
  if (stage == 1) { // Welcome Screen

    Tft.drawString("Welcome!", 20, 80, 3, WHITE);
    Tft.drawString("BitPet ver 1.0", 20, 140, 2, WHITE);
    Tft.drawString("Offline Mode", 20, 170, 2, WHITE);
    Tft.drawString("Tap to begin", 20, 230, 2, WHITE);

  }
  else if (stage == 2) { // Question 1
    Tft.drawString("Q1.", 10, 20, 3, WHITE);
    Tft.drawString("Feed your BitPet", 10, 70, 2, WHITE);
    Tft.drawString("with a word", 10, 100, 2, WHITE);
    Tft.drawString("a) Crime", 10, 150, 2, WHITE);
    Tft.drawString("b) Risky", 10, 210, 2, WHITE);
    Tft.drawString("c) Useless", 10, 270, 2, WHITE);
  }
  else if (stage == 3) {  // Question 2
    Tft.drawString("Q2.", 10, 20, 3, WHITE);
    Tft.drawString("Feed your BitPet", 10, 70, 2, WHITE);
    Tft.drawString("with another word", 10, 100, 2, WHITE);
    Tft.drawString("a) Trust", 10, 150, 2, WHITE);
    Tft.drawString("b) Safe", 10, 210, 2, WHITE);
    Tft.drawString("c) Useful", 10, 270, 2, WHITE);
  }
  else if (stage == 4) {  // Egg Hatching Animation
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(500);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(500);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(500);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(500);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(400);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(300);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(200);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
  }
  else if (stage == 5) { // Egg Hatched, Bitcoin Idle Mode
    Point p = ts.getPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    petIdle();
    Tft.drawString("i", 30, 285, 3, WHITE);
    Tft.drawString("t", 110, 285, 3, WHITE);
    Tft.drawString("?", 190, 285, 3, WHITE);
    Tft.drawHorizontalLine(0, 270, 240, WHITE);
    Tft.drawVerticalLine(70, 270, 100, WHITE);
    Tft.drawVerticalLine(160, 270, 100, WHITE);
    if (stage == 5) {
      if (p.z > __PRESURE) {
        if (p.y > 0 && p.y < 240 && p.x > 0 && p.x < 120) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          ++key;
          ++tweetsCrime;
          ++tweetsRisky;
          ++tweetsUseless;
        }
        else if (p.y > 0 && p.y < 240 && p.x > 120 && p.x < 240) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          --key;
          ++tweetsTrust;
          ++tweetsSafe;
          ++tweetsUseful;
        }
      }
    }
  }
  else if (stage == 6) { // Stats Screen
    Tft.drawString("Stats", 10, 20, 3, WHITE);
    Tft.drawString("Size", 10, 70, 2, WHITE);
    Tft.drawNumber(tweets, 10, 90, 2, WHITE);
    Tft.drawString("Evolutions", 10, 130, 2, WHITE);
    Tft.drawNumber(evolutions, 10, 150, 2, WHITE);
    Tft.drawString("Type", 10, 200, 2, WHITE);
    if (key > 0) {
      Tft.drawString("Unhealthy", 10, 220, 2, WHITE);
    }
    else if (key <= 0) {
      Tft.drawString("Healthy", 10, 220, 2, WHITE);
    }
  }
  else if (stage == 7) { // Tweets Screen
    Tft.drawString("Tweets", 10, 20, 3, WHITE);
    Tft.drawString("Tweets Fed", 10, 70, 2, WHITE);
    Tft.drawNumber(tweets, 10, 90, 2, WHITE);
    Tft.drawString("Tweets with", 10, 130, 2, WHITE);
    if (CrimeA == true) {
      Tft.drawString("'Crime'", 10, 150, 2, WHITE);
      Tft.drawNumber(tweetsCrime, 10, 170, 2, WHITE);
    }
    else if (RiskyA == true) {
      Tft.drawString("'Risky'", 10, 150, 2, WHITE);
      Tft.drawNumber(tweetsRisky, 10, 170, 2, WHITE);
    }
    else if (UselessA == true) {
      Tft.drawString("'Useless'", 10, 150, 2, WHITE);
      Tft.drawNumber(tweetsUseless, 10, 170, 2, WHITE);
    }
    Tft.drawString("Tweets with", 10, 210, 2, WHITE);
    if (TrustB == true) {
      Tft.drawString("'Trust'", 10, 230, 2, WHITE);
      Tft.drawNumber(tweetsTrust, 10, 250, 2, WHITE);
    }
    else if (SafeB == true) {
      Tft.drawString("'Safe'", 10, 230, 2, WHITE);
      Tft.drawNumber(tweetsSafe, 10, 250, 2, WHITE);
    }
    else if (UsefulB == true) {
      Tft.drawString("'Useful'", 10, 230, 2, WHITE);
      Tft.drawNumber(tweetsUseful, 10, 250, 2, WHITE);
    }
  }

  else if (stage == 8) {  // ? Screen

    Tft.drawString("Restart?", 10, 20, 3, WHITE);
    Tft.drawString("a) Yes", 10, 100, 2, WHITE);
    Tft.drawString("b) No", 10, 150, 2, WHITE);
  }

  else if (stage == 9) { // Evolution Animation 1
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(500);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(500);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(500);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(500);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(400);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(300);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(200);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
  }
  else if (stage == 10) { // Evolved BitPet Idle Mode

    Point p = ts.getPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    petIdleA();
    Tft.drawString("i", 30, 285, 3, WHITE);
    Tft.drawString("t", 110, 285, 3, WHITE);
    Tft.drawString("?", 190, 285, 3, WHITE);
    Tft.drawHorizontalLine(0, 270, 240, WHITE);
    Tft.drawVerticalLine(70, 270, 100, WHITE);
    Tft.drawVerticalLine(160, 270, 100, WHITE);
    if (stage == 10) {
      if (p.z > __PRESURE) {
        if (p.y > 0 && p.y < 240 && p.x > 0 && p.x < 120) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          ++key;
          ++tweetsCrime;
          ++tweetsRisky;
          ++tweetsUseless;
        }
        else if (p.y > 0 && p.y < 240 && p.x > 120 && p.x < 240) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          --key;
          ++tweetsTrust;
          ++tweetsSafe;
          ++tweetsUseful;
        }
      }
    }
  }

  else if (stage == 13) { // Evolved BitPet Idle Mode

    Point p = ts.getPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    petIdleB();
    Tft.drawString("i", 30, 285, 3, WHITE);
    Tft.drawString("t", 110, 285, 3, WHITE);
    Tft.drawString("?", 190, 285, 3, WHITE);
    Tft.drawHorizontalLine(0, 270, 240, WHITE);
    Tft.drawVerticalLine(70, 270, 100, WHITE);
    Tft.drawVerticalLine(160, 270, 100, WHITE);
    if (stage == 13) {
      if (p.z > __PRESURE) {
        if (p.y > 0 && p.y < 240 && p.x > 0 && p.x < 120) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          ++key;
          ++tweetsCrime;
          ++tweetsRisky;
          ++tweetsUseless;
        }
        else if (p.y > 0 && p.y < 240 && p.x > 120 && p.x < 240) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          --key;
          ++tweetsTrust;
          ++tweetsSafe;
          ++tweetsUseful;
        }
      }
    }
  }

  else if (stage == 11) { // Evolution Animation 2
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(500);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(500);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(500);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(500);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(400);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(300);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(200);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
    Tft.drawCircle(120, 170, 30, YELLOW);
    Tft.fillCircle(120, 170, 30, YELLOW);
    delay(100);
    Tft.drawCircle(120, 170, 30, WHITE);
    Tft.fillCircle(120, 170, 30, WHITE);
    delay(100);
  }
  else if (stage == 12) {

    Point p = ts.getPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    petIdleAA();
    Tft.drawString("i", 30, 285, 3, WHITE);
    Tft.drawString("t", 110, 285, 3, WHITE);
    Tft.drawString("?", 190, 285, 3, WHITE);
    Tft.drawHorizontalLine(0, 270, 240, WHITE);
    Tft.drawVerticalLine(70, 270, 100, WHITE);
    Tft.drawVerticalLine(160, 270, 100, WHITE);
    if (stage == 12) {
      if (p.z > __PRESURE) {
        if (p.y > 0 && p.y < 240 && p.x > 0 && p.x < 120) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          ++key;
          ++tweetsCrime;
          ++tweetsRisky;
          ++tweetsUseless;
        }
        else if (p.y > 0 && p.y < 240 && p.x > 120 && p.x < 240) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          --key;
          ++tweetsTrust;
          ++tweetsSafe;
          ++tweetsUseful;
        }
      }
    }
  }
  else if (stage == 14) {

    Point p = ts.getPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    petIdleBB();
    Tft.drawString("i", 30, 285, 3, WHITE);
    Tft.drawString("t", 110, 285, 3, WHITE);
    Tft.drawString("?", 190, 285, 3, WHITE);
    Tft.drawHorizontalLine(0, 270, 240, WHITE);
    Tft.drawVerticalLine(70, 270, 100, WHITE);
    Tft.drawVerticalLine(160, 270, 100, WHITE);
    if (stage == 14) {
      if (p.z > __PRESURE) {
        if (p.y > 0 && p.y < 240 && p.x > 0 && p.x < 120) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          ++key;
          ++tweetsCrime;
          ++tweetsRisky;
          ++tweetsUseless;
        }
        else if (p.y > 0 && p.y < 240 && p.x > 120 && p.x < 240) {
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, WHITE);
          delay(200);
          Tft.drawString("+1", 110, 80, 3, BLACK);
          delay(200);
          ++tweets;
          --key;
          ++tweetsTrust;
          ++tweetsSafe;
          ++tweetsUseful;
        }
      }
    }
  }
}



//----------------------------------------------------
// -------------- Update Stage Conditions ------------
//----------------------------------------------------


void updateStage() {
  Point p = ts.getPoint();

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

  if (stage == 1 && p.z > __PRESURE) { // Entering Q1
    Tft.drawRectangle(0, 0, 400, 400, BLACK);
    Tft.fillRectangle(0, 0, 400, 400, BLACK);
    delay(500);
    stage = 2;
  }
  else if (stage == 2) { // Entering Q2
    if (p.z > __PRESURE) {
      if (p.y > 150 && p.y < 170 && p.x > 10 && p.x < 80) { // Crime
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        delay(500);
        CrimeA = true;
        stage = 3;
      }
      else if (p.y > 210 && p.y < 230 && p.x > 10 && p.x < 80) { // Risky
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        delay(500);
        RiskyA = true;
        stage = 3;
      }
      else if (p.y > 280 && p.y < 300 && p.x > 10 && p.x < 80) { // Useless
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        delay(500);
        UselessA = true;
        stage = 3;
      }
    }
  }
  else if (stage == 3 && p.z > __PRESURE) { // Entering Hatching Animation
    if (p.z > __PRESURE) {
      if (p.y > 150 && p.y < 170 && p.x > 10 && p.x < 80) { // Trust
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        delay(500);
        TrustB = true;
        stage = 4;
      }
      else if (p.y > 210 && p.y < 230 && p.x > 10 && p.x < 80) { // Safe
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        delay(500);
        SafeB = true;
        stage = 4;
      }
      else if (p.y > 280 && p.y < 300 && p.x > 10 && p.x < 80) { // Useful
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        delay(500);
        UsefulB = true;
        stage = 4;
      }
    }
  }
  else if (stage == 4) {  // BitPet Idle Mode
    Tft.drawRectangle(0, 0, 400, 400, WHITE);
    Tft.fillRectangle(0, 0, 400, 400, WHITE);
    delay(3000);
    Tft.drawRectangle(0, 0, 400, 400, BLACK);
    Tft.fillRectangle(0, 0, 400, 400, BLACK);
    delay(500);
    stage = 5;
  }
  else if (stage == 5) { // Entering Menu Screens
    if (p.z > __PRESURE) {
      if (p.y > 270 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 6; // Stat Screen
      }
      else if (p.y > 270 && p.x > 70 && p.x < 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 7; // Tweet Screen
      }
      else if (p.y > 270 && p.x > 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 8; // ? Screen
      }
    }
    else if (stage == 5 && tweets == 5) { // Entering Evolution 1
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 9;
    }
  }
  else if (stage == 6) { // Returning to Idle Mode
    if (tweets < 5 && p.z > __PRESURE) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 5;
    }
    else if (tweets >= 5 && tweets < 10 && p.z > __PRESURE && evolveA == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 10;
    }
    else if (tweets >= 5 && tweets < 10 && p.z > __PRESURE && evolveB == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 13;
    }
    else if (tweets >= 10 && p.z > __PRESURE && evolveAA == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 12;
    }
    else if (tweets >= 10 && p.z > __PRESURE && evolveBB == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 14;
    }
  }
  else if (stage == 7) { // Returning to Idle Mode
    if (tweets < 5 && p.z > __PRESURE) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 5;
    }
    else if (tweets >= 5 && tweets < 10 && p.z > __PRESURE && evolveA == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 10;
    }
    else if (tweets >= 5 && tweets < 10 && p.z > __PRESURE && evolveB == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 13;
    }
    else if (tweets >= 10 && p.z > __PRESURE && evolveAA == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 12;
    }
    else if (tweets >= 10 && p.z > __PRESURE && evolveBB == true) {
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 14;
    }
  }
  else if (stage == 8) { // Returning to Idle Mode
    if (p.z > __PRESURE) {
      if (tweets < 5 && p.y < 180 && p.y > 150 && p.x > 10 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 5;
      }
      else if (tweets >= 5 && p.y < 180 && p.y > 150 && p.x > 10 && p.x < 70 && evolveA == true) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 10;
      }
      else if (tweets >= 5 && p.y < 180 && p.y > 150 && p.x > 10 && p.x < 70 && evolveB == true) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 13;
      }
      else if (tweets >= 10 && p.y < 180 && p.y > 150 && p.x > 10 && p.x < 70 && evolveAA == true) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 12;
      }
      else if (tweets >= 10 && p.y < 180 && p.y > 150 && p.x > 10 && p.x < 70 && evolveBB == true) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 14;
      }
      else if (p.y > 100 && p.y < 130 && p.x > 10 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        tweets = 0;
        evolutions = 0;
        key = 0;
        tweetsCrime = 0;
        tweetsRisky = 0;
        tweetsUseless = 0;
        tweetsTrust = 0;
        tweetsSafe = 0;
        tweetsUseful = 0;
        CrimeA = false;
        RiskyA = false;
        UselessA = false;
        TrustA = false;
        SafeA = false;
        UsefulA = false;
        CrimeB = false;
        RiskyB = false;
        UselessB = false;
        TrustB = false;
        SafeB = false;
        UsefulB = false;
        evolveA = false;
        evolveAA = false;
        evolveB = false;
        evolveBB = false;
        stage = 1; // Return to Beginning Screen
      }
    }
  }
  else if (stage == 9) { // Entering to Evolved Bitpet
    ++evolutions;
    Tft.drawRectangle(0, 0, 400, 400, WHITE);
    Tft.fillRectangle(0, 0, 400, 400, WHITE);
    delay(3000);
    Tft.drawRectangle(0, 0, 400, 400, BLACK);
    Tft.fillRectangle(0, 0, 400, 400, BLACK);
    delay(500);
    if (key <= 0) {
      evolveA = true;
      stage = 10;
    }
    else if (key > 0) {
      evolveB = true;
      stage = 13;
    }
  }
  else if (stage == 10) { // Entering Menu Screens from Evolved Idle Mode
    if (p.z > __PRESURE) {
      if (p.y > 270 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 6; // Stat Screen
      }
      else if (p.y > 270 && p.x > 70 && p.x < 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 7; // Tweet Screen
      }
      else if (p.y > 270 && p.x > 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 8; // ? Screen
      }
    }
    else if (stage == 10 && tweets == 10) { // Entering Evolution 2
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 11;
    }
  }
  else if (stage == 13) { // Entering Menu Screens from Evolved Idle Mode
    if (p.z > __PRESURE) {
      if (p.y > 270 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 6; // Stat Screen
      }
      else if (p.y > 270 && p.x > 70 && p.x < 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 7; // Tweet Screen
      }
      else if (p.y > 270 && p.x > 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 8; // ? Screen
      }
    }
    else if (stage == 13 && tweets == 10) { // Entering Evolution 2
      Tft.drawRectangle(0, 0, 400, 400, BLACK);
      Tft.fillRectangle(0, 0, 400, 400, BLACK);
      stage = 11;
    }
  }
  else if (stage == 11) { // Entering Mega Evolution BitPet
    ++evolutions;
    Tft.drawRectangle(0, 0, 400, 400, WHITE);
    Tft.fillRectangle(0, 0, 400, 400, WHITE);
    delay(3000);
    Tft.drawRectangle(0, 0, 400, 400, BLACK);
    Tft.fillRectangle(0, 0, 400, 400, BLACK);
    delay(500);
    if (key <= 0) {
      evolveAA = true;
      stage = 12;
    }
    else if (key > 0) {
      evolveBB = true;
      stage = 14;
    }
  }
  else if (stage == 12) { // Entering Menu Screens form Mega Evolved
    if (p.z > __PRESURE) {
      if (p.y > 270 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 6; // Stat Screen
      }
      else if (p.y > 270 && p.x > 70 && p.x < 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 7; // Tweet Screen
      }
      else if (p.y > 270 && p.x > 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 8; // ? Screen
      }
    }
  }
  else if (stage == 14) { // Entering Menu Screens form Mega Evolved
    if (p.z > __PRESURE) {
      if (p.y > 270 && p.x < 70) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 6; // Stat Screen
      }
      else if (p.y > 270 && p.x > 70 && p.x < 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 7; // Tweet Screen
      }
      else if (p.y > 270 && p.x > 160) {
        Tft.drawRectangle(0, 0, 400, 400, BLACK);
        Tft.fillRectangle(0, 0, 400, 400, BLACK);
        stage = 8; // ? Screen
      }
    }
  }
}



//---------------------------------------------
//-------------Pet Idle States-----------------
//---------------------------------------------


void petIdle() { //BitPet Idle Mode

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (petY == 0) {
      Tft.drawString("b", petX - 5, 170, 3, BLACK);
      Tft.drawString("b", petX, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 1) {
      Tft.drawString("b", petX, 170, 3, BLACK);
      Tft.drawString("b", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 2) {
      Tft.drawString("b", petX + 5, 170, 3, BLACK);
      Tft.drawString("b", petX + 10, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 3) {
      Tft.drawString("b", petX + 10, 170, 3, BLACK);
      Tft.drawString("b", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 4) {
      Tft.drawString("b", petX + 10, 170, 3, BLACK);
      Tft.drawString("b", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 5) {
      Tft.drawString("b", petX + 5, 170, 3, BLACK);
      Tft.drawString("b", petX, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 6) {
      Tft.drawString("b", petX, 170, 3, BLACK);
      Tft.drawString("b", petX - 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 7) {
      Tft.drawString("b", petX - 5, 170, 3, BLACK);
      Tft.drawString("b", petX - 10, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 8) {
      Tft.drawString("b", petX - 10, 170, 3, BLACK);
      Tft.drawString("b", petX - 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 9) {
      petY = 0;
    }
  }
}

void petIdleA() { // Evolved BitPet Idle Mode

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (petY == 0) {
      Tft.drawString("B", petX - 5, 170, 3, BLACK);
      Tft.drawString("B", petX, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 1) {
      Tft.drawString("B", petX, 170, 3, BLACK);
      Tft.drawString("B", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 2) {
      Tft.drawString("B", petX + 5, 170, 3, BLACK);
      Tft.drawString("B", petX + 10, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 3) {
      Tft.drawString("B", petX + 10, 170, 3, BLACK);
      Tft.drawString("B", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 4) {
      Tft.drawString("B", petX + 10, 170, 3, BLACK);
      Tft.drawString("B", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 5) {
      Tft.drawString("B", petX + 5, 170, 3, BLACK);
      Tft.drawString("B", petX, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 6) {
      Tft.drawString("B", petX, 170, 3, BLACK);
      Tft.drawString("B", petX - 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 7) {
      Tft.drawString("B", petX - 5, 170, 3, BLACK);
      Tft.drawString("B", petX - 10, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 8) {
      Tft.drawString("B", petX - 10, 170, 3, BLACK);
      Tft.drawString("B", petX - 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 9) {
      petY = 0;
    }
  }
}


void petIdleB() { // Evolved BitPet Idle Mode

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (petY == 0) {
      Tft.drawString("A", petX - 5, 170, 3, BLACK);
      Tft.drawString("A", petX, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 1) {
      Tft.drawString("A", petX, 170, 3, BLACK);
      Tft.drawString("A", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 2) {
      Tft.drawString("A", petX + 5, 170, 3, BLACK);
      Tft.drawString("A", petX + 10, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 3) {
      Tft.drawString("A", petX + 10, 170, 3, BLACK);
      Tft.drawString("A", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 4) {
      Tft.drawString("A", petX + 10, 170, 3, BLACK);
      Tft.drawString("A", petX + 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 5) {
      Tft.drawString("A", petX + 5, 170, 3, BLACK);
      Tft.drawString("A", petX, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 6) {
      Tft.drawString("A", petX, 170, 3, BLACK);
      Tft.drawString("A", petX - 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 7) {
      Tft.drawString("A", petX - 5, 170, 3, BLACK);
      Tft.drawString("A", petX - 10, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 8) {
      Tft.drawString("A", petX - 10, 170, 3, BLACK);
      Tft.drawString("A", petX - 5, 170, 3, WHITE);
      ++petY;
    }
    else if (petY == 9) {
      petY = 0;
    }
  }
}


void petIdleAA() { // Evolved BitPet Idle Mode

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (petY == 0) {
      Tft.drawString("B", petX - 5, 170, 4, BLACK);
      Tft.drawString("B", petX, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 1) {
      Tft.drawString("B", petX, 170, 4, BLACK);
      Tft.drawString("B", petX + 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 2) {
      Tft.drawString("B", petX + 5, 170, 4, BLACK);
      Tft.drawString("B", petX + 10, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 3) {
      Tft.drawString("B", petX + 10, 170, 4, BLACK);
      Tft.drawString("B", petX + 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 4) {
      Tft.drawString("B", petX + 10, 170, 4, BLACK);
      Tft.drawString("B", petX + 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 5) {
      Tft.drawString("B", petX + 5, 170, 4, BLACK);
      Tft.drawString("B", petX, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 6) {
      Tft.drawString("B", petX, 170, 4, BLACK);
      Tft.drawString("B", petX - 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 7) {
      Tft.drawString("B", petX - 5, 170, 4, BLACK);
      Tft.drawString("B", petX - 10, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 8) {
      Tft.drawString("B", petX - 10, 170, 4, BLACK);
      Tft.drawString("B", petX - 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 9) {
      petY = 0;
    }
  }
}

void petIdleBB() { // Evolved BitPet Idle Mode

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (petY == 0) {
      Tft.drawString("A", petX - 5, 170, 4, BLACK);
      Tft.drawString("A", petX, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 1) {
      Tft.drawString("A", petX, 170, 4, BLACK);
      Tft.drawString("A", petX + 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 2) {
      Tft.drawString("A", petX + 5, 170, 4, BLACK);
      Tft.drawString("A", petX + 10, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 3) {
      Tft.drawString("A", petX + 10, 170, 4, BLACK);
      Tft.drawString("A", petX + 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 4) {
      Tft.drawString("A", petX + 10, 170, 4, BLACK);
      Tft.drawString("A", petX + 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 5) {
      Tft.drawString("A", petX + 5, 170, 4, BLACK);
      Tft.drawString("A", petX, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 6) {
      Tft.drawString("A", petX, 170, 4, BLACK);
      Tft.drawString("A", petX - 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 7) {
      Tft.drawString("A", petX - 5, 170, 4, BLACK);
      Tft.drawString("A", petX - 10, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 8) {
      Tft.drawString("A", petX - 10, 170, 4, BLACK);
      Tft.drawString("A", petX - 5, 170, 4, WHITE);
      ++petY;
    }
    else if (petY == 9) {
      petY = 0;
    }
  }
}



