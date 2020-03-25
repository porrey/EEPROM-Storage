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
#ifndef EEPROM_STORAGE_H
#define EEPROM_STORAGE_H

#include "Checksum.h"

// ***
// *** Cross-compatable
// *** with Arduino, GNU C++ for tests, and Particle.
// ***
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <EEPROM.h>
#elif defined(SPARK)
#include "Particle.h"
#endif

// ***
// *** Maximum buffer size to use when transfering
// *** the EEPROM contents to a byte array.
// ***
#define MAX_VARIABLE_LENGTH 16

// ***
// *** Generic class to wrap an EEPROM variable.
// ***
template <typename T>
class EEPROMStorage
{
  public:
    EEPROMStorage(const uint16_t address, T defaultValue)
    {
      this->_address = address;
      this->_defaultValue = defaultValue;
    }

    // ***
    // *** Allows the variable to be used on the left side of
    // *** the equal sign.
    // ***
    T operator = (T const& value) const
    {
      this->set(value);
      return this->get();
    }

    // ***
    // *** Allows the variable to be used on the right side of
    // *** the equal sign.
    // ***
    operator T()
    {
      return this->get();
    }

    // ***
    // *** ++ postfix
    // ***
    T operator ++ (int)
    {
      T oldValue = this->get();
      T newValue = oldValue + 1;
      this->set(newValue);
      return oldValue;
    }

    // ***
    // *** ++ prefix
    // ***
    T operator ++ ()
    {
      T newValue = this->get() + 1;
      this->set(newValue);
      return newValue;
    }

    // ***
    // *** -- postifx
    // ***
    T operator -- (int)
    {
      T oldValue = this->get();
      T newValue = oldValue - 1;
      this->set(newValue);
      return oldValue;
    }

    // ***
    // *** -- prefix
    // ***
    T operator -- ()
    {
      T newValue = this->get() - 1;
      this->set(newValue);
      return newValue;
    }

    // ***
    // *** += operator
    // ***
    T operator += (T const& value) const
    {
      T newValue = this->get() + value;
      this->set(newValue);
      return newValue;
    }

    // ***
    // *** -= operator
    // ***
    T operator -= (T const& value) const
    {
      T newValue = this->get() - value;
      this->set(newValue);
      return newValue;
    }

		// ***
    // *** *= operator
    // ***
    T operator *= (T const& value) const
    {
      T newValue = this->get() * value;
      this->set(newValue);
      return newValue;
    }

		// ***
    // *** /= operator
    // ***
    T operator /= (T const& value) const
    {
      T newValue = this->get() / value;
      this->set(newValue);
      return newValue;
    }

		// ***
    // *** %= operator
    // ***
    T operator %= (T const& value) const
    {
      T newValue = this->get() % value;
      this->set(newValue);
      return newValue;
    }

		// ***
    // *** &= operator
    // ***
    T operator &= (T const& value) const
    {
      T newValue = this->get() & value;
      this->set(newValue);
      return newValue;
    }

		// ***
	  // *** |= operator
	  // ***
	  T operator |= (T const& value) const
	  {
	    T newValue = this->get() | value;
	    this->set(newValue);
	    return newValue;
	  }

    // ***
    // *** > operator
    // ***
    bool operator > (T const& value) const
    {
      return this->get() > value;
    }

    // ***
    // *** < operator
    // ***
    bool operator < (T const& value) const
    {
      return this->get() < value;
    }

    // ***
    // *** >= operator
    // ***
    bool operator >= (T const& value) const
    {
      return this->get() >= value;
    }

    // ***
    // *** <= operator
    // ***
    bool operator <= (T const& value) const
    {
      return this->get() <= value;
    }

    // ***
    // *** == operator
    // ***
    bool operator == (T const& value) const
    {
      return this->get() == value;
    }

    // ***
    // *** Get the value from EEPROM.
    // ***
    T get()
    {
      T returnValue;

      // ***
      // *** Check if the variable has been set or not
      // *** by comparing the value to the not set value
      // *** specified in the constructor.
      // ***
      if (this->isInitialized())
      {
        // ***
        // *** Get the variable from EEPROM
        // *** using the address this->_address.
        // ***
        EEPROM.get(this->_address, returnValue);
      }
      else
      {
        // ***
        // *** Return the default value specified in
        // *** the constructor.
        // ***
        returnValue = this->_defaultValue;
      }

      return returnValue;
    }

    // ***
    // *** Save the value to EEPROM.
    // ***
    void set(T const& value) const
    {
      // ***
      // *** Set the value in EEPROM using the
      // *** update method.
      // ***
      EEPROM.put(this->_address, value);

      // ***
      // *** Write the checksum.
      // ***
      uint8_t checksum = Checksum<T>::get(value);
      EEPROM.update(this->checksumAddress(), checksum);
    }

    // ***
    // *** Determines if the variable has been
    // *** initialized or not by comparing the
    // *** stored hecksum to the actual checksum
    // *** of the bytes stored.
    // ***
    bool isInitialized()
    {
      return (this->checksum() == this->checksumByte());
    }

    // ***
    // *** Returns the number of EEPROM bytes
    // *** used by this instance.
    // ***
    uint16_t length()
    {
      // ***
      // *** The extra byte is the checksum byte.
      // ***
      return sizeof(T) + 1;
    }

    // ***
    // *** Unset the variable (return the EEPROM values
    // *** back to 0xff).
    // ***
    void unset(byte unsetValue = 0xff)
    {
      for ( int i = 0; i < this->length(); i++)
      {
        EEPROM.update(this->_address + i, unsetValue);
      }
    }

    // ***
    // *** Gets the address of the checksum byte.
    // ***
    uint16_t checksumAddress()
    {
      return this->_address + this->length() - 1;
    }

    // ***
    // *** Gets the stored checksum byte.
    // ***
    uint16_t checksumByte()
    {
      return EEPROM.read(this->checksumAddress());
    }

    // ***
    // *** Calcuate the checksum of the
    // *** data in the EEPROM for this instance.
    // ***
    uint8_t checksum()
    {
      byte data[MAX_VARIABLE_LENGTH];
      this->copyTo(data, sizeof(T));
      return Checksum<T>::get(data, sizeof(T));
    }

    // ***
    // *** Copy the EEPROM bytes of this instance to
    // *** a byte array.
    // ***
    void copyTo(byte* data, uint32_t length)
    {
      for (int i = 0; i < length; i++)
      {
        data[i] = EEPROM[this->_address + i];
      }
    }

    uint16_t getAddress()
    {
      return this->_address;
    }

    T getDefaultValue()
    {
      return this->_defaultValue;
    }

  private:
    // ***
    // *** The address of this variable in the EEPROM.
    // ***
    uint16_t _address = 0;

    // ***
    // *** The default value to return when the EEPROM
    // *** has not been initialized.
    // ***
    T _defaultValue;
};
#endif
