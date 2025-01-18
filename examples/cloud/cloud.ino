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
// For Particle platform only.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>

//
// Define a 32-bit integer at adress 0 (first argument) with a
// default value of 11 (second agument).
//
EEPROMStorage<int32_t> _cloudVariable(0, 11);

void setup()
{
  //
  // Initial the serial port.
  //
  Serial.begin(115200);

  //
  // Wait for serial port to connect. Needed
  // for native USB port only
  //
  while (!Serial);

  //
  // Initial the cloud variables and functions.
  //
  Particle.function("SetVariable", setVariable);
  Particle.function("GetVariable", getVariable);

  //
  // Display the variable value.
  //
  Serial.print("Cloud Variable value is "); Serial.println(_cloudVariable);
}

void loop()
{
}

//
// Sets the variable value.
//
int setVariable(String data)
{
  int returnValue = 0;

  if (data.trim() != "")
  {
    int value = data.toInt();
    _cloudVariable = value;
    returnValue = 1;
  }

  return returnValue;
}

//
// Gets the variable value.
//
int getVariable(String data)
{
  return _cloudVariable;
}
