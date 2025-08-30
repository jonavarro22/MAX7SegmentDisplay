#include "MAX7SegmentDisplay.h"

// Common wiring for ATMEGA 328P like in an Arduino Uno
#define DIN 11 // Also known as MOSI, the data input for the chip
#define CS 8   // Also known as LOAD, with this we select the chip
#define CLK 13 // Also known as SCLK, the clock input for the chip

bool direction = false;

// Initialize display with detected or fallback pins (DIN/MOSI, CS/LOAD, CLK)
MAX7SegmentDisplay max = MAX7SegmentDisplay(DIN, CS, CLK);

void setup() {

  Serial.begin(9600);
  Serial.println("MAX7SegmentDisplay Demo");

  max.setBright(10);    // Set the brightness min:1, max:15
  max.setDigitLimit(8); // Set the digit count

  /*
    If the numbers appear in reverse order uncomment the following line
    max.ReverseDirection();

    You can also toggle the direction of the display using the following line
    max.setReverseDirection(true);
  */

}

void loop() {

  Serial.print("Printing with direction: ");
  Serial.println(direction);
  max.setReverseDirection(direction);

  Serial.println(12345678);
  max.printDigit(12345678);
  delay(1000);
  max.clear();


  Serial.println("Printing with an offset:");
  for (int i = 0; i < 100; i++) {
    max.printDigit(i);

    max.printDigit(i, 4);
    delay(50);
  }

  Serial.println("Turning display off and on:");
  for (int i = 0; i <= 10; i++) {
    max.off();
    delay(150);

    max.on();
    delay(150);
  }

  Serial.println("Clearing display:");
  max.clear();
  delay(1000);

  Serial.println("Direct write to digit using binary:");
  for (int i = 0; i <= 20; i++) {
    /* Select Digit 5 and write B01100011 */
    max.write(5, B01100011);
    delay(200);

    /* Select Digit 5 and write B00011101 */
    max.write(5, B00011101);
    delay(200);
  }

  Serial.println("Clearing display:");
  max.clear();
  delay(1000);

  direction = !direction;

}