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
// Displays the placement of EEPROM variables in memory when using nextAddress()
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include "functions.h"

//
// Define the EEPROM variables.
//
EEPROMStorage<uint8_t> a(0, 0);
EEPROMStorage<uint16_t> b(a.nextAddress(), 0);
EEPROMStorage<uint32_t> c(b.nextAddress(), 0);
EEPROMStorage<uint64_t> d(c.nextAddress(), 0);
EEPROMStorage<float> e(d.nextAddress(), 0);
EEPROMStorage<double> f(e.nextAddress(), 0);
EEPROMStorage<char> g(f.nextAddress(), ' ');

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
  // Clear EEPROM.
  //
  EEPROMUtil.clearEEPROM();
  
  //
  // Initialize the random number generator.
  //
  randomSeed(analogRead(0));

  //
  // Set random values to each EEPROM variable.
  //
  a = random(1, 255);
  b = random(1, 1000);
  c = random(1, 10000);
  d = random(1, 100000);
  e = random(1, 100);
  f = random(1, 100);
  g = 'y';

  //
  // Display the EEPROM properties.
  //
  displayHeader();
  display("a", a);
  display("b", b);
  display("c", c);
  display("d", d);
  display("e", e);
  display("f", f);
  display("g", g);

  //
  // Display the EEPROM contents.
  //
  Serial.println();
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
  //
  // Delay 2 seconds.
  //
  delay(2000);
}