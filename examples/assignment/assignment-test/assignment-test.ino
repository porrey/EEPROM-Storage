// Copyright © 2017-2020 Daniel Porrey. All Rights Reserved.
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

// ***************************************************************************************
// This example tests the assignment of one EEPROM variable to another.
// ***************************************************************************************

#include <EEPROM-Storage.h>

EEPROMStorage<int> a(0, 0);
EEPROMStorage<int> b(sizeof(int) + 1, 0);

void setup() 
{
  Serial.begin(115200);

  Serial.println("Values at startup: ");
  Serial.print("a: "); Serial.println(a);
  Serial.print("b: "); Serial.println(b);

  if (a == b)
  {
    Serial.println("Test passed!");
  }
  else
  {
    Serial.println("Test failed!");
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
    Serial.println("Assigning b the value of a.");
    b = a;
    Serial.println("Assigned a to b!");

    Serial.println("New values: ");
    Serial.print("a: "); Serial.println(a);
    Serial.print("b: "); Serial.println(b);
    Serial.println("Reset the arduino now, the value of b at startup should be the same as a.");

    while(true) delay(100);
  }
}