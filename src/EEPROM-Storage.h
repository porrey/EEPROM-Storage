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

#include "EEPROM-Util.h"
#include "Checksum.h"

//
// Generic class to wrap an EEPROM variable.
//
template <typename T>
class EEPROMStorage
{
  public:
    //
    // Initialize an instance of EEPROM<T> with the specified address
    // and default value.
    //
    EEPROMStorage(const uint address, T defaultValue)
    {
      this->_address = this->normalizeAddress(address);
      this->_defaultValue = defaultValue;
    }

    //
    // Initialize an instance of EEPROM<T> with the specified address.
    //
    EEPROMStorage(const uint address)
    {
      this->_address = this->normalizeAddress(address);
    }

    //
    // Treating the variable as a byte array, get the byte
    // at position index where index is between 0 and
    // length.
    //
    byte operator[] (const uint index) const
    {
      uint address = this->normalizeAddress(this->getAddress() + index);
      return EEPROM[address];
    }

    //
    // Accounts for EEPROMStorage<T> = T
    //
    EEPROMStorage<T> operator = (T const& value) const
    {
      this->set(value);
      return *this;
    }

    //
    // Accounts for EEPROMStorage<T> = EEPROMStorage<T>
    //
    EEPROMStorage<T> operator = (EEPROMStorage<T> const& value) const
    {
      this->set(value);
      return *this;
    }

    //
    // Allows the variable to be used on the right side of
    // the equal sign.
    //
    operator T() const
    {
      return this->get();
    }

    //
    // ++ postfix
    //
    T operator ++ (int)
    {
      T oldValue = this->get();
      T newValue = oldValue + 1;
      this->set(newValue);
      return oldValue;
    }

    //
    // ++ prefix
    //
    T operator ++ ()
    {
      T newValue = this->get() + 1;
      this->set(newValue);
      return newValue;
    }

    //
    // -- postifx
    //
    T operator -- (int)
    {
      T oldValue = this->get();
      T newValue = oldValue - 1;
      this->set(newValue);
      return oldValue;
    }

    //
    // -- prefix
    //
    T operator -- ()
    {
      T newValue = this->get() - 1;
      this->set(newValue);
      return newValue;
    }

    //
    // += operator
    //
    T operator += (T const& value) const
    {
      T newValue = this->get() + value;
      this->set(newValue);
      return newValue;
    }

    //
    // -= operator
    //
    T operator -= (T const& value) const
    {
      T newValue = this->get() - value;
      this->set(newValue);
      return newValue;
    }

		//
    // *= operator
    //
    T operator *= (T const& value) const
    {
      T newValue = this->get() * value;
      this->set(newValue);
      return newValue;
    }

		//
    // /= operator
    //
    T operator /= (T const& value) const
    {
      T newValue = this->get() / value;
      this->set(newValue);
      return newValue;
    }

		//
    // %= operator
    //
    T operator %= (T const& value) const
    {
      T newValue = this->get() % value;
      this->set(newValue);
      return newValue;
    }

		//
    // &= operator
    //
    T operator &= (T const& value) const
    {
      T newValue = this->get() & value;
      this->set(newValue);
      return newValue;
    }

		//
	  // |= operator
	  //
	  T operator |= (T const& value) const
	  {
	    T newValue = this->get() | value;
	    this->set(newValue);
	    return newValue;
	  }

    //
    // Get the variable value from the EEPROM.
    //
    T get() const
    {
      T returnValue;

      //
      // Check if the variable has been set or not
      // by comparing the value to the not set value
      // specified in the constructor.
      //
      if (this->isInitialized())
      {
        //
        // Get the variable from EEPROM
        // using the address this->_address.
        //
        EEPROM.get(this->_address, returnValue);
      }
      else
      {
        //
        // Return the default value.
        //
        returnValue = this->_defaultValue;
      }

      return returnValue;
    }

    //
    // Save the variable value to the EEPROM.
    //
    void set(T const& value) const
    {
      //
      // Set the value in EEPROM using the put method. 
      // Put uses EEPROM.update() to perform the write, 
      // so it will not rewrite the value if it didn't 
      // change.
      //
      EEPROM.put(this->_address, value);

      //
      // Write the checksum.
      //
      byte checksum = Checksum<T>::get(value);
      EEPROMUtil.updateEEPROM(this->checksumAddress(), checksum);
    }

    //
    // Determines if the variable has been
    // initialized by comparing the
    // stored checksum to the actual checksum
    // of the bytes stored.
    //
    bool isInitialized() const
    {
      return (this->checksum() == this->checksumByte());
    }

    //
    // Returns the number of EEPROM bytes
    // used by this instance.
    //
    uint length() const
    {
      //
      // The extra byte is the checksum byte.
      //
      return this->size() + 1;
    }

    //
    // Returns the number of EEPROM bytes
    // used by T.
    //
    uint size() const
    {
      //
      // The extra byte is the checksum byte.
      //
      return sizeof(T);
    }

    //
    // Unset the variable (change the EEPROM values
    // back to UNSET_VALUE).
    //
    void unset(byte unsetValue = UNSET_VALUE) const
    {
      for (uint i = 0; i < this->length(); i++)
      {
        uint address = this->normalizeAddress(this->_address + i);
        EEPROMUtil.updateEEPROM(address, unsetValue);
      }
    }

    //
    // Gets the address of the checksum byte.
    //
    uint checksumAddress() const
    {
      return this->normalizeAddress(this->_address + this->length() - 1);
    }

    //
    // Gets the stored checksum byte.
    //
    uint checksumByte() const
    {
      return EEPROM.read(this->checksumAddress());
    }

    //
    // Calcuate the checksum of the
    // data in the EEPROM for this instance.
    //
    byte checksum() const
    {
      return Checksum<T>::getEEPROM(this->getAddress(), sizeof(T));
    }

    //
    // Copy the EEPROM bytes of this instance to
    // a byte array.
    //
    void copyTo(byte* data, uint length) const
    {
      for (uint i = 0; i < length; i++)
      {
        uint address = this->normalizeAddress(this->_address + i);
        data[i] = EEPROM[address];
      }
    }

    //
    // The the EEPROM address of the variable represented
    // in this instance.
    //
    uint getAddress() const
    {
      return this->_address;
    }

    //
    // Return the default value for this instance.
    //
    T getDefaultValue() const
    {
      return this->_defaultValue;
    }

    //
    // Get the next EEPROM address after this variable. This can be used to set the
    // address of another EEPROM variable.
    //
    uint nextAddress() const
    {
      return this->normalizeAddress(this->getAddress() + this->length());
    }

  private:
    //
    // The address of this variable in the EEPROM. This variable
    // cannot/will not be modified after the class is initialized.
    //
    uint _address = 0;

    //
    // The default value to return when the EEPROM has not been 
    // initialized.  This variable cannot/will not be modified 
    // after the class is initialized.
    //
    T _defaultValue;

    //
    // Don't allow an address to go beyond the end of the EEPROM space.
    //
    uint normalizeAddress(uint address) const
    {
      return min(address, EEPROM.length() - 1);

      /*
      uint returnValue = address;

      if (address < EEPROM.length())
      {
        this->_address = address;
      }
      else
      {
        this->_address = EEPROM.length() - 1;
      }

      return returnValue;
      */
    }
};
#endif