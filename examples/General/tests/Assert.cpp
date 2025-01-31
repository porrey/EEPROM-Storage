#include "Assert.h"

//
// Boolean
//
bool AssertClass::IsTrue(bool value)
{
  this->DebugPassFail(value);
  return this->DebugEqualNotEqual(value, value, (bool)true); 
};

bool AssertClass::IsFalse(bool value)
{
  this->DebugPassFail(!value);
  return this->DebugEqualNotEqual(!value, value, (bool)false); 
};

//
// Are Equal
//
bool AssertClass::AreEqual(bool value1, bool value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(unsigned char value1, unsigned char value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(char value1, char value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(int value1, int value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(unsigned int value1, unsigned int value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(long value1, long value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(unsigned long value1, unsigned long value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(short value1, short value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(unsigned short value1, unsigned short value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(float value1, float value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(double value1, double value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

//
// Are Equal
//
bool AssertClass::AreNotEqual(bool value1, bool value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(unsigned char value1, unsigned char value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(char value1, char value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(int value1, int value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(unsigned int value1, unsigned int value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(long value1, long value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(unsigned long value1, unsigned long value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(short value1, short value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(unsigned short value1, unsigned short value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(float value1, float value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(double value1, double value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

//
// Debug
//
bool AssertClass::DebugPassFail(bool value)
{
  DEBUG_INFO((value ? "\tPASSED" : "\tFAILED"));
  return value;
};

bool AssertClass::DebugEqualNotEqual(bool equal, bool value1, bool value2)
{
  DEBUG_INFO("\t[%s %s %s]", (value1 ? "true" : "false"), (equal ? " == " : " != "), (value2 ? "true" : "false"));
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, char value1, char value2)
{
  DEBUG_INFO("\t[%c %s %c]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned char value1, unsigned char value2)
{
  DEBUG_INFO("\t[%c %s %c]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, int value1, int value2)
{
  DEBUG_INFO("\t[%d %s %d]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned int value1, unsigned int value2)
{
  DEBUG_INFO("\t[%u %s %u]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, long value1, long value2)
{
  DEBUG_INFO("\t[%d %s %d]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned long value1, unsigned long value2)
{
  DEBUG_INFO("\t[%u %s %u]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, short value1, short value2)
{
  DEBUG_INFO("\t[%d %s %d]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned short value1, unsigned short value2)
{
  DEBUG_INFO("\t[%u %s %u]", value1, (equal ? " == " : " != "), value2);
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, float value1, float value2)
{
  #if defined(PARTICLE)
    DEBUG_INFO("\t[%.2f %.2f %.2f]", value1, (equal ? " == " : " != "), value2);
  #elif defined(ARDUINO) && ARDUINO >= 100
    char buffer1[11];
    dtostrf(value1, 6, 2, buffer1);

    char buffer2[11];
    dtostrf(value2, 6, 2, buffer2);

    DEBUG_INFO("\t[%s %s %s]", buffer1, (equal ? " == " : " != "), buffer2);
  #endif

  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, double value1, double value2)
{
  #if defined(PARTICLE)
    DEBUG_INFO("\t[%.2f %.2f %.2f]", value1, (equal ? " == " : " != "), value2);
  #elif defined(ARDUINO) && ARDUINO >= 100
    char buffer1[11];
    dtostrf(value1, 6, 2, buffer1);

    char buffer2[11];
    dtostrf(value2, 6, 2, buffer2);

    DEBUG_INFO("\t[%s %s %s]", buffer1, (equal ? " == " : " != "), buffer2);
  #endif

  return equal;
};