#include "CharacterLCD.h"

LCD MyLCD = LCD();

//setup & main loop
void setup() {
	Serial.begin(9600);
}

void loop() { //blink to make sure arduino is alive
	while(Serial.available() > 0){
		String input = Serial.readString();

		//Serial CLI to interact with the display, recommended to use for debugging
		if(input.substring(0, 5) == "clear"){
			Serial.println("clearing display");
			MyLCD.clearDisp();
		}else if(input.substring(0, 4) == "home"){
			Serial.println("returning home");
			MyLCD.returnHome();
		}else if(input.substring(0, 4) == "data"){
			String param = input.substring(5, 13);
			unsigned char param_val = strToChar(param);

			bool validparam = true;
			for(int i = 0; i < param.length(); i++){
				if(param.charAt(i) != '0' && param.charAt(i) != '1'){
					validparam = false;
					break;
				}
			}

			if(validparam){
				Serial.print("sending binary data ");
				Serial.println(param);

				MyLCD.sendInstruction(param_val, false);
			}else{
				Serial.println("invalid parameter!");
			}
		}else if(input.substring(0, 5) == "allon"){
			Serial.println("all on");
			MyLCD.displayControl(true, true, true);
		}else if(input.substring(0, 5) == "pinit"){
			Serial.println("plain initialization");
			MyLCD.functionSet(true, true, false);
		}else if(input.substring(0, 4) == "inst"){
			String param = input.substring(5, 13);
			unsigned char param_val = strToChar(param);

			bool validparam = true;
			for(int i = 0; i < param.length(); i++){
				if(param.charAt(i) != '0' && param.charAt(i) != '1'){
					validparam = false;
					break;
				}
			}

			if(validparam){
				Serial.print("sending binary instruction ");
				Serial.println(param);

				MyLCD.sendInstruction(param_val);
			}else{
				Serial.println("invalid parameter!");
			}
		}else if(input.substring(0, 6) == "setbus"){
			char param = input.charAt(7);
			if(param == 'l'){
				Serial.println("programmer set to 8-bit communication mode");
				MyLCD.setLongBus(true);
			}else if(param == 's'){
				Serial.println("programmer set to 4-bit communication mode");
				MyLCD.setLongBus(false);
			}else{
				Serial.println("invalid parameter!");
			}
		}else if(input.substring(0, 9) == "shiftloop"){
			MyLCD.returnHome();
			
		}
		}else{
		  Serial.println("unrecognized instruction!");
		}
	}
}