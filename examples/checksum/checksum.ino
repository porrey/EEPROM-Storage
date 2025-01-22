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
// This example demonstrates the checksum function.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>

#define VALUE 1395478

EEPROMStorage<uint32_t> a(0, 0);

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
  // Clear EEPROM.
  //
  EEPROMUtil.clearEEPROM();

  //
  // Display the checksum and state of the EEPROM variable before a value is set.
  //
  Serial.print("Checksum for EEPROM variable a is "); Serial.println(a.checksumByte());
  Serial.print("The EEPROM variable a"); Serial.print(a.isInitialized() ? " is " : " is NOT "); Serial.println("initialized.");

  //
  // Set the vaue of the EEPROM variable.
  //
  Serial.print("Setting EEPROM variable value to "); Serial.println(VALUE);
  a = VALUE;
  Serial.print("The EEPROM variable a"); Serial.print(a.isInitialized() ? " is " : " is NOT "); Serial.println("initialized.");

  //
  // Calculate the check sum of the value.
  //
  byte checksum = Checksum<uint32_t>::get(VALUE);
  Serial.print("Expected checksum for "); Serial.print(VALUE); Serial.print(" is "); Serial.println(checksum);

  //
  // Display the checksum of the EEPROM variable.
  //
  Serial.print("Checksum for EEPROM variable a is "); Serial.println(a.checksumByte());
}

void loop()
{
  //
  // Delay 2 seconds.
  //
  delay(2000);
}