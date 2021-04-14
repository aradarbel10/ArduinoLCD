#include "Arduino.h"

unsigned char strToChar(String str);

class LCD{
public:
	LCD() = default;
	LCD(int RegSel, int Enable, int data0, int data1, int data2, int data3, int data4, int data5, int data6, int data7);

	//instructions
	void clearDisp();
	void setDDRAMAddress(unsigned char addr);
	void writeToRAM(unsigned char data);
	void functionSet(bool data_length, bool lines_num, bool font);
	void displayControl(bool disp, bool curs, bool blnk);
	void returnHome();

	//utility to communicate with LCD
	void setWriteDuration(float dur);
	void setLongBus(bool is_long);

	void sendByte(unsigned char data);
	void sendNibble(unsigned char nib);
	void sendInstruction(unsigned char val, bool is_inst = true);
	void sendData(unsigned char data);

private:
	int RS = 11, EN = 12;
	int D0 = 2, D1 = 3, D2 = 4, D3 = 5, D4 = 6, D5 = 7, D6 = 8, D7 = 9;
	float write_duration = 50;

	bool longbus = true;
};