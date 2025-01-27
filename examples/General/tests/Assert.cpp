#include "Assert.h"

AssertClass::AssertClass(HardwareSerial* serial)
{
  this->_serial = serial;
};

//
// Boolean
//
bool AssertClass::IsTrue(const bool value)
{
  this->DebugPassFail(value);
  return this->DebugEqualNotEqual(value == true, value, true); 
};

bool AssertClass::IsFalse(const bool value)
{
  this->DebugPassFail(!value);
  return this->DebugEqualNotEqual(value == false, value, false); 
};

//
// Are Equal
//
bool AssertClass::AreEqual(const bool value1, const bool value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const unsigned char value1, const unsigned char value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const char value1, const char value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const int value1, const int value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const unsigned int value1, const unsigned int value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const long value1, const long value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const unsigned long value1, const unsigned long value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const short value1, const short value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const unsigned short value1, const unsigned short value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const float value1, const float value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreEqual(const double value1, const double value2)
{
  this->DebugPassFail(value1 == value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

//
// Are Equal
//
bool AssertClass::AreNotEqual(const bool value1, const bool value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const unsigned char value1, const unsigned char value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const char value1, const char value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const int value1, const int value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const unsigned int value1, const unsigned int value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const long value1, const long value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const unsigned long value1, const unsigned long value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const short value1, const short value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const unsigned short value1, const unsigned short value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const float value1, const float value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

bool AssertClass::AreNotEqual(const double value1, const double value2)
{
  this->DebugPassFail(value1 != value2);
  return this->DebugEqualNotEqual(value1 == value2, value1, value2);
};

//
// Debug
//
bool AssertClass::DebugPassFail(bool value)
{
  this->_serial->print((value ? "-PASSED!" : "-FAILED!"));
  return value;
};

bool AssertClass::DebugEqualNotEqual(bool equal, bool value1, bool value2)
{
  this->_serial->print(" ["); this->_serial->print((value1 ? "true" : "false")); this->_serial->print((equal ? " == " : " != ")); this->_serial->print((value2 ? "true" : "false")); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned char value1, unsigned char value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, char value1, char value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, int value1, int value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned int value1, unsigned int value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, long value1, long value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned long value1, unsigned long value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, short value1, short value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, unsigned short value1, unsigned short value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, float value1, float value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};

bool AssertClass::DebugEqualNotEqual(bool equal, double value1, double value2)
{
  this->_serial->print(" ["); this->_serial->print(value1); this->_serial->print((equal ? " == " : " != ")); this->_serial->print(value2); this->_serial->print("]");
  return equal;
};