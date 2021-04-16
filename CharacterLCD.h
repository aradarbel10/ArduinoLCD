#pragma once
#include "Arduino.h"

unsigned char strToChar(String str);

class LCD{
public:
	LCD(int RegSel = 11, int Enable = 12, int data0 = 2, int data1 = 3, int data2 = 4, int data3 = 5, int data4 = 6, int data5 = 7, int data6 = 8, int data7 = 9);

	enum DIRECTION{ BACK, FORWARD }

	//higher-level stuff
	void print(String str);
	void drawBitmap(bool[][] bmp);

	//instructions
	void clearDisp();
	void returnHome();
	void setEntryMode(DIRECTION dir, bool curs);
	void setDDRAMAddress(unsigned char addr);
	void writeToRAM(unsigned char data);
	void functionSet(bool data_length, bool lines_num, bool font);
	void displayControl(bool disp, bool curs, bool blnk);

	//utility to communicate with LCD
	void setWriteDuration(float dur);
	void setLongBus(bool is_long);

	void sendByte(unsigned char data);
	void sendNibble(unsigned char nib);
	void sendInstruction(unsigned char val, bool is_inst = true);
	void sendData(unsigned char data);

private:
	//digital pins
	int RS, EN;
	int D0, D1, D2, D3, D4, D5, D6, D7;

	//timing
	float write_duration = 50;

	//display settings
	bool longbus = true;
	int num_of_lines = 2;
	bool small_font = true;

	bool disp_active = false;
	bool curs_active = false;
	bool blnk_active = false;

	DIRECTION entry_dir = FORWARD;
	bool entry_shift_disp = false;

	uint8_t DDRAMAddress = 0;

};