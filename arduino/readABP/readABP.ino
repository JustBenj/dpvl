#include <SPI.h>
#include "src/UWRT_ABP/UWRT_ABP.h"

using namespace UWRT;

int pins[] = {3, 4, 5, 6, 7};
AbpArray sensors(5, pins);

void setup() 
{
  Serial.begin(19200);
  sensors.init();
}

void loop() 
{
  sensors.update();

  char str[100];
  sensors.report(str);

  Serial.println(str);

  delay(500);
}
