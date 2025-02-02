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

#include <EEPROM-Cache.h>
#include <EEPROM-Display.h>

//
// Create a variable to be stored in EEPROM. The first parameter is the
// address or location in EEPROM. The second parameter is the default
// value to return when the variable has not been initialized.
//
// This variable is stored in memory unil committed. When it
// is committed, it is save to EEPROM positions 0, 1, 2, 3 
// and 4 (5 bytes).
//
EEPROMCache<uint32_t> a(0);

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
  // If initialized, retrieve the stored value.
  //
  if (a.isInitialized())
  {
    a.restore();
    DEBUG_INFO("The restored value of EEPROM variable a is %u.", a.get());
  }

  //
  // Increment the value of a.
  //
  DEBUG_INFO("Incrementing the EEPROM variable a by 1.");
  a++;

  //
  // Display the value of a.
  //
  DEBUG_INFO("a = %u.", a.get());

  //
  // Display the EEPROM contents before commit.
  //
  EEPROMDisplay.displayEEPROM();

  //
  // Commit the value to EEPROM.
  //
  a.commit();

  //
  // Display the EEPROM contents after commit.
  //
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
  //
  // Increment the value of a by 1.
  //
  DEBUG_INFO("Incrementing a.");
  a++;

  //
  // Display the value of a.
  //
  DEBUG_INFO("The value of a, from memory, is %u.", a.get());

  //
  // Commit the value to EEPROM.
  //
  if (a % 100 == 0)
  {
    DEBUG_INFO("Committing variable to EEPROM memory.");
    a.commit();

    //
    // Display the EEPROM contents after commit.
    //
    EEPROMDisplay.displayEEPROM();
  }

  //
  // Wait for 2 seconds.
  //
  delay(750);
}