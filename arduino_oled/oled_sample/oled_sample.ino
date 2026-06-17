// set pin numbers
// const int buttonPin = 4;  // the number of the pushbutton pin
const int ledPin =  5;    // the number of the LED pin

// variable for storing the pushbutton status 
int buttonState = 0;

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#include <Wire.h>
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_WIDTH 128 // OLED display width, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  // Display static text
  display.println("KG & CG");
  display.display(); 
  delay(100);
}
void loop() {
  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(7000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(7000);
  display.stopscroll();
  delay(1000);
}

// void setup() {
//   Serial.begin(115200);
//   // initialize the pushbutton pin as an input
//   //pinMode(buttonPin, INPUT);
//   // initialize the LED pin as an output
//   pinMode(ledPin, OUTPUT);
// }

// void loop() {
//   // read the state of the pushbutton value
//   //buttonState = digitalRead(buttonPin);
//   Serial.println(buttonState);
//   // check if the pushbutton is pressed.
//   // if it is, the buttonState is HIGH
//   if (buttonState == HIGH) {
//     // turn LED on
//     digitalWrite(ledPin, HIGH);
//   } else {
//     // turn LED off
//     digitalWrite(ledPin, LOW);
//   }
//   delay(1000);
//   buttonState = !buttonState;
// }
