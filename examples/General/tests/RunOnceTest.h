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
#ifndef RUN_ONCE_TEST_H
#define RUN_ONCE_TEST_H

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
  #include <EEPROM.h>
#elif defined(SPARK)
  #include <Particle.h>
#endif

#if defined(TARGET_STORAGE)
  #include <EEPROM-Storage.h>
#else
  #include <EEPROM-Cache.h>
#endif

template <typename T>
class RunOnceTest
{
  public:
    RunOnceTest(const char* name, uint address, T minValue, T maxValue)
    {
      //
      // Save the address and create the variable.
      //
      this->_address = address;

      //
      // Save the name.
      //
      this->_name = name;

      //
      // Save the min and max values.
      //
      this->_minValue = minValue;
      this->_maxValue = maxValue;
    }

    const char* name()
    {
      return this->_name;
    }

    //
    // Prepare to run the test.
    //
    virtual void setup()
    {
    }

    //
    // Run the test and return the number
    // of passed tests.
    //
    virtual int runOnce()
    {
      int returnValue = 0;

      Serial.print("TEST: "); Serial.print(this->_name); Serial.print(": ");
      this->setup();
      returnValue = this->onRunOnce();
      Serial.println();

      return returnValue;
    }

    virtual int onRunOnce()
    {
    }

    int totalPassed()
    {
      return this->_totalPassed;
    }

    virtual int totalTests();

  protected:
    uint _address;
    T _minValue;
    T _maxValue;
    uint _totalPassed = 0;
    const char* _name;
};
#endif