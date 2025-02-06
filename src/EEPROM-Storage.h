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
#ifndef EEPROM_STORAGE_H
#define EEPROM_STORAGE_H

/**
 * @file EEPROM-Storage.h
 * @brief This file contains the EEPROMStorage<T> definition.
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

/**
 * @class EEPROMStorage
 * @brief Provides direct access to an EEPROM variable.
 * @details This class provides direct access to an EEPROM variable
 * wrapped as type T. Accessing the value of the variable is done
 * directly from the EEPROM variable. Subsequently, writing the
 * variable value is done directly to the EEPROM memory.
 * @tparam T The type of the variable stored.
 */
template <typename T>
class EEPROMStorage : public EEPROMBase<T>
{
  public:
    /**
     * @brief Initialize an instance of EEPROMStorage<T> with the specified address.
     * @param address The address (or index) of the variable within EEPROM.
     */
    EEPROMStorage(const uint address) : EEPROMBase<T>(address)
    {
    }

    /**
     * @brief Initialize an instance of EEPROMBase with the specified address and default value.
     * @param address The address (or index) of the variable within EEPROM.
     * @tparam defaultValue The default value returned when the variable has not been initialized.
     */
    EEPROMStorage(const uint address, T defaultValue) : EEPROMBase<T>(address, defaultValue)
    {
    }

    /**
     * @brief Allows assignment of a variable of type T value to be 
     * this instance's value.
     * @details Accounts for EEPROMStorage<T> = T.
     * @tparam item The new value to store in EEPROM.
     * @return A reference to the EEPROMStorage<T> variable.
     */
    EEPROMStorage<T>& operator = (T const& value)
    {
      this->set(value);
      return *this;
    }

    /**
     * @brief Allows assignment of one EEPROMStorage<T> value to another.
     * @details Accounts for EEPROMStorage<T> = EEPROMStorage<T>.
     * @tparam item The new value to store in EEPROM.
     * @return A reference to the EEPROMStorage<T> variable.
     */
    EEPROMStorage<T>& operator = (EEPROMStorage<T> const& item)
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
      return this->read();
    }

    /**
     * @brief Set the variable value.
     * @tparam value The new value to store in EEPROM.
     * @return The stored value as type T.
     */
    T set(T const& value)
    {
      this->write(value);
      return this->get();
    }
};
#endif