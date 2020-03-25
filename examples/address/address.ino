// Copyright © 2017-2020 Daniel Porrey. All Rights Reserved.
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
// *** This example will calculate the address and
// *** create initialization code for one or more
// *** EEPROM-Storage variables. Just follow the steps
// *** outlined below.
// ******************************************************************************************

// ******************************************************************************************
// ******************************************************************************************
// ***
// *** Complete Steps 1 through 3 (below) for your project.
// ***
// ******************************************************************************************
// ******************************************************************************************

#if defined(SPARK)
#define word short
#endif

#define DT_BYTE      0
#define DT_CHAR      1
#define DT_BOOL      2
#define DT_SHORT     3
#define DT_WORD      4
#define DT_INT       5
#define DT_LONG      6
#define DT_FLOAT     7
#define DT_DOUBLE    8

#define DT_UBYTE     9
#define DT_UCHAR    10
#define DT_USHORT   11
#define DT_UWORD    12
#define DT_UINT     13
#define DT_ULONG    14

#define DT_UINT8_T  15
#define DT_UINT16_T 16
#define DT_UINT32_T 17
#define DT_UINT64_T 18

#define DT_UINT8_T  19
#define DT_UINT16_T 20
#define DT_UINT32_T 21
#define DT_UINT64_T 22

byte _size[] =
{
  sizeof(byte), sizeof(char), sizeof(bool), sizeof(short), sizeof(word), sizeof(int), sizeof(long), sizeof(float), sizeof(double),
  sizeof(unsigned byte), sizeof(unsigned char), sizeof(unsigned short), sizeof(unsigned word), sizeof(unsigned int), sizeof(unsigned long),
  sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t), sizeof(uint64_t),
  sizeof(int8_t), sizeof(int16_t), sizeof(int32_t), sizeof(int64_t)
};

char* _name[] =
{
  "byte", "char", "bool", "short", "word", "int", "long", "float", "double",
  "unsigned byte", "unsigned char", "unsigned short", "unsigned word", "unsigned int", "unsigned long",
  "uint8_t", "uint16_t", "uint32_t", "uint64_t",
  "int8_t", "int16_t", "int32_t", "int64_t"
};

struct definition
{
  int type;
  int defaultValue;
};

void setup()
{
  // ***
  // *** Initialize the serial port.
  // ***
  Serial.begin(115200);

  // ***
  // *** STEP 1 of 3:
  // ***
  // *** Create a list of definitions that each contain the data type and the default value.
  // ***
  definition myDefinitions[] =
  {
    { DT_INT, 0 },
    { DT_UINT, 0 },
    { DT_ULONG, 0 },
    { DT_FLOAT, 5.5 },
    { DT_DOUBLE, 6.6 },
    { DT_INT, 10 }
  };

  // ***
  // *** STEP 2 of 3:
  // ***
  // *** Define the starting address in EEPROM. If you are manually string other data in EEPROM this
  // *** address could be defined at the end of that data.
  // ***
  int myFirstAddress = 0;

  // ***
  // *** STEP 3 of 3:
  // ***
  // *** Set the value below to true to display comments and false to hide the comments.
  // ***
  bool showComments = true;


  // ******************************************************************************************
  // ******************************************************************************************
  // ***
  // *** This will output declarations through the serial port.
  // ***
  // ******************************************************************************************
  // ******************************************************************************************
  int items = sizeof(myDefinitions) / sizeof(definition);
  Serial.print("The number of declarations defined is "); Serial.println(items);
  Serial.println();
  int nextAddress = myFirstAddress;

  for (int i = 0; i < items; i++)
  {
    if (showComments)
    {
      Serial.println("// ***");
      Serial.print("// *** Total length = "); Serial.print(_size[myDefinitions[i].type] + 1); Serial.print(" [Addresses "); Serial.print(nextAddress); Serial.print(" through "); Serial.print(nextAddress + _size[myDefinitions[i].type]); Serial.println("]");
      Serial.println("// ***");
    }

    Serial.print("EEPROMStorage<"); Serial.print(_name[myDefinitions[i].type]); Serial.print(">("); Serial.print(nextAddress); Serial.print(", "); Serial.print(myDefinitions[i].defaultValue); Serial.println(");");
    if (showComments) Serial.println();

    nextAddress += _size[myDefinitions[i].type] + 1;
  }
}

void loop()
{
  // ***
  // *** Delay 2 seconds.
  // ***
  delay(2000);
}
