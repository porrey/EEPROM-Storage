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

/**
 * @file EEPROM-Base.h
 * @brief This file contains the EEPROMBase<T> definition.
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

#include "EEPROM-Util.h"
#include "EEPROM-Checksum.h"

/**
 * @class EEPROMBase
 * @brief Base class to wrap an EEPROM variable.
 * @details This class contains the methods and properties to
 * allow reading and writing EEPROM, storing the location of 
 * the variable (address), calculating, storing and comparing 
 * the variable checksum, computing the next address for 
 * subsequent EEPROM variables, standard operator functionality,
 * and implicit conversion to the value type from the class instance.
 * @tparam T The type of the variable stored.
 */
template <typename T>
class EEPROMBase
{
  public:
    /**
     * @brief Initialize an instance of EEPROMBase<T> with the specified address.
     * @param address The address (or index) of the variable within EEPROM.
     */
    EEPROMBase(const uint address)
    {
      this->_address = this->normalizeAddress(address);
    }

    /**
     * @brief Initialize an instance of EEPROMBase with the specified address and default value.
     * @param address The address (or index) of the variable within EEPROM.
     * @tparam defaultValue The default value returned when the variable has not been initialized.
     */
    EEPROMBase(const uint address, T defaultValue) : EEPROMBase(address)
    {
      this->_defaultValue = defaultValue;
    }

    /**
     * @brief Implicitly converts the class instance to the value of type T. This 
     * allows the variable to be used on the right side of the equal sign.
     * @return The current value of the variable as type T.
     */
    operator T()
    {
      return this->get();
    }

    /**
     * @brief Treating the variable as a byte array, get the byte
     * at position index where index is between 0 and
     * length.
     * @param index The index position.
     * @return The byte at the specified index as a byte.
     */
    byte operator[] (const uint index)
    {
      uint address = this->normalizeAddress(this->getAddress() + index);
      return EEPROM[address];
    }

    /**
     * @brief Postfix increment operator.
     * @return The value before incrementing as type T.
     */
    T operator ++ (int)
    {
      T oldValue = this->get();
      this->set(oldValue + 1);
      return oldValue;
    }

    /**
     * @brief Prefix increment operator.
     * @return The value after incrementing as type T.
     */
    T operator ++ ()
    {
      return this->set(this->get() + 1);
    }

    /**
     * @brief Postfix decrement operator.
     * @return The value before decrementing as type T.
     */
    T operator -- (int)
    {
      T oldValue = this->get();
      this->set(this->get() - 1);
      return oldValue;
    }

    /**
     * @brief Postfix decrement operator.
     * @return The value before decrementing as type T.
     */
    T operator -- ()
    {
      return this->set(this->get() - 1);
    }

    /**
     * @brief Addition assignment operator.
     * @param value The value to add.
     * @return The result of the addition as type T.
     */
    T operator += (T const& value)
    {
      return this->set(this->get() + value);
    }

    /**
     * @brief Subtraction assignment operator.
     * @param value The value to subtract.
     * @return The result of the subtraction as type T.
     */
    T operator -= (T const& value)
    {
      return this->set(this->get() - value);
    }

    /**
     * @brief Multiplication assignment operator.
     * @tparam value The value to multiply by.
     * @return The result of the multiplication as type T.
     */
    T operator *= (T const& value)
    {
      return this->set(this->get() * value);
    }

    /**
     * @brief Division assignment operator.
     * @tparam value The value to divide by.
     * @return The result of the division as type T.
     */
    T operator /= (T const& value)
    {
      return this->set(this->get() / value);
    }

    /**
     * @brief Bitwise XOR assignment operator.
     * @tparam value The value to XOR with.
     * @return The result of the XOR operation as type T.
     */
    T operator ^= (T const& value)
    {
      return this->set(this->get() ^ value);
    }

    /**
     * @brief Modulus assignment operator.
     * @tparam value The value to mod with.
     * @return The result of the modulus operation as type T.
     */
    T operator %= (T const& value)
    {
      return this->set(this->get() % value);
    }

    /**
     * @brief Bitwise AND assignment operator.
     * @tparam value The value to AND with.
     * @return The result of the AND operation as type T.
     */
    T operator &= (T const& value)
    {
      return this->set(this->get() & value);
    }

    /**
     * @brief Bitwise OR assignment operator.
     * @tparam value The value to OR with.
     * @return The result of the OR operation as type T.
     */
    T operator |= (T const& value)
    {
      return this->set(this->get() | value);
    }

    /**
     * @brief Bitwise left shift assignment operator.
     * @tparam value The value to shift by.
     * @return The result of the left shift operation as type T.
     */
    T operator <<= (T const& value)
    {
      return this->set(this->get() << value);
    }

    /**
     * @brief Bitwise right shift assignment operator.
     * @tparam value The value to shift by.
     * @return The result of the right shift operation as type T.
     */
    T operator >>= (T const& value)
    {
      return this->set(this->get() >> value);
    }

