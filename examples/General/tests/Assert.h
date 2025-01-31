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
  #include <Arduino.h>
  #include <Arduino_DebugUtils.h>
#elif defined(PARTICLE)
  #include <Particle.h>
#endif

class AssertClass
{
  public:
    bool IsTrue(bool);
    bool IsFalse(bool);
    
    bool AreEqual(bool, bool);
    bool AreEqual(char, char);
    bool AreEqual(unsigned char, unsigned char);
    bool AreEqual(int, int);
    bool AreEqual(unsigned int, unsigned int);
    bool AreEqual(long, long);
    bool AreEqual(unsigned long, unsigned long);
    bool AreEqual(short, short);
    bool AreEqual(unsigned short, unsigned short);
    bool AreEqual(float, float);
    bool AreEqual(double, double);

    bool AreNotEqual(bool, bool);
    bool AreNotEqual(char, char);
    bool AreNotEqual(unsigned char, unsigned char);
    bool AreNotEqual(int, int);
    bool AreNotEqual(unsigned int, unsigned int);
    bool AreNotEqual(long, long);
    bool AreNotEqual(unsigned long, unsigned long);
    bool AreNotEqual(short, short);
    bool AreNotEqual(unsigned short, unsigned short);
    bool AreNotEqual(float, float);
    bool AreNotEqual(double, double);

  protected:
    bool DebugPassFail(bool);
    bool DebugEqualNotEqual(bool, bool, bool);
    bool DebugEqualNotEqual(bool, char, char);
    bool DebugEqualNotEqual(bool, unsigned char, unsigned char);
    bool DebugEqualNotEqual(bool, int, int);
    bool DebugEqualNotEqual(bool, unsigned int, unsigned int);
    bool DebugEqualNotEqual(bool, long, long);
    bool DebugEqualNotEqual(bool, unsigned long, unsigned long);
    bool DebugEqualNotEqual(bool, short, short);
    bool DebugEqualNotEqual(bool, unsigned short, unsigned short);
    bool DebugEqualNotEqual(bool, float, float);
    bool DebugEqualNotEqual(bool, double, double);
};

static AssertClass Assert;
#endif