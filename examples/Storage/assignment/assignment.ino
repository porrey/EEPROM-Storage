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
#include <EEPROM-Display.h>

EEPROMStorage<uint32_t> a(0, 0);
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
  // Clear EEPROM. 
  //
  // Uncomment this line of code and run once. Afterwards comment the line again.
  //
  //EEPROMUtil.clearEEPROM();

  //
  // Display the EEPROM properties.
  //
  EEPROMDisplay.displayHeader();
  EEPROMDisplay.displayVariable("a", a);
  EEPROMDisplay.displayVariable("b", b);

  if (a.isInitialized() && b.isInitialized())
  {
    //
    // Display the values of a and b.
    //
    DEBUG_INFO("\r\nValues at startup:");
    DEBUG_INFO("a: %u", a.get());
    DEBUG_INFO("b: %u", b.get());

    //
    // Check if the two values are the same.
    //
    if (a == b)
    {
      DEBUG_INFO("\r\nTest passed!");
    }
    else
    {
      DEBUG_INFO("\r\nTest failed!");
    }
  }
  else
  {
    DEBUG_INFO("\r\nClearing EEPROM and resetting variables.");

    //
    // Clear EEPROM.
    //
    EEPROMUtil.clearEEPROM();

    //
    // Initialize the values.
    //
    DEBUG_INFO("Initializing value of a to 5.");
    a = 5;
    DEBUG_INFO("Initializing value of b to 5.");
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
  // When variable a mod 5 is 0 then assign the value stored in 
  // variable a to the value stored in variable b.
  //
  if(a % 5 == 0)
  {
    //
    // Asign the value of a to b.
    //
    DEBUG_INFO("\r\nAssigning b the value of a.");
    b = a;
    DEBUG_INFO("Assigned a to b!");

    //
    // Display the new values.
    //
    DEBUG_INFO("\r\nNew values: ");
    DEBUG_INFO("a: %d", a.get());
    DEBUG_INFO("b: %d", b.get());
    DEBUG_INFO("\r\nReset the arduino now, the value of b at startup should be the same as a.");

    //
    // Loop forever so the microcontroller can be rebooted.
    //
    while(true) delay(100);
  }
}