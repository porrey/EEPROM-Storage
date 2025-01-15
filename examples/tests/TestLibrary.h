// Copyright © 2017-2020 Daniel Porrey. All Rights Reserved.
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

//
// Results
//
unsigned int _totalTests = 0;
unsigned int _totalPassed = 0;

void displayTestHeader(String testName)
{
  Serial.print("TEST: ["); Serial.print(testName); Serial.print("]");
  _totalTests++;
}

bool assertIsTrue(const bool item)
{
  bool returnValue = false;

  if (item)
  {
    Serial.print(" -PASSED!");
    returnValue = true;
  }
  else
  {
    Serial.print(" -FAILED!");
  }

  return returnValue;
}

bool assertIsFalse(const bool item)
{
  bool returnValue = false;

  if (!item)
  {
    Serial.print(" -PASSED!");
    returnValue = true;
  }
  else
  {
    Serial.print(" -FAILED!");
  }

  return returnValue;
}

template <typename T> bool assertAreEqual(EEPROMStorage<T> item1, T item2)
{
  bool returnValue = false;

  if (item1.get() == item2)
  {
    Serial.print(" -PASSED!"); Serial.print("  ["); Serial.print(item1.get()); Serial.print(" == "); Serial.print(item2); Serial.print("]");
    returnValue = true;
  }
  else
  {
    Serial.print(" -FAILED!");
    Serial.print("  ["); Serial.print(item1.get()); Serial.print(" != "); Serial.print(item2); Serial.print("]");
  }

  return returnValue;
}

template <typename T> bool assertAreNotEqual(EEPROMStorage<T> item1, T item2)
{
  bool returnValue = false;

  if (item1.get() != item2)
  {
    Serial.print(" -PASSED!"); Serial.print("  ["); Serial.print(item1.get()); Serial.print(" != "); Serial.print(item2); Serial.print("]");
    returnValue = true;
  }
  else
  {
    Serial.print(" -FAILED!");
    Serial.print("  ["); Serial.print(item1.get()); Serial.print(" == "); Serial.print(item2); Serial.print("]");
  }

  return returnValue;
}

