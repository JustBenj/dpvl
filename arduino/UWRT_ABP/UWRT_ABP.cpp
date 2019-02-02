#include "UWRT_ABP.h"

namespace UWRT
{
    ABP::ABP(int pin)
    {

        pinMode(pin, OUTPUT);
        _cs = pin;
    }

    int ABP::Update()
    {
        digitalWrite(_cs, LOW);
        _rsp[0] = SPI.transfer(0x00);
        _rsp[1] = SPI.transfer(0x00);
        _rsp[2] = SPI.transfer(0x00);
        _rsp[3] = SPI.transfer(0x00);
        digitalWrite(_cs, HIGH);

        return _rsp[0] >> 6;
    }

    void ABP::ToString(char* buff)
    {
        //unsigned int stat = _rsp[0] >> 6;
        unsigned int output = ((_rsp[0] & 0x3F) << 8) + _rsp[1];
        float pressure = ((float)(output - O_MIN) * P_B_SLOPE) + P_MIN;
        
        char pstr[10];
        dtostrf(pressure, 4, 5, pstr);
        sprintf(buff, "%s", pstr);
    }
}
