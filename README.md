# NMEAParser
Library for parsing NMEA data strings

## Building

To build the project run the following

```
./bootstrap
./configure
make
```

The compiled libraries will be stored in libs/.libs/ and the headers are also
stored in lib/

## Testing

Test can be compiled and run by

```
make check
./test/gprmc-print
```
