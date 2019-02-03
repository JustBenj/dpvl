#include "UWRT_ABP.h"

namespace UWRT
{
    ABP::ABP(int pin)
    {

        pinMode(pin, OUTPUT);
        _cs = pin;
    }

    void ABP::Update()
    {
        digitalWrite(_cs, LOW);
        _rsp[0] = SPI.transfer(0x00);
        _rsp[1] = SPI.transfer(0x00);
        _rsp[2] = SPI.transfer(0x00);
        _rsp[3] = SPI.transfer(0x00);
        digitalWrite(_cs, HIGH);

        unsigned int output = ((_rsp[0] & 0x3F) << 8) + _rsp[1];
        float t = ((float)(output - O_MIN) * P_B_SLOPE) + P_MIN;
        Serial.println(t, 5);
    }

    // void ABP::ToString(char* buff)
    // {
    //     //unsigned int stat = _rsp[0] >> 6;
    //     unsigned int output = ((_rsp[0] & 0x3F) << 8) + _rsp[1];
    //     float pressure = ((float)(output - O_MIN) * P_B_SLOPE) + P_MIN;
        
    //     char pstr[10];
    //     dtostrf(pressure, 4, 5, pstr);
    //     sprintf(buff, ",%s", pstr);
    // }

    float ABP::GetReading()
    {
        unsigned int output = ((_rsp[0] & 0x3F) << 8) + _rsp[1];
        float t = ((float)(output - O_MIN) * P_B_SLOPE) + P_MIN;
        return t;
    }

    ABParray::ABParray(int num, int* pins)
    {
        _num = num;

        for (int i = 0; i < _num; i++)
        {
            _sensors[i] = ABP(pins[i]);
        }
    }

    void ABParray::Init()
    {
        SPI.begin();
        SPI.beginTransaction(SPISettings(SPI_BAUD, MSBFIRST, SPI_MODE0));
    }

    void ABParray::Update()
    {
        _stamp = millis();

        for (int i = 0; i < _num; i++)
        {
            _sensors[i].Update();
        }
    }

    void ABParray::Report(char* buff)
    {
        sprintf(buff, "%lu", _stamp);
        

        char pstr[10];
        for (int i = 0; i < 1; i++)
        {
            dtostrf(_sensors[i].GetReading(), 4, 5, pstr);
            strcat(buff, ",");
            strcat(buff, pstr);
        }

       // Serial.println(buff);
    }
}
