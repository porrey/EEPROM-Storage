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
#ifndef EEPROM_CACHE_H
#define EEPROM_CACHE_H

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <EEPROM.h>
#elif defined(SPARK)
#include "Particle.h"
#endif

#include "EEPROM-Base.h"

//
// Generic class to wrap a cached EEPROM variable. The variable
// is stored in memory and is only written to the EEPROM when
// commit() is called.
//
template <typename T>
class EEPROMCache : public EEPROMBase<T>
{
  public:
    //
    // Initialize an instance of EEPROMCache<T> with the specified address.
    //
    EEPROMCache(const uint address) : EEPROMBase<T>(address)
    {
    }

    //
    // Initialize an instance of EEPROMCache<T> with the specified address
    // and value.
    //
    EEPROMCache(const uint address, T value) : EEPROMCache(address, value)
    {
      this->_value = value;
    }

    //
    // Get the variable value from memory.
    //
    T get() const
    {
      return this->_value;
    }

    //
    // Save the variable value to memory.
    //
    void set(T const& value)
    {
      this->_value = value;
    }

    //
    // Write the value stored in memory to the EEPROM
    // using the address in this instance.
    //
    virtual void commit()
    {
      //
      // Set the value in EEPROM using the put method. 
      // Put uses EEPROM.update() to perform the write 
      // so it will not rewrite the value if it didn't 
      // change.
      //
      EEPROM.put(this->_address, this->_value);

      //
      // Write the checksum.
      //
      byte checksum = Checksum<T>::get(this->_value);
      EEPROMUtil.updateEEPROM(this->checksumAddress(), checksum);
    }

  protected:
    //
    // The cached value of the EEPROM variable.
    //
    T _value;
};
#endif