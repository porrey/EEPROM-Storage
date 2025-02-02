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
// EEPROM-Storage variables.
// ---------------------------------------------------------------------------------------

#include "types.h"
#include <EEPROM.h>
#include <EEPROM-Debug.h>

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
  // Define the starting address in EEPROM. If you are manually storing other data in EEPROM this
  // address could be defined at the end of that data.
  //
  int myFirstAddress = 0;

  //
  // This will output declarations through the serial port.
  //
  int itemCount = sizeof(myDefinitions) / sizeof(definition);
  DEBUG_INFO("The number of definitons defined is %u.\r\n", itemCount);
  int nextAddress = myFirstAddress;

  for (int i = 0; i < itemCount; i++)
  {
    DEBUG_INFO("//");
    DEBUG_INFO("// Total length = %u [Addresses %u  through %u]", _size[myDefinitions[i].type] + 1, nextAddress, nextAddress + _size[myDefinitions[i].type]);
    DEBUG_INFO("//");
    DEBUG_INFO("EEPROMStorage<%s>(%u, %u)", _name[myDefinitions[i].type], nextAddress, myDefinitions[i].defaultValue);

    nextAddress += _size[myDefinitions[i].type] + 1;
  }
}

void loop()
{
}