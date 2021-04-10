const int RS = 11, EN = 12;
const int D0 = 2, D1 = 3, D2 = 4, D3 = 5, D4 = 6, D5 = 7, D6 = 8, D7 = 9;
const float write_duration = 100;

bool longbus = true;

unsigned char strToChar(String str){
  unsigned char res = 0;
  
  for(int i = 0; i < str.length(); i++){
    res = res << 1;
    if(str.charAt(i) == '1') res++;
  }
  return res;
}

//utility to communicate with LCD
void sendByte(unsigned char data){
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

void sendNibble(unsigned char nib){
  digitalWrite(EN, HIGH);

  digitalWrite(D7, (nib & 0b1000) >> 3);
  digitalWrite(D6, (nib & 0b0100) >> 2);
  digitalWrite(D5, (nib & 0b0010) >> 1);
  digitalWrite(D4, (nib & 0b0001) >> 0);

  delay(write_duration);
  digitalWrite(EN, LOW);
}

void sendInstruction(unsigned char val, bool is_inst = true){
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

void sendData(unsigned char data){
  sendInstruction(data, false);
}

//instructions
void clearDisp(){
  sendInstruction(0b00000001);
}

void setDDRAMAddress(unsigned char addr){
  sendInstruction(0b01000000 & (addr & 0b00111111));
}

void writeToRAM(unsigned char data){
  sendData(data);
}

void functionSet(bool data_length, bool lines_num, bool font){
  sendInstruction(0b00100001 & (data_length << 4) & (lines_num << 3) & (font << 2));
}

void displayControl(bool disp, bool curs, bool blnk){
  sendInstruction(0b00001000 & (disp << 2) & (curs << 1) & (curs << 0));
}

void returnHome(){
  sendInstruction(0b00000010);
}
