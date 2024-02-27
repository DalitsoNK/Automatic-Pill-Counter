#include "DFRobot_GDL.h"

/*#if defined ARDUINO_SAM_ZERO
#define TFT_DC  7
#define TFT_CS  5
#define TFT_RST 6
#define TFT_BL  9
/*ESP32 and ESP8266*/
//#elif defined(ESP32) || defined(ESP8266)
#define TFT_DC  4
#define TFT_CS  5
#define TFT_RST 2
//define TFT_BL  D13
/* AVR series mainboard */
/*#else
#define TFT_DC  2
#define TFT_CS  3
#define TFT_RST 4
#define TFT_BL  5
#endif

/**
   @brief Constructor Constructor of hardware SPI communication
   @param dc Command/data line pin for SPI communication
   @param cs Chip select pin for SPI communication
   @param rst reset pin of the screen
*/

DFRobot_ST7789_240x320_HW_SPI screen(/*dc=*/TFT_DC,/*cs=*/TFT_CS,/*rst=*/TFT_RST);

/*
  User-selectable macro definition color
  COLOR_RGB565_BLACK   COLOR_RGB565_NAVY    COLOR_RGB565_DGREEN   COLOR_RGB565_DCYAN 
  COLOR_RGB565_MAROON  COLOR_RGB565_PURPLE  COLOR_RGB565_OLIVE    COLOR_RGB565_LGRAY
  COLOR_RGB565_DGRAY   COLOR_RGB565_BLUE    COLOR_RGB565_GREEN    COLOR_RGB565_CYAN  
  COLOR_RGB565_RED     COLOR_RGB565_MAGENTA COLOR_RGB565_YELLOW   COLOR_RGB565_ORANGE           
  COLOR_RGB565_WHITE
*/

void setup() {
  Serial.begin(9600);
  screen.begin();
  screen.fillScreen(COLOR_RGB565_BLACK);
}

void loop() {
  testRects(COLOR_RGB565_BLACK, COLOR_RGB565_WHITE);
  SelectMedicine();
  ConfirmationPrint();
}

void testRects(uint16_t color1, uint16_t color2) {
  screen.drawRect(/*x=*/0, /*y=*/0 ,   /*w=*/240, /*h=*/320, /*color=*/COLOR_RGB565_WHITE); //Main border

  screen.drawRect(/*x=*/0, /*y=*/0 ,   /*w=*/240, /*h=*/50,  /*color=*/COLOR_RGB565_WHITE); //Title border

  screen.drawRect(/*x=*/0, /*y=*/50 , /*w=*/240, /*h=*/30,  /*color=*/COLOR_RGB565_WHITE); //Subtitle border

  screen.drawRect(/*x=*/0, /*y=*/80 , /*w=*/150, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE);
  screen.drawRect(/*x=*/0, /*y=*/80 , /*w=*/240, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE); //Nitrogen border

  screen.drawRect(/*x=*/0, /*y=*/120 , /*w=*/150, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE);
  screen.drawRect(/*x=*/0, /*y=*/120 , /*w=*/240, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE); //Phosphorus border

  screen.drawRect(/*x=*/0, /*y=*/160 , /*w=*/150, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE);
  screen.drawRect(/*x=*/0, /*y=*/160 , /*w=*/240, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE); //Potassium border

  screen.drawRect(/*x=*/0, /*y=*/200 , /*w=*/150, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE);
  screen.drawRect(/*x=*/0, /*y=*/200 , /*w=*/240, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE); //pH border

  screen.drawRect(/*x=*/0, /*y=*/240 , /*w=*/150, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE);
  screen.drawRect(/*x=*/0, /*y=*/240 , /*w=*/240, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE); //Moist border

  screen.drawRect(/*x=*/0, /*y=*/280 , /*w=*/150, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE);
  screen.drawRect(/*x=*/0, /*y=*/280 , /*w=*/240, /*h=*/40,  /*color=*/COLOR_RGB565_WHITE); //Temp border

}

void SelectMedicine() {
  //  Title
  screen.setTextSize(3);
  screen.setTextColor(COLOR_RGB565_BLACK);
  screen.setCursor(40, 15); //(x,y)
  screen.print("PILL");

  screen.setTextColor(COLOR_RGB565_BLACK);
  screen.setCursor(110, 15); //(x,y)
  screen.print("DISPENSER");

  screen.setTextColor(COLOR_RGB565_BLACK);
  screen.setTextSize(2);
  screen.setCursor(10, 60); //(x,y)
  screen.print("Select Medicine");


  screen.setTextColor(COLOR_RGB565_BLACK);

  screen.setCursor(5, 95); //(x,y)
  screen.print("Paracetamol");

  screen.setCursor(5, 135); //(x,y)
  screen.print("Hedax");

  screen.setCursor(5, 175); //(x,y)
  screen.print("Ibuprofen");

  screen.setCursor(5, 215); //(x,y)
  screen.print("Acepar");

  screen.setCursor(5, 255); //(x,y)
  screen.print("Paracetamol Xtra");

  screen.setCursor(5, 295); //(x,y)
  screen.print("Amoxicillin");
}

void ConfirmationPrint() {

  screen.setCursor(5, 135); //(x,y)
  screen.print("ARE YOU SURE?");

  screen.setCursor(5, 175); //(x,y)
  screen.print("yes");

  screen.setCursor(10, 175); //(x,y)
  screen.print("No");


}
