#!/usr/bin/env python2.7

import serial
import time
import csv
import sys

def save(filename, data):
    with open(filename, 'wb') as file:
        file.write('Time(ms),Sensor ID,Status,Pressure(psi)\n')
        for row in data:
            file.write(row)

def main():
    COM_PORT = '/dev/ttyACM0'
    MAX_SAMPLES = 1000
    print("Let's do this. Give me a filename: ")
    FNAME = str(raw_input())
    print("Fantastic choice! I just love " + FNAME + "! Well, let's see if we can't find the Arduino...\n")
    FNAME = FNAME + ".csv"

    dataList = []
    ser = serial.Serial(COM_PORT, baudrate=19200, timeout=None)
    if ser is not None:
        print("Aha! I found it.");
        samples = 0
        while(samples < MAX_SAMPLES):
            data = ser.readline()
            print(data)
            samples += 1
            dataList.append(data)

        save(FNAME, dataList)
        sys.exit()

if __name__ == "__main__":
    main()
