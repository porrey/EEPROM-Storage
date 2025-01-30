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
// This example displays the sizes of various data types to the Serial output.
// ---------------------------------------------------------------------------------------

#include <EEPROM.h>
#include <EEPROM-Vars.h>
#include <Arduino_DebugUtils.h>

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

  DEBUG_INFO("");
  DEBUG_INFO("The size of byte is %u.", sizeof(byte));
  DEBUG_INFO("The size of char is %u.", sizeof(char));
  DEBUG_INFO("The size of bool is %u.", sizeof(bool));
  DEBUG_INFO("The size of boolean is %u.", sizeof(boolean));
  DEBUG_INFO("The size of short is %u.", sizeof(short));
  DEBUG_INFO("The size of word is %u.", sizeof(word));
  DEBUG_INFO("The size of int is %u.", sizeof(int));
  DEBUG_INFO("The size of long is %u.", sizeof(long));
  DEBUG_INFO("The size of float is %u.", sizeof(float));
  DEBUG_INFO("The size of double is %u.", sizeof(double));
  DEBUG_INFO("");

  DEBUG_INFO("The size of unsigned char is %u.", sizeof(unsigned char));
  DEBUG_INFO("The size of unsigned byte is %u.", sizeof(unsigned byte));
  DEBUG_INFO("The size of unsigned short is %u.", sizeof(unsigned short));
  DEBUG_INFO("The size of unsigned word is %u.", sizeof(unsigned word));
  DEBUG_INFO("The size of unsigned int is %u.", sizeof(unsigned int));
  DEBUG_INFO("The size of unsigned long is %u.", sizeof(unsigned long));
  DEBUG_INFO("");

  DEBUG_INFO("The size of uint8_t is %u.", sizeof(uint8_t));
  DEBUG_INFO("The size of uint16_t is %u.", sizeof(uint16_t));
  DEBUG_INFO("The size of uint32_t is %u.", sizeof(uint32_t));
  DEBUG_INFO("The size of uint64_t is %u.", sizeof(uint64_t));
  DEBUG_INFO("");

  DEBUG_INFO("The size of int8_t is %u.", sizeof(int8_t));
  DEBUG_INFO("The size of int16_t is %u.", sizeof(int16_t));
  DEBUG_INFO("The size of int32_t is %u.", sizeof(int32_t));
  DEBUG_INFO("The size of int64_t is %u.", sizeof(int64_t));
  DEBUG_INFO("");
}

void loop()
{
}