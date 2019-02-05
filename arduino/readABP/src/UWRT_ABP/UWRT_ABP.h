/**
 * @file UWRT_ABP.h
 * @author Benji Justice (justice.251@osu.edu)
 * @brief Class definitions for SPI communications with Honeywell ABP Differential Pressure Sensors on Arduino.
 * 
 * @version 0.1
 * @date 2019-02-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef UWRT_ABP_h
#define UWRT_ABP_h

#include <Arduino.h>
#include <SPI.h>

namespace UWRT 
{
    #define P_MIN -1.0f             ///< Minimum pressure for the ABP sensor in psi
    #define P_B_SLOPE 0.00015259f   ///< Pressure (psi) per count
    #define O_MIN 1638              ///< Minimum output (counts)
    #define SPI_BAUD 800000         ///< Baudrate to use for SPI

    /**
     * @brief ABP Differential Pressure Sensor object.
     * 
     */
    class Abp
    {
        public:
            /**
             * @brief Construct a new ABP sensor object
             * 
             * @param pin SPI chip select pin number
             */
            Abp(int pin);

            /**
             * @brief Update the sensor's latest measurement
             * 
             */
            void update();

            /**
             * @brief Read the sensor's latest measurement
             * 
             * @return float The latest differential pressure reading (psi)
             */
            float read();

        private:
            int _cs; ///< SPI chip select pin
            byte _rsp[4]; ///<
    };

    /**
     * @brief Array of ABP objects.
     * 
     * This class contains functions useful for efficiently reading from multiple ABP sensors at a time.
     * 
     */
    class  AbpArray
    {
        public:
            /**
             * @brief Construct a new AbpArray object.
             * 
             * @param num The number of sensors
             * @param pins SPI chip select pin number for each sensor
             */
            AbpArray(int num, int* pins);

            /**
             * @brief Initialize the Arduino SPI hardware.
             * 
             */
            void init();

            /**
             * @brief Update each sensor's latest measurement.
             * 
             */
            void update();

            /**
             * @brief Read each sensors latest measurement.
             * 
             * Gives the report in the form of a comma delimitted string of values
             * of the form:
             * 
             * <timestamp>,<pressure_1>,<pressure_2>, . . ., <pressure_N>
             * 
             * @param buff Buffer to store the 
             */
            void report(char* buff);


        private:
            int _num; ///< Number of sensors in the array.
            unsigned long _stamp; ///< Timestamp (milliseconds) of the most recent update
            Abp** _sensors; ///< The array of ABP sensor objects
    };
}


#endif