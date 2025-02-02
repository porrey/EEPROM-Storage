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
#ifndef EEPROM_BASE_H
#define EEPROM_BASE_H

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <EEPROM.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

#include "EEPROM-Util.h"
#include "EEPROM-Checksum.h"

//
// Generic class to wrap an EEPROM variable.
//
template <typename T>
class EEPROMBase
{
  public:
    //
    // Initialize an instance of EEPROMBase<T> with the specified address.
    //
    EEPROMBase(const uint address)
    {
      this->_address = this->normalizeAddress(address);
    }

    //
    // Initialize an instance of EEPROMBase<T> with the specified address
    // and default value.
    //
    EEPROMBase(const uint address, T defaultValue) : EEPROMBase(address)
    {
      this->_defaultValue = defaultValue;
    }

    //
    // Allows the variable to be used on the right side of
    // the equal sign.
    //
    operator T()
    {
      return this->get();
    }

    //
    // Treating the variable as a byte array, get the byte
    // at position index where index is between 0 and
    // length.
    //
    byte operator[] (const uint index)
    {
      uint address = this->normalizeAddress(this->getAddress() + index);
      return EEPROM[address];
    }

    //
    // ++ postfix
    //
    T operator ++ (int)
    {
      T oldValue = this->get();
      this->set(oldValue + 1);
      return oldValue;
    }

    //
    // ++ prefix
    //
    T operator ++ ()
    {
      return this->set(this->get() + 1);
    }

    //
    // -- postifx
    //
    T operator -- (int)
    {
      T oldValue = this->get();
      this->set(this->get() - 1);
      return oldValue;
    }

    //
    // -- prefix
    //
    T operator -- ()
    {
      return this->set(this->get() - 1);
    }

    //
    // += operator
    //
    T operator += (T const& value)
    {
      return this->set(this->get() + value);
    }

    //
    // -= operator
    //
    T operator -= (T const& value)
    {
      return this->set(this->get() - value);
    }

    //
    // *= operator
    //
    T operator *= (T const& value)
    {
      return this->set(this->get() * value);
    }

    //
    // /= operator
    //
    T operator /= (T const& value)
    {
      return this->set(this->get() / value);
    }

    //
    // ^= operator (NEW)
    //
    T operator ^= (T const& value)
    {
      return this->set(this->get() ^ value);
    }

    //
    // %= operator
    //
    T operator %= (T const& value)
    {
      return this->set(this->get() % value);
    }

    //
    // &= operator
    //
    T operator &= (T const& value)
    {
      return this->set(this->get() & value);
    }

    //
    // |= operator
    //
    T operator |= (T const& value)
    {
      return this->set(this->get() | value);
    }

    //
    // <<= operator (NEW)
    //
    T operator <<= (T const& value)
    {
      return this->set(this->get() << value);
    }

    //
    // >>= operator (NEW)
    //
    T operator >>= (T const& value)
    {
      return this->set(this->get() >> value);
    }

    //
    // Get the variable value.
    //
    virtual T get() const
    {
      #if defined(PARTICLE) || defined(ESP8266)
      return (T)0;
      #endif
    }

    //
    // Save the variable value.
    //
    virtual T set(T const& value)
    {
      return value;
    }

    //
    // Read the variable value from the EEPROM
    // using the address in this instance.
    //
    T read() const
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
    // Write the value to the EEPROM
    // using the address in this instance.
    //
    void write(T const& value) const
    {
      //
      // Write the value to EEPROM using the put method. 
      // Put uses EEPROM.update() to perform the write 
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
    void unset(byte unsetValue = UNSET_VALUE)
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
    // Calculate the checksum of the
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
    // Get the next EEPROM address after this variable. This can be used to set the
    // address of another EEPROM variable.
    //
    uint nextAddress() const
    {
      return this->normalizeAddress(this->getAddress() + this->length());
    }

    //
    // Return the default value for this instance.
    //
    T getDefaultValue() const
    {
      return this->_defaultValue;
    }

  protected:
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
    }
};
#endif