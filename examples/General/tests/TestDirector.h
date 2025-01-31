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
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      DEBUG_INFO("Running Arithmetic tests on Type %s.", this->_typeName);
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
    
      {
        InitializationTest<T> t("Initialization", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        AdditionTest<T> t("+", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        SubtractionTest<T> t("-", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        MultiplicationTest<T> t("*", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        DivisionTest<T> t("/", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        IncrementPostfixTest<T> t("x++", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        IncrementPrefixTest<T> t("++x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        PlusEqualTest<T> t("+=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        MinusEqualTest<T> t("-=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        MultiplyEqualTest<T> t("*=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        DivideEqualTest<T> t("/=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        GreaterThanValueTest<T> t("> x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        GreaterThanVariableTest<T> t("x >", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanValueTest<T> t("< x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanVariableTest<T> t("x <", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

     {
        GreaterThanOrEqualToValueTest<T> t(">= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        GreaterThanOrEqualToVariableTest<T> t("x >=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanOrEqualToValueTest<T> t("<= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanOrEqualToVariableTest<T> t("x <=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        EqualityTest<T> t("==", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        NotEqualityTest<T> t("!=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      DEBUG_INFO("");
      return this->_testResults;
    }

    TestResults runBinaryTests()
    {
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      DEBUG_INFO("Running Binary tests on Type %s.", this->_typeName);
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
    
      {
        ModuloTest<T> t("%", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        ModuloEqualTest<T> t("%=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseAndTest<T> t("&", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseAndEqualTest<T> t("&=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseOrTest<T> t("|", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseOrEqualTest<T> t("|=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseXorTest<T> t("^", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseXorEqualTest<T> t("^=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseNotTest<T> t("~", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LeftShiftTest<T> t("<<", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LeftShiftEqualTest<T> t("<<=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        RightShiftTest<T> t(">>", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        RightShiftEqualTest<T> t(">>=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      DEBUG_INFO("");
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