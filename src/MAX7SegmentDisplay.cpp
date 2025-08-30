#include "MAX7SegmentDisplay.h"

#define DECODEMODE_ADDR 9
#define BRIGHTNESS_ADDR	10
#define SCANLIMIT_ADDR	11
#define SHUTDOWN_ADDR	12
#define DISPLAYTEST_ADDR 15


MAX7SegmentDisplay::MAX7SegmentDisplay(int dinPin, int csPin, int clkPin) {
    DIN_PIN = dinPin;
    CS_PIN = csPin;
    CLK_PIN = clkPin;
    reverseDirection = false;
    
    pinMode(DIN_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);
}

void MAX7SegmentDisplay::setBright(int brightness) {
    if (brightness>=0 && brightness<16)    
        write(BRIGHTNESS_ADDR, brightness);
}

void MAX7SegmentDisplay::setDigitLimit(int limit) {
    _digitLimit = limit;

    write(DISPLAYTEST_ADDR, 0);
    write(SCANLIMIT_ADDR, limit-1);

    // 0: Register Format
    // 255: Code B Font (0xff)
    write(DECODEMODE_ADDR, 0);
    clear();
    write(SHUTDOWN_ADDR, 1);
}

	    
void MAX7SegmentDisplay::on() {
    write(SHUTDOWN_ADDR, 0x01);
}

void MAX7SegmentDisplay::off() {
    write(SHUTDOWN_ADDR, 0x00);
}

void MAX7SegmentDisplay::clear() {
  for (int i = 1; i <=_digitLimit; i++) {
    write(i, B00000000);
  }
}

void MAX7SegmentDisplay::table(byte address, int val) {
    byte tableValue;
    tableValue = pgm_read_byte_near(charTable + val);
    write(address, tableValue);
}

void MAX7SegmentDisplay::write(volatile byte address, volatile byte data) {
    digitalWrite(CS_PIN, LOW);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, address);
    shiftOut(DIN_PIN, CLK_PIN, MSBFIRST, data);
    digitalWrite(CS_PIN, HIGH);
}

void MAX7SegmentDisplay::printDigit(long number, byte startDigit) {
    String figure = String(number);
    int figureLength = figure.length();

    int parseInt;
    char str[2];
    if(reverseDirection) {
        for(int i = figure.length() - 1; i >= 0; i--) {
            str[0] = figure[i];
            str[1] = '\0';
            parseInt = (int) strtol(str, NULL, 10);
            table(figureLength - i + startDigit, parseInt);
        }
    } else {
        for(int i = 0; i < figure.length(); i++) {
            str[0] = figure[i];
            str[1] = '\0';
            parseInt = (int) strtol(str, NULL, 10);
            table(i + startDigit, parseInt);
        }
    }
}

void MAX7SegmentDisplay::setReverseDirection(bool rev) {
    reverseDirection = rev;
}
void MAX7SegmentDisplay::ReverseDirection() {
    reverseDirection = true;
}
