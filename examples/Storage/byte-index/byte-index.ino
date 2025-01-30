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
  DEBUG_INFO("\r\n");
  
  //
  // On ESP8266 platforms EEPROM must be initialized.
  //
  #if defined(ESP8266)
  EEPROM.begin(4096);
  #endif

  //
  // Display the EEPROM size.
  //
  DEBUG_INFO("The total size of EEPROM on this device is %d bytes", EEPROM.length());
  
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
  // Display the byte values of the variable.
  //
  DEBUG_INFO("");
  DEBUG_INFO("byte values of EEROM variable a:");
  DEBUG_INFO("byte at a[0] is 0x%.2X", a[0]);
  DEBUG_INFO("byte at a[1] is 0x%.2X", a[1]);
  DEBUG_INFO("byte at a[2] is 0x%.2X", a[2]);
  DEBUG_INFO("byte at a[3] is 0x%.2X", a[3]);
  DEBUG_INFO("byte at a[4] is 0x%.2X", a[4]);
  DEBUG_INFO("byte at a[5] is 0x%.2X", a[5]);
  DEBUG_INFO("byte at a[6] is 0x%.2X", a[6]);
  DEBUG_INFO("byte at a[7] is 0x%.2X", a[7]);
  DEBUG_INFO("byte at a[8] is 0x%.2X", a[8]);

  //
  // Display the EEPROM contents.
  //
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}