#include "CharacterLCD.h"

using namespace std;

unsigned char strToChar(String str){
	unsigned char res = 0;

	for(int i = 0; i < str.length(); i++){
		res = res << 1;
		if(str.charAt(i) == '1') res++;
	}
	return res;
}

LCD::LCD(int RegSel = 11, int Enable = 12, int data0 = 2, int data1 = 3, int data2 = 4, int data3 = 5, int data4 = 6, int data5 = 7, int data6 = 8, int data7 = 9){
	RS = RegSel;
	EN = Enable;

	D0 = data0;
	D1 = data1;
	D2 = data2;
	D3 = data3;
	D4 = data4;
	D5 = data5;
	D6 = data6;
	D7 = data7;

	pinMode(RS, OUTPUT);
	pinMode(EN, OUTPUT);

	pinMode(D0, OUTPUT);
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
}

void LCD::setWriteDuration(float dur){
	write_duration = dur;
}

void LCD::setLongBus(bool is_long){
	longbus = is_long;
}

//utility to communicate with LCD
void LCD::sendByte(unsigned char data){
	digitalWrite(EN, HIGH);
  
	digitalWrite(D7, (data & 0b10000000) >> 7);
	digitalWrite(D6, (data & 0b01000000) >> 6);
	digitalWrite(D5, (data & 0b00100000) >> 5);
	digitalWrite(D4, (data & 0b00010000) >> 4);
	digitalWrite(D3, (data & 0b00001000) >> 3);
	digitalWrite(D2, (data & 0b00000100) >> 2);
	digitalWrite(D1, (data & 0b00000010) >> 1);
	digitalWrite(D0, (data & 0b00000001) >> 0);


	delay(write_duration);
	digitalWrite(EN, LOW);
}

void LCD::sendNibble(unsigned char nib){
	digitalWrite(EN, HIGH);

	digitalWrite(D7, (nib & 0b1000) >> 3);
	digitalWrite(D6, (nib & 0b0100) >> 2);
	digitalWrite(D5, (nib & 0b0010) >> 1);
	digitalWrite(D4, (nib & 0b0001) >> 0);

	delay(write_duration);
	digitalWrite(EN, LOW);
}

void LCD::sendInstruction(unsigned char val, bool is_inst = true){
	digitalWrite(RS, !is_inst);
	if(longbus){
		sendByte(val);
	}else{
		sendNibble(val >> 4);
		delay(write_duration);
		sendNibble(val & 0b1111);
	}

	delay(write_duration);
}

void LCD::sendData(unsigned char data){
	sendInstruction(data, false);
}

//instructions
void LCD::clearDisp(){
	sendInstruction(0b00000001);
}

void LCD::setDDRAMAddress(unsigned char addr){
	addr &= 0b01111111
	sendInstruction(0b10000000 & addr);
	DDRAMAddress = addr;
}

void LCD::writeToRAM(unsigned char data){
	sendData(data);
	DDRAMAddress += entry_dir==FORWARD ? 1 : -1; //remember to check if addr incremented on display shift
}

void LCD::functionSet(bool data_length, bool lines_num, bool font){
	sendInstruction(0b00100001 & (data_length << 4) & (lines_num << 3) & (font << 2));
	longbus = data_length;
	num_of_lines = lines_num ? 2 : 1;
	small_font = !font;
}

void LCD::displayControl(bool disp, bool curs, bool blnk){
	sendInstruction(0b00001000 & (disp << 2) & (curs << 1) & (curs << 0));
	disp_active = disp;
	curs_active = curs;
	blnk_active = blnk;
}

void LCD::returnHome(){
	sendInstruction(0b00000010);
}

void setEntryMode(bool inc, bool curs){
	sendInstruction(0b00000100 & (inc << 1) & (curs << 0));
}