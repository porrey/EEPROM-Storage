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

#include <EEPROM-Cache.h>
#include <EEPROM-Display.h>
#include "struct.h"

//
// Define the EEPROM variable. Using the initialization
// values of {0, 0, 0, ' ', 0, 0} as th default value.
//
EEPROMCache<Matrix> a(0, {0, 0, 0, ' ', 0, 0});

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
  // Initialize the random number generator.
  //
  randomSeed(analogRead(0));

  //
  // Display the default values.
  //
  displayStruct("EEPROM default values:", "a.get()", a.get());

  //
  // Create a Matrix struct and assign random 
  // values to the struct properties. Commit
  // the values to EEPROM.
  //
  a = { random(1, 255), random(1, 1000), random(1, 10000), 'y', random(1, 100), random(1, 100)};
  a.commit();

  //
  // Display the EEPROM properties.
  //
  DEBUG_INFO("");
  DEBUG_INFO("EEPROM<T> Properties:");
  DEBUG_INFO("--------------------------------------------------------------------------------------------------------------");
  EEPROMDisplay.displayVariable("a", a);

  //
  // Display the struct property values.
  //
  displayStruct("EEPROM struct values:", "a.get()", a.get());

  //
  // Read the struct from EEPROM.
  //
  Matrix x = a.restore();
  displayStruct("x struct:", "x", x);

  //
  // Update the EEPROM struct values
  // and commit the values to EEPROM.
  //
  a = {99, 99, 99, 'z', 99.99, 99.99};
  a.commit();

  //
  // Restore the value to show they have been written to EEPROM.
  //
  a.restore();
  displayStruct("Updated EEPROM struct values:", "a.get()", a.get());
  
  //
  // Display the EEPROM contents.
  //
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}