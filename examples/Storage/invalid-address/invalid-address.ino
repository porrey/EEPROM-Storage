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
// This example demonstrates displaying and clearing EEPROM contents.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include <EEPROM-Display.h>

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
  // Define a variable that overlaps the end of the EEPROM address space.
  //
  EEPROMStorage<uint32_t> a(EEPROM.length() - 2, 0);

  //
  // Set the EEPROM variable value.
  //
  a = 1145;

  //
  // Display the EEPROM properties.
  //
  DEBUG_INFO("");
  DEBUG_INFO("The variable starts 2 bytes before the end of EEPROM which does not allow enough space to hold the value and the checksum.");
  DEBUG_INFO("The variable will not initialize.");
  EEPROMDisplay.displayHeader();
  EEPROMDisplay.displayVariable("a", a);

  //
  // Show that the variable does not have a value.
  //
  DEBUG_INFO("");
  DEBUG_INFO("Value of EEPROM variable a is %u.", a.get());
   
  //
  // Display the EEPROM contents.
  //
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}