template <typename T> void runStandardTests(EEPROMStorage<T> item, long minRandomValue, long maxRandomValue)
{
  //
  // Uninitialize test
  //
  displayTestHeader("Uninitialized");
  item.unset();
  _totalPassed += assertIsFalse(item.isInitialized());
  Serial.println();

  //
  // Initialize test
  //
  {
    displayTestHeader("Initialized Value");
    T initValue = (T)random(minRandomValue, maxRandomValue);
    item = initValue;
    _totalPassed += assertAreEqual(item, initValue);
    Serial.println();

    displayTestHeader("Is Initialized");
    _totalPassed += assertIsTrue(item.isInitialized());
    Serial.println();
  }

  //
  // Addition test
  //
  {
    displayTestHeader("Addition");
    T value = item;
    value = value + (T)5;
    item = item + (T)5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Subtraction test
  //
  {
    displayTestHeader("Subtraction");
    T value = (T)10;
    item = (T)10;
    value = value - (T)5;
    item = item - (T)5;
    _totalPassed += assertAreEqual<T>(item, value);
    Serial.println();
  }

  //
  // Multiplication test
  //
  {
    displayTestHeader("Multiplication");
    T value = (T)10;
    item = (T)10;
    value = value * (T)5;
    item = item * (T)5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Division test
  //
  {
    displayTestHeader("Multiplication");
    T value = (T)10;
    item = (T)10;
    value = value / (T)5;
    item = item / (T)5;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // ++ postfix test
  //
  {
    displayTestHeader("++ postfix");
    T value = (T)60;
    item = (T)60;
    value++;
    item++;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // -- postfix test
  //
  {
    displayTestHeader("-- postfix");
    T value = (T)60;
    item = (T)60;
    value--;
    item--;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // ++ prefix test
  //
  {
    displayTestHeader("++ prefix");
    T value = (T)60;
    item = (T)60;
    ++value;
    ++item;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // -- postfix test
  //
  {
    displayTestHeader("-- prefix");
    T value = (T)60;
    item = (T)60;
    --value;
    --item;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // += test
  //
  {
    displayTestHeader("+=");
    T value = (T)60;
    item = (T)60;
    value += (T)10;
    item += (T)10;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // -= test
  //
  {
    displayTestHeader("-=");
    T value = (T)60;
    item = (T)60;
    value -= (T)10;
    item -= (T)10;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // *= test
  //
  {
    displayTestHeader("*=");
    T value = (T)60;
    item = (T)60;
    value *= (T)10;
    item *= (T)10;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // /= test
  //
  {
    displayTestHeader("/=");
    T value = (T)60;
    item = (T)60;
    value /= (T)30;
    item /= (T)30;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // > test
  //
  {
    displayTestHeader("> x");
    item = 100;
    _totalPassed += assertIsTrue(item > (T)1);
    Serial.println();
  }

  //
  // > test
  //
  {
    displayTestHeader("x >");
    item = (T)100;
    _totalPassed += assertIsTrue((T)101 > item);
    Serial.println();
  }

  //
  // < test
  //
  {
    displayTestHeader("< x");
    item = (T)100;
    _totalPassed += assertIsTrue(item < (T)101);
    Serial.println();
  }

  //
  // > test
  //
  {
    displayTestHeader("x <");
    item = (T)100;
    _totalPassed += assertIsTrue((T)1 < item);
    Serial.println();
  }

  //
  // >= test (different)
  //
  {
    displayTestHeader(">= x (different)");
    item = (T)100;
    _totalPassed += assertIsTrue(item >= (T)1);
    Serial.println();
  }

  //
  // >= test (different)
  //
  {
    displayTestHeader("x >= (different)");
    item = (T)100;
    _totalPassed += assertIsTrue((T)101 >= item);
    Serial.println();
  }

  //
  // <= test (different)
  //
  {
    displayTestHeader("<= x (different)");
    item = (T)100;
    _totalPassed += assertIsTrue(item <= (T)101);
    Serial.println();
  }

  //
  // >= test (different)
  //
  {
    displayTestHeader("x <= (different)");
    item = 100;
    _totalPassed += assertIsTrue((T)1 <= item);
    Serial.println();
  }

  //
  // >= test (same)
  //
  {
    displayTestHeader(">= x (same)");
    item = (T)100;
    _totalPassed += assertIsTrue(item >= (T)100);
    Serial.println();
  }

  //
  // >= test (same)
  //
  {
    displayTestHeader("x >= (same)");
    item = (T)100;
    _totalPassed += assertIsTrue((T)100 >= item);
    Serial.println();
  }

  //
  // <= test (same)
  //
  {
    displayTestHeader("<= x (same)");
    item = (T)100;
    _totalPassed += assertIsTrue(item <= (T)100);
    Serial.println();
  }

  //
  // >= test (same)
  //
  {
    displayTestHeader("x <= (same)");
    item = (T)100;
    _totalPassed += assertIsTrue((T)100 <= item);
    Serial.println();
  }
}

template <typename T> void runAdvancedTests(EEPROMStorage<T> item, long minRandomValue, long maxRandomValue)
{
  //
  // Modulo test
  //
  {
    displayTestHeader("Modulo");
    T value = (T)10;
    item = (T)10;
    value = value % (T)6;
    item = item % (T)6;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // %= test
  //
  {
    displayTestHeader("%=");
    T value = (T)10;
    item = (T)10;
    value %= (T)6;
    item %= (T)6;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // &= test
  //
  {
    displayTestHeader("&=");
    T value = (T)129191;
    item = (T)129191;
    value &= (T)45234;
    item &= (T)45234;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // |= test
  //
  {
    displayTestHeader("|=");
    T value = (T)129191;
    item = (T)129191;
    value &= (T)45234;
    item &= (T)45234;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // == test
  //
  {
    displayTestHeader("==");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // != test
  //
  {
    displayTestHeader("!=");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    _totalPassed += assertAreNotEqual(item, (T)(value + (T)10));
    Serial.println();
  }

  //
  // Bitwise AND (&)
  //
  {
    displayTestHeader("Bitwise AND (&)");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    value = value & 0xAAAA;
    item = item & 0xAAAA;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Bitwise OR (|)
  //
  {
    displayTestHeader("Bitwise OR (|)");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    value = value | 0xAAAA;
    item = item | 0xAAAA;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Bitwise XOR (^)
  //
  {
    displayTestHeader("Bitwise XOR (^)");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    value = value ^ 0xAAAA;
    item = item ^ 0xAAAA;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Bitwise NOT (~)
  //
  {
    displayTestHeader("Bitwise NOT (~)");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    value = ~value;
    item = ~item;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Bitshift Left (<<)
  //
  {
    displayTestHeader("Bitshift Left (<<)");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    value = value << 2;
    item = item << 2;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }

  //
  // Bitshift Right (>>)
  //
  {
    displayTestHeader("Bitshift Right (>>)");
    T value = (T)random(minRandomValue, maxRandomValue);
    item = value;
    value = value >> 2;
    item = item >> 2;
    _totalPassed += assertAreEqual(item, value);
    Serial.println();
  }
}

template <typename T> void testProxyStandard(String typeName, int address, long minRandomValue, long maxRandomValue)
{
  //
  // Run standard tests on data type.
  //
  EEPROMStorage<T> var(address, 0);

  Serial.println("*********************************************");
  Serial.print("Running standard tests on ["); Serial.print(typeName); Serial.println("]");
  Serial.println("*********************************************");

  //
  // Run standard tests.
  //
  runStandardTests<T>(var, minRandomValue, maxRandomValue);

  Serial.println();
}

template <typename T> void testProxyAdvanced(String typeName, int address, long minRandomValue, long maxRandomValue)
{
  //
  // Run advanced tests on data type.
  //
  EEPROMStorage<T> var(address, 0);

  Serial.println("*********************************************");
  Serial.print("Running advanced tests on ["); Serial.print(typeName); Serial.println("]");
  Serial.println("*********************************************");

  //
  // Run standard tests.
  //
  runAdvancedTests<T>(var, minRandomValue, maxRandomValue);

  Serial.println();
}
