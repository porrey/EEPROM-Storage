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

/**
 * @file EEPROM-Util.h
 * @brief This file contains the EEPROMUtilClass definition.
 */

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <EEPROM.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

#include "EEPROM-Vars.h"

/**
 * @class EEPROMUtilClass
 * @brief Provides the ability to clear the EEPROM memory.
 */
class EEPROMUtilClass
{
  public:
    /**
     * @brief Resets the contents of EEPROM to the value specified.
     * @details Writes the byte specified by the parameter value to every
     * memory location in EEPROM. If value is not specified then UNSET_VALUE
     * is used which is defined s 0xFF.
     * @param value The value to write to the EEPROM.
     * @return A reference to the EEPROMStorage<T> variable.
     */
    void clearEEPROM(uint value = UNSET_VALUE)
    {
      for (uint i = 0; i < EEPROM.length(); i++)
      {
        this->updateEEPROM(i, value);
      }
    }
    
    /**
     * @brief Provides a unified method od writing to the EEPROM
     * on multiple platforms.alignas
     * @details This method prefers usage of EEPROM.update() over
     * EEPROM.write() to reduce the number of writes to EEPROM memory.
     * @param address The address in EEPROM to write the value in.
     * @param value The value to write to the EEPROM.
     */
    void updateEEPROM(uint address, byte value)
    {
      if (address < EEPROM.length())
      {
        #if defined(ESP8266)
        EEPROM.write(address, value);
        #else
        EEPROM.update(address, value);
        #endif
      }
    }
};

/**
 * @brief Defines a static instance of EEPROMUtilClass.
 */
static EEPROMUtilClass EEPROMUtil;
#endif