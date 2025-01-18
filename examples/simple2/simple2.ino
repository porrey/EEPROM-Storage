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
// This example demonstrates simple usage.
// ---------------------------------------------------------------------------------------

#include "EEPROM-Storage.h"

//
// Create two variables to be stored in EEPROM.
//
EEPROMStorage<uint32_t> _myInt1(0, 0);
EEPROMStorage<uint32_t> _myInt2(_myInt1.nextAddress(), 0);

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

  //
  // Set the value of _myInt1 to 10.
  //
  _myInt1 = 10;

  //
  // Set the value of _myInt2 to 20.
  //
  _myInt2 = 20;

  //
  // Create a variable i and set the value to 10.
  int i = 10;

  //
  // Increment iby the value of _myInt2.
  //
  i += _myInt2;
  Serial.print("i = "); Serial.println(i);

  //
  // Display the value of _myInt2.
  //
  Serial.print("_myInt2 = "); Serial.println(_myInt2);

  //
  // Multiply the value of _myInt2 by 10.
  //
  _myInt2 *= 10;

  //
  // Display the new value of _myInt2.
  //
  Serial.print("_myInt2 = "); Serial.println(_myInt2);
}

void loop()
{
  //
  // Delay 2 seconds.
  //
  delay(2000);
}