    /**
     * @brief Get the variable value.
     * @return The current value of the variable as type T.
     */
    virtual T get() const
    {
      //
      // Use default initialization.
      //
      return T{};
    }

    /**
     * @brief Set the variable value.
     * @tparam value The new value to store in EEPROM.
     * @return The stored value as type T.
     */
    virtual T set(T const& value)
    {
      return value;
    }

    /**
     * @brief Read the variable value from the EEPROM using the address in this variable.
     * @return The value read from EEPROM as type T.
     */
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

    /**
     * @brief Write the value to the EEPROM using the address in this instance.
     * @tparam value The new value to store in EEPROM.
     */
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

    /**
     * @brief Checks whether the EEPROM variable has been initialized.
     * @details Determines if the variable has been initialized by comparing the stored checksum to the actual checksum of the bytes stored.
     * @return True if the EEPROM variable has been initialized, false otherwise.
     */
    bool isInitialized() const
    {
      return (this->checksum() == this->checksumByte());
    }

    /**
     * @brief Returns the number of EEPROM bytes used.
     * @details Returns the number of EEPROM bytes used by this instance including the checksum byte.
     * @return The number of bytes used in the EEPROM as an unsigned integer .
     */
    uint length() const
    {
      //
      // The extra byte is the checksum byte.
      //
      return this->size() + 1;
    }

    /**
     * @brief Returns the number of EEPROM bytes used by T.
     * @details Returns the number of EEPROM bytes used by this instance NOT including the 
     * checksum byte.
     * @return The number of bytes used by T in the EEPROM as n unsigned integer.
     */
    uint size() const
    {
      //
      // The extra byte is the checksum byte.
      //
      return sizeof(T);
    }

    /**
     * @brief Unset the variable.
     * @details Change the EEPROM values back to UNSET_VALUE as if the variable has never 
     * been written to the EEPROM. The isInitialized() method will return false. 
     */
    void unset(byte unsetValue = UNSET_VALUE)
    {
      for (uint i = 0; i < this->length(); i++)
      {
        uint address = this->normalizeAddress(this->_address + i);
        EEPROMUtil.updateEEPROM(address, unsetValue);
      }
    }

    /**
     * @brief Gets the address of the checksum byte in EEPROM for this variable.
     * @return The EEPROM address of the checksum as an unsigned integer.
     */
    uint checksumAddress() const
    {
      return this->normalizeAddress(this->_address + this->length() - 1);
    }

    /**
     * @brief Gets the stored checksum byte.
     * @return The checksum value read from EEPROM for this variable as a byte.
     */
    byte checksumByte() const
    {
      return EEPROM.read(this->checksumAddress());
    }

    /**
     * @brief Calculate the checksum of the data in the EEPROM for this instance.
     * @return The calculated checksum as a byte.
     */
    byte checksum() const
    {
      return Checksum<T>::getEEPROM(this->getAddress(), sizeof(T));
    }

    /**
     * @brief Copy the EEPROM bytes of this instance to a byte array.
     */
    void copyTo(byte* data, uint length) const
    {
      for (uint i = 0; i < length; i++)
      {
        uint address = this->normalizeAddress(this->_address + i);
        data[i] = EEPROM[address];
      }
    }

    /**
     * @brief Get the EEPROM address of the variable.
     * @return The memory address in EEPROM as an unsigned integer.
     */
    uint getAddress() const
    {
      return this->_address;
    }

    /**
     * @brief Gets the next EEPROM address after this variable.
     * @details This can be used to set the address of another EEPROM variable.
     * @return The next address in EEPROM as an unsigned integer.
     */
    uint nextAddress() const
    {
      return this->normalizeAddress(this->getAddress() + this->length());
    }

    /**
     * @brief Gets the default value for this instance.
     * @return The default value as type T.
     */
    T getDefaultValue() const
    {
      return this->_defaultValue;
    }

  protected:
    /**
     * @brief The address of this variable in the EEPROM.
     * @details This variable cannot/will not be modified after instantiation.
     */
    uint _address = 0;

   /**
     * @brief The default value.
     * @details The default value to return when the EEPROM has not 
     * been initialized. The address of this variable in the EEPROM. 
     * This variable cannot/will not be modified after instantiation.
     */
    T _defaultValue;

    /**
     * @brief Computes the checksum of the given value.
     * @tparam value The value to compute the checksum for.
     * @return The computed checksum as a byte.
     */
    byte computeChecksum(T value);
    
    /**
     * @brief Normalize the given EEPROM address to ensure it is within valid range.
     * @param address The address to normalize.
     * @return The normalized address as an unsigned integer.
     */
    uint normalizeAddress(uint address) const
    {
      return min(address, EEPROM.length() - 1);
    }
};
#endif