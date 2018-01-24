/*
  OLED_I2C.cpp - Arduino/chipKit library support for 128x64 pixel SSD1306 OLEDs
  Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
  
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

#include "oled.h"
#include "../i2c.h"
#include <string.h>
#include "../mtrace.h"
#include "../dwt.h"

#define SSD1306_COMMAND		0x00
#define SSD1306_DATA		0xC0
#define SSD1306_DATA_CONTINUE	0x40

// SSD1306 Commandset
// ------------------
// Fundamental Commands
#define SSD1306_SET_CONTRAST_CONTROL		0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME		0xA4
#define SSD1306_DISPLAY_ALL_ON			0xA5
#define SSD1306_NORMAL_DISPLAY			0xA6
#define SSD1306_INVERT_DISPLAY			0xA7
#define SSD1306_DISPLAY_OFF			0xAE
#define SSD1306_DISPLAY_ON			0xAF
#define SSD1306_NOP				0xE3
// Scrolling Commands
#define SSD1306_HORIZONTAL_SCROLL_RIGHT		0x26
#define SSD1306_HORIZONTAL_SCROLL_LEFT		0x27
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_RIGHT	0x29
#define SSD1306_HORIZONTAL_SCROLL_VERTICAL_AND_LEFT	0x2A
#define SSD1306_DEACTIVATE_SCROLL		0x2E
#define SSD1306_ACTIVATE_SCROLL			0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA	0xA3
// Addressing Setting Commands
#define SSD1306_SET_LOWER_COLUMN		0x00
#define SSD1306_SET_HIGHER_COLUMN		0x10
#define SSD1306_MEMORY_ADDR_MODE		0x20
#define SSD1306_SET_COLUMN_ADDR			0x21
#define SSD1306_SET_PAGE_ADDR			0x22
// Hardware Configuration Commands
#define SSD1306_SET_START_LINE			0x40
#define SSD1306_SET_SEGMENT_REMAP		0xA0
#define SSD1306_SET_MULTIPLEX_RATIO		0xA8
#define SSD1306_COM_SCAN_DIR_INC		0xC0
#define SSD1306_COM_SCAN_DIR_DEC		0xC8
#define SSD1306_SET_DISPLAY_OFFSET		0xD3
#define SSD1306_SET_COM_PINS			0xDA
#define SSD1306_CHARGE_PUMP			0x8D
// Timing & Driving Scheme Setting Commands
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO	0xD5
#define SSD1306_SET_PRECHARGE_PERIOD		0xD9
#define SSD1306_SET_VCOM_DESELECT		0xDB

#define SIZEOF(a) (sizeof(a)/sizeof(a[0]))

#define SCRBUF_SIZE 1024
#define SCRBUF_CMD_SIZE (SCRBUF_SIZE + 1)
static uint8_t scrbuf_cmd[SCRBUF_CMD_SIZE] = { SSD1306_DATA_CONTINUE, };
static uint8_t * const scrbuf = scrbuf_cmd + 1;

int _sendTWIcommand(uint8_t cmd) {
	int err;
	uint8_t v[2] = { 0, cmd };
	// uint32_t ts;

	// ts = dwt_get_cycles();
	err = i2c_write(0x3c, v, 2);
	// MTRACE("cmd: 0x%02x, time: %d ms", (unsigned int)cmd, dwt_ms_since(ts));

	return err;
}

void send_commands(uint8_t *cmds, unsigned long length)
{
	for (; length; length--, cmds++)
		_sendTWIcommand(*cmds);
}

uint8_t update_cmds[] = {
	SSD1306_SET_COLUMN_ADDR,
	0,
	127,
	SSD1306_SET_PAGE_ADDR,
	0,
	7,
};

void oled_update(void)
{
	// uint32_t ts;
	// int err;

	send_commands(update_cmds, SIZEOF(update_cmds));

	// ts = dwt_get_cycles();
	i2c_write(0x3c, scrbuf_cmd, SCRBUF_CMD_SIZE);
	// MTRACE("update buffer: err: %d, time: %d ms", err, dwt_ms_since(ts));
}

uint8_t init_cmds[] = {
	SSD1306_DISPLAY_OFF,
	SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO,
	0x80,
	SSD1306_SET_MULTIPLEX_RATIO,
	0x3F,
	SSD1306_SET_DISPLAY_OFFSET,
	0x0,
	SSD1306_SET_START_LINE | 0x0,
	SSD1306_CHARGE_PUMP,
	0x14,
	SSD1306_MEMORY_ADDR_MODE,
	0x00,
	SSD1306_SET_SEGMENT_REMAP | 0x1,
	SSD1306_COM_SCAN_DIR_DEC,
	SSD1306_SET_COM_PINS,
	0x12,
	SSD1306_SET_CONTRAST_CONTROL,
	0xCF,
	SSD1306_SET_PRECHARGE_PERIOD,
	0xF1,
	SSD1306_SET_VCOM_DESELECT,
	0x40,
	SSD1306_DISPLAY_ALL_ON_RESUME,
	SSD1306_NORMAL_DISPLAY,
	SSD1306_DISPLAY_ON,
};

void oled_begin(void) {
	i2c_init();
	// dwt_enable();
	send_commands(init_cmds, SIZEOF(init_cmds));
	oled_clrScr();
	oled_update();
}

void oled_clrScr() {
	memset(scrbuf, 0, SCRBUF_SIZE);
}

void oled_fillScr() {
	memset(scrbuf, 255, SCRBUF_SIZE);
}

void oled_setBrightness(uint8_t value) {
	_sendTWIcommand(SSD1306_SET_CONTRAST_CONTROL);
	_sendTWIcommand(value);
}

void oled_invert(bool mode) {
	if (mode == true)
		_sendTWIcommand(SSD1306_INVERT_DISPLAY);
	else
		_sendTWIcommand(SSD1306_NORMAL_DISPLAY);
}

void oled_setPixel(uint16_t x, uint16_t y) {
	int by, bi;

	if (x < 128 && y < 64) {
		by=((y/8)*128)+x;
		bi=y % 8;

		scrbuf[by]=scrbuf[by] | (1<<bi);
	}
}

void oled_clrPixel(uint16_t x, uint16_t y) {
	int by, bi;

	if (x < 128 && y < 64) {
		by=((y/8)*128)+x;
		bi=y % 8;

		scrbuf[by]=scrbuf[by] & ~(1<<bi);
	}
}

void oled_invPixel(uint16_t x, uint16_t y) {
	int by, bi;

	if (x < 128 && y < 64) {
		by=((y/8)*128)+x;
		bi=y % 8;

		if ((scrbuf[by] & (1<<bi))==0)
			scrbuf[by]=scrbuf[by] | (1<<bi);
		else
			scrbuf[by]=scrbuf[by] & ~(1<<bi);
	}
}

void oled_printChar(struct font *f, bool inverted, unsigned char c, int x, int y)
{
	if ((f->y_size % 8) == 0) {
		int font_idx = ((c - f->offset) * (f->x_size * (f->y_size / 8))) + 4;
		int rowcnt;
		for (rowcnt = 0; rowcnt < (f->y_size / 8); rowcnt++) {
			int cnt;
			for(cnt = 0; cnt < f->x_size; cnt++) {
				int b;
				for (b = 0; b < 8; b++)
					if ((f->font[font_idx+cnt+(rowcnt * f->x_size)] & (1 << b)) != 0)
						if (!inverted)
							oled_setPixel(x+cnt, y+(rowcnt*8)+b);
						else
							oled_clrPixel(x+cnt, y+(rowcnt*8)+b);
					else
						if (!inverted)
							oled_clrPixel(x+cnt, y+(rowcnt*8)+b);
						else
							oled_setPixel(x+cnt, y+(rowcnt*8)+b);
			}
		}
	} else {
		int font_idx = ((c - f->offset) * ((f->x_size * f->y_size / 8))) + 4;
		int cbyte = f->font[font_idx];
		int cbit = 7;
		int cx;
		for (cx = 0; cx < f->x_size; cx++) {
			int cy;
			for (cy = 0; cy < f->y_size; cy++) {
				if ((cbyte & (1<<cbit)) != 0)
					if (!inverted)
						oled_setPixel(x+cx, y+cy);
					else
						oled_clrPixel(x+cx, y+cy);
				else
					if (!inverted)
						oled_clrPixel(x+cx, y+cy);
					else
						oled_setPixel(x+cx, y+cy);
				cbit--;
				if (cbit<0)
				{
					cbit=7;
					font_idx++;
					cbyte=f->font[font_idx];
				}
			}
		}
	}
}

void oled_print(struct font *f, bool inverted, char *st, int x, int y)
{
	int stl;
	int cnt;

	stl = strlen(st);
	if (x == OLED_RIGHT)
		x = 128 - (stl * f->x_size);
	if (x == OLED_CENTER)
		x = (128 - (stl * f->x_size)) / 2;

	for (cnt = 0; cnt < stl; cnt++)
		oled_printChar(f, inverted, *st++, x + (cnt * (f->x_size)), y);
}

void oled_drawHLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) && (x<128) && (y>=0) && (y<64))
	{
		for (int cx=0; cx<l; cx++)
		{
			by=((y/8)*128)+x;
			bi=y % 8;

			scrbuf[by+cx] |= (1<<bi);
		}
	}
}

void oled_clrHLine(int x, int y, int l)
{
	int by, bi;

	if ((x>=0) && (x<128) && (y>=0) && (y<64))
	{
		for (int cx=0; cx<l; cx++)
		{
			by=((y/8)*128)+x;
			bi=y % 8;

			scrbuf[by+cx] &= ~(1<<bi);
		}
	}
}

void oled_drawVLine(int x, int y, int l)
{
	if ((x>=0) && (x<128) && (y>=0) && (y<64))
	{
		for (int cy=0; cy<l; cy++)
		{
			oled_setPixel(x, y+cy);
		}
	}
}

void oled_clrVLine(int x, int y, int l)
{
	if ((x>=0) && (x<128) && (y>=0) && (y<64))
	{
		for (int cy=0; cy<l; cy++)
		{
			oled_clrPixel(x, y+cy);
		}
	}
}

int abs(int x)
{
	return x > 0 ? x : -x;
}

void oled_drawLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		oled_drawHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		oled_drawVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=(double)(y2-y1)/(double)(x2-x1);
		ty=(double)y1;
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				oled_setPixel(i, (int)(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				oled_setPixel(i, (int)(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=(float)(x2-x1)/(float)(y2-y1);
		tx=(float)x1;
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		oled_setPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		oled_setPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void oled_clrLine(int x1, int y1, int x2, int y2)
{
	int tmp;
	double delta, tx, ty;
	
	if (((x2-x1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
    if (((y2-y1)<0))
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	if (y1==y2)
	{
		if (x1>x2)
		{
			tmp=x1;
			x1=x2;
			x2=tmp;
		}
		oled_clrHLine(x1, y1, x2-x1);
	}
	else if (x1==x2)
	{
		if (y1>y2)
		{
			tmp=y1;
			y1=y2;
			y2=tmp;
		}
		oled_clrVLine(x1, y1, y2-y1);
	}
	else if (abs(x2-x1)>abs(y2-y1))
	{
		delta=(double)(y2-y1)/(double)(x2-x1);
		ty=(double)y1;
		if (x1>x2)
		{
			for (int i=x1; i>=x2; i--)
			{
				oled_clrPixel(i, (int)(ty+0.5));
        		ty=ty-delta;
			}
		}
		else
		{
			for (int i=x1; i<=x2; i++)
			{
				oled_clrPixel(i, (int)(ty+0.5));
        		ty=ty+delta;
			}
		}
	}
	else
	{
		delta=(float)(x2-x1)/(float)(y2-y1);
		tx=(float)x1;
        if (y1>y2)
        {
			for (int i=y2+1; i>y1; i--)
			{
		 		oled_clrPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
        else
        {
			for (int i=y1; i<y2+1; i++)
			{
		 		oled_clrPixel((int)(tx+0.5), i);
        		tx=tx+delta;
			}
        }
	}

}

void oled_drawRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	oled_drawHLine(x1, y1, x2-x1);
	oled_drawHLine(x1, y2, x2-x1);
	oled_drawVLine(x1, y1, y2-y1);
	oled_drawVLine(x2, y1, y2-y1+1);
}

void oled_clrRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}

	oled_clrHLine(x1, y1, x2-x1);
	oled_clrHLine(x1, y2, x2-x1);
	oled_clrVLine(x1, y1, y2-y1);
	oled_clrVLine(x2, y1, y2-y1+1);
}

void oled_drawRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		oled_setPixel(x1+1,y1+1);
		oled_setPixel(x2-1,y1+1);
		oled_setPixel(x1+1,y2-1);
		oled_setPixel(x2-1,y2-1);
		oled_drawHLine(x1+2, y1, x2-x1-3);
		oled_drawHLine(x1+2, y2, x2-x1-3);
		oled_drawVLine(x1, y1+2, y2-y1-3);
		oled_drawVLine(x2, y1+2, y2-y1-3);
	}
}

void oled_clrRoundRect(int x1, int y1, int x2, int y2)
{
	int tmp;

	if (x1>x2)
	{
		tmp=x1;
		x1=x2;
		x2=tmp;
	}
	if (y1>y2)
	{
		tmp=y1;
		y1=y2;
		y2=tmp;
	}
	if ((x2-x1)>4 && (y2-y1)>4)
	{
		oled_clrPixel(x1+1,y1+1);
		oled_clrPixel(x2-1,y1+1);
		oled_clrPixel(x1+1,y2-1);
		oled_clrPixel(x2-1,y2-1);
		oled_clrHLine(x1+2, y1, x2-x1-3);
		oled_clrHLine(x1+2, y2, x2-x1-3);
		oled_clrVLine(x1, y1+2, y2-y1-3);
		oled_clrVLine(x2, y1+2, y2-y1-3);
	}
}

void oled_drawCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	
	oled_setPixel(x, y + radius);
	oled_setPixel(x, y - radius);
	oled_setPixel(x + radius, y);
	oled_setPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		oled_setPixel(x + x1, y + y1);
		oled_setPixel(x - x1, y + y1);
		oled_setPixel(x + x1, y - y1);
		oled_setPixel(x - x1, y - y1);
		oled_setPixel(x + y1, y + x1);
		oled_setPixel(x - y1, y + x1);
		oled_setPixel(x + y1, y - x1);
		oled_setPixel(x - y1, y - x1);
	}
}

void oled_clrCircle(int x, int y, int radius)
{
	int f = 1 - radius;
	int ddF_x = 1;
	int ddF_y = -2 * radius;
	int x1 = 0;
	int y1 = radius;
	
	oled_clrPixel(x, y + radius);
	oled_clrPixel(x, y - radius);
	oled_clrPixel(x + radius, y);
	oled_clrPixel(x - radius, y);
 
	while(x1 < y1)
	{
		if(f >= 0) 
		{
			y1--;
			ddF_y += 2;
			f += ddF_y;
		}
		x1++;
		ddF_x += 2;
		f += ddF_x;    
		oled_clrPixel(x + x1, y + y1);
		oled_clrPixel(x - x1, y + y1);
		oled_clrPixel(x + x1, y - y1);
		oled_clrPixel(x - x1, y - y1);
		oled_clrPixel(x + y1, y + x1);
		oled_clrPixel(x - y1, y + x1);
		oled_clrPixel(x + y1, y - x1);
		oled_clrPixel(x - y1, y - x1);
	}
}

void oled_drawBitmap(int x, int y, uint8_t* bitmap, int sx, int sy)
{
	int bit;
	uint8_t data;

	for (int cy=0; cy<sy; cy++)
	{
		bit= cy % 8;
		for(int cx=0; cx<sx; cx++)
		{
			data=bitmap[cx+((cy/8)*sx)];
			if ((data & (1<<bit))>0)
				oled_setPixel(x+cx, y+cy);
			else
				oled_clrPixel(x+cx, y+cy);
		}
	}      
}
