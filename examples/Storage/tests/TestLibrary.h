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
#ifndef TEST_LIBRARY_H
#define TEST_LIBRARY_H

template <typename T>
class TestLibrary
{
  public:
    TestLibrary()
    {
        //
        // Initialize the random number generator.
        //
        randomSeed(analogRead(0));
    }
    
    void TestStandard(String typeName, uint address, T minRandomValue, T maxRandomValue)
    {
      //
      // Run tests on data type [double]
      //
      EEPROMStorage<T> var(address, 0);
    
      Serial.println("*********************************************");
      Serial.print("Running standard tests on ["); Serial.print(typeName); Serial.println("]");
      Serial.println("*********************************************");
    
      //
      // Run standard tests.
      //
      this->RunStandardTests(var, minRandomValue, maxRandomValue);
    
      Serial.println();
    }
    
    void TestAdvanced(String typeName, uint address, T minRandomValue, T maxRandomValue)
    {
      //
      // Run tests on data type [double]
      //
      EEPROMStorage<T> var(address, 0);
    
      Serial.println("*********************************************");
      Serial.print("Running advanced tests on ["); Serial.print(typeName); Serial.println("]");
      Serial.println("*********************************************");
    
      //
      // Run standard tests.
      //
      this->RunAdvancedTests(var, minRandomValue, maxRandomValue);
    
      Serial.println();
    }

    //
    // Results
    //
    uint totalTests = 0;
    uint totalPassed = 0;
        
