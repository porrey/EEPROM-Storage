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
#include <EEPROM-Debug.h>

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
        InitializationTest<T> test("Initialization", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        AdditionTest<T> test("+", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        SubtractionTest<T> test("-", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        MultiplicationTest<T> test("*", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        DivisionTest<T> test("/", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }
      
      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        IncrementPostfixTest<T> test("x++", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        IncrementPrefixTest<T> test("++x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        PlusEqualTest<T> test("+=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        MinusEqualTest<T> test("-=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        MultiplyEqualTest<T> test("*=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        DivideEqualTest<T> test("/=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        GreaterThanValueTest<T> test("> x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        GreaterThanVariableTest<T> test("x >", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        LessThanValueTest<T> test("< x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        LessThanVariableTest<T> test("x <", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        GreaterThanOrEqualToValueTest<T> test(">= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        GreaterThanOrEqualToVariableTest<T> test("x >=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        LessThanOrEqualToValueTest<T> test("<= x", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        LessThanOrEqualToVariableTest<T> test("x <=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        EqualityTest<T> test("==", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

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
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      DEBUG_INFO("Running Binary tests on Type %s.", this->_typeName);
      DEBUG_INFO("-----------------------------------------------------------------------------------------------------------------------------");
      
      {
        ModuloTest<T> test("%", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        ModuloEqualTest<T> test("%=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseAndTest<T> test("&", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseAndEqualTest<T> test("&=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseOrTest<T> test("|", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseOrEqualTest<T> test("|=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseXorTest<T> test("^", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseXorEqualTest<T> test("^=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        BitwiseNotTest<T> test("~", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        LeftShiftTest<T> test("<<", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        LeftShiftEqualTest<T> test("<<=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        RightShiftTest<T> test(">>", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
      }

      #if defined(PARTICLE)
      Particle.process();
      #endif

      {
        RightShiftEqualTest<T> test(">>=", this->_address, this->_minValue, this->_maxValue);
        this->_testResults.totalTests += test.totalTests();
        this->_testResults.totalPassed += test.runOnce();
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