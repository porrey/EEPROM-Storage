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
    void displayEEPROM()
    {
      this->getSerial()->println("EEPROM Contents:");
      
      //
      // Get every byte from EEPROM
      //
      for (int i = 0; i < EEPROM.length(); i++)
      {
        displayPaddedHexByte(EEPROM[i], false);
        this->getSerial()->print(" ");

        //
        // Start a new line
        //
        if ((i + 1) % 32 == 0)
        {
          this->getSerial()->println();
        }
      }
    }

    HardwareSerial* getSerial()
    {
      return this->_serial;
    }

    void setSerial(HardwareSerial* serial)
    {
      this->_serial = serial;
    }

    private:
      HardwareSerial* _serial;
};

static EEPROMUtilClass EEPROMUtil(&Serial);
#endif