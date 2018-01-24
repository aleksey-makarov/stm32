// OLED_I2C_3D_Cube
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my OLED_I2C library to rotate a 3D cube.
// The average FPS (Frames Per Second) will be displayed on the screen.
//
// NOTE: The FPS counter will overflow if left for an extended amount of time.
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the OLED display to any available pin but if you use 
// any other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

#include "oled.h"
#include "../mtrace.h"

typedef int32_t fixpoint_t;

static const fixpoint_t half = (1 << 15);
static const fixpoint_t perspective = (1 << (16 - 6));
// static const fixpoint_t PI = ((uint64_t)314159265ULL << 16) / 100000000;

static fixpoint_t _fixpoint(int v)
{
	return v << 16;
}

static fixpoint_t fixpoint(int v)
{
	if (v < 0)
		return -_fixpoint(-v);
	else
		return _fixpoint(v);
}

static int16_t _fixpoint_to_int(fixpoint_t v)
{
	return (v + half) >> 16;
}

static int16_t fixpoint_to_int(fixpoint_t v)
{
	/* FIXME: do we need this? */
	if (v < 0)
		return -_fixpoint_to_int(-v);
	else
		return _fixpoint_to_int(v);
}

static fixpoint_t _x(fixpoint_t a, fixpoint_t b)
{
	bool neg = false;
	fixpoint_t res;
	uint64_t ax, bx;

	if (a < 0) {
		neg = true;
		ax = -a;
	} else {
		ax = a;
	}
	if (b < 0) {
		neg = (neg == false);
		bx = -b;
	} else {
		bx = b;
	}
	res = ((ax * bx) + (1ULL << 15)) >> 16;
	return neg ? -res : res;
}

static const int vectors_init[8][3] = {
	{
		20,
		20,
		20,
	}, {
		-20,
		20,
		20,
	}, {
		-20,
		-20,
		20,
	}, {
		20,
		-20,
		20,
	}, {
		20,
		20,
		-20,
	}, {
		-20,
		20,
		-20,
	}, {
		-20,
		-20,
		-20,
	}, {
		20,
		-20,
		-20,
	}
};

static fixpoint_t vectors[8][3];

// static void print_fixpoint(const char *str, fixpoint_t f)
// {
// 	bool neg = false;
// 	if (f < 0) {
// 		neg = true;
// 		f = -f;
// 	}
// 	printf(str);
// 	if (neg)
// 		putchar('-');
// 	printf("%d", f >> 16);
// 	putchar('.');
// 	printf("%03d\n", (f & 0xffff) * 1000 >> 16);
// }

static void rotateX(fixpoint_t cosa, fixpoint_t sina)
{
	fixpoint_t Yn, Zn;
	int i;

	for (i = 0; i < 8; i++) {
		// print_fixpoint("y: ", vectors[i][1]);
		// print_fixpoint("z: ", vectors[i][2]);
		Yn = _x(vectors[i][1], cosa) - _x(vectors[i][2], sina);
		Zn = _x(vectors[i][1], sina) + _x(vectors[i][2], cosa);
		vectors[i][1] = Yn;
		vectors[i][2] = Zn;
	}
}

static void rotateY(fixpoint_t cosa, fixpoint_t sina)
{
	fixpoint_t Xn, Zn;
	int i;

	for (i = 0; i < 8; i++) {
		Xn = _x(vectors[i][0], cosa) - _x(vectors[i][2], sina);
		Zn = _x(vectors[i][0], sina) + _x(vectors[i][2], cosa);
		vectors[i][0] = Xn;
		vectors[i][2] = Zn;
	}
}

static void rotateZ(fixpoint_t cosa, fixpoint_t sina)
{
	fixpoint_t Yn, Xn;
	int i;

	for (i = 0; i < 8; i++) {
		Xn = _x(vectors[i][0], cosa) - _x(vectors[i][1], sina);
		Yn = _x(vectors[i][0], sina) + _x(vectors[i][1], cosa);
		vectors[i][0] = Xn;
		vectors[i][1] = Yn;
	}
}

