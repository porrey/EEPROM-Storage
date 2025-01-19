// Copyright © 2017-2025 Daniel Porrey. All Rights Reserved.
//
// This file is part of the EEPROM-Storage library.
//
// EEPROM-Storage library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EEPROM-Storage library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with EEPROM-Storage library. If not,
// see http://www.gnu.org/licenses/.
//
#pragma once
#ifndef EEPROM_UTIL_H
#define EEPROM_UTIL_H

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <EEPROM.h>
#elif defined(SPARK)
#include "Particle.h"
#endif

#include "EEPROM-Var.h"

class EEPROMUtilClass
{
  public:
    EEPROMUtilClass(HardwareSerial* serial)
    {
      this->setSerial(serial);
    }

    //
    // Print a byte value in HEX with leading 0x.
    //
    void displayPaddedHexByte(byte value, bool showPrefix = true)
    {
      if (showPrefix) this->getSerial()->print("0x");
      if (value <= 0x0F) this->getSerial()->print("0");
      this->getSerial()->print(value, HEX);
    }

    //
    // Resets the contents of EEPROM to UNSET_VALUE
    //
    void clearEEPROM(uint16_t value = UNSET_VALUE)
    {
      for (int i = 0; i < EEPROM.length(); i++)
      {
        EEPROM.update(i, value);
      }
    }

    //
    // Displays the contents of the EEPROM
    //
    void displayEEPROM(uint16_t width = 32)
    {
      this->getSerial()->println("EEPROM Contents:");

      //
      // Draw a line.
      //
      this->drawLine(width + 6);

      //
      // Display header addresses
      //
      this->getSerial()->print("     | ");
      for(int i = 0; i < width; i++)
      {
        this->display2Digits(i);
        this->getSerial()->print(" ");
      }
      this->getSerial()->println();

      //
      // Draw a line.
      //
      this->drawLine(width + 6);

      //
      // Get every byte from EEPROM
      //
      uint16_t lineNumber = 0;
      this->displayLineNumber(lineNumber);
      
      for (int i = 0; i < EEPROM.length(); i++)
      {
        //
        // Display the byt in HEX with the leading 0x.
        //
        displayPaddedHexByte(EEPROM[i], false);

        //
        // Add a space after the HEX.
        //
        this->getSerial()->print(" ");

        //
        // Start a new line when the width is encountered.
        //
        if ((i + 1) % width == 0)
        {
          lineNumber += width;

          if (lineNumber < EEPROM.length())
          {
            this->getSerial()->println();
            this->displayLineNumber(lineNumber);
          }
        }
      }
    }

    //
    // Get a pointer to serial device
    // being used by this instance.
    //
    HardwareSerial* getSerial()
    {
      return this->_serial;
    }

    //
    // Set a pointer to serial device
    // being used by this instance.
    //
    void setSerial(HardwareSerial* serial)
    {
      this->_serial = serial;
    }

    private:
      //
      // A pointer to a serial device. This instance
      // will write all output to this serial device.
      //
      HardwareSerial* _serial;

      //
      // Display a number of the serial port to use
      // two positions with the text aligned to the
      // right padded with spaces.
      //
      void display2Digits(uint16_t number)
      {
        if (number < 10)
        {
          this->getSerial()->print(" ");
        }

        this->getSerial()->print(number);
      }

      //
      // Display a number of the serial port to use
      // four positions with the text aligned to the
      // right padded with spaces.
      //
      void display4Digits(uint16_t number)
      {
        if (number < 10)
        {
          this->getSerial()->print("   ");
        }
        else if (number < 100)
        {
          this->getSerial()->print("  ");
        }
        else if (number < 1000)
        {
          this->getSerial()->print(" ");
        }

        this->getSerial()->print(number);
      }

      //
      // Dispays the line number down the 
      // left side of the grid.
      //
      void displayLineNumber(uint16_t lineNumber)
      {
        display4Digits(lineNumber);
        this->getSerial()->print(" | ");
      }

      //
      // Draw a line using dashes with the given width.
      //
      void drawLine(uint16_t width)
      {
        for(int i = 0; i < width; i++)
        {
          this->getSerial()->print("---");
        }
        this->getSerial()->println();
      }
};

//
// Create a static instance of EEPROMUtilClass.
//
static EEPROMUtilClass EEPROMUtil(&Serial);
#endif