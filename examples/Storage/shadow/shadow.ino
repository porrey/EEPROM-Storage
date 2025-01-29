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
// This example demonstrates how one variable can shadow another.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include <EEPROM-Display.h>

//
// Create a variable to be stored in EEPROM. The first parameter is the
// address or location in EEPROM. The second parameter is the default
// value to return when the variable has not been initialized.
//
EEPROMStorage<uint32_t> a(0, 0);  // This variable is stored in EEPROM at positions 0, 1, 2, 3 and 4 (5 bytes)

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
  // Demonstrates a local variable taking on the value
  // of a previously defined global variable. This one
  // will use the same address as a. Note the same data
  // type must be used or we will get unexpected values.
  //
  EEPROMStorage<uint32_t> shadowVar(a.getAddress(), 0);

  //
  // Assign the value of 16 to a.
  //
  DEBUG_INFO("Assigning a the value of 16.");
  a = 16;

  //
  // Display the EEPROM contents.
  //
  EEPROMDisplay.displayEEPROM();

  //
  // Display the values of a and shadowVar. Both
  // variables will have the value of 16.
  //
  Serial.print("\r\na = "); DEBUG_INFO(a);
  Serial.print("shadowVar = "); DEBUG_INFO(a);

  //
  // Assign the value of 11 to shadowVar.
  //
  DEBUG_INFO("Assigning shadowVar the value of 11.");
  shadowVar = 11;

  //
  // Display the values of a and shadowVar. Both variables
  // will have the value of 11.
  //
  Serial.print("a = "); DEBUG_INFO(a);
  Serial.print("shadowVar = "); DEBUG_INFO(a);
}

void loop()
{
}