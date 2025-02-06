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
#ifndef CHECKSUM_H
#define CHECKSUM_H

/**
 * @file EEPROM-Checksum.h
 * @brief This file contains the Checksum definition.
 */

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

/**
 * @class Checksum
 * @brief Provides checksum calculation options.
 * @details Computes a single-byte checksum on any data 
 * type or directly from an EEPROM address.
 * @tparam T The type of the variable against whose value 
 * the checksum will be calculated.
 */
template <typename T>
class Checksum
{
  public:
    /**
     * @brief Calculate the checksum of a byte array.
     * @details Calculate the checksum of the byte array specified by 
     * the data parameter whose number of bytes is specified by the 
     * length parameter.
     * @param data Points to the starting byte in the array.
     * @param length The length of the byte array.
     * @return The calculated checksum as a byte.
     */
    static byte get(byte* data, uint length)
    {
      byte returnValue = 0;

      if (length == 1)
      {
        //
        // For a single byte use the bit
        // pattern 0xAA (10101010).
        //
        returnValue = 0xAA ^ data[0];
      }
      else
      {
        for (uint i = 0; i < length ; i++)
        {
          byte b = data[i];
          returnValue ^= b;
        }
      }

      //
      // Do not let the checksum be UNSET_VALUE
      //
      if (returnValue == UNSET_VALUE)
      {
        returnValue <<= 1;
      }

      return returnValue;
    }

    /**
     * @brief Calculates the checksum from data in the EEPROM.
     * @details Calculate the checksum of the byte array in EEPROM
     * specified by the address parameter whose number of bytes 
     * is specified by the length parameter.
     * @param address The EEPROM address of the first byte of the array.
     * @param length The number of EEPROM bytes to read.
     * @return The calculated checksum as a byte.
     */
    static byte getEEPROM(uint address, uint length)
    {
      byte returnValue = 0;

      if (length == 1)
      {
        //
        // For a single byte use the bit
        // pattern 0xAA (10101010).
        //
        returnValue = 0xAA ^ EEPROM[address];
      }
      else
      {
        for (uint i = 0; i < length ; i++)
        {
          byte b = EEPROM[address + i];
          returnValue ^= b;
        }
      }

      //
      // Do not let the checksum be UNSET_VALUE
      //
      if (returnValue == UNSET_VALUE)
      {
        returnValue <<= 1;
      }

      return returnValue;
    }

    /**
     * @brief Calculates the checksum of the value of T.
     * @param value The value whose checksum will be calculated.
     * @return The calculated checksum as a byte.
     */
    static byte get(T value)
    {
      //
      // Get a pointer to the bytes in memory
      // for the variable value.
      //
      byte *ptr = (byte*) &value;

      //
      // Calculate and return the checksum.
      //
      return Checksum<T>::get(ptr, sizeof(T));
    }
};
#endif