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

/**
 * @file EEPROM-Cache.h
 * @brief This file contains the EEPROMCache<T> definition.
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

#include "EEPROM-Base.h"

//
// Generic class to wrap a cached EEPROM variable. The variable
// is stored in memory and is only written to the EEPROM when
// commit() is called.
//

/**
 * @class EEPROMCache
 * @brief Provides indirect access to an EEPROM variable.
 * @details This class provides indirect access to an EEPROM variable
 * wrapped as type T. Accessing the value of the variable is done
 * through a cached value. Subsequently, writing the
 * variable value is done to the cached value. A call to restore()
 * is required to read the value from EEPROM while a call
 * to commit() is required to write the value to EEPROM. This version
 * will perform faster and have less ware on the delicate EEPROM memory.
 * @tparam T The type of the variable stored.
 */
template <typename T>
class EEPROMCache : public EEPROMBase<T>
{
  public:
    /**
     * @brief Initialize an instance of EEPROMCache<T> with the specified address.
     * @param address The address (or index) of the variable within EEPROM.
     */
    EEPROMCache(const uint address) : EEPROMBase<T>(address)
    {
      //
      // Read the current value from EEPROM.
      //
      this->restore();
    }

    /**
     * @brief Initialize an instance of EEPROMBase with the specified address and initial value.
     * @param address The address (or index) of the variable within EEPROM.
     * @tparam value The initial value of the variable before restore() is called.
     */
    EEPROMCache(const uint address, T value) : EEPROMBase<T>(address, value)
    {
      this->_value = value;
    }
    
    /**
     * @brief Allows assignment of a variable of type T value to be 
     * this instance's value.
     * @details Accounts for EEPROMCache<T> = T.
     * @tparam item The new value to store in EEPROM.
     * @return A reference to the EEPROMCache<T> variable.
     */
    EEPROMCache<T>& operator = (T const& value)
    {
      this->set(value);
      return *this;
    }

    /**
     * @brief Allows assignment of one EEPROMCache<T> value to another.
     * @details Accounts for EEPROMCache<T> = EEPROMCache<T>.
     * @tparam item The new value to store in EEPROM.
     * @return A reference to the EEPROMCache<T> variable.
     */
    EEPROMCache<T>& operator = (EEPROMCache<T> const& item)
    {
      this->set(item.get());
      return *this;
    }

    /**
     * @brief Get the variable value.
     * @return The current value of the variable as type T.
     */
    T get() const
    {
      return this->_value;
    }

    /**
     * @brief Set the variable value.
     * @tparam value The new value to store in EEPROM.
     * @return The stored value as type T.
     */
    T set(T const& value)
    {
      this->_value = value;
      return this->_value;
    }

    /**
     * @brief Restores the cached value by reading from EEPROM.
     * @return The value as type T.
     */
    T restore()
    {
      //
      // Read the current value from EEPROM.
      //
      this->_value = this->read();
      return this->_value;
    }

    /**
     * @brief Commit the cached value to the EEPROM.
     * @return The value as type T.
     */
    T commit()
    {
      this->write(this->_value);
      return this->_value;
    }

  protected:
    T _value; ///< The cached value of the EEPROM variable.
};
#endif