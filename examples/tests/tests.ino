// Copyright © 2017-2021 Daniel Porrey. All Rights Reserved.
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

// ******************************************************************************************
// *** This example runs tests on the EEEPROM-Storage
// *** library with various data types.
// ******************************************************************************************
#include <EEPROM-Storage.h>
#include "TestLibrary.h"

void setup()
{
  // ***
  // *** Initialize the serial port. On a Particle
  // *** device the baud rate will be ignored.
  // ***
  Serial.begin(115200);

  // ***
  // *** Wait for serial port to connect. Needed
  // *** for native USB port only
  // ***
  while (!Serial);

  // ***
  // *** Initialize the random number generator.
  // ***
  randomSeed(analogRead(0));

  // **********************************************************************
  // ***
  // *** There may not be enough memory to run all of the tests. Uncomment
  // *** sections to run tests on the various data types.
  // ***
  // **********************************************************************

  // ***
  // *** Use te same address for all tests. Need to be careful no to write
  // *** to often to the same address.
  // ***
  int address = EEPROM.length() - 10;

  testProxyStandard<int>("int", address, -99999, 99999);
  testProxyAdvanced<int>("int", address, -99999, 99999);

  testProxyStandard<unsigned int>("unsigned int", address, 0, 99999);
  testProxyAdvanced<unsigned int>("unsigned int", address, 0, 99999);

  testProxyStandard<long>("long", address, -99999, 99999);
  testProxyAdvanced<long>("long", address, -99999, 99999);

  testProxyStandard<byte>("byte", address, 0, 255);
  testProxyAdvanced<byte>("byte", address, 0, 255);

  // ***
  // *** Not enough memeory on the Arduino platform.
  // ***
#if defined(SPARK)
  testProxyStandard<char>("char", address, -128, 128);
  testProxyAdvanced<char>("char", address, -128, 128);
  
  testProxyStandard<unsigned long>("unsigned long", address, 0, 99999);
  testProxyAdvanced<unsigned long>("unsigned long", address, 0, 99999);

  testProxyStandard<unsigned char>("unsigned char", address, 0, 255); // *** Same as byte
  testProxyAdvanced<unsigned char>("unsigned char", address, 0, 255); // *** Same as byte

  testProxyStandard<float>("float", address, 0, 99999);

  testProxyStandard<double>("double", address, 0, 99999);
#endif

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
}
