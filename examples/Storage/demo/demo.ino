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
// This example demonstrates the usage of the EEPROM-Storage library.
// ---------------------------------------------------------------------------------------

#include <EEPROM-Storage.h>
#include <EEPROM-Display.h>

//
// Create variables to be stored in EEPROM. The first parameter is the
// address or location in EEPROM. The second parameter is the default
// value to return when the variable has not been initialized. Each
// variable requires enough bytes to hold the data type plus one additional
// byte for a checksum.
//
EEPROMStorage<uint32_t> _v1(0, 0);                       // This variable is stored in EEPROM at positions 0, 1, 2, 3 and 4 (5 bytes)
EEPROMStorage<uint32_t> _v2(_v1.nextAddress(), 0);       // This variable is stored in EEPROM at positions 5, 6, 7, 8 and 9 (5 bytes)
EEPROMStorage<float>    _v3(_v2.nextAddress(), 0.0);     // This variable is stored in EEPROM at positions 10, 11, 12, 13 and 14 (5 bytes)
EEPROMStorage<float>    _v4(_v3.nextAddress(), 0.0);     // This variable is stored in EEPROM at positions 15, 16, 17, 18 and 19 (5 bytes)
EEPROMStorage<bool>     _v5(_v4.nextAddress(), false);   // This variable is stored in EEPROM at positions 20 and 21 (2 bytes)

//
// Funtion header
//
void printHeader(String description);
template <typename T> void displayVariableAddress(String name, EEPROMStorage<T> item);
template <typename T> void displayCurrentValue(String name, EEPROMStorage<T> item);
template <typename T> void initializationCheck(String name, EEPROMStorage<T> item, T initValue);
template <typename T> void checksumCheck(String name, EEPROMStorage<T> item);
template <typename T> void operatorCheck(String name, EEPROMStorage<T> item);
template <typename T> void comparisonCheck(String name1, EEPROMStorage<T> item1, String name2, EEPROMStorage<T> item2);
template <typename T> void scopeCheck(String name1, EEPROMStorage<T> item1, String name2, EEPROMStorage<T> item2);
void booleanCheck(String name, EEPROMStorage<bool> item);

void setup()
{
  //
  // Initialize the serial port. On a Particle
  // device the baud rate will be ignored.
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
  // Initialize the random number generator.
  //
  randomSeed(analogRead(0));

  //
  // Clear the contents of EEPROM;
  //
  EEPROMUtil.clearEEPROM();

  //
  // Display the contents of EEPROM;
  //
  EEPROMDisplay.displayEEPROM(); 

  printHeader("\r\nEEPROM Variable Addresses/Locations");
  displayVariableAddress("V1", _v1);
  displayVariableAddress("V2", _v2);
  displayVariableAddress("V3", _v3);
  displayVariableAddress("V4", _v4);
  displayVariableAddress("V5", _v5); DEBUG_INFO("\r\n");

  checksumCheck<uint32_t>("V1", _v1); DEBUG_INFO("\r\n");
  checksumCheck<uint32_t>("V2", _v2); DEBUG_INFO("\r\n");
  checksumCheck<float>("V3", _v3); DEBUG_INFO("\r\n");
  checksumCheck<float>("V4", _v4); DEBUG_INFO("\r\n");
  checksumCheck<bool>("V5", _v5); DEBUG_INFO("\r\n");

  initializationCheck<uint32_t>("V1", _v1, random(0, 0xFFFF)); DEBUG_INFO("\r\n");
  initializationCheck<uint32_t>("V2", _v2, random(0, 0xFFFF)); DEBUG_INFO("\r\n");
  initializationCheck<float>("V3", _v3, random(0, 0xFFFFFF) / 100.0); DEBUG_INFO("\r\n");
  initializationCheck<float>("V4", _v4, random(0, 0xFFFFFF) / 100.0); DEBUG_INFO("\r\n");
  initializationCheck<bool>("V5", _v5, true);

  operatorCheck<uint32_t>("V1", _v1); DEBUG_INFO("\r\n");
  operatorCheck<uint32_t>("V2", _v2); DEBUG_INFO("\r\n");
  operatorCheck<float>("V3", _v3); DEBUG_INFO("\r\n");
  operatorCheck<float>("V4", _v4); DEBUG_INFO("\r\n");

  comparisonCheck<uint32_t>("V1", _v1, "V2", _v2); DEBUG_INFO("\r\n");
  comparisonCheck<float>("V3", _v3, "V4", _v4); DEBUG_INFO("\r\n");

  checksumCheck<uint32_t>("V1", _v1); DEBUG_INFO("\r\n");
  checksumCheck<uint32_t>("V2", _v2); DEBUG_INFO("\r\n");
  checksumCheck<float>("V3", _v3); DEBUG_INFO("\r\n");
  checksumCheck<float>("V4", _v4); DEBUG_INFO("\r\n");
  checksumCheck<bool>("V5", _v5); DEBUG_INFO("\r\n");

  booleanCheck("V5", _v5); DEBUG_INFO("\r\n");

  //
  // Demonstrates a local variable taking on the value
  // of a previously defined global variable. This one
  // will use the same address as _v4. Note the same data
  // type must be used or we will get unexpected values.
  //
  EEPROMStorage<float> v6(_v4.get(), 0.0);
  scopeCheck("V6", v6, "V4", _v4);

  printHeader("EEPROM Contents (" + String(EEPROM.length()) + " bytes)");
  EEPROMDisplay.displayEEPROM();
}

