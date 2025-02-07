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

/**
 * @file EEPROM-Util.h
 * @brief This file contains the EEPROMDisplayClass definition.
 */

/**
 * @brief Define a Serial port to used for displaying output.
 */
#ifndef DEBUG
  #if defined(ARDUINO) && ARDUINO >= 100
    #define DEBUG Serial
  #elif defined(PARTICLE)
    #define DEBUG USBSerial
  #endif
#endif

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <EEPROM.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

#include "EEPROM-Base.h"
#include "EEPROM-Vars.h"
#include "EEPROM-Debug.h"

#define WIDTH 32
#define LINE_WIDTH (WIDTH * 3) + 8

/**
 * @class EEPROMDisplayClass
 * @brief Provides methods to display EEPROM data for debugging.
 * @details This class provides methods to display the contents
 * of EEPROM, the properties of an EEPROM variable and other 
 * useful option for debugging code related to using this library.
 */
class EEPROMDisplayClass
{
  public:
    /**
     * @brief Sets default behavior for the Arduino Debug Utils library.
     */
    void begin()
    {
        Debug.timestampOff();
        Debug.debugLabelOff();
    }

    /**
     * @brief Print a byte value in HEX with leading 0x.
     */
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

    /**
     * @brief Displays the contents of the EEPROM.
     */
    void displayEEPROM()
    {
      DEBUG_INFO("");
      DEBUG_INFO("EEPROM Contents:");

      //
      // Draw a line.
      //
      this->drawLine(WIDTH + 2);

      //
      // Create a buffer for a line of characters.
      //
      char buffer[LINE_WIDTH] = "     | ";
      
      //
      // Add string terminating character.
      //
      buffer[LINE_WIDTH - 1] = 0;

      //
      // Build the header address line.
      //
      for(uint i = 0; i < WIDTH; i++)
      {
        char b[3];
        sprintf(b, "%2u ", i);
        buffer[(i * 3) + 7] = b[0];
        buffer[(i * 3) + 8] = b[1];
        buffer[(i * 3) + 9] = b[2];
      }

      //
      // Display header addresses.
      //
      DEBUG_INFO("%s", buffer);

      //
      // Draw a line.
      //
      this->drawLine(WIDTH + 2);

      //
      // Get every byte from EEPROM
      //
      uint maxLines = EEPROM.length() / WIDTH;
      uint i = 0;

      for (uint row = 0; row < maxLines; row++)
      {
        uint lineNumber = row * WIDTH;
        sprintf(buffer, "%4d | ", lineNumber);

        for(uint j = 0; j < WIDTH; j++)
        {
          char b[3];
          sprintf(b, "%.2X ", (byte)EEPROM[i++]);
          buffer[(j * 3) + 7] = b[0];
          buffer[(j * 3) + 8] = b[1];
          buffer[(j * 3) + 9] = b[2];
        }

        DEBUG_INFO("%s", buffer);
      }
    }

    /**
     * @brief Display the properties of a variable.
     * @param name The name of the variable.
     * @tparam value The value of the variable.
     */
    template<typename T>
    void displayVariable(const char* name, EEPROMBase<T> value)
    {
      DEBUG_INFO("%s: Variable Size: %2d, Memory Length = %2d, Start Address = %2d, Checksum Address = %2d, Checksum Value = %2d, Initialized = %s",
                  name, value.size(), value.length(), value.getAddress(), value.checksumAddress(), value.checksumByte(), value.isInitialized() ? "Yes" : "No");
    }

    /**
     * @brief Display a header that can be used for listing variable properties.
     */
    void displayHeader()
    {
      //
      // Display the EEPROM properties.
      //
      DEBUG_INFO("");
      DEBUG_INFO("EEPROM<T> Properties:");
      this->drawLine(50);
    }

    private:
      //
      // Draw a line using dashes with the given width.
      //
      void drawLine(uint width)
      {
        //
        // Create a buffer for a line of characters.
        //
        char buffer[LINE_WIDTH];
        
        //
        // Add string terminating character.
        //
        buffer[LINE_WIDTH - 1] = 0;

        for(uint i = 0; i < LINE_WIDTH - 2; i++)
        {
          buffer[i] = '-';
        }

        DEBUG_INFO("%s", buffer);
      }
};

/**
 * @brief Defines a static instance of EEPROMDisplayClass.
 */
static EEPROMDisplayClass EEPROMDisplay;
#endif