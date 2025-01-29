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

#include <EEPROM-Cache.h>
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

  //
  // Create a variable x using the random
  // address generated above with an initial
  // value of 0.
  //
  EEPROMCache<uint32_t> x(address, 0);

  //
  // Set the value of x to a random number
  // between 1000 and 5000.
  //
  x = random(1000, 5000);

  //
  // Show the state of the variable. Note that
  // it has not been initialized since we have
  // not calle commit() yet.
  //
  DEBUG_INFO("\r\nVariable x BEFORE calling commit():");
  EEPROMDisplay.displayVariable("x", x);

  //
  // Show the value.
  //
  DEBUG_INFO("The value of variable x is %u.", x.get());

  //
  // Call commit().
  //
  x.commit();

  //
  // Show the state of the variable. Now the 
  // variable will show initialed.
  //
  DEBUG_INFO("\r\nVariable x AFTER calling commit():");
  EEPROMDisplay.displayVariable("x", x);
  DEBUG_INFO("The value of variable x is %u.", x.get());

  //
  // Change the value of x to a random
  // number between 6000 and 9000.
  //
  x = random(6000, 9000);

  //
  // Read the value from the EEPROM.
  //
  uint32_t eepromValue = x.read();

  //
  // Read the value from the memory.
  //
  uint32_t memoryValue = x;

  //
  // Show the values. The will be different because
  // we have not called commit() yet.
  //
  DEBUG_INFO("\r\nVariable x BEFORE calling commit():");
  DEBUG_INFO("The value of x in EEPROM is %u (the previous value).", eepromValue);
  DEBUG_INFO("The value of x in Memory is %u (the new value).", memoryValue);

  //
  // Call commit().
  //
  x.commit();

  //
  // Read the value from the EEPROM.
  //
  eepromValue = x.read();

  //
  // Read the value from the memory.
  //
  memoryValue = x;

  //
  // Show the values. The will be different because
  // we have not called commit() yet.
  //
  DEBUG_INFO("\r\nVariable x AFTER calling commit():");
  DEBUG_INFO("The value of x in EEPROM is %u (the previous value).", eepromValue);
  DEBUG_INFO("The value of x in Memory is %u (the new value).", memoryValue);

  //
  // Restore the value from EEPROM. First change
  // the value in memory and then restore the
  // previous value from EEPROM.
  //
  x = random(20000, 30000);
  DEBUG_INFO("\r\nThe new value of x in memory is %u.", x.get());
  DEBUG_INFO("Restoring EEPROM value...");

  x.restore();
  DEBUG_INFO("The value of x in memory after the restore is %u.", x.get());
  
  //
  // Display the EEPROM contents.
  //
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}