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

// ***************************************************************************************
// This example demonstrates simple usage.
// ***************************************************************************************

#include <EEPROM-Storage.h>

//
// Create a variable to be stored in EEPROM. The first parameter is the
// address or location in EEPROM. The second parameter is the default
// value to return when the variable has not been initialized.
//
EEPROMStorage<uint32_t> _myInt(0, 0);  // This variable is stored in EEPROM at positions 0, 1, 2, 3 and 4 (5 bytes)

void setup()
{
  //
  // Initialize the serial port. On a Particle
  // device the baud rate will be ignored.
  //
  Serial.begin(115200);

  //
  // Wait for serial port to connect. Needed
  // for native USB port only
  //
  while (!Serial);

  //
  // Assign the value of 128 to _myInt.
  //
  Serial.print("Assigning _myInt the value of 128.");
  _myInt = 128;

  //
  // Display the value of _myInt.
  //
  Serial.print("_myInt = "); Serial.println(_myInt);

  //
  // Display the EEPROM contents.
  //
  displayEEPROM();
}

void loop()
{
  //
  // Wait for 2 seconds.
  //
  delay(2000);

  //
  // Increment the value of _myInt by 1.
  //
  Serial.print("Incrementing _myInt.");
  _myInt++;

  //
  // Display the value of _myInt.
  //
  Serial.print("_myInt = "); Serial.println(_myInt);
}