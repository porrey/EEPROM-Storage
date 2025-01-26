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
#include <EEPROM-Display.h>

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
  // On ESP8266 platforms EEPROM must be initialized.
  //
  #if defined(ESP8266)
  EEPROM.begin(4096);
  #endif

  //
  // Display the EEPROM size.
  //
  Serial.print("The total size of EEPROM on this device is "); Serial.print(EEPROM.length()); Serial.println(" bytes.");
  
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
  // Set the EEPROM variable value.
  //
  a = 987184729185656876;

  //
  // Display the EEPROM properties.
  //
  EEPROMDisplay.displayHeader();
  EEPROMDisplay.displayVariable("a", a);

  //
  // Disply the byte values of the variable.
  //
  Serial.println();
  Serial.println("byte values of EEROM variable a:");
  Serial.print("byte at a[0] is "); EEPROMDisplay.displayPaddedHexByte(a[0]); Serial.println();
  Serial.print("byte at a[1] is "); EEPROMDisplay.displayPaddedHexByte(a[1]); Serial.println();
  Serial.print("byte at a[2] is "); EEPROMDisplay.displayPaddedHexByte(a[2]); Serial.println();
  Serial.print("byte at a[3] is "); EEPROMDisplay.displayPaddedHexByte(a[3]); Serial.println();
  Serial.print("byte at a[4] is "); EEPROMDisplay.displayPaddedHexByte(a[4]); Serial.println();
  Serial.print("byte at a[5] is "); EEPROMDisplay.displayPaddedHexByte(a[5]); Serial.println();
  Serial.print("byte at a[6] is "); EEPROMDisplay.displayPaddedHexByte(a[6]); Serial.println();
  Serial.print("byte at a[7] is "); EEPROMDisplay.displayPaddedHexByte(a[7]); Serial.println();
  Serial.print("byte at a[8] is "); EEPROMDisplay.displayPaddedHexByte(a[8]); Serial.println();

  //
  // Display the EEPROM contents.
  //
  Serial.println();
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}