// Import necessary libraries for OLED display and graphics
#include <Wire.h>               // I2C library for communication
#include <Adafruit_GFX.h>       // Graphics library (used to draw shapes)
#include <Adafruit_SSD1306.h>   // Library for controlling SSD1306 OLED displays

// Define OLED display width and height
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Define OLED reset pin, set to -1 if shared with Arduino reset
#define OLED_RESET    -1 

// Create the display object (using I2C communication)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Cube vertices
float cubeVertices[8][3] = {
  { -1, -1, -1 },
  {  1, -1, -1 },
  {  1,  1, -1 },
  { -1,  1, -1 },
  { -1, -1,  1 },
  {  1, -1,  1 },
  {  1,  1,  1 },
  { -1,  1,  1 }
};

// Define cube edges (pairs of vertices to connect)
int cubeEdges[12][2] = {
  {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
  {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
  {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
};

// Function to project 3D coordinates onto 2D screen space
void project(float x, float y, float z, int &x2d, int &y2d) {
  float scale = 64;   // Scaling factor for projection (change to adjust size)
  float distance = 3; // Distance from the "camera"
  
  x2d = (int)(SCREEN_WIDTH / 2 + x * scale / (z + distance));
  y2d = (int)(SCREEN_HEIGHT / 2 + y * scale / (z + distance));
}

// Function to draw the rotating cube
void drawCube(float angle) {
  int projectedVertices[8][2]; // To store 2D projected coordinates

  // Rotation transformation around Y-axis
  float cosA = cos(angle);
  float sinA = sin(angle);

  // Loop through each vertex and apply rotation and projection
  for (int i = 0; i < 8; i++) {
    float x = cubeVertices[i][0];
    float y = cubeVertices[i][1];
    float z = cubeVertices[i][2];

    // Apply Y-axis rotation matrix
    float newX = cosA * x - sinA * z;
    float newZ = sinA * x + cosA * z;

    // Project the 3D coordinates onto 2D screen
    project(newX, y, newZ, projectedVertices[i][0], projectedVertices[i][1]);
  }

  // Draw edges by connecting the projected vertices
  for (int i = 0; i < 12; i++) {
    int v1 = cubeEdges[i][0];
    int v2 = cubeEdges[i][1];
    display.drawLine(
      projectedVertices[v1][0], projectedVertices[v1][1],
      projectedVertices[v2][0], projectedVertices[v2][1],
      WHITE
    );
  }
}

void setup() {
  // Initialize serial communication for debugging purposes
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Halt if initialization fails
  }

  // Clear the display initially
  display.clearDisplay();
}

void loop() {
  static float angle = 0; // Variable to track cube rotation angle

  // Clear the display before drawing the new frame
  display.clearDisplay();

  // Draw the cube at the current rotation angle
  drawCube(angle);

  // Update the display with the drawn content
  display.display();

  // Increment the angle to rotate the cube
  angle += 0.05; // Adjust this value to control rotation speed

  // Small delay to control the frame rate (adjust as needed)
  delay(30);
}
