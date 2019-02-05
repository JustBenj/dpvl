#include "UWRT_ABP.h"

namespace UWRT
{
    Abp::Abp(int pin)
    {
        pinMode(pin, OUTPUT);
        _cs = pin;
    }

    void Abp::update()
    {
        digitalWrite(_cs, LOW);
        _rsp[0] = SPI.transfer(0x00);
        _rsp[1] = SPI.transfer(0x00);
        _rsp[2] = SPI.transfer(0x00);
        _rsp[3] = SPI.transfer(0x00);
        digitalWrite(_cs, HIGH);
    }

    float Abp::read()
    {
        unsigned int output = ((_rsp[0] & 0x3F) << 8) + _rsp[1];
        float t = ((float)(output - O_MIN) * P_B_SLOPE) + P_MIN;
        return t;
    }

    AbpArray::AbpArray(int num, int* pins)
    {
        _num = num;

        _sensors = new Abp*[_num];

        for (int i = 0; i < _num; i++)
        {
            _sensors[i] = new Abp(pins[i]);
        }
    }

    void AbpArray::init()
    {
        SPI.begin();
        SPI.beginTransaction(SPISettings(SPI_BAUD, MSBFIRST, SPI_MODE0));
    }

    void AbpArray::update()
    {
        _stamp = millis();
        
        for (int i = 0; i < _num; i++)
        {
            _sensors[i]->update();
        }
    }

    void AbpArray::report(char* buff)
    {
        char c[2] = ",";
        char str[100];
        ultoa(_stamp, str, 10);
        for (int i = 0; i < _num; i++)
        {
            strcat(str, c);
            char pstr[10];
            dtostrf(_sensors[i]->read(),4,5,pstr);
            strcat(str, pstr);
        }
    }
}
