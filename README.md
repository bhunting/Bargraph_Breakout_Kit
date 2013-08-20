##Bargraph Breakout Kit

This kit contains a PCB and all the parts needed to build a fun, 30-LED bargraph that can be driven by an Arduino or other microcontroller. This kit uses 74HC595 shift registers and three, 10-LED bargraph modules to create the display. We supply one green, one yellow and one red module for “safe / caution / DANGER!” displays, or you can use other 10-LED bargraphs for different colors (not included). The display is easily driven by any microcontroller with an SPI interface, and you have individual control over every LED.

For instructions on building and using the kit, see the .PDF file included with this repository.

###Arduino demo code installation:

If you haven't, install the latest version of the Arduino IDE available at http://www.arduino.cc.

The demo code uses a nonstandard library called SFEbarGraph which is included in this repository.

####Installing the library:

TL;DR: The one-step procedure is to drag the contents of the Arduino folder to your personal Arduino sketch folder. This will create a "libraries" folder containing the SFEbarGraph library.

To install the library manually, copy the "libraries" folder from this repository to your personal Arduino sketch directory. (If there is already a "libraries" folder there, go ahead and add the included library to it.) You'll need to restart the Arduino IDE to get it to recognize the new library.

The library includes example sketches. To load one of them:

1. Connect the Bargraph Breakout board to your Arduino following the wiring instructions in the .PDF file.

2. Connect the Arduino to your computer.

3. Start the Arduino IDE.

4. Load your desired example from: File/Examples/SFEbarGraph/

5. Select your Arduino from the Tools/Board menu.

6. Select your serial port from the Tools/Port menu.

7. Click on the Upload (right arrow) button at the top of the window. The code should compile, upload to your Arduino, and run. Hopefully your Bargraph Breakout is now doing something interesting!

If you have any problems, we'll be happy to help you out. Our email address is techsupport@sparkfun.com

Have fun! -Your friends at SparkFun.