void loop()
{
}

void printHeader(String description)
{
  DEBUG_INFO("***");
  Serial.print("*** "); DEBUG_INFO(description);
  DEBUG_INFO("***");
}

template <typename T> void displayVariableAddress(String name, EEPROMStorage<T> item)
{
  Serial.print("The EEPROM start address for "); Serial.print(name); Serial.print(" is "); Serial.print(item.getAddress());
  Serial.print(" [length = "); Serial.print(item.length()); Serial.print(" byte(s); end address is "); Serial.print(item.getAddress() + item.length() - 1);
  DEBUG_INFO("].");
}

template <typename T> void displayCurrentValue(String name, EEPROMStorage<T> item)
{
  Serial.print("The current value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO(".");
}

template <typename T> void checksumCheck(String name, EEPROMStorage<T> item)
{
  printHeader("Checksum Check for " + name);
  displayCurrentValue<T>(name, item);

  T value = item.get();

  byte checksum1 = Checksum<T>::get(value);
  Serial.print("The Calculated checksum for the value "); Serial.print(value); Serial.print(" is "); EEPROMDisplay.displayPaddedHexByte(checksum1); DEBUG_INFO(".");

  byte checksum2 = item.checksum();
  Serial.print("The Calculated checksum for the variable "); Serial.print(name); Serial.print(" is "); EEPROMDisplay.displayPaddedHexByte(checksum2); DEBUG_INFO(".");

  byte checksum3 = item.checksumByte();
  Serial.print("The Stored checksum for the variable "); Serial.print(name); Serial.print(" is "); EEPROMDisplay.displayPaddedHexByte(checksum3); DEBUG_INFO(".");
  Serial.print("The Stored checksum for the variable "); Serial.print(name); Serial.print(" is at address "); Serial.print(item.checksumAddress()); DEBUG_INFO(".");
}

template <typename T> void initializationCheck(String name, EEPROMStorage<T> item, T initValue)
{
  printHeader("Initialization Check for " + name);

  if (item.isInitialized())
  {
    Serial.print("The variable "); Serial.print(name); DEBUG_INFO(" IS initialized.");
    displayCurrentValue<T>(name, item);

    //
    // Change the variable value.
    //
    Serial.print("Changing variable "); Serial.print(name); Serial.print(" to "); Serial.print(initValue); DEBUG_INFO(".");
    item = initValue;
  }
  else
  {
    Serial.print("The variable "); Serial.print(name); DEBUG_INFO(" is NOT initialized.");

    //
    // The default will match the value specified in the constructor.
    //
    Serial.print("The default value is "); Serial.print(item); DEBUG_INFO(".");

    //
    // Initialize the variable value.
    //
    Serial.print("Initializing variable "); Serial.print(name); Serial.print(" to "); Serial.print(initValue); DEBUG_INFO(".");
    item = initValue;
  }

  displayCurrentValue<T>(name, item);
}

template <typename T> void operatorCheck(String name, EEPROMStorage<T> item)
{
  printHeader("Operator Check for " + name);
  displayCurrentValue<T>(name, item);

  DEBUG_INFO("operator: ++ (postfix)");
  item++;
  Serial.print("The new value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO("."); DEBUG_INFO("\r\n");

  DEBUG_INFO("operator: -- (postfix)");
  item--;
  Serial.print("The new value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO("."); DEBUG_INFO("\r\n");

  DEBUG_INFO("operator: ++ (prefix)");
  ++item;
  Serial.print("The new value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO("."); DEBUG_INFO("\r\n");

  DEBUG_INFO("operator: -- (prefix)");
  --item;
  Serial.print("The new value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO("."); DEBUG_INFO("\r\n");

  T addValue = random(0, 51);
  Serial.print("operator: += "); Serial.print(addValue); DEBUG_INFO(".");
  item += addValue;
  Serial.print("The new value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO("."); DEBUG_INFO("\r\n");

  T minusValue = random(0, 51);
  Serial.print("operator: += "); Serial.print(minusValue); DEBUG_INFO(".");
  item -= minusValue;
  Serial.print("The new value of "); Serial.print(name); Serial.print(" is "); Serial.print(item); DEBUG_INFO(".");
}

template <typename T> void comparisonCheck(String name1, EEPROMStorage<T> item1, String name2, EEPROMStorage<T> item2)
{
  printHeader("Comparison Check between " + name1 + " [" + String(item1) + "] and " + name2 + " [" + String(item2) + "]");
  displayCurrentValue<T>(name1, item1);
  displayCurrentValue<T>(name2, item2);

  //
  // Greater than
  //
  if (item1 > item2)
  {
    Serial.print(name1); Serial.print(" is GREATER THAN "); Serial.print(name2); DEBUG_INFO(".");
  }
  else
  {
    Serial.print(name2); Serial.print(" is GREATER THAN "); Serial.print(name1); DEBUG_INFO(".");
  }

  //
  // Less than
  //
  if (item1 < item2)
  {
    Serial.print(name1); Serial.print(" is LESS THAN "); Serial.print(name2); DEBUG_INFO(".");
  }
  else
  {
    Serial.print(name2); Serial.print(" is LESS THAN "); Serial.print(name1); DEBUG_INFO(".");
  }

  //
  // Greater than or equal to
  //
  if (item1 >= item2)
  {
    Serial.print(name1); Serial.print(" is GREATER THAN or EQUAL TO "); Serial.print(name2); DEBUG_INFO(".");
  }
  else
  {
    Serial.print(name2); Serial.print(" is GREATER THAN or EQUAL TO "); Serial.print(name1); DEBUG_INFO(".");
  }

  //
  // Less than or equal to
  //
  if (item1 < item2)
  {
    Serial.print(name1); Serial.print(" is LESS THAN or EQUAL TO "); Serial.print(name2); DEBUG_INFO(".");
  }
  else
  {
    Serial.print(name2); Serial.print(" is LESS THAN or EQUAL TO "); Serial.print(name1); DEBUG_INFO(".");
  }

  //
  // Equal to
  //
  if (item1 == item2)
  {
    Serial.print(name1); Serial.print(" is EQUAL TO "); Serial.print(name2); DEBUG_INFO(".");
  }
  else
  {
    Serial.print(name1); Serial.print(" is NOT EQUAL TO "); Serial.print(name2); DEBUG_INFO(".");
  }
}

void booleanCheck(String name, EEPROMStorage<bool> item)
{
  printHeader("Boolean Check for " + name);
  displayCurrentValue<bool>(name, item);

  DEBUG_INFO("Setting value to true.");
  item = true;
  displayCurrentValue<bool>(name, item);

  DEBUG_INFO("Setting value to false.");
  item = false;
  displayCurrentValue<bool>(name, item);

  DEBUG_INFO("Toggling value.");
  item = !item;
  displayCurrentValue<bool>(name, item);

  DEBUG_INFO("Toggling value again.");
  item = !item;
  displayCurrentValue<bool>(name, item);
}

template <typename T> void scopeCheck(String name1, EEPROMStorage<T> item1, String name2, EEPROMStorage<T> item2)
{
  printHeader("Scope Check between " + name1 + " and " + name2);

  if (item1.getAddress() == item2.getAddress())
  {
    Serial.print("The variable "); Serial.print(name1); Serial.print(" has the same address as the variable "); Serial.print(name2); DEBUG_INFO(".");
    Serial.print("The EEPROM storage address is "); Serial.print(item1.getAddress()); DEBUG_INFO(".");

    Serial.print("The variable "); Serial.print(name2); if (item2.isInitialized()) DEBUG_INFO(" IS initialized."); else DEBUG_INFO(" is NOT initialized.");
    displayCurrentValue<float>(name2, item2);
    Serial.print("The variable "); Serial.print(name1); if (item1.isInitialized()) DEBUG_INFO(" IS initialized."); else DEBUG_INFO(" is NOT initialized.");
    displayCurrentValue<float>(name1, item1);

    float value = random(0, 0xFFFFFF) / 100.0;
    Serial.print("Setting "); Serial.print(name1); Serial.print(" to "); Serial.print(value); DEBUG_INFO(".");
    item1 = value;

    displayCurrentValue<float>(name1, item1);
    displayCurrentValue<float>(name2, item2);
  }
  else
  {
    Serial.print("The variable "); Serial.print(name1); Serial.print(" DOES NOT has the same address as the variable "); Serial.print(name2); DEBUG_INFO(".");
    Serial.print("The EEPROM storage address for "); Serial.print(name1); Serial.print(" is "); Serial.print(item1.getAddress()); DEBUG_INFO(".");
    Serial.print("The EEPROM storage address for "); Serial.print(name2); Serial.print(" is "); Serial.print(item2.getAddress()); DEBUG_INFO(".");
  }

  DEBUG_INFO("\r\n");
}