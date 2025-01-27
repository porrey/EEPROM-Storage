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
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "TestDirector.h"

class TestRunnerClass
{
  public:
    TestResults runAll(uint address)
    {
      TestResults returnValue;

      //
      // Run predefined tests.
      //
      {
        TestDirector<bool> t("bool", address, 0, 1);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<char> t("char", address, 0, 127);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<unsigned char> t("unsigned char", address, 0, 255);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<int> t("int", address, -15000, 15000);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<unsigned int> t("unsigned int", address, 0, 15000);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<long> t("long", address, -150000, 150000);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<unsigned long> t("unsigned long", address, 0, 150000);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<short> t("short", address, -15000, 15000);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<unsigned short> t("unsigned short", address, -15000, 15000);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<float> t("float", address, -150000, 150000);
        returnValue.add(t.runArithmeticTests());
      }

      {
        TestDirector<double> t("double", address, -150000, 150000);
        returnValue.add(t.runArithmeticTests());
      }

      //
      // Test the int types for completeness.
      //
      {
        TestDirector<int8_t> t("int8_t", address, -100, 100);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<uint8_t> t("uint8_t", address, 0, 200);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<int16_t> t("int16_t", address, -9999, 9999);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<uint16_t> t("uint16_t", address, 0, 19998);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<int32_t> t("int32_t", address, -199999, 199999);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<uint32_t> t("uint32_t", address, 0, 399998);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      return returnValue;
    }

};

static TestRunnerClass TestRunner;
#endif