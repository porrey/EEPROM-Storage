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
#ifndef STRUCT_H
#define STRUCT_H

#include <Arduino_DebugUtils.h>

//
// Define a complex structure to store in EEPROM.
//
typedef struct  
{
  uint8_t sa;
  uint16_t sb;
  uint32_t sc;
  char sd;
  float se;
  double sf;

  const char* toString(float value)
  {
    dtostrf(value, 6, 2, _buffer);
    return _buffer;
  }

  char _buffer[11];

} Matrix, *pmatrix;

void displayStruct(const char* label, const char* prefix, Matrix m)
{
  //
  // Display the struct property values.
  //
  DEBUG_INFO("");
  DEBUG_INFO(label);
  DEBUG_INFO("----------------------------------------");
  DEBUG_INFO("%s.sa = %u", prefix, m.sa);
  DEBUG_INFO("%s.sb = %u", prefix, m.sb);
  DEBUG_INFO("%s.sc = %u", prefix, m.sc);
  DEBUG_INFO("%s.sd = %c", prefix, m.sd);
  DEBUG_INFO("%s.se = %s", prefix, m.toString(m.se));
  DEBUG_INFO("%s.sf = %s", prefix, m.toString(m.sf));
}
#endif