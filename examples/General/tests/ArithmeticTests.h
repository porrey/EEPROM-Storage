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
#ifndef ARITHMETIC_TESTS_H
#define ARITHMETIC_TESTS_H

#if defined(TARGET_STORAGE)
  #define TARGET_LIBRARY EEPROMStorage<T>
#else
  #define TARGET_LIBRARY EEPROMCache<T>
#endif

#include "RunOnceTest.h"
#include "Assert.h"

template <typename T>
class InitializationTest : public RunOnceTest<T>
{
  public:
    InitializationTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      T initValue = random(this->_minValue, this->_maxValue);

      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      item = initValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      Serial.print("Value Initialized: ");
      this->_totalPassed += Assert.AreEqual(item, initValue);
      Serial.print(", Variable Is Initialized: ");
      this->_totalPassed += Assert.IsTrue(item.isInitialized());
    }
};

template <typename T>
class AdditionTest : public RunOnceTest<T>
{
  public:
    AdditionTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value = value + 5;
      item = item + 5;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class SubtractionTest : public RunOnceTest<T>
{
  public:
    SubtractionTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value = value - 5;
      item = item - 5;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class MultiplicationTest : public RunOnceTest<T>
{
  public:
    MultiplicationTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value = value * 2;
      item = item * 2;
      
      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class DivisionTest : public RunOnceTest<T>
{
  public:
    DivisionTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value = value / 2;
      item = item / 2;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class IncrementPostfixTest : public RunOnceTest<T>
{
  public:
    IncrementPostfixTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value++;
      item++;
      
      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class IncrementPrefixTest : public RunOnceTest<T>
{
  public:
    IncrementPrefixTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      T v1 = ++value;
      T v2 = ++item;
      
      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
      this->_totalPassed += Assert.AreEqual(v1, v2);
    }
};

template <typename T>
class DecrementPostfixTest : public RunOnceTest<T>
{
  public:
    DecrementPostfixTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value--;
      item--;
      
      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class DecrementPrefixTest : public RunOnceTest<T>
{
  public:
    DecrementPrefixTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      T v1 = --value;
      T v2 = --item;
      
      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
      this->_totalPassed += Assert.AreEqual(v1, v2);
    }
};

template <typename T>
class PlusEqualTest : public RunOnceTest<T>
{
  public:
    PlusEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value += 10;
      item += 10;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class MinusEqualTest : public RunOnceTest<T>
{
  public:
    MinusEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value -= 10;
      item -= 10;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class MultiplyEqualTest : public RunOnceTest<T>
{
  public:
    MultiplyEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value *= 10;
      item *= 10;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class DivideEqualTest : public RunOnceTest<T>
{
  public:
    DivideEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      value /= 10;
      item /= 10;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.AreEqual(item, value);
    }
};

template <typename T>
class GreaterThanValueTest : public RunOnceTest<T>
{
  public:
    GreaterThanValueTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue - 1;
      item = randomValue;
      
      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(item > value);
    }
};

template <typename T>
class GreaterThanVariableTest : public RunOnceTest<T>
{
  public:
    GreaterThanVariableTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue + 1;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(value > item);
    }
};

template <typename T>
class LessThanValueTest : public RunOnceTest<T>
{
  public:
    LessThanValueTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue + 1;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(item < value);
    }
};

template <typename T>
class LessThanVariableTest : public RunOnceTest<T>
{
  public:
    LessThanVariableTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 1; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue - 1;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(value < item);
    }
};

template <typename T>
class GreaterThanOrEqualToValueTest : public RunOnceTest<T>
{
  public:
    GreaterThanOrEqualToValueTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value1 = randomValue;
      item = randomValue;
      T value2 = value1 - 1;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(item >= value1);
      this->_totalPassed += Assert.IsTrue(item >= value2);
    }
};

template <typename T>
class GreaterThanOrEqualToVariableTest : public RunOnceTest<T>
{
  public:
    GreaterThanOrEqualToVariableTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value1 = randomValue;
      item = randomValue;
      T value2 = value1 + 1;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(value1 >= item);
      this->_totalPassed += Assert.IsTrue(value2 >= item);
    }
};

template <typename T>
class LessThanOrEqualToValueTest : public RunOnceTest<T>
{
  public:
    LessThanOrEqualToValueTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value1 = randomValue;
      item = randomValue;
      T value2 = value1 + 1;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(item <= value1);
      this->_totalPassed += Assert.IsTrue(item <= value2);
    }
};

template <typename T>
class LessThanOrEqualToVariableTest : public RunOnceTest<T>
{
  public:
    LessThanOrEqualToVariableTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value1 = randomValue;
      item = randomValue;
      T value2 = value1 - 1;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(value1 <= item);
      this->_totalPassed += Assert.IsTrue(value2 <= item);
    }
};

template <typename T>
class EqualityTest : public RunOnceTest<T>
{
  public:
    EqualityTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif

      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(value == item);
      this->_totalPassed += Assert.IsTrue(item == value);
    }
};

template <typename T>
class NotEqualityTest : public RunOnceTest<T>
{
  public:
    NotEqualityTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

    int totalTests() { return 2; }

    int onRunOnce()
    {
      //
      // Set the initial value.
      //
      TARGET_LIBRARY item(this->_address);
      T randomValue = random(this->_minValue, this->_maxValue);
      T value = randomValue + 10;
      item = randomValue;

      #if defined(TARGET_CACHE)
      item.commit();
      item.restore();
      #endif
      
      //
      // Assert
      //
      this->_totalPassed += Assert.IsTrue(value != item);
      this->_totalPassed += Assert.IsTrue(item != value);
    }
};
#endif