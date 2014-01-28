/*
 SparkFun Bargraph Breakout example sketch

 2014-01-28 Brad Hunting - modified from Sparkfun's bargraph_example.

 This sketch shows how to map an analog input to SparkFun's Bargraph Breakout board
 similar to an analog VU meter.

 Hardware connections:

 Connect the following pins on the bargraph board to your Arduino:

 Name       Function        Uno pin     Mega pin

 +5V	    Power supply    5V          5V
 GND	    Ground          GND         GND
 SIN	    SPI input       11 (MOSI)   51 (MOSI)
 CLK	    Clock input     13 (SCK)    52 (SCK)
 LAT	    Latch input     10 (SS)     53 (SS)

 Connect the following pins on a 3 pin potentiometer to your Arduino:

 Name       Function       Uno pin     Mega pin

 +5V	    Power supply   5V          5V
 GND	    Ground         GND         GND
 AIN	    Analog value   A0          A0

 */

// Step one: include both the SFEbarGraph and SPI libraries
#include <SFEbarGraph.h>
#include <SPI.h>

// Step two: create a bargraph object; we call it BG in this example but you can call it whatever you wish
// (use the same name in front of all the library functions)

SFEbarGraph BG;
// BAH: normally I would not use global variables but I am following the format
// of the Sparkfun Bargraph breakout and Arduino Analog Input examples.

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store the value coming from the sensor

/* The SFEbarGraph.sendLong() function maps the first 30 bits of an unsigned long
 * argument to the 30 LEDs of the bargraph display.
 *
 * The 31 bit patterns, from all LEDS off to all LEDS on, can be decribed with 31
 * unsigned long values. The 31 possible display patterns can be pre-calculated
 * and stored in an array for later lookup.
 *
 * The Arduino map() function maps does a linear mapping between one range of
 * values to another range of values.  The map function can be used to map between
 * the 0 - 1023 (10 bit) analog input value to one of the 31 possible LED
 * display patterns for a VU meter.
 *
 * The LED patterns could of course be calculated on the fly rather than be
 * looked up in a table.  The trade-offs are the standard ones between
 * run time speed of execution and memory footprint.  The array of
 * 31 unsigned longs will take up 31 x 4 = 124 bytes of the 2K bytes of
 * atmega328p ram memory, or about 6%, for just one data structure.
 * The trade off is the lookup time for the array access is constant
 * time, O(1).  Calculating the LED pattern on the fly is O(n).  Although
 * in this case n is relatively small, 31 possible patterns, so the
 * computation is far from enormous.  This is just one way of doing it.
 *
 * An alternative would be to define a program space array with the
 * pre-calculated values and then use a progmem instruction to read the
 * values from the 32K bytes of program flash storage.
 *
 * Read the analog value
 * Map the analog value to an index into the led pattern array
 * Send the led pattern for that index to the bargraph sendLong function
 *
 * The sendLong function is blocking, spin locks on the spi transmitter, and
 * one school of thought is to only call the display send / update function
 * when the display actually changes.  Keeping a copy of the last index used
 * and comparing it to the new index allows for only sending data to the display
 * when the data changes.
 *
 */
unsigned int const ledcount = 30;
int ledindex = 0;
int ledindexold = 0;
unsigned long ledPatterns[ledcount + 1]; // +0 for the zero, all off value

void setup()
// Runs once upon reboot
{
    // Initialize the bargraph library. Without parameters, it defaults to
    // one bargraph board and LATch pin set to 10 on Uno, or 53 on Mega.
    BG.begin();

    // initialize the serial port so we can watch the program progress on the
    // Arduino console
    Serial.begin( 38400 );

    // pre-calculate the LED patterns and store in the LED pattern array
    ledPatterns[0] = 0;
    for( int i = 1; i < (ledcount + 1); i++ )
    {
        ledPatterns[i] = (ledPatterns[i - 1] << 1) + 1;
    }

    // uncomment to display the LED patterns in the array
    //  for( int i = 0; i < (ledcount+1); i++ )
    //  {
    //    Serial.println( ledPatterns[i], HEX );
    //  }

    // clear the display of any garbage
    BG.clear();
    BG.send();

    // fill the display from low to high by sending each pattern in sequence
    for( int i = 0; i < (ledcount + 1); i++ )
    {
        BG.sendLong( ledPatterns[i] );
        delay( 50 ); // delay long enough to see the pattern
    }

    // clear the display from high to low by sending each pattern in reverse sequence
    for( int i = ledcount; i >= 0; i-- )
    {
        BG.sendLong( ledPatterns[i] );
        delay( 50 ); // delay long enough to see the pattern
    }
}

void loop()
// Runs continuously after setup() ends
{
    sensorValue = analogRead( sensorPin );
    ledindex = map( sensorValue, 0, 1023, 0, ledcount );
    //Serial.println( sensorValue );
    //Serial.println( ledindex );
    if( ledindex != ledindexold )
    {
        BG.sendLong( ledPatterns[ledindex] );
        ledindexold = ledindex;
    }
}

