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
    //
    // Resets the contents of EEPROM to UNSET_VALUE
    //
    void clearEEPROM(uint value = UNSET_VALUE)
    {
      for (uint i = 0; i < EEPROM.length(); i++)
      {
        this->updateEEPROM(i, value);
      }
    }
      
    void updateEEPROM(uint address, byte value)
    {
      #if defined(ESP8266)
      EEPROM.write(address, value);
      #else
      EEPROM.update(address, value);
      #endif
    }
};

//
// Create a static instance of EEPROMUtilClass.
//
static EEPROMUtilClass EEPROMUtil;
#endif