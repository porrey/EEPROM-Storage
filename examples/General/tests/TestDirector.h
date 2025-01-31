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
#ifndef TEST_DIRECTOR_H
#define TEST_DIRECTOR_H

#include "TestResults.h"
#include "ArithmeticTests.h"
#include "BinaryTests.h"

template <typename T>
class TestDirector
{
  public:
    TestDirector(const char* typeName, uint address, T minValue, T maxValue)
    {
      this->_typeName = typeName;
      this->_address = address;
      this->_minValue = minValue;
      this->_maxValue = maxValue;
    }

    TestResults runArithmeticTests()
    {
      #if defined(ARDUINO) && ARDUINO >= 100
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      DEBUG_INFO("Running Arithmetic tests on Type %s.", this->_typeName);
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      #endif

      {
        InitializationTest<T> test("Initialization", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        AdditionTest<T> test("+", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        SubtractionTest<T> test("-", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        MultiplicationTest<T> test("*", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        DivisionTest<T> test("/", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        IncrementPostfixTest<T> test("x++", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        IncrementPrefixTest<T> test("++x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        PlusEqualTest<T> test("+=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        MinusEqualTest<T> test("-=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        MultiplyEqualTest<T> test("*=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        DivideEqualTest<T> test("/=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        GreaterThanValueTest<T> test("> x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        GreaterThanVariableTest<T> test("x >", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        LessThanValueTest<T> test("< x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        LessThanVariableTest<T> test("x <", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

     {
        GreaterThanOrEqualToValueTest<T> test(">= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        GreaterThanOrEqualToVariableTest<T> test("x >=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        LessThanOrEqualToValueTest<T> test("<= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        LessThanOrEqualToVariableTest<T> test("x <=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        EqualityTest<T> test("==", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        NotEqualityTest<T> test("!=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(ARDUINO) && ARDUINO >= 100
      DEBUG_INFO("");
      #endif

      return this->_testResults;
    }

    TestResults runBinaryTests()
    {
      #if defined(ARDUINO) && ARDUINO >= 100
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      DEBUG_INFO("Running Binary tests on Type %s.", this->_typeName);
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      #endif

      {
        ModuloTest<T> test("%", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        ModuloEqualTest<T> test("%=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseAndTest<T> test("&", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseAndEqualTest<T> test("&=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseOrTest<T> test("|", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseOrEqualTest<T> test("|=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseXorTest<T> test("^", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseXorEqualTest<T> test("^=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        BitwiseNotTest<T> test("~", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        LeftShiftTest<T> test("<<", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        LeftShiftEqualTest<T> test("<<=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        RightShiftTest<T> test(">>", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      {
        RightShiftEqualTest<T> test(">>=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(ARDUINO) && ARDUINO >= 100
      DEBUG_INFO("");
      #endif
      
      return this->_testResults;
    }

  protected:
    const char* _typeName;
    uint _address;
    T _minValue;
    T _maxValue;
    TestResults _testResults;
};
#endif