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
// This example demonstrates ho to adjust the Arduino Debug library output.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Debug.h>

unsigned int _i = 0;

void setup()
{
  //
  // Use Serial2 by uncommenting the next two lines.
  //
  //Debug.setDebugOutputStream(&Serial2);
  //Serial2.begin(115200);

  //
  // Initialize the serial port. On a Particle
  // device the baud rate will be ignored.
  //
  Serial.begin(115200);

  //
  // Disable output by uncommenting the next line.
  // Levels: 
  // DBG_NONE, DBG_ERROR, DBG_WARNING, 
  // DBG_INFO, DBG_DEBUG, DBG_VERBOSE
  //
  //Debug.setDebugLevel(DBG_NONE);

  //
  // Other option to try...
  //
  //Debug.timestampOn();
  //Debug.formatTimestampOn();
  //Debug.debugLabelOn();

	//
	// wait for serial port to connect. Needed
	// for native USB port only
	//
	while (!Serial);
  DEBUG_INFO("\r\n");

  //
  // Display the EEPROM size.
  //
  DEBUG_INFO("Setup completed.");
}

void loop()
{
  //
  // Increment _i.
  //
  _i++;

  //
  // Display the loop iteration.
  //
  DEBUG_INFO("In loop(%u)", _i);

  //
  // Delay 3 seconds.
  //
  delay(3000);
}