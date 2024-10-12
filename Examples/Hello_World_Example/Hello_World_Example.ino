// Import required libraries for SPI communication, I2C, and the OLED display
#include <SPI.h>              // SPI library for communication
#include <Wire.h>             // I2C library for communication
#include <Adafruit_GFX.h>     // Graphics library for the OLED display
#include <Adafruit_SSD1306.h> // Library for controlling SSD1306 OLED displays

// Define constants for OLED display size (width and height)
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Define OLED reset pin, set to -1 as the reset is shared with the Arduino's reset pin
#define OLED_RESET -1  

// Define the I2C address for the OLED display (default is usually 0x3C)
#define SCREEN_ADDRESS 0x3C 

// Create an instance of the display object (using I2C communication)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Start serial communication at 9600 baud rate for debugging purposes
  Serial.begin(9600);

  // Initialize the OLED display with internal 3.3V generation (SSD1306_SWITCHCAPVCC)
  // If the initialization fails, print an error message and stop the program
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));  // Display error message
    for (;;);  // Enter infinite loop to prevent further code execution
  }

  // Clear the display buffer (clear any previous content on the OLED)
  display.clearDisplay();
  
  // Set text size to 1 (smallest readable size on the display)
  display.setTextSize(1);

  // Set text color to white (since the OLED is monochrome, WHITE means turning on pixels)
  display.setTextColor(WHITE);

  // Set the cursor position where text will start displaying (x=0, y=10)
  display.setCursor(0, 10);

  // Print "Hello, World!" on the OLED display
  display.println("Hello, World!");

  // Push the buffer to the display (makes the text actually appear on the screen)
  display.display();
}

void loop() {
  // Main loop: in this case, nothing happens repeatedly as the display only updates once in setup()
}
