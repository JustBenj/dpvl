#ifndef UWRT_ABP_h
#define UWRT_ABP_h

#include <Arduino.h>
#include <SPI.h>

#define P_MIN -1.0f             // Minimum pressure for the ABP sensor in PSI
#define P_B_SLOPE 0.00015259f   // Pressure (PSI) per count
#define O_MIN 1638              // Minimum output (counts)

namespace UWRT 
{
    class ABP
    {
        public:
            ABP(int pin);
            int Update();
            void ToString(char* buff);

        private:
            int _cs;
            byte _rsp[4];
    };

    class  ABParray
    {
        public:
            ABParray(int num, int* pins);
            int update();


        private:
            int _num;
            ABP* _sensors;
    };
}


#endif