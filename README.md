MAX7SegmentDisplay
==========
MAX7SegmentDisplay is an [Arduino](http://arduino.cc) library for MAX7219 and MAX7221 8 bit 7-segment digital LED display module drivers.

Install
-------
[Arduino library install guide](https://www.arduino.cc/en/Guide/Libraries)

Or you can copy DigitLedDisplay library to -> arduino\libraries\

-------
*Start From Digit: Default Value Zero*\
`max.printDigit(1234);`\
![digidled0](https://cloud.githubusercontent.com/assets/3593584/26308379/a9b9fd84-3f01-11e7-924b-f0f810f4d22a.jpg)

*Start From Digit 4*\
`digitLedDisplay.printDigit(1234, 4);`\
![digidled4](https://cloud.githubusercontent.com/assets/3593584/26308387/b0f90c7a-3f01-11e7-93a0-2834827b2145.jpg)

Image credit: the images above are from the original library by Ozhan Duran and are used here with attribution.

## Quickstart

```c
#include <MAX7SegmentDisplay.h>

// initialize with pin numbers for data, cs, and clock
MAX7SegmentDisplay max = MAX7SegmentDisplay(11, 8, 13);

void setup() {
  max.setBright(15); // range is 0-15
  max.setDigitLimit(8);
}

long i = 12345678;

void loop() {
  max.printDigit(i++);
  delay(10);
}
```

For additional features see [Digit7SegmentDemo.ino](examples/Digit7SegmentDemo/Digit7SegmentDemo.ino)

## Reverse direction

This library supports reversing the order in which digits are written to the display.

- setReverseDirection(bool rev)
  - Call with `true` to enable reverse printing, `false` to restore normal order.
  - Example: `max.setReverseDirection(true); max.printDigit(1234);` — the digits will be sent in reverse order.

- ReverseDirection()
  - Compatibility helper (older API). Calling `max.ReverseDirection()` will enable reverse mode (equivalent to `setReverseDirection(true)`).

Note: Reverse mode affects only the order the library writes digit values to the MAX chip; it does not change wiring or physical orientation of the module. Use `setReverseDirection(false)` to return to the default behavior.
