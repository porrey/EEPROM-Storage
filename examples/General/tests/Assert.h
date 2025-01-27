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
#ifndef ASSERT_H
#define ASSERT_H

//
// Cross-compatable with Arduino, GNU C++ for tests, and Particle.
//
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#include <EEPROM.h>
#elif defined(SPARK)
#include "Particle.h"
#endif

class AssertClass
{
  public:
    AssertClass(HardwareSerial* serial);
    bool IsTrue(const bool);
    bool IsFalse(const bool);
    
    bool AreEqual(const bool, const bool);
    bool AreEqual(const unsigned char, const unsigned char);
    bool AreEqual(const char, const char);
    bool AreEqual(const int, const int);
    bool AreEqual(const unsigned int, const unsigned int);
    bool AreEqual(const long, const long);
    bool AreEqual(const unsigned long, const unsigned long);
    bool AreEqual(const short, const short);
    bool AreEqual(const unsigned short, const unsigned short);
    bool AreEqual(const float, const float);
    bool AreEqual(const double, const double);

    bool AreNotEqual(const bool, const bool);
    bool AreNotEqual(const unsigned char, const unsigned char);
    bool AreNotEqual(const char, const char);
    bool AreNotEqual(const int, const int);
    bool AreNotEqual(const unsigned int, const unsigned int);
    bool AreNotEqual(const long, const long);
    bool AreNotEqual(const unsigned long, const unsigned long);
    bool AreNotEqual(const short, const short);
    bool AreNotEqual(const unsigned short, const unsigned short);
    bool AreNotEqual(const float, const float);
    bool AreNotEqual(const double, const double);

  protected:
      bool DebugPassFail(bool);
      bool DebugEqualNotEqual(bool, bool, bool);
      bool DebugEqualNotEqual(bool, unsigned char, unsigned char);
      bool DebugEqualNotEqual(bool, char, char);
      bool DebugEqualNotEqual(bool, int, int);
      bool DebugEqualNotEqual(bool, unsigned int, unsigned int);
      bool DebugEqualNotEqual(bool, long, long);
      bool DebugEqualNotEqual(bool, unsigned long, unsigned long);
      bool DebugEqualNotEqual(bool, short, short);
      bool DebugEqualNotEqual(bool, unsigned short,unsigned short);
      bool DebugEqualNotEqual(bool, float, float);
      bool DebugEqualNotEqual(bool, double, double);

  private:
      //
      // A pointer to a serial device. This instance will write all
      // output to this serial device.
      //
      HardwareSerial* _serial;
};

static AssertClass Assert(&Serial);
#endif