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
#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "EEPROM-Display.h"

void displayLine()
{
  //----------
  Serial.println("----------------------------------------------------------------------------------------------------------------------------------");
}

void displayHeader()
{
  //
  // Display the EEPROM properties.
  //
  Serial.println();
  Serial.println("EEPROM<T> Properties:");
  displayLine();
}

void print2digits(uint number)
{
  if (number < 10) {
    Serial.print(" ");
  }

  Serial.print(number);
}

template<typename T>
void display(String name, EEPROMStorage<T> value)
{
  Serial.print(name);
  Serial.print(": Variable Size: ");
  print2digits(value.size());
  Serial.print(", Memory Length = ");
  print2digits(value.length());
  Serial.print(", Start Address = ");
  print2digits(value.getAddress());
  Serial.print(", Checksum Address = ");
  print2digits(value.checksumAddress());
  Serial.print(", Checksum Value = ");
  EEPROMDisplay.displayPaddedHexByte(value.checksumByte());
  Serial.print(", Initialized = ");
  Serial.print(value.isInitialized() ? "Yes" : "No");
  Serial.println();
}
#endif