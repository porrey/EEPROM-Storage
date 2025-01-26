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
// This example will calculate the address and
// create initialization code for one or more
// EEPROM-Storage variables. Just follow the steps
// outlined below.
//
// Complete Steps 1 through 3 (below) for your project.
//
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include "Types.h"

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
  // Display the EEPROM size.
  //
  Serial.print("The total size of EEPROM on this device is "); Serial.print(EEPROM.length()); Serial.println(" bytes.");
  
  //
  // STEP 1 of 3:
  //
  // Create a list of definitions that each contain the data type and the default value.
  //
  definition myDefinitions[] =
  {
    { DT_INT, 0 },
    { DT_UINT, 0 },
    { DT_ULONG, 0 },
    { DT_FLOAT, 5.5 },
    { DT_DOUBLE, 6.6 },
    { DT_INT, 10 }
  };

  //
  // STEP 2 of 3:
  //
  // Define the starting address in EEPROM. If you are manually storing other data in EEPROM this
  // address could be defined at the end of that data.
  //
  int myFirstAddress = 0;

  //
  // STEP 3 of 3:
  //
  // Set the value below to true to display comments and false to hide the comments.
  //
  bool showComments = true;

  //
  // This will output declarations through the serial port.
  //
  int items = sizeof(myDefinitions) / sizeof(definition);
  Serial.print("The number of declarations defined is "); Serial.println(items);
  Serial.println();
  int nextAddress = myFirstAddress;

  for (int i = 0; i < items; i++)
  {
    if (showComments)
    {
      Serial.println("//");
      Serial.print("// Total length = "); Serial.print(_size[myDefinitions[i].type] + 1); Serial.print(" [Addresses "); Serial.print(nextAddress); Serial.print(" through "); Serial.print(nextAddress + _size[myDefinitions[i].type]); Serial.println("]");
      Serial.println("//");
    }

    Serial.print("EEPROMStorage<"); Serial.print(_name[myDefinitions[i].type]); Serial.print(">("); Serial.print(nextAddress); Serial.print(", "); Serial.print(myDefinitions[i].defaultValue); Serial.println(");");
    if (showComments) Serial.println();

    nextAddress += _size[myDefinitions[i].type] + 1;
  }
}

void loop()
{
}