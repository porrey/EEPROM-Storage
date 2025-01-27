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
#ifndef BINARY_TESTS_H
#define BINARY_TESTS_H

#if defined(TARGET_STORAGE)
  #define TARGET_LIBRARY EEPROMStorage<T>
#else
  #define TARGET_LIBRARY EEPROMCache<T>
#endif

#include "RunOnceTest.h"
#include "Assert.h"

template <typename T>
class ModuloTest : public RunOnceTest<T>
{
  public:
    ModuloTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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

      value = value % 6;
      item = item % 6;
      
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
class ModuloEqualTest : public RunOnceTest<T>
{
  public:
    ModuloEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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

      value %= 2;
      item %= 2;
      
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
class BitwiseAndEqualTest : public RunOnceTest<T>
{
  public:
    BitwiseAndEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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

      value &= 0xAAAA;
      item &= 0xAAAA;
      
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
class BitwiseAndTest : public RunOnceTest<T>
{
  public:
    BitwiseAndTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value = value & 0xAAAA;
      item = value & 0xAAAA;
      
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
class BitwiseOrEqualTest : public RunOnceTest<T>
{
  public:
    BitwiseOrEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value |= 0xAAAA;
      item |= 0xAAAA;
      
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
class BitwiseOrTest : public RunOnceTest<T>
{
  public:
    BitwiseOrTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value = value | 0xAAAA;
      item = item | 0xAAAA;
      
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
class BitwiseXorEqualTest : public RunOnceTest<T>
{
  public:
    BitwiseXorEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value ^= 0xAAAA;
      item ^= 0xAAAA;
      
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
class BitwiseXorTest : public RunOnceTest<T>
{
  public:
    BitwiseXorTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value = value ^ 0xAAAA;
      item = item ^ 0xAAAA;
      
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
class BitwiseNotTest : public RunOnceTest<T>
{
  public:
    BitwiseNotTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value = ~0xAAAA;
      item = ~0xAAAA;
      
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
class LeftShiftEqualTest : public RunOnceTest<T>
{
  public:
    LeftShiftEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value <<= 2;
      item <<= 2;
      

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
class LeftShiftTest : public RunOnceTest<T>
{
  public:
    LeftShiftTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value = value << 2;
      item = item << 2;
      

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
class RightShiftEqualTest : public RunOnceTest<T>
{
  public:
    RightShiftEqualTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value >>= 2;
      item >>= 2;
      
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
class RightShiftTest : public RunOnceTest<T>
{
  public:
    RightShiftTest(const char* name, uint address, T minValue, T maxValue) : RunOnceTest<T>(name, address, minValue, maxValue) {}

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
      
      value = value >> 2;
      item = item >> 2;
      
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
#endif