  protected:
    void RunStandardTests(EEPROMStorage<T> item, T minRandomValue, T maxRandomValue)
    {
      //
      // Uninitialize test
      //
      this->DisplayTestHeader("Uninitialized");
      item.unset();
      this->totalPassed += this->AssertIsFalse(item.isInitialized());
      Serial.println();
    
      //
      // Initialize test
      //
      {
        this->DisplayTestHeader("Initialized Value");
        T initValue = random(minRandomValue, maxRandomValue);
        item = initValue;
        this->totalPassed += this->AssertAreEqual(item, initValue);
        Serial.println();
    
        this->DisplayTestHeader("Is Initialized");
        this->totalPassed += this->AssertIsTrue(item.isInitialized());
        Serial.println();
      }
    
      //
      // Addition test
      //
      {
        this->DisplayTestHeader("Addition");
        T value = item;
        value = value + 5;
        item = item + 5;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Subtraction test
      //
      {
        this->DisplayTestHeader("Subtraction");
        T value = 10;
        item = 10;
        value = value - 5;
        item = item - 5;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Multiplication test
      //
      {
        this->DisplayTestHeader("Multiplication");
        T value = 10;
        item = 10;
        value = value * 5;
        item = item * 5;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Division test
      //
      {
        this->DisplayTestHeader("Multiplication");
        T value = 10;
        item = 10;
        value = value / 5;
        item = item / 5;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // ++ postfix test
      //
      {
        this->DisplayTestHeader("++ postfix");
        T value = 60;
        item = 60;
        value++;
        item++;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // -- postfix test
      //
      {
        this->DisplayTestHeader("-- postfix");
        T value = 60;
        item = 60;
        value--;
        item--;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // ++ prefix test
      //
      {
        this->DisplayTestHeader("++ prefix");
        T value = 60;
        item = 60;
        ++value;
        ++item;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // -- postfix test
      //
      {
        this->DisplayTestHeader("-- prefix");
        T value = 60;
        item = 60;
        --value;
        --item;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // += test
      //
      {
        this->DisplayTestHeader("+=");
        T value = 60;
        item = 60;
        value += 10;
        item += 10;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // -= test
      //
      {
        this->DisplayTestHeader("-=");
        T value = 60;
        item = 60;
        value -= 10;
        item -= 10;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // *= test
      //
      {
        this->DisplayTestHeader("*=");
        T value = 60;
        item = 60;
        value *= 10;
        item *= 10;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // /= test
      //
      {
        this->DisplayTestHeader("/=");
        T value = 60;
        item = 60;
        value /= 30;
        item /= 30;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }

      //
      // > test
      //
      {
        this->DisplayTestHeader("> x");
        item = 100;
        this->totalPassed += this->AssertIsTrue(item > 1);
        Serial.println();
      }
    
      //
      // > test
      //
      {
        this->DisplayTestHeader("x >");
        item = 100;
        this->totalPassed += this->AssertIsTrue(101 > item);
        Serial.println();
      }
    
      //
      // < test
      //
      {
        this->DisplayTestHeader("< x");
        item = 100;
        this->totalPassed += this->AssertIsTrue(item < 101);
        Serial.println();
      }
    
      //
      // > test
      //
      {
        this->DisplayTestHeader("x <");
        item = 100;
        this->totalPassed += this->AssertIsTrue(1 < item);
        Serial.println();
      }
    
      //
      // >= test (different)
      //
      {
        this->DisplayTestHeader(">= x (different)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(item >= 1);
        Serial.println();
      }
    
      //
      // >= test (different)
      //
      {
        this->DisplayTestHeader("x >= (different)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(101 >= item);
        Serial.println();
      }
    
      //
      // <= test (different)
      //
      {
        this->DisplayTestHeader("<= x (different)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(item <= 101);
        Serial.println();
      }
    
      //
      // >= test (different)
      //
      {
        this->DisplayTestHeader("x <= (different)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(1 <= item);
        Serial.println();
      }
    
      //
      // >= test (same)
      //
      {
        this->DisplayTestHeader(">= x (same)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(item >= 100);
        Serial.println();
      }
    
      //
      // >= test (same)
      //
      {
        this->DisplayTestHeader("x >= (same)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(100 >= item);
        Serial.println();
      }
    
      //
      // <= test (same)
      //
      {
        this->DisplayTestHeader("<= x (same)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(item <= 100);
        Serial.println();
      }
    
      //
      // >= test (same)
      //
      {
        this->DisplayTestHeader("x <= (same)");
        item = 100;
        this->totalPassed += this->AssertIsTrue(100 <= item);
        Serial.println();
      }
    }
    
    void RunAdvancedTests(EEPROMStorage<T> item, T minRandomValue, T maxRandomValue)
    {
      //
      // Modulo test
      //
      {
        this->DisplayTestHeader("Modulo");
        T value = 10;
        item = 10;
        value = value % 6;
        item = item % 6;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // %= test
      //
      {
        this->DisplayTestHeader("%=");
        T value = 10;
        item = 10;
        value %= 6;
        item %= 6;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // &= test
      //
      {
        this->DisplayTestHeader("&=");
        T value = 129191;
        item = 129191;
        value &= 45234;
        item &= 45234;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // |= test
      //
      {
        this->DisplayTestHeader("|=");
        T value = 129191;
        item = 129191;
        value &= 45234;
        item &= 45234;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // == test
      //
      {
        this->DisplayTestHeader("==");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // != test
      //
      {
        this->DisplayTestHeader("!=");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value += 10;
        this->totalPassed += this->AssertAreNotEqual(item, value);
        Serial.println();
      }
    
      //
      // Bitwise AND (&)
      //
      {
        this->DisplayTestHeader("Bitwise AND (&)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value = value & 0xAAAA;
        item = item & 0xAAAA;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Bitwise OR (|)
      //
      {
        this->DisplayTestHeader("Bitwise OR (|)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value = value | 0xAAAA;
        item = item | 0xAAAA;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Bitwise XOR (^)
      //
      {
        this->DisplayTestHeader("Bitwise XOR (^)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value = value ^ 0xAAAA;
        item = item ^ 0xAAAA;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }

      //
      // Bitwise XOR (^=)
      //
      {
        this->DisplayTestHeader("Bitwise XOR (^=)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value ^= 0xAAAA;
        item ^= 0xAAAA;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Bitwise NOT (~)
      //
      {
        this->DisplayTestHeader("Bitwise NOT (~)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value = ~value;
        item = ~item;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Bitshift Left (<<)
      //
      {
        this->DisplayTestHeader("Bitshift Left (<<)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value = value << 2;
        item = item << 2;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }

      //
      // Bitshift Left (<<=)
      //
      {
        this->DisplayTestHeader("Bitshift Left (<<=)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value <<= 2;
        item <<= 2;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    
      //
      // Bitshift Right (>>)
      //
      {
        this->DisplayTestHeader("Bitshift Right (>>)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value = value >> 2;
        item = item >> 2;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }

      //
      // Bitshift Right (>>=)
      //
      {
        this->DisplayTestHeader("Bitshift Right (>>=)");
        T value = random(minRandomValue, maxRandomValue);
        item = value;
        value >>= 2;
        item >>= 2;
        this->totalPassed += this->AssertAreEqual(item, value);
        Serial.println();
      }
    }
    
    void DisplayTestHeader(String testName)
    {
      Serial.print("TEST: ["); Serial.print(testName); Serial.print("]");
      this->totalTests++;
    }
    
    bool AssertIsTrue(const bool item)
    {
      bool returnValue = false;
    
      if (item)
      {
        Serial.print(" -PASSED!");
        returnValue = true;
      }
      else
      {
        Serial.print(" -FAILED!");
      }
    
      return returnValue;
    }
    
    bool AssertIsFalse(const bool item)
    {
      bool returnValue = false;
    
      if (!item)
      {
        Serial.print(" -PASSED!");
        returnValue = true;
      }
      else
      {
        Serial.print(" -FAILED!");
      }
    
      return returnValue;
    }
    
    bool AssertAreEqual(EEPROMStorage<T> item1, T item2)
    {
      bool returnValue = false;
    
      if (item1.get() == item2)
      {
        Serial.print(" -PASSED!"); Serial.print("  ["); Serial.print(item1.get()); Serial.print(" == "); Serial.print(item2); Serial.print("]");
        returnValue = true;
      }
      else
      {
        Serial.print(" -FAILED!");
        Serial.print("  ["); Serial.print(item1.get()); Serial.print(" != "); Serial.print(item2); Serial.print("]");
      }
    
      return returnValue;
    }
    
    bool AssertAreNotEqual(EEPROMStorage<T> item1, T item2)
    {
      bool returnValue = false;
    
      if (item1.get() != item2)
      {
        Serial.print(" -PASSED!"); Serial.print("  ["); Serial.print(item1.get()); Serial.print(" != "); Serial.print(item2); Serial.print("]");
        returnValue = true;
      }
      else
      {
        Serial.print(" -FAILED!");
        Serial.print("  ["); Serial.print(item1.get()); Serial.print(" == "); Serial.print(item2); Serial.print("]");
      }
    
      return returnValue;
    }  
};
#endif