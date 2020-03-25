// Copyright © 2017-2020 Daniel Porrey. All Rights Reserved.
//
// This file is part of the  library.
//
// EEPROM-Storage library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EEPROM-Storage library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with EEPROM-Storage library. If not,
// see http://www.gnu.org/licenses/.
//
#pragma once
#ifndef CHECKSUM_H
#define CHECKSUM_H

// ***
// *** Cross-compatable
// *** with Arduino, GNU C++ for tests, and Particle.
// ***
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(SPARK)
#include "Particle.h"
#endif

template <typename T>
class Checksum
{
  public:
    static uint8_t get(byte* data, uint32_t length)
    {
      uint8_t returnValue = 0;

      if (length == 1)
      {
        // ***
        // *** For a single byte use the bit
        // *** pattern 0xAA (10101010).
        // ***
        returnValue = 0xAA ^ data[0];
      }
      else
      {
        for (int i = 0; i < length ; i++)
        {
          byte b = data[i];
          returnValue ^= b;
        }
      }

      // ***
      // *** Do not let the checksum be 0xFF
      // ***
      if (returnValue == 0xFF)
      {
        returnValue <<= 1;
      }

      return returnValue;
    }

    static uint8_t get(T value)
    {
      // ***
      // *** Get a pointer to the bytes in memory
      // *** for the variable value.
      // ***
      uint8_t *ptr = (uint8_t*) &value;
      return Checksum<T>::get(ptr, sizeof(T));
    }
};
#endif
