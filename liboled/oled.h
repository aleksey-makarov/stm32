/*
  OLED_I2C.h - Arduino/chipKit library support for 128x64 pixel SSD1306 OLEDs
  Copyright (C) 2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  Copyright (C) 2018 Aleksey Makarov
  
  This library has been made to make it easy to use 128x64 pixel OLED displays
  based on the SSD1306 controller chip with an Arduino or a chipKit.

  You can always find the latest version of the library at 
  http://www.RinkyDinkElectronics.com/

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/

#ifndef __oled_h__
#define __oled_h__

#include <stdint.h>
#include <stdbool.h>

void oled_begin();
void oled_update();
void oled_setBrightness(uint8_t value);
void oled_clrScr();
void oled_fillScr();
void oled_invert(bool mode);
void oled_setPixel(uint16_t x, uint16_t y);
void oled_clrPixel(uint16_t x, uint16_t y);
void oled_invPixel(uint16_t x, uint16_t y);
void oled_invertText(bool mode);
void oled_print(char *st, int x, int y);
// void oled_printNumI(long num, int x, int y, int length=0, char filler=' ');
// void oled_printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ');
void oled_setFont(uint8_t* font);
void oled_drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy);
void oled_drawLine(int x1, int y1, int x2, int y2);
void oled_clrLine(int x1, int y1, int x2, int y2);
void oled_drawRect(int x1, int y1, int x2, int y2);
void oled_clrRect(int x1, int y1, int x2, int y2);
void oled_drawRoundRect(int x1, int y1, int x2, int y2);
void oled_clrRoundRect(int x1, int y1, int x2, int y2);
void oled_drawCircle(int x, int y, int radius);
void oled_clrCircle(int x, int y, int radius);

#endif