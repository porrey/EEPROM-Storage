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
  #include <Arduino.h>
  #include <EEPROM.h>
#elif defined(PARTICLE)
  #include <Particle.h>
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
      //
      // Read the current value from EEPROM.
      //
      this->restore();
    }

    //
    // Initialize an instance of EEPROMCache<T> with the specified address
    // and value.
    //
    EEPROMCache(const uint address, T value) : EEPROMBase<T>(address, value)
    {
      this->_value = value;
    }
    
    //
    // Accounts for EEPROMCache<T> = T
    //
    EEPROMCache<T> operator = (T const& value)
    {
      this->set(value);
      return *this;
    }

    //
    // Accounts for EEPROMCache<T> = EEPROMCache<T>
    //
    EEPROMCache<T> operator = (EEPROMCache<T> const& item)
    {
      this->set(item.get());
      return *this;
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
    T set(T const& value)
    {
      this->_value = value;
      return this->_value;
    }

    //
    // Restores the value by reading from EEPROM.
    //
    T restore()
    {
      //
      // Read the current value from EEPROM.
      //
      this->_value = this->read();
      return this->_value;
    }

    //
    // Commit the cached value to the EEPROM.
    //
    T commit()
    {
      this->write(this->_value);
      return this->_value;
    }

  protected:
    //
    // The cached value of the EEPROM variable.
    //
    T _value;
};
#endif