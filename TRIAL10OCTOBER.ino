#include "DFRobot_GDL.h"
#define TFT_DC  4
#define TFT_CS  21
#define TFT_RST 2
DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

#include "Adafruit_Keypad.h"
// Define your specific keypad here via PID
#define KEYPAD_PID1332
// Define your pins here
// Can ignore ones that don't apply
#define R1    16
#define C1    17
#define C2    5
#define C3    22
#define C4    19

#include <Stepper.h>
// Define the number of steps per revolution
const int stepsPerRevolution = 2048; // 28BYJ-48 has 2048 steps per revolution
// Define the motor interface pins
#define IN1 26
#define IN2 25
#define IN3 33
#define IN4 32
Stepper motor(stepsPerRevolution, IN1, IN3, IN2, IN4);

// Define IR sensor pin and variables
const int irSensorPin = 35;
int pillCount = 0;
int setInput = 0;

// Define LED pin
const int LedPin = 14;

enum Page {
  SELECT_MEDICINE,
  INPUT_NUMBER,
  COUNTED_PILLS, // New page for entering numbers
};

Page currentPage = SELECT_MEDICINE; // Initial page

// Medicine names
const char* medicineNames[] = {
  "1.Paracetamol",
  "2.Hedax",
  "3.Ibuprofen",
  "4.Acepar",
  "5.Paracetamol Xtra",
  "6.Amoxicillin"
};

const byte ROWS = 1; // Rows
const byte COLS = 4; // Columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
};
byte rowPins[ROWS] = {R1}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {C1, C2, C3, C4}; // Connect to the column pinouts of the keypad
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int enteredNumber = 0; // Default entered number
int selectedMedicine = 0; // Currently selected medicine
bool motorEnabled = false;

void setup() {
  Serial.begin(9600);
  screen.begin();
  screen.fillScreen(COLOR_RGB565_BLACK);
  customKeypad.begin();

  // Set the motor speed (RPM)
  motor.setSpeed(15); // Speed of the motor
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(irSensorPin), pillDetection, FALLING); // Attach interrupt

  // Setting LED PIN
  pinMode(LedPin, OUTPUT);
}

void loop() {
  customKeypad.tick();

  while (customKeypad.available()) {
    keypadEvent e = customKeypad.read();
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      handleKeyPress(e.bit.KEY);
    }
  }

  switch (currentPage) {
    case SELECT_MEDICINE:
      SelectMedicine();
      break;
    case INPUT_NUMBER:
      InputNumber();
      break;
    case COUNTED_PILLS:
      CountedPills();
      break;
  }

  if (motorEnabled) {
    Motor(); // Execute the Motor function if motorEnabled is true
  }

 }
 void handleKeyPress(char key) {
  if (currentPage == SELECT_MEDICINE) {
    if (key == '1') {
      // Scroll up
      selectedMedicine = (selectedMedicine + 5) % 6;
    }
    else if (key == '2') {
      // Scroll down
      selectedMedicine = (selectedMedicine + 1) % 6;
    }
    else if (key == '3') {
      // Enter key, switch to the number input page
      currentPage = INPUT_NUMBER;
    }
  }
  else if (currentPage == INPUT_NUMBER) {
    if (key == '1') {
      // Scroll up 
       enteredNumber--;
    } else if (key == '2') {
      // Scroll down
      enteredNumber++;
    } else if (key == '3') {
      // Enter key, store enteredNumber and display it in Serial Monitor
      Serial.print("Entered Number: ");
      Serial.println(enteredNumber);
      motorEnabled = true;
      // Print the selected medicine
      if (selectedMedicine >= 0 && selectedMedicine < 6) {
        Serial.print("Selected Medicine: ");
        Serial.println(medicineNames[selectedMedicine]);
      }

      // Switch back to SELECT_MEDICINE page
      currentPage =  COUNTED_PILLS;
    }
  }
}
void SelectMedicine() {
  // Clear the screen
  screen.fillScreen(COLOR_RGB565_BLACK);

  // Title
  screen.setTextSize(2);
  screen.setTextColor(COLOR_RGB565_BLACK);
  screen.setCursor(40, 15); //(x,y)
  screen.print("PILL");

  screen.setTextColor(COLOR_RGB565_BLACK);
  screen.setCursor(110, 15); //(x,y)
  screen.print("DISPENSER");

  // Display medicine names with highlighting
  for (int i = 0; i < 6; i++) {
    screen.setTextSize(2);
    if (i == selectedMedicine) {
      // Highlight the selected medicine
      screen.setTextColor(COLOR_RGB565_RED);
    } else {
      screen.setTextColor(COLOR_RGB565_WHITE);
    }
    screen.setCursor(10, 60 + i * 40); //(x,y)
    screen.print(medicineNames[i]);
  }
}

void InputNumber() {
  // Clear the screen
  screen.fillScreen(COLOR_RGB565_BLACK);

  // Display number input page
  screen.setTextSize(2.8);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setCursor(50, 100); // (x,y)
  screen.print("Enter Number:");
  screen.setCursor(50, 140); // (x,y)
  screen.print(enteredNumber);
}
void Motor() {
  int stepsToMove = stepsPerRevolution * enteredNumber ;
  motor.step(stepsToMove);
  // Check if the count matches the user-set input
  if (pillCount < enteredNumber) {
    // Continue rotating the motor
    motor.step(stepsPerRevolution);
  } else {
    // Object count matches user input, stop the motor
    Serial.println("Object counting complete.");
    motor.setSpeed(0); // Stop the motor
  }
}

void pillDetection() {
  // Read the IR sensor input
  int irSensorValue = digitalRead(irSensorPin);

  // If an object is detected, increment the count
  if (irSensorValue == LOW) {
    ++pillCount;
    Serial.print("Pills Counted: ");
    Serial.println(pillCount);
  }
}
 void CountedPills() {
  // Clear the screen
  screen.fillScreen(COLOR_RGB565_BLACK);

  // Display number input page
  screen.setTextSize(2.8);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setCursor(50, 100); // (x,y)
  screen.print("Pills Counted: ");
  screen.setCursor(50, 140); // (x,y)
  screen.print(pillCount);
  screen.setTextColor(COLOR_RGB565_BLACK);



}
