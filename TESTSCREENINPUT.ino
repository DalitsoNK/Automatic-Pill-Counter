#include "DFRobot_GDL.h"

#define TFT_DC  4
#define TFT_CS  21
#define TFT_RST 2

#include "Adafruit_Keypad.h"

// define your specific keypad here via PID
#define KEYPAD_PID1332
// define your pins here
// can ignore ones that don't apply
#define R1    16
// #define R2    3
// #define R3    4
// #define R4    5
#define C1    17
#define C2    5
#define C3    22
#define C4    19
// leave this import after the above configuration

DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

enum Page {
  SELECT_MEDICINE,
  CONFIRMATION,
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

int selectedMedicine = 0; // Currently selected medicine

const byte ROWS = 1; // rows
const byte COLS = 4; // columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', '4'},
};
byte rowPins[ROWS] = {R1}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {C1, C2, C3, C4}; // connect to the column pinouts of the keypad

Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  screen.begin();
  screen.fillScreen(COLOR_RGB565_BLACK);
  customKeypad.begin();
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
    case CONFIRMATION:
      ConfirmationPrint();
      break;
  }
}

void handleKeyPress(char key) {
  if (key == '1') {
    // Scroll up
    selectedMedicine = (selectedMedicine + 5) % 6;
  } else if (key == '2') {
    // Scroll down
    selectedMedicine = (selectedMedicine + 1) % 6;
  } else if (key == '3') {
    // Enter key, switch to confirmation page
    currentPage = CONFIRMATION;
  }
}

void SelectMedicine() {
  // Clear the screen
  screen.fillScreen(COLOR_RGB565_BLACK);

  //  Title
  screen.setTextSize(3);
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

void ConfirmationPrint() {
  // Clear the screen
  screen.fillScreen(COLOR_RGB565_BLACK);

  // Display confirmation message
  screen.setTextSize(2);
  screen.setTextColor(COLOR_RGB565_WHITE);
  screen.setCursor(10, 60); //(x,y)
  screen.print("Are you sure?");

  // Highlight the selected option
  screen.setTextColor(selectedMedicine == 0 ? COLOR_RGB565_RED : COLOR_RGB565_WHITE);
  screen.setCursor(80, 100); //(x,y)
  screen.print("Yes");

  screen.setTextColor(selectedMedicine == 1 ? COLOR_RGB565_RED : COLOR_RGB565_WHITE);
  screen.setCursor(80, 140); //(x,y)
  screen.print("No");
  //delay(5000);
  // Simulate a user interaction (e.g., button press) to select Yes or No
  // You can handle the selection similar to how you handled medicine selection
}
