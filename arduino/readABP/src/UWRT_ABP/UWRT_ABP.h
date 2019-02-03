#ifndef UWRT_ABP_h
#define UWRT_ABP_h

#include <Arduino.h>
#include <SPI.h>

#define P_MIN -1.0f             // Minimum pressure for the ABP sensor in kPa
#define P_B_SLOPE 0.00015259f   // Pressure (kPa) per count
#define O_MIN 1638              // Minimum output (counts)
#define SPI_BAUD 800000         // Baudrate to use for SPI

namespace UWRT 
{
    class ABP
    {
        public:
            ABP(int pin);
            void Update();
            float GetReading();

        private:
            int _cs;
            byte _rsp[4];
    };

    class  ABParray
    {
        public:
            ABParray(int num, int* pins);
            void Init();
            void Update();
            void Report(char* buff);


        private:
            int _num;
            unsigned long _stamp;
            ABP* _sensors;
    };
}


#endif