int translateX(fixpoint_t x, fixpoint_t z)
{
	return fixpoint_to_int((x + fixpoint(64)) + _x(z, _x(x, perspective)));
}

int translateY(fixpoint_t y, fixpoint_t z)
{
	return fixpoint_to_int((y + fixpoint(32)) + _x(z, _x(y, perspective)));
}

static void draw(void)
{
	oled_drawLine(
		translateX(vectors[0][0], vectors[0][2]),
		translateY(vectors[0][1], vectors[0][2]),
		translateX(vectors[1][0], vectors[1][2]),
		translateY(vectors[1][1], vectors[1][2]));
	oled_drawLine(
		translateX(vectors[1][0], vectors[1][2]),
		translateY(vectors[1][1], vectors[1][2]),
		translateX(vectors[2][0], vectors[2][2]),
		translateY(vectors[2][1], vectors[2][2]));
	oled_drawLine(
		translateX(vectors[2][0], vectors[2][2]),
		translateY(vectors[2][1], vectors[2][2]),
		translateX(vectors[3][0], vectors[3][2]),
		translateY(vectors[3][1], vectors[3][2]));
	oled_drawLine(
		translateX(vectors[3][0], vectors[3][2]),
		translateY(vectors[3][1], vectors[3][2]),
		translateX(vectors[0][0], vectors[0][2]),
		translateY(vectors[0][1], vectors[0][2]));
	oled_drawLine(
		translateX(vectors[4][0], vectors[4][2]),
		translateY(vectors[4][1], vectors[4][2]),
		translateX(vectors[5][0], vectors[5][2]),
		translateY(vectors[5][1], vectors[5][2]));
	oled_drawLine(
		translateX(vectors[5][0], vectors[5][2]),
		translateY(vectors[5][1], vectors[5][2]),
		translateX(vectors[6][0], vectors[6][2]),
		translateY(vectors[6][1], vectors[6][2]));
	oled_drawLine(
		translateX(vectors[6][0], vectors[6][2]),
		translateY(vectors[6][1], vectors[6][2]),
		translateX(vectors[7][0], vectors[7][2]),
		translateY(vectors[7][1], vectors[7][2]));
	oled_drawLine(
		translateX(vectors[7][0], vectors[7][2]),
		translateY(vectors[7][1], vectors[7][2]),
		translateX(vectors[4][0], vectors[4][2]),
		translateY(vectors[4][1], vectors[4][2]));
	oled_drawLine(
		translateX(vectors[0][0], vectors[0][2]),
		translateY(vectors[0][1], vectors[0][2]),
		translateX(vectors[4][0], vectors[4][2]),
		translateY(vectors[4][1], vectors[4][2]));
	oled_drawLine(
		translateX(vectors[1][0], vectors[1][2]),
		translateY(vectors[1][1], vectors[1][2]),
		translateX(vectors[5][0], vectors[5][2]),
		translateY(vectors[5][1], vectors[5][2]));
	oled_drawLine(
		translateX(vectors[2][0], vectors[2][2]),
		translateY(vectors[2][1], vectors[2][2]),
		translateX(vectors[6][0], vectors[6][2]),
		translateY(vectors[6][1], vectors[6][2]));
	oled_drawLine(
		translateX(vectors[3][0], vectors[3][2]),
		translateY(vectors[3][1], vectors[3][2]),
		translateX(vectors[7][0], vectors[7][2]),
		translateY(vectors[7][1], vectors[7][2]));
}

void init_3dcube(void)
{
	int i, j;

	for (i = 0; i < 8; i++)
		for (j = 0; j < 3; j++)
			vectors[i][j] = fixpoint(vectors_init[i][j]);
}

void loop_3dcube(void)
{
	static int iter = 0;

	if (iter++) {
		rotateX((9962 << 16) / 10000, ( 872 << 16) / 10000); // 5
		rotateY((9925 << 16) / 10000, (1219 << 16) / 10000); // 7
		rotateZ((9816 << 16) / 10000, (1908 << 16) / 10000); // 11
	}
	oled_clrScr();
	draw();
	oled_update();
}
