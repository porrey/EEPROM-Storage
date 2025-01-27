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
    TestDirector(String typeName, uint address, T minValue, T maxValue)
    {
      this->_typeName = typeName;
      this->_address = address;
      this->_minValue = minValue;
      this->_maxValue = maxValue;
    }

    TestResults runArithmeticTests()
    {
      Serial.println("-----------------------------------------------------------------------------------------------------------------------------");
      Serial.print("Running Arithmetic tests on Type ");
      Serial.print(this->_typeName);
      Serial.println(".");
      Serial.println("-----------------------------------------------------------------------------------------------------------------------------");
    
      {
        InitializationTest<int> t("Initialization", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        AdditionTest<int> t("+", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        SubtractionTest<int> t("-", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        MultiplicationTest<int> t("*", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        DivisionTest<int> t("/", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        IncrementPostfixTest<int> t("x++", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        IncrementPrefixTest<int> t("++x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        PlusEqualTest<int> t("+=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        MinusEqualTest<int> t("-=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        MultiplyEqualTest<int> t("*=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        DivideEqualTest<int> t("/=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        GreaterThanValueTest<int> t("> x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        GreaterThanVariableTest<int> t("x >", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanValueTest<int> t("< x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanVariableTest<int> t("x <", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

     {
        GreaterThanOrEqualToValueTest<int> t(">= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        GreaterThanOrEqualToVariableTest<int> t("x >=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanOrEqualToValueTest<int> t("<= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LessThanOrEqualToVariableTest<int> t("x <=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        EqualityTest<int> t("==", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        NotEqualityTest<int> t("!=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      Serial.println();
      return this->_testResults;
    }

    TestResults runBinaryTests()
    {
      Serial.println("-----------------------------------------------------------------------------------------------------------------------------");
      Serial.print("Running binary tests on Type ");
      Serial.print(this->_typeName);
      Serial.println(".");
      Serial.println("-----------------------------------------------------------------------------------------------------------------------------");
    
      {
        ModuloTest<int> t("%", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        ModuloEqualTest<int> t("%=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseAndTest<int> t("&", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseAndEqualTest<int> t("&=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseOrTest<int> t("|", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseOrEqualTest<int> t("|=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseXorTest<int> t("^", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseXorEqualTest<int> t("^=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        BitwiseNotTest<int> t("~", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LeftShiftTest<int> t("<<", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        LeftShiftEqualTest<int> t("<<=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        RightShiftTest<int> t(">>", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      {
        RightShiftEqualTest<int> t(">>=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += t.totalTests();
        this->_testResults.totalPassed += t.runOnce();
      }

      Serial.println();
      return this->_testResults;
    }

  protected:
    String _typeName;
    uint _address;
    T _minValue;
    T _maxValue;
    TestResults _testResults;
};
#endif