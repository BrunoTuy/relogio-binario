#include <Arduino.h>
#include <MaxMatrix.h>
#include <CurieTime.h>

int data = 13;    // DIN pin of MAX7219 module
int load = 2;    // CS pin of MAX7219 module
int clock = 3;  // CLK pin of MAX7219 module

int maxInUse = 1;    //change this variable to set how many MAX7219's you'll use

MaxMatrix m(data, load, clock, maxInUse); // define module

int c = 0;
int sm[2][8] = {
  {B00111100, B01000010, B10100101, B10000001, B10100101, B10011001, B01000010, B00111100},
  {B00111100, B01000010, B10100101, B10000001, B10000001, B10111101, B01000010, B00111100}
};
int quadro[8] = {B11111111, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B11111111};
int h = 10;
int mm = 33;
int s = 00;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  m.init();

	m.setCommand(max7219_reg_displayTest, 0x01);
  delay(1000);
	m.setCommand(max7219_reg_displayTest, 0x00);
  delay(500);

  m.init();
  m.setIntensity(0);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    s++;

    if (s > 59) {
      s = 0;
      mm++;
    }

    if (mm > 59) {
      mm = 0;
      h++;
    }

    if (h > 23) {
      h = 0;
    }

    int set[8] = {B10000001, B10000000, B10000000, B10000001, B10000001, B10000000, B10000000, B10000001};
    set[1] += (s%10)*2*2;
    set[2] += (s/10%10)*2*2;
    set[3] += (mm%10)*2*2;
    set[4] += (mm/10%10)*2*2;
    set[5] += (h%10)*2*2;
    set[6] += (h/10%10)*2*2;

    for (int i=0; i<8; i++) {
      m.setColumn(i, set[i]);
    }

    previousMillis = currentMillis;
  }

	// for (int i=0; i<8; i++) {
		// m.setColumn(i, sm[c][i]);
  // }

  // delay(1000);
  // c++;

  // if (c > 1) {
    // c = 0;
  // }
}
