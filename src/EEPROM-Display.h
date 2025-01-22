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
#ifndef EEPROM_DISPLAY_H
#define EEPROM_DISPLAY_H

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

class EEPROMDisplayClass
{
  public:
    EEPROMDisplayClass(HardwareSerial* serial)
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
    // Displays the contents of the EEPROM
    //
    void displayEEPROM(uint width = 32)
    {
      this->getSerial()->println("EEPROM Contents:");

      //
      // Draw a line.
      //
      this->drawLine(width + 2);

      //
      // Display header addresses
      //
      this->getSerial()->print("     | ");
      
      for(uint i = 0; i < width; i++)
      {
        this->display2Digits(i);
        this->getSerial()->print(" ");
      }

      this->getSerial()->println();

      //
      // Draw a line.
      //
      this->drawLine(width + 2);

      //
      // Get every byte from EEPROM
      //
      uint lineNumber = 0;
      this->displayLineNumber(lineNumber);
      
      for (uint i = 0; i < EEPROM.length(); i++)
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

      this->getSerial()->println();
    }

    //
    //
    //
    template<typename T>
    void displayVariable(String name, EEPROMStorage<T> value)
    {
      this->getSerial()->print(name);
      this->getSerial()->print(": Variable Size: ");
      this->display2Digits(value.size());
      this->getSerial()->print(", Memory Length = ");
      this->display2Digits(value.length());
      this->getSerial()->print(", Start Address = ");
      this->display2Digits(value.getAddress());
      this->getSerial()->print(", Checksum Address = ");
      this->display2Digits(value.checksumAddress());
      this->getSerial()->print(", Checksum Value = ");
      this->displayPaddedHexByte(value.checksumByte());
      this->getSerial()->print(", Initialized = ");
      this->getSerial()->print(value.isInitialized() ? "Yes" : "No");
      this->getSerial()->println();
    }

    void displayHeader()
    {
      //
      // Display the EEPROM properties.
      //
      this->getSerial()->println();
      this->getSerial()->println("EEPROM<T> Properties:");
      this->drawLine(50);
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
      void display2Digits(uint number)
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
      void display4Digits(uint number)
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
      void displayLineNumber(uint lineNumber)
      {
        display4Digits(lineNumber);
        this->getSerial()->print(" | ");
      }

      //
      // Draw a line using dashes with the given width.
      //
      void drawLine(uint width)
      {
        for(uint i = 0; i < width; i++)
        {
          this->getSerial()->print("---");
        }
        this->getSerial()->println();
      }
};

//
// Create a static instance of EEPROMUtilClass.
//
static EEPROMDisplayClass EEPROMDisplay(&Serial);
#endif