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
// Displays the placement of EEPROM variables in memory when using nextAddress()
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include "functions.h"

//
// Define the EEPROM variables.
//
EEPROMStorage<uint64_t> a(0, 0);

void setup()
{
  //
  // Initialize the serial port.
  //
  Serial.begin(115200);

  //
  // Wait for serial port to connect. Needed
  // for native USB port only
  //
  while (!Serial);
  Serial.println();

  //
  // Clear EEPROM.
  //
  EEPROMUtil.clearEEPROM();

  //
  // Set random values to each EEPROM variable.
  //
  a = 98718472918565687689393;

  //
  // Display the EEPROM properties.
  //
  displayHeader();
  display("a", a);

  //
  // Disply the byte values of the variable.
  //
  Serial.println();
  Serial.println("byte values of EEROM variable a:");
  Serial.print("byte at a[0] is "); Serial.println(a[0], HEX);
  Serial.print("byte at a[1] is "); Serial.println(a[1], HEX);
  Serial.print("byte at a[2] is "); Serial.println(a[2], HEX);
  Serial.print("byte at a[3] is "); Serial.println(a[3], HEX);
  Serial.print("byte at a[4] is "); Serial.println(a[4], HEX);
  Serial.print("byte at a[5] is "); Serial.println(a[5], HEX);
  Serial.print("byte at a[6] is "); Serial.println(a[6], HEX);
  Serial.print("byte at a[7] is "); Serial.println(a[7], HEX);
  Serial.print("byte at a[8] is "); Serial.println(a[8], HEX);

  //
  // Display the EEPROM contents.
  //
  Serial.println();
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
  //
  // Delay 2 seconds.
  //
  delay(2000);
}