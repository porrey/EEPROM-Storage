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
        TestDirector<unsigned char> t("unsigned char", address, 0, 255);
        returnValue.add(t.runArithmeticTests());
        returnValue.add(t.runBinaryTests());
      }

      {
        TestDirector<char> t("char", address, 0, 127);
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

      return returnValue;
    }

};

static TestRunnerClass TestRunner;
#endif