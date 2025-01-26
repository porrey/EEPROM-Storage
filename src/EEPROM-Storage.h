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
// Generic class to wrap an EEPROM variable that reads and writes
// directly to and from the EEPROm storage.
//
template <typename T>
class EEPROMStorage : public EEPROMBase<T>
{
  public:
    //
    // Initialize an instance of EEPROMStorage<T> with the specified address.
    //
    EEPROMStorage(const uint address) : EEPROMBase<T>(address)
    {
    }

    //
    // Initialize an instance of EEPROMStorage<T> with the specified address
    // and default value.
    //
    EEPROMStorage(const uint address, T defaultValue) : EEPROMBase<T>(address, defaultValue)
    {
    }

    //
    // Accounts for EEPROMStorage<T> = T
    //
    EEPROMStorage<T> operator = (T const& value)
    {
      this->set(value);
      return *this;
    }

    //
    // Accounts for EEPROMStorage<T> = EEPROMStorage<T>
    //
    EEPROMStorage<T> operator = (EEPROMStorage<T> const& item)
    {
      this->set(item.get());
      return *this;
    }

    //
    // Get the variable value from the EEPROM.
    //
    T get() const
    {
      return this->read();
    }

    //
    // Save the variable value to the EEPROM.
    //
    T set(T const& value)
    {
      this->write(value);
      return this->get();
    }
};
#endif