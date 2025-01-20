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
// This example tests the assignment of one EEPROM variable to another.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include "functions.h"

EEPROMStorage<uint32_t> a(0, 04);
EEPROMStorage<uint32_t> b(b.nextAddress(), 0);

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
  // Clear EEPROM. 
  //
  // Uncomment this line of code and run once. Afterwards comment the line again.
  //
  //EEPROMUtil.clearEEPROM();

  //
  // Display the EEPROM properties.
  //
  displayHeader();
  display("a", a);
  display("b", b);

  if (a.isInitialized() && b.isInitialized())
  {
    //
    // Display the values of a and b.
    //
    Serial.println();
    Serial.println("Values at startup: ");
    Serial.print("a: "); Serial.println(a);
    Serial.print("b: "); Serial.println(b);

    //
    // Check if the two values are the same.
    //
    if (a == b)
    {
      Serial.println();
      Serial.println("Test passed!");
    }
    else
    {
      Serial.println();
      Serial.println("Test failed!");
    }
  }
  else
  {
    Serial.println();
    Serial.println("Clearing EEPROM and resetting variables.");

    //
    // Clear EEPROM.
    //
    EEPROMUtil.clearEEPROM();

    //
    // Initialize the values.
    //
    a = 5;
    b = 5;
  }
}

void loop() 
{
  //
  // Increment a.
  //
  a++;

  //
  // When a mod 5 is 0 then assign the value stored in a
  // to the value stored in b.
  //
  if(a % 5 == 0)
  {
    //
    // Asign the value of a to b.
    //
    Serial.println();
    Serial.println("Assigning b the value of a.");
    b = a;
    Serial.println("Assigned a to b!");

    //
    // Display the new values.
    //
    Serial.println();
    Serial.println("New values: ");
    Serial.print("a: "); Serial.println(a);
    Serial.print("b: "); Serial.println(b);

    Serial.println();
    Serial.println("Reset the arduino now, the value of b at startup should be the same as a.");

    //
    // Loop forever so the microcontroller can be rebooted.
    //
    while(true) delay(100);
  }
}
