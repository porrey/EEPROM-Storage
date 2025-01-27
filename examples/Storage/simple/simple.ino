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

#include <EEPROM-Storage.h>

//
// Create two variables to be stored in EEPROM.
//
EEPROMStorage<uint32_t> a(0, 0);
EEPROMStorage<uint32_t> b(a.nextAddress(), 0);

void setup()
{
  //
  // Initialize the serial port. On a Particle
  // device the baud rate will be ignored.
  //
  Serial.begin(115200);

	//
	// wait for serial port to connect. Needed
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
  // Assign the value of 128 to a.
  //
  Serial.print("Assigning a the value of 128.");
  a = 128;

  //
  // Display the value of a.
  //
  Serial.print("a = "); Serial.println(a);

  //
  // Set the value of b to 20.
  //
  b = 20;

  //
  // Create a variable i and set the value to 10.
  //
  int i = 10;

  //
  // Increment i by the value of b.
  //
  i += b;
  Serial.print("i = "); Serial.println(i);

  //
  // Display the value of b.
  //
  Serial.print("b = "); Serial.println(b);

  //
  // Multiply the value of b by 10.
  //
  b *= 10;

  //
  // Display the new value of b.
  //
  Serial.print("b = "); Serial.println(b);
}

void loop()
{
  //
  // Wait for 2 seconds.
  //
  delay(2000);

  //
  // Increment the value of a by 1.
  //
  Serial.print("Incrementing EEPROM variable a.");
  a++;

  //
  // Display the value of a.
  //
  Serial.print("The value of a is "); Serial.println(a);
}