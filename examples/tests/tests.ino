// Copyright © 2017 Daniel Porrey. All Rights Reserved.
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

#include "EEPROM-Storage.h"

// ***
// *** Funtion header
// ***
template <typename T> void runTests(EEPROMStorage<T> item);
template <typename T> void assertAreEqual(T item1, T item2);

// ***
// *** Resutls
// ***
unsigned int _totalTests = 0;
unsigned int _totalPassed = 0;

void setup()
{
  // ***
  // *** Initialize the serial port. On a Particle
  // *** device the baud rate will be ignored.
  // ***
  Serial.begin(115200);

  // ***
  // *** Initialize the random number generator.
  // ***
  randomSeed(analogRead(0));

  // ***
  // *** Run tests on data type int
  // ***
  EEPROMStorage<int> var1(0, 0);
  Serial.println("Running tests on [int]");
  runTests(var1);

  // ***
  // *** Display results.
  // ***
  int totalFailed = _totalTests - _totalPassed;
  Serial.println();
  Serial.print("Ran a total of "); Serial.print(_totalTests); Serial.println(" test(s).");
  Serial.print(_totalPassed); Serial.print(" of "); Serial.print(_totalTests); Serial.print(" test(s) passed ["); Serial.print(_totalPassed / _totalTests * 100); Serial.println("%].");
  Serial.print(totalFailed); Serial.print(" of "); Serial.print(_totalTests); Serial.print(" test(s) failed ["); Serial.print(totalFailed / _totalTests * 100); Serial.println("%].");
}

void loop()
{
  // ***
  // *** Delay 2 seconds.
  // ***
  delay(2000);
}

template <typename T> void runTests(EEPROMStorage<T> item)
{
  // ***
  // *** Uninitialize test
  // ***
  displayTestHeader("Uninitialized");
  item.unset();
  _totalPassed += assertAreEqual(item.isInitialized(), false);
  Serial.println();

  // ***
  // *** Initialize test
  // ***
  {
    displayTestHeader("Initialize");
    T initValue = random(0, 0xFFFF);
    item = initValue;
    _totalPassed += assertAreEqual(item, initValue);
    Serial.println();
  }

  // ***
  // *** Addition test
  // ***
  {
    displayTestHeader("Addition");
    T value = item;
    value = value + 5;
    item = item + 5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  // ***
  // *** Subtraction test
  // ***
  {
    displayTestHeader("Subtraction");
    T value = 10;
    item = 10;
    value = value - 5;
    item = item - 5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  // ***
  // *** Multiplication test
  // ***
  {
    displayTestHeader("Multiplication");
    T value = 10;
    item = 10;
    value = value * 5;
    item = item * 5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  // ***
  // *** Division test
  // ***
  {
    displayTestHeader("Multiplication");
    T value = 10;
    item = 10;
    value = value / 5;
    item = item / 5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }
}

void displayTestHeader(String testName)
{
  Serial.print("TEST: ["); Serial.print(testName); Serial.print("]");
  _totalTests++;
}

bool assertAreEqual(const bool item1, const bool item2)
{
  bool returnValue = false;

  if (item1 == item2)
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

template <typename T> bool assertAreEqual(const T item1, const T item2)
{
  bool returnValue = false;

  if (item1 == item2)
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

