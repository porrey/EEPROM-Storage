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
#include <Arduino_DebugUtils.h>

class EEPROMDisplayClass
{
  public:
    void begin()
    {
        Debug.timestampOff();
        Debug.debugLabelOff();
    }

    //
    // Print a byte value in HEX with leading 0x.
    //
    void displayPaddedHexByte(byte value, bool showPrefix = true)
    {
      if (showPrefix)
      {
        DEBUG_INFO("0x%2X ", value);
      }
      else
      {
        DEBUG_INFO("%2X ", value);
      }
    }

    //
    // Displays the contents of the EEPROM
    //
    void displayEEPROM(uint width = 32)
    {
      DEBUG_INFO("\r\nEEPROM Contents:");

      //
      // Draw a line.
      //
      this->drawLine(width + 2);

      //
      // Display header addresses
      //
      Debug.newlineOff();
      DEBUG_INFO("     | ");
      
      for(uint i = 0; i < width; i++)
      {
        DEBUG_INFO("%2u ", i);
      }

      Debug.newlineOn();
      DEBUG_INFO("");

      //
      // Draw a line.
      //
      this->drawLine(width + 2);

      //
      // Get every byte from EEPROM
      //
      Debug.newlineOff();
      uint lineNumber = 0;
      DEBUG_INFO("%4d | ", lineNumber);
      
      for (uint i = 0; i < EEPROM.length(); i++)
      {
        //
        // Display the value in HEX.
        //
        byte value = EEPROM[i];
        DEBUG_INFO("%.2X ", value);

        //
        // Start a new line when the width is encountered.
        //
        if ((i + 1) % width == 0)
        {
          lineNumber += width;

          if (lineNumber < EEPROM.length())
          {
            DEBUG_INFO("\r\n");
            DEBUG_INFO("%4d | ", lineNumber);
          }
        }
      }

      Debug.newlineOn();
      DEBUG_INFO("");
    }

    //
    // Display the properties of a variable.
    //
    template<typename T>
    void displayVariable(const char* name, EEPROMBase<T> value)
    {
      DEBUG_INFO("%s: Variable Size: %2d, Memory Length = %2d, Start Address = %2d, Checksum Address = %2d, Checksum Value = %2d, Initialized = %s",
                  name, value.size(), value.length(), value.getAddress(), value.checksumAddress(), value.checksumByte(), value.isInitialized() ? "Yes" : "No");
    }

    //
    // Display a header that can be used for listing variable properties.
    //
    void displayHeader()
    {
      //
      // Display the EEPROM properties.
      //
      DEBUG_INFO("\r\nEEPROM<T> Properties:");
      this->drawLine(50);
    }

    private:
      //
      // Draw a line using dashes with the given width.
      //
      void drawLine(uint width)
      {
        Debug.newlineOff();

        for(uint i = 0; i < width; i++)
        {
          DEBUG_INFO("---");
        }

        Debug.newlineOn();
        DEBUG_INFO("");
      }
};

//
// Create a static instance of EEPROMDisplayClass.
//
static EEPROMDisplayClass EEPROMDisplay;
#endif