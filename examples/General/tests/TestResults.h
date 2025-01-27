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
#ifndef TEST_RESULTS_H
#define TEST_RESULTS_H

//
// Define a complex structure to store in EEPROM.
//
class TestResults
{
    public:
      uint totalTests = 0;
      uint totalPassed = 0;

      void add(TestResults results)
      {
        totalTests += results.totalTests;
        totalPassed += results.totalPassed;
      }

      uint totalFailed()
      {
        return totalTests - totalPassed;
      }
};
#endif