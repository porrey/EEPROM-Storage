// Copyright © 2017 Daniel Porrey. All Rights Reserved.
//
// This file is part of the  library.
//
// EEPROM-Storage library is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EEPROM-Storage library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with EEPROM-Storage library. If not,
// see http://www.gnu.org/licenses/.
//

// ******************************************************************************************
// *** This example displays the sizes of various
// *** dat types to the Serial output.
// ******************************************************************************************

#if defined(SPARK)
#define word short
#endif

void setup()
{
	Serial.begin(115200);

	Serial.print("The size of byte is "); Serial.print(sizeof(byte)); Serial.println(".");
	Serial.print("The size of char is "); Serial.print(sizeof(char)); Serial.println(".");
	Serial.print("The size of bool is "); Serial.print(sizeof(bool)); Serial.println(".");
	Serial.print("The size of boolean is "); Serial.print(sizeof(boolean)); Serial.println(".");
	Serial.print("The size of short is "); Serial.print(sizeof(short)); Serial.println(".");
	Serial.print("The size of word is "); Serial.print(sizeof(word)); Serial.println(".");
	Serial.print("The size of int is "); Serial.print(sizeof(int)); Serial.println(".");
	Serial.print("The size of long is "); Serial.print(sizeof(long)); Serial.println(".");
	Serial.print("The size of float is "); Serial.print(sizeof(float)); Serial.println(".");
	Serial.print("The size of double is "); Serial.print(sizeof(double)); Serial.println(".");
	Serial.println();

	Serial.print("The size of unsigned char is "); Serial.print(sizeof(unsigned char)); Serial.println(".");
	Serial.print("The size of unsigned byte is "); Serial.print(sizeof(unsigned byte)); Serial.println(".");
	Serial.print("The size of unsigned short is "); Serial.print(sizeof(unsigned short)); Serial.println(".");
	Serial.print("The size of unsigned word is "); Serial.print(sizeof(unsigned word)); Serial.println(".");
	Serial.print("The size of unsigned int is "); Serial.print(sizeof(unsigned int)); Serial.println(".");
	Serial.print("The size of unsigned long is "); Serial.print(sizeof(unsigned long)); Serial.println(".");
	Serial.println();

	Serial.print("The size of uint8_t is "); Serial.print(sizeof(uint8_t)); Serial.println(".");
	Serial.print("The size of uint16_t is "); Serial.print(sizeof(uint16_t)); Serial.println(".");
	Serial.print("The size of uint32_t is "); Serial.print(sizeof(uint32_t)); Serial.println(".");
	Serial.print("The size of uint64_t is "); Serial.print(sizeof(uint64_t)); Serial.println(".");
	Serial.println();

	Serial.print("The size of int8_t is "); Serial.print(sizeof(int8_t)); Serial.println(".");
	Serial.print("The size of int16_t is "); Serial.print(sizeof(int16_t)); Serial.println(".");
	Serial.print("The size of int32_t is "); Serial.print(sizeof(int32_t)); Serial.println(".");
	Serial.print("The size of int64_t is "); Serial.print(sizeof(int64_t)); Serial.println(".");
	Serial.println();
}

void loop()
{
  // ***
  // *** Delay 2 seconds.
  // ***
  delay(2000);
}
