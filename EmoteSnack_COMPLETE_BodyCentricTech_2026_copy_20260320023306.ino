/*

Emoting Through Arduino 
Code as a Material   

Your Name:  Amelia
Your emotion in one word: Happy

*/ 

//Install your CircuitPlayground's memorys
     //Note <---
     // You MUST install this by clicking the Library manager bookstack icon. 
     // Search "Adafruit Circuit Playground" by Adafruit  
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>


//Add inputs 
bool button1; 
bool button2;

// Add outputs 
//Create a "Class" that holds your emotional state 
class Emotional_state{
  public:
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

//Declare yourself
Emotional_state Amelia;

/* *** IMPORTANT: Set up function runs once.
 When you upload the code to your Arduino and reads every word
 line by line, top to bottom 
*/ 
void setup() {
  // Open the communication port from you to your Arduino and back 
  Serial.begin(115200);

  //Begin communication 
  CircuitPlayground.begin();

  //Set Brightness of LED strip
  CircuitPlayground.strip.setBrightness(10);
}


//***** IMPORTANT: Loop function runs over and over again, continuously in a LOOP
void loop() {

  // Buttons on the circuit board for different needs 
  button1 = CircuitPlayground.leftButton();
  button2 = CircuitPlayground.rightButton();

  //***Sensing state
  // if both buttons are pressed we want to begin sensing the emotion
   if (button2 && button1){
    CircuitPlayground.clearPixels();

    //Sense the colors you need from the light sensor
    CircuitPlayground.senseColor(Amelia.red, Amelia.green, Amelia.blue);

    //Gamma correction makes LED brightness appear more linear
    //lots of times raw data values require correction or recalibration
    Amelia.red   = CircuitPlayground.gamma8(Amelia.red);
    Amelia.green = CircuitPlayground.gamma8(Amelia.green);
    Amelia.blue  = CircuitPlayground.gamma8(Amelia.blue);
  }

  //***Relaying state
  // if one button is pressed we want to display the sensed color as an emotion 
  if (button1 && !button2) {
    CircuitPlayground.clearPixels(); // Reset the board to blank slate 

  //In the shape of a smile 
    CircuitPlayground.strip.setPixelColor(1, Amelia.red, Amelia.green, Amelia.blue);
    CircuitPlayground.strip.setPixelColor(3, Amelia.red, Amelia.green, Amelia.blue);
    CircuitPlayground.strip.setPixelColor(5, Amelia.red, Amelia.green, Amelia.blue);
    CircuitPlayground.strip.setPixelColor(6, Amelia.red, Amelia.green, Amelia.blue);
    CircuitPlayground.strip.setPixelColor(7, Amelia.red, Amelia.green, Amelia.blue);
    CircuitPlayground.strip.setPixelColor(8, Amelia.red, Amelia.green, Amelia.blue);
    CircuitPlayground.strip.setPixelColor(9, Amelia.red, Amelia.green, Amelia.blue);


    CircuitPlayground.strip.show();
  }
}

/* Example of code with less control 
Advanced coders -> can you work backwards and untangle this code to apply a rainbow color to the emoting arduino? 
*/
void rainbow() {
  // 
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<CircuitPlayground.strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      int pixelHue = firstPixelHue + (i * 65536L / CircuitPlayground.strip.numPixels());

      if(i == 0 || i == 2 || i == 4){
        CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.strip.gamma32(CircuitPlayground.strip.ColorHSV(pixelHue, 255, 0)));
      }
      CircuitPlayground.strip.setPixelColor(i, CircuitPlayground.strip.gamma32(CircuitPlayground.strip.ColorHSV(pixelHue)));
    }
    CircuitPlayground.strip.show(); // Update strip with new contents
    delay(20);  // Pause for a moment
  }
}

/*References that parts of code were adapted from: 
-> Adafruit library:https://github.com/adafruit/Adafruit_CircuitPlayground/tree/master/examples
-> COLOR SENSE example - Author: Limor Fried & Tony DiCola
-> BUTTON CYCLER example - Author: Paint your dragon 
-> Build out Author: Amelia Lochhead
-> Date last Motified: 3/20/26
*/
