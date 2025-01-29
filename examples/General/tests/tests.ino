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

// ---------------------------------------------------------------------------------------
// This example runs tests on the EEEPROM-Storage library with various data types.
// ---------------------------------------------------------------------------------------

//
// Uncomment one or the other to select
// the library to test.
//
#define TARGET_STORAGE
//#define TARGET_CACHE

#include <EEPROM-Display.h>
#include <EEPROM-Util.h>
#include "TestRunner.h"

#if defined(SPARK)
//
// Cloud function variables.
//
int _isCompleted = 0;
int _totalTests = 0;
int _passedTests = 0;
int _failedTests = 0;
#endif

void setup() 
{
  #if defined(SPARK)
  //
  // Initial the cloud variables and functions.
  //
  Particle.function("GetTotalTests", getTotalTests);
  Particle.function("GetPassedTests", getPassedTests);
  Particle.function("GetFailedTests", getFailedTests);
  Particle.function("IsCompleted", isCompleted);
  #endif

  //
  // Initialize the serial port. On a Particle
  // device the baud rate will be ignored.
  //
  Serial.begin(115200);

  //
  // wait for serial port to connect. Needed
  // for native USB port only
  //
  while (!Serial);
  DEBUG_INFO("\r\n");

  //
  // On ESP8266 platforms EEPROM must be initialized.
  //
  #if defined(ESP8266)
  EEPROM.begin(4096);
  #endif

  //
  // Clear the EEPROM.
  //
  EEPROMUtil.clearEEPROM();

  //
  // Initialize the random number generator.
  //
  randomSeed(analogRead(0));

  //
  // Use the a random address for all tests. Need to be careful not to write
  // too often to the same address.
  //
  uint address = EEPROM.length() - random(20, EEPROM.length() / 2);
  Serial.print("Using address "); Serial.print(address); DEBUG_INFO(" for the test variables.");

  //
  // Run predefined tests.
  //
  TestResults results =  TestRunner.runAll(address);

  //
  // Display results.
  //
  DEBUG_INFO("Ran a total of %u tests", results.totalTests);
  DEBUG_INFO("%u of %u tests passed.", results.totalPassed, results.totalTests);
  DEBUG_INFO("%u of %u tests failed.",results.totalFailed(), results.totalTests);

  #if defined(SPARK)
  _isCompleted = 1;
  _totalTests = results.totalTests;
  _passedTests = results.totalPassed;
  _failedTests = results.totalFailed();
  #endif
}

void loop()
{
}

#if defined(SPARK)
//
// Returns 1 if the tests completed.
//
int isCompleted(String data)
{
  return _isCompleted;
}

//
// Returns the total number of tests run.
//
int getTotalTests(String data)
{
  return _totalTests;
}

//
// Returns the total number of tests passed.
//
int getPassedTests(String data)
{
  return _passedTests;
}

//
// Returns the number of failed tests.
//
int getFailedTests(String data)
{
  return _failedTests;
}
#endif