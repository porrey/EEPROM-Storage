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
// Demonstrates how two variables in different scopes can share a value.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include <EEPROM-Display.h>

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
  // Initialize the random number generator.
  //
  randomSeed(analogRead(0));

  //
  // Create a local variable scoped to the
  // setup method.
  //
  DEBUG_INFO("");
  DEBUG_INFO("Creating a new EEPROM variable x at address 0 in setup().");
  EEPROMStorage<uint32_t> x(0, 0);

  //
  // Assign a random value to the EEPROM variable x.
  //
  uint32_t value = random(1, 99999);
  DEBUG_INFO("Assigning EEPROM variable x the value of %u.", value);
  x = value;
  DEBUG_INFO("The value of the EEPROM variable x is %u.", x.get());
}

void loop() 
{
  //
  // Create a local variable scoped to the
  // loop method. The value will match the
  // value of the variable x.
  //
  DEBUG_INFO("");
  DEBUG_INFO("Creating a new EEPROM variable y at address 0 in setup().");
  EEPROMStorage<uint32_t> y(0, 0);
  DEBUG_INFO("The value of the EEPROM variable y is %u.", y.get());

  //
  // Loop forever.
  //
  while (true) delay(100);
}