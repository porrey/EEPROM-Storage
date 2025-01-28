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
// Define a Serial port to used 
// for displaying output.
//
#ifndef DEBUG
  #if defined(ARDUINO) && ARDUINO >= 100
    #define DEBUG Serial
  #elif defined(SPARK)
    #define DEBUG USBSerial
  #endif
#endif

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <EEPROM.h>
#elif defined(SPARK)
  #include <Particle.h>
#endif

#include "EEPROM-Base.h"
#include "EEPROM-Vars.h"

class EEPROMDisplayClass
{
  public:
    //
    // Print a byte value in HEX with leading 0x.
    //
    void displayPaddedHexByte(byte value, bool showPrefix = true)
    {
      if (showPrefix) Serial.print("0x");
      if (value <= 0x0F) Serial.print("0");
      Serial.print(value, HEX);
    }

    //
    // Displays the contents of the EEPROM
    //
    void displayEEPROM(uint width = 32)
    {
      Serial.println("EEPROM Contents:");

      //
      // Draw a line.
      //
      this->drawLine(width + 2);

      //
      // Display header addresses
      //
      Serial.print("     | ");
      
      for(uint i = 0; i < width; i++)
      {
        this->display2Digits(i);
        Serial.print(" ");
      }

      Serial.println();

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
        Serial.print(" ");

        //
        // Start a new line when the width is encountered.
        //
        if ((i + 1) % width == 0)
        {
          lineNumber += width;

          if (lineNumber < EEPROM.length())
          {
            Serial.println();
            this->displayLineNumber(lineNumber);
          }
        }
      }

      Serial.println();
    }

    //
    // Display the properties of a variable.
    //
    template<typename T>
    void displayVariable(String name, EEPROMBase<T> value)
    {
      Serial.print(name);
      Serial.print(": Variable Size: ");
      this->display2Digits(value.size());
      Serial.print(", Memory Length = ");
      this->display2Digits(value.length());
      Serial.print(", Start Address = ");
      this->display2Digits(value.getAddress());
      Serial.print(", Checksum Address = ");
      this->display2Digits(value.checksumAddress());
      Serial.print(", Checksum Value = ");
      this->displayPaddedHexByte(value.checksumByte());
      Serial.print(", Initialized = ");
      Serial.print(value.isInitialized() ? "Yes" : "No");
      Serial.println();
    }

    //
    // Display a header that can be used for listing variable properties.
    //
    void displayHeader()
    {
      //
      // Display the EEPROM properties.
      //
      Serial.println();
      Serial.println("EEPROM<T> Properties:");
      this->drawLine(50);
    }

    private:
      //
      // Display a number of the serial port to use two positions with
      // the text aligned to the right padded with spaces.
      //
      void display2Digits(uint number)
      {
        if (number < 10)
        {
          Serial.print(" ");
        }

        Serial.print(number);
      }

      //
      // Display a number of the serial port to use four positions with
      // the text aligned to the right padded with spaces.
      //
      void display4Digits(uint number)
      {
        if (number < 10)
        {
          Serial.print("   ");
        }
        else if (number < 100)
        {
          Serial.print("  ");
        }
        else if (number < 1000)
        {
          Serial.print(" ");
        }

        Serial.print(number);
      }

      //
      // Dispays the line number down the left side of the grid.
      //
      void displayLineNumber(uint lineNumber)
      {
        display4Digits(lineNumber);
        Serial.print(" | ");
      }

      //
      // Draw a line using dashes with the given width.
      //
      void drawLine(uint width)
      {
        for(uint i = 0; i < width; i++)
        {
          Serial.print("---");
        }
        Serial.println();
      }
};

//
// Create a static instance of EEPROMDisplayClass.
//
static EEPROMDisplayClass EEPROMDisplay;
#endif