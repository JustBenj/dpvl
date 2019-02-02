#include <SPI.h>
#include <UWRT_ABP.h>

#define NUM_SENSE 5

int sensor[] = {3, 4, 5, 6, 7};
unsigned long stamp;

byte raw[NUM_SENSE][4];
char reply[100];
char pstr[10];
bool started = false;

using namespace UWRT;

ABP sense(3);

void setup() {
 
  Serial.begin(19200);

  // NEED THIS LINE!!!!
  SPI.begin();
  SPI.beginTransaction(SPISettings(800000, MSBFIRST, SPI_MODE0));
  delay(500);
}

void loop() {
  int stat = sense.Update();
  char str[20];
  sense.ToString(str);

  Serial.println(str);
  delay(100);
}
