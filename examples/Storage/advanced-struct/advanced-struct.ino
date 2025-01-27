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
#include <EEPROM-Display.h>

//
// Define a complex structure to store in EEPROM.
//
typedef struct  {
  uint8_t sa;
  uint16_t sb;
  uint32_t sc;
  char sd;
  float se;
  double sf;
} Matrix, *pmatrix;

//
// Define the EEPROM variable. Using the initialization
// values of {0, 0, 0, ' ', 0, 0} as th default value.
//
EEPROMStorage<Matrix> a(0, {0, 0, 0, ' ', 0, 0});

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
  // Clear EEPROM.
  //
  EEPROMUtil.clearEEPROM();

  //
  // Initialize the random number generator.
  //
  randomSeed(analogRead(0));

  //
  // Display the default values.
  //
  displayStruct("EEPROM default values:", "a.get()", a.get());

  //
  // Create a Matrix struct and assign random 
  // values to the struct properties.
  //
  a = { random(1, 255), random(1, 1000), random(1, 10000), 'y', random(1, 100), random(1, 100)};

  //
  // Display the EEPROM properties.
  //
  Serial.println();
  Serial.println("EEPROM<T> Properties:");
  Serial.println("--------------------------------------------------------------------------------------------------------------");
  EEPROMDisplay.displayVariable("a", a);

  //
  // Display the struct property values.
  //
  displayStruct("EEPROM struct values:", "a.get()", a.get());

  //
  // Read the struct from EEPROM.
  //
  Matrix x = a;
  displayStruct("x struct:", "x", x);

  //
  // Update the EEPROM struct values.
  //
  a = {99, 99, 99, 'z', 99.99, 99.99};
  displayStruct("Updated EEPROM struct values:", "a.get()", a.get());

  //
  // Display the EEPROM contents.
  //
  Serial.println();
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}

void displayStruct(String label, String prefix, Matrix m)
{
  //
  // Display the struct property values.
  //
  Serial.println();
  Serial.println(label);
  Serial.println("----------------------------------------");
  Serial.print(prefix); Serial.print(".sa = "); Serial.println(m.sa);
  Serial.print(prefix); Serial.print(".sb = "); Serial.println(m.sb);
  Serial.print(prefix); Serial.print(".sc = "); Serial.println(m.sc);
  Serial.print(prefix); Serial.print(".sd = "); Serial.println(m.sd);
  Serial.print(prefix); Serial.print(".se = "); Serial.println(m.se);
  Serial.print(prefix); Serial.print(".sf = "); Serial.println(m.sf);
}