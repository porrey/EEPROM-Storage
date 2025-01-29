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
// This example demonstrates the usage of the EEPROM-Storage library.
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
  // Clear EEPROM.
  //
  EEPROMUtil.clearEEPROM();

  //
  // Create a random address so we are not always 
  // writing to the same location (this is only 
  // necessary in the dmemo).
  //
  uint address = random(0, EEPROM.length() - 5);
  DEBUG_INFO("\r\nUsing address %u for the EEPROM variable.", address);

  //
  // Create a variable x using the random
  // address generated above with an initial
  // value of 0.
  //
  DEBUG_INFO("\r\nCreating a new EEPROM variable x.");
  EEPROMStorage<uint32_t> x(address, 0);

  //
  // Show the state of the variable.
  //
  EEPROMDisplay.displayVariable("x", x);

  //
  // Set the value of x to a random number
  // between 1000 and 5000.
  //
  uint32_t value = random(1000, 5000);
  x = value;
  DEBUG_INFO("\r\nAssigning a value of %u to the EEPROM variable.", value);
  DEBUG_INFO("The value of x is %u.", x.get());
  
  //
  // Assign the varaible to another "normal" variable.
  //
  DEBUG_INFO("\r\nAssigning the value of x to the new variable y.");
  uint32_t y = x;

  //
  // Show the value of y.
  //
  DEBUG_INFO("The value of variable y is %u.", y);

  //
  // Change the value of x to a random
  // number between 6000 and 9000.
  //
  DEBUG_INFO("\r\nAssigning a random number to the EEPROMvariable x.");
  x = random(6000, 9000);

  //
  // Show the values.
  //
  DEBUG_INFO("The value of x is %u.", x.get());

  //
  // Display the EEPROM contents.
  //
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}