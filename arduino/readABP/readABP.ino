#include <SPI.h>
#include "src/UWRT_ABP/UWRT_ABP.h"

#define NUM_SENSE 5

unsigned long stamp;

byte raw[NUM_SENSE][4];
char reply[100];
char pstr[10];
bool started = false;

using namespace UWRT;

int pins[] = {5};
ABParray* sense;

void setup() {
 
  Serial.begin(19200);

  sense = new ABParray(1, pins);

  sense->Init();
  unsigned long m = millis();
  Serial.println(m);

  delay(500);
}

void loop() {
  sense->Update();
  char str[100] = "";

  sense->Report(str);
  //Serial.println(str);

  delay(2000);
}
