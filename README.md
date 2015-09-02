# NMEAParser

## Build Status

| master | develop |
| ------ | ------- |
| [![Build Status](https://travis-ci.org/NeuralSandwich/NMEAParser.svg?branch=master)](https://travis-ci.org/NeuralSandwich/NMEAParser) | [![Build Status](https://travis-ci.org/NeuralSandwich/NMEAParser.svg?branch=develop)](https://travis-ci.org/NeuralSandwich/NMEAParser) | 

Library for parsing NMEA data strings

## Building

To build the project run the following

```
mkdir build && cd build
cmake ..
make
```

## Testing

Test can be compiled and run by

```
make test
```

# Testing

All methods of NMEAParser are tested. All parser functions have their
own test suite. The test suite name is based on the function name and
parameter signature.

## Implemented Tests

* ParseTimeStamp_String_Test
* ParseTimeStamp_String_String_Test