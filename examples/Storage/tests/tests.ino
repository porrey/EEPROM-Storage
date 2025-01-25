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

#include <EEPROM-Storage.h>
#include <EEPROM-Util.h>
#include "TestLibrary.h"

//
// Results
//
uint _totalTests = 0;
uint _totalPassed = 0;

void setup()
{
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
  Serial.println();
  
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
  // Display the EEPROM size.
  //
  Serial.print("The total size of EEPROM on this device is "); Serial.print(EEPROM.length()); Serial.println(" bytes.");
  
  // ---------------------------------------------------------------------------------------
  // There may not be enough memory to run all of the tests. Comment
  // sections to only run tests on the various data types.
  // ---------------------------------------------------------------------------------------
  
  //
  // Use the a random address for all tests. Need to be careful not to write
  // too often to the same address.
  //
  uint address = EEPROM.length() - random(20, EEPROM.length() / 2);
  Serial.print("Using address "); Serial.print(address); Serial.println(" for the test variables.");
  Serial.println();
  
  //
  // Type: int
  //
  TestLibrary<int> t1;
  t1.TestStandard("int", address, -99999, 99999);
  t1.TestAdvanced("int", address, -99999, 99999);
  _totalTests += t1.totalTests;
  _totalPassed += t1.totalPassed;
  
  //
  // Type: unsigned int
  //
  TestLibrary<unsigned int> t2;
  t2.TestStandard("unsigned int", address, 0, 99999);
  t2.TestAdvanced("unsigned int", address, 0, 99999);
  _totalTests += t2.totalTests;
  _totalPassed += t2.totalPassed;
  
  //
  // Type: long
  //
  TestLibrary<long> t3;
  t3.TestStandard("long", address, -99999, 99999);
  t3.TestAdvanced("long", address, -99999, 99999);
  _totalTests += t3.totalTests;
  _totalPassed += t3.totalPassed;

  //
  // Type: unsigned long
  //
  TestLibrary<unsigned long> t4;
  t4.TestStandard("unsigned long", address, 0, 99999);
  t4.TestAdvanced("unsigned long", address, 0, 99999);
  _totalTests += t4.totalTests;
  _totalPassed += t4.totalPassed;

    //
    // Type: byte
    //
  TestLibrary<byte> t5;
  t5.TestStandard("byte", address, 0, 255);
  t5.TestAdvanced("byte", address, 0, 255);
  _totalTests += t5.totalTests;
  _totalPassed += t5.totalPassed;

  //
  // Type: char
  //
  TestLibrary<char> t6;
  t6.TestStandard("char", address, -128, 128);
  t6.TestAdvanced("char", address, -128, 128);
  _totalTests += t6.totalTests;
  _totalPassed += t6.totalPassed;

  //
  // Type: unsigned char
  //
  TestLibrary<unsigned char> t7;
  t7.TestStandard("unsigned char", address, 0, 255); // Same as byte
  t7.TestAdvanced("unsigned char", address, 0, 255); // Same as byte
  _totalTests += t7.totalTests;
  _totalPassed += t7.totalPassed;

  //
  // Type: float
  //
  TestLibrary<float> t8;
  t8.TestStandard("float", address, 0, 99999);
  _totalTests += t8.totalTests;
  _totalPassed += t8.totalPassed;

  //
  // Type: double
  //
  TestLibrary<double> t9;
  t9.TestStandard("double", address, 0, 99999);
  _totalTests += t9.totalTests;
  _totalPassed += t9.totalPassed;

  //
  // Display results.
  //
  int totalFailed = _totalTests - _totalPassed;
  Serial.println();
  Serial.print("Ran a total of "); Serial.print(_totalTests); Serial.println(" test(s).");
  Serial.print(_totalPassed); Serial.print(" of "); Serial.print(_totalTests); Serial.print(" test(s) passed ["); Serial.print((float)_totalPassed / (float)_totalTests * 100.0); Serial.println("%].");
  Serial.print(totalFailed); Serial.print(" of "); Serial.print(_totalTests); Serial.print(" test(s) failed ["); Serial.print((float)totalFailed / (float)_totalTests * 100.0); Serial.println("%].");
}

void loop()
{
  //
  // Delay 2 seconds.
  //
  delay(2000);
}
