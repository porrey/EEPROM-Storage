[![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/porrey/EEPROM-Storage/.github/workflows/arduino-mega-2560-build.yml?style=for-the-badge&label=Arduino%20Mega%202560%20Build&logo=github)](https://github.com/porrey/EEPROM-Storage/actions/workflows/arduino-mega-2560-build.yml)
[![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/porrey/EEPROM-Storage/.github/workflows/arduino-uno-r4-build.yml?style=for-the-badge&label=Arduino%20Uno%20R4%20Build&logo=github)](https://github.com/porrey/EEPROM-Storage/actions/workflows/arduino-uno-r4-build.yml)
[![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/porrey/EEPROM-Storage/.github/workflows/arduino-esp8266-build.yml?style=for-the-badge&label=Arduino%20ESP8266%20Build&logo=github)](https://github.com/porrey/EEPROM-Storage/actions/workflows/arduino-esp8266-build.yml)
[![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/porrey/EEPROM-Storage/.github/workflows/particle-build.yml?style=for-the-badge&label=Particle%20Build&logo=github)](https://github.com/porrey/EEPROM-Storage/actions/workflows/particle-build.yml)
[![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/porrey/EEPROM-Storage/.github/workflows/arduino-lint.yml?style=for-the-badge&label=Arduino%20Lint&logo=github)](https://github.com/porrey/EEPROM-Storage/actions/workflows/arduino-lint.yml)

[![GitHub release](https://img.shields.io/github/v/release/porrey/EEPROM-Storage?style=for-the-badge&label=Latest%20Release&branch=master&logo=github)](https://github.com/porrey/EEPROM-Storage/releases/)
![GitHub license](https://img.shields.io/github/license/porrey/EEPROM-Storage.svg?style=for-the-badge&logo=github)
![GitHub issues](https://img.shields.io/github/issues/porrey/EEPROM-Storage.svg?style=for-the-badge&logo=github)
[![Custom Badge](https://img.shields.io/badge/Library-Documentation-purple?style=for-the-badge&logo=github)](https://porrey.github.io/EEPROM-Storage)

# EEPROM-Storage Library
## Overview
The EEPROM Storage library provides the ability to access variables stored in EEPROM just as if they were stored in normal RAM.

Detailed library class and code documentation can be found here: <a href="https://porrey.github.io/EEPROM-Storage" target="_blank">View Documentation</a> [*Ctrl+Click (Windows/Linux) or Cmd+Click (Mac) to open in a new tab*].


## EEPROMStorage\<T\> vs EEPROMCache\<T\>
There are two classes that provide the similar access to EEEPROM. The first is the Direct Storage class which reads and writes to directly to and from EEPROM. The second is the Cache Access which reads and writes from memory and writes to the EEPROM when directed.

Other than the `restore()` and `commit()` (*see description below*) methods on the cache based class, these objects can be used interchangeably.

### Direct Storage (EEPROMStorage\<T\>)
This class writes directly to the EEPROM whenever the variable value is updated and reads directly from EEPROM when the variable value is accessed.

Within the library, examples of how to use this type of access can be found in the **Storage** folder under **Examples**.

### Cached Access (EEPROMCache\<T\>)
This class reads and writes the variable value from RAM and only updates the value from EEPROM when `restore()` is called. Subsequently it only writes to EEPROM when `commit()` is called.

Within the library, examples of how to use this type of access can be found in the **Cache** folder under **Examples**.

## General Usage
Once defined, a variable can be used in in the same manner as its underlying type. For example, a variable defined as an integer (int) would be defined as follows:

    int i = 0;

Throughout the code this variable can be read and written in various ways. For example, to increment the variable, we would use the statement

    i++;

To set the value to a specific value we would, for example, use the statement

    i = 12;

This is all standard coding to even the novice programmer but is used here to show the simplicity of the EEPROM Storage/Cache class. An integer variable stored in EEPROM would be defined in the following manner:

    EEPROMStorage<int> i(0, 0);
    
or

	EEPROMCache<int> i(0, 0);

where the first parameter of the constructor defines the address of the variable in EEPROM, and the second parameter defines the default value.

After the definition, the variable `i` can be used in the same manner, `i++` and `i = 12` will work the same way they did before, but now the value is stored and retrieved to and from EEPROM.

## EEPROM Address
### Memory Requirement
---
When defining an EEPROM Storage variable, it is important to understand the number of bytes required for the underlying type and ensuring that the variables are spaced appropriately so they do not collide.

Each variable requires enough memory to store the underlying type plus one additional byte for a checksum.

Consider the following variable definitions.

	EEPROMStorage<uint8_t> v1(0, 0);	// 2 bytes (1 + 1 checksum), positions 0 and 1
	EEPROMStorage<uint16_t> v2(2, 0);	// 3 bytes (2 + 1 checksum), positions 2, 3 and 4
	EEPROMStorage<uint32_t> v3(5, 0);	// 5 bytes (4 + 1 checksum), positions 5, 6, 6, 8 and 9
	EEPROMStorage<float> v4(10, 0.0);	// 5 bytes (4 + 1 checksum), positions 10, 11, 12, 13 and 14
	EEPROMStorage<bool> v5(15, false);	// 2 bytes (1 + 1 checksum), positions 15, 16, 17, 18 and 19

The best way to think about EEPROM memory is to think about it as a large byte array with a base index of 0. In fact, the Arduino libraries construct access to EEPROM in this manner. 

In the above definitions, `v1` is stored at position 0 and occupies two bytes. The first byte is for the data type and the second byte is for the one-byte checksum. The variable `v1` requires two bytes and thus occupies EEPROM memory locations 0 and 1,

The next variable, `v2`, is in the position 2, immediately following `v1`, and occupies three bytes. The variables `v3`, `v4` and `v5` follow in the same contiguous manner, ensuring that no two variables occupy the same memory positions.

> Aligning variables at the beginning of memory or aligning them in a contiguous nature is not required. This just makes it easier, in my opinion, to keep track. You are free to arrange them in any manner that suits your needs.

If you need help determining the proper address for your `EEPROMStorage` instances, open the example sketch called **address.ino** and follow the instructions.

Using the nextAddress() method will make it easier to align your variables in memory.

	EEPROMStorage<uint8_t> v1(0, 0);			// 2 bytes (1 + 1 checksum), positions 0 and 1
	EEPROMStorage<uint16_t> v2(v1.nextAddress(), 0);	// 3 bytes (2 + 1 checksum), positions 2, 3 and 4
	EEPROMStorage<uint32_t> v3(v2.nextAddress(), 0);	// 5 bytes (4 + 1 checksum), positions 5, 6, 6, 8 and 9
	EEPROMStorage<float> v4(v3.nextAddress(), 0.0);		// 5 bytes (4 + 1 checksum), positions 10, 11, 12, 13 and 14
	EEPROMStorage<bool> v5(v4.nextAddress(), false);	// 2 bytes (1 + 1 checksum), positions 15, 16, 17, 18 and 19

### Determining Data Type Size ###
---
If you are not sure of the memory requirement for a given data type, you can use the `sizeof` operator. User the Serial port to display the size of any data type.

    Serial.print("The size of int is "); Serial.print(sizeof(int)); DEBUG_INFO(".");

When using the `sizeof` operator to determine the number of bytes to preserve remember to add one extra byte for the **checksum**.

To see a full demonstration of this, open the example sketch called **sizeof.ino**.

## EEPROM Storage Initialization
When data has never been stored EEPROM on a micro-controller the memory is in an uninitialized state. Since each byte of memory must have a value between 0 and 255, it is not always possible to detect an uninitialized byte. This behavior could have unexpected side effects if you define a variable and fail to detect whether the instance has been initialized.

For this reason, the EEPROM Storage library uses a one-byte checksum to determine if the instance has been initialized or not. When an instance is constructed, a default value is specified. This default value is always returned until a value is set thus initializing the location. Each write operation to EEPROM will update the checksum.

## Scope
It is important to note that since `EEPROMStorage` variables are in fact, stored in the Micro-controllers EEPROM, the scope of these variables is always global. In fact it is possible to instantiate more than one instance using the same address that as a result will keep the two instances in sync.

> The `EEPROMStorage` variable never caches the value internally and will read the value from EEPROM each time it is requested. Similarly, each time the instance value is updated it is written directly to EEPROM.

# Usage
## Declaration
An instance of `EEPROMStorage` can be declared globally, within a class or within a function keeping in mind, as stated previously, that the address controls whether two or more instances share the same value.

The syntax for declaration is as follows:

    EEPROMStorage<data type> variableName(address, default value);

### Data Type
---
Specifies the underlying data type for the given instance.

### Address
---
Specifies the starting index in EEPROM where the value will be stored.

### Default Value
---
Specifies the value that will be returned by the instance when the EEPROM memory location has not been initialized (initialization is determined by the checksum).

### Example
---
To initialize an instance with an underlying data type of int located in position 50 of the EEPROM and a default value of 10, the syntax would be as follows:

	EEPROMStorage<int> myInt(50, 10);

## Assignment
Using the previous example, assigning a value to the instance is as simple as the assignment shown here.

	myInt = 100; 

The `EEPROMStorage` class also defines a `set()` method that can be used.

	myInt.set(100);

## Retrieving
To get the instance value, simply assign it to a variable, as shown below,

	int x = myInt;

or pass it as an argument in any function that takes an int argument as shown below.

	Serial.print("myInt = "); DEBUG_INFO(myInt);

The `EEPROMStorage` class also defines a `get()` method that can be used.

	int x = myInt.get();

## Platform/Boards Used in Testing
The library was compiled and uploaded to the boards listed below for testing.

1. Arduino on Mega 2560
2. Arduino on ESP8266 [ESPino (ESP-12 Module)]
3. Particle on Argon with OS version 6.2.1
4. Particle on Photon with OS version 3.3.1
5. Particle on Electron with OS version 3.3.1

## 💖 Support This Project

Hey there! If you find this project useful, consider supporting its development. Your contributions help keep this project alive, improve features, and ensure regular updates.

### 🚀 How You Can Help
- ⭐ Star this repository – It helps others discover the project!

- 💵 Sponsor on GitHub Sponsors – Recurring support keeps the project sustainable.

- ☕ Buy Me a Coffee – One-time support via Buy Me a Coffee.

- 💳 PayPal Donations – Direct support via PayPal.

- 🏢 Business Support – If your company uses this project, consider a sponsorship.

Your support means a lot and helps me continue improving this project. Thank you! ❤️

## LICENSE
*Licensed under the LGPL-3.0 license*

*Copyright 2017-2025 Daniel Porrey*
