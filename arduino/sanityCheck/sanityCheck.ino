#include <SPI.h>

#define P_DELTA 2.0f
#define P_MIN -1.0f
#define O_DELTA 13107
#define O_MIN 1638
#define NUM_SENSE 5

int sensor[] = {3,4,5,6,7};

byte raw[NUM_SENSE][4];
byte r[4];

void readABP(int pin, byte* buff)
{
  digitalWrite(pin, LOW);
  buff[0] = SPI.transfer(0x00);
  buff[1] = SPI.transfer(0x00);
  buff[2] = SPI.transfer(0x00);
  buff[3] = SPI.transfer(0x00);
  digitalWrite(pin, HIGH);
}

void debug(int num, byte* r)
{
  // 0 = new, normal
  // 1 = command mode, abnormal
  // 2 = stale data
  // 3 = diagnostic
  byte stat = r[0] >> 6;
  unsigned int output = ((r[0] & 0x3F) << 8) + r[1];

  float pressure = (((float)(output - O_MIN) * P_DELTA) / O_DELTA) + P_MIN;

  r[0] = 0x00;
  r[1] = 0x00;
  r[2] = 0x00;
  r[3] = 0x00;
  
  Serial.print("---");
  Serial.print(num);
  Serial.println("---");
  Serial.println(stat);
  Serial.println(pressure, 5);
}

void setup() {
  
 for (int i=0; i < NUM_SENSE; i++)
 {
  pinMode(sensor[i], OUTPUT);
  digitalWrite(sensor[i], HIGH);
 }

  Serial.begin(9600);

  // NEED THIS LINE!!!!
  SPI.begin();
  SPI.beginTransaction(SPISettings(800000, MSBFIRST, SPI_MODE0));
}

void loop() {
    for (int i = 0; i < NUM_SENSE; i++)
    {
      readABP(sensor[i], raw[i]);
      delay(1);
    }

    for (int i = 0; i < NUM_SENSE; i++)
    {
      debug(i, raw[i]);
    }
    
    
    delay(1000);
}
