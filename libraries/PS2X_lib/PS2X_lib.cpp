#include "PS2X_lib.h"
#include <math.h>
#include <stdio.h>
#include <stdint.h>

#if !defined(__SAM3X8E__) && !defined(__arm__)
#include <avr/io.h>
#endif
#if ARDUINO > 22
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

//#define PS2_DEBUG
#ifdef PS2_DEBUG
    //#define PS2_DEBUG_VERBOSE
    #define PS2X_COM_DEBUG
    #define PS2_PRINT(x)        Serial.print(x);
    #define PS2_PRINTF(x,y)     Serial.print(x,y);
    #define PS2_PRINTLN(x)      Serial.println(x);
    #define PS2_PRINTFLN(x,y)   Serial.println(x,y);
    #define PS2_PRINTBYTE(b)    if(b < 0x10){ Serial.print("0");}Serial.print(b, HEX);Serial.print(" ");
#else
    #define PS2_PRINT(x)
    #define PS2_PRINTF(x,y)
    #define PS2_PRINTLN(x)
    #define PS2_PRINTFLN(x,y)
    #define PS2_PRINTBYTE(b)
#endif

static byte enter_config[]={0x01,0x43,0x00,0x01,0x00};
static byte set_mode[]={0x01,0x44,0x00,0x01,0x03,0x00,0x00,0x00,0x00};
static byte set_bytes_large[]={0x01,0x4F,0x00,0xFF,0xFF,0x03,0x00,0x00,0x00};
static byte exit_config[]={0x01,0x43,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A};
static byte enable_rumble[]={0x01,0x4D,0x00,0x00,0x01};
static byte type_read[]={0x01,0x45,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};

boolean PS2X::NewButtonState() {
   return ((last_buttons ^ buttons) > 0);

}

boolean PS2X::NewButtonState(unsigned int button) {
  return (((last_buttons ^ buttons) & button) > 0);
}

boolean PS2X::ButtonPressed(unsigned int button) {
  return(NewButtonState(button) & Button(button));
}

boolean PS2X::ButtonReleased(unsigned int button) {
  return((NewButtonState(button)) & ((~last_buttons & button) > 0));
}
  
boolean PS2X::Button(uint16_t button) {
   return ((~buttons & button) > 0);
}

unsigned int PS2X::ButtonDataByte() {
   return (~buttons);
}

byte PS2X::Analog(byte button) {
  return PS2data[button];
}

unsigned char PS2X::_gamepad_shiftinout (char byte) {
    #ifdef PS2_DEBUG_VERBOSE
        PS2_PRINTLN("_gamepad_shiftinout");
        PS2_PRINT("\tbyte: "); PS2_PRINTBYTE((uint8_t)byte); PS2_PRINTLN("");
    #endif
    
    unsigned char tmp = 0;
    for(i = 0; i < 8; i++) {

        if(CHK(byte, i)) CMD_SET();
        else  CMD_CLR();
        CLK_CLR();

        delayMicroseconds(CTRL_CLK);

        if(DAT_CHK()) SET(tmp,i);
        CLK_SET();
        
        #if CTRL_CLK_HIGH
            delayMicroseconds(CTRL_CLK_HIGH);
        #endif	  
    }
    CMD_SET();
    delayMicroseconds(CTRL_BYTE_DELAY);
    
    #ifdef PS2_DEBUG_VERBOSE
        PS2_PRINT("exit _gamepad_shiftinout tmp: "); PS2_PRINT(tmp); PS2_PRINTLN("");
    #endif
    
    return tmp;
}

void PS2X::read_gamepad() {
    read_gamepad(false, 0x00);
}

boolean PS2X::read_gamepad(boolean motor1, byte motor2) {
    PS2_PRINTLN("read_gamepad");
    PS2_PRINT("\tmotor1: "); PS2_PRINT(motor1 ? "true" : "false"); PS2_PRINTLN("");
    PS2_PRINT("\tmotor2: "); PS2_PRINTBYTE(motor2); PS2_PRINTLN("");
    
    double temp = millis() - last_read;
  
    if (temp > 1500) //waited to long
        reconfig_gamepad();

    if(temp < read_delay)  //waited too short
        delay(read_delay - temp);
    
    if(motor2 != 0x00)
        motor2 = map(motor2,0,255,0x40,0xFF); //noting below 40 will make it spin
  
    char dword[9] = {0x01,0x42,0,motor1,motor2,0,0,0,0};
    byte dword2[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    
    // Try a few times to get valid data...
    PS2_PRINTLN("\tAttempting acquire valid data");
    for (byte RetryCnt = 0; RetryCnt < 5; RetryCnt++) {
        CMD_SET();
        CLK_SET();
        ATT_CLR(); // low enable joystick
        
        delayMicroseconds(CTRL_BYTE_DELAY);
        //Send the command to send button and joystick data;

        for (int i = 0; i < 9; i++) {
            #ifdef PS2_DEBUG
                if(i == 1){
                    PS2_PRINTLN("\t - setting PS2data[1] = _gamepad_shaftinout(dword[1])");
                    PS2_PRINT("\t - PS2data[1] start value: "); PS2_PRINTFLN(PS2data[i], HEX);
                    PS2_PRINT("\t - dword[1] start value: "); PS2_PRINTFLN(dword[i], HEX);
                }
            #endif
            PS2data[i] = _gamepad_shiftinout(dword[i]);
            #ifdef PS2_DEBUG
                if(i == 1){
                    PS2_PRINT("\t - dword[1] end value: "); PS2_PRINTFLN(dword[i], HEX);
                    PS2_PRINT("\t - PS2data[1] end value: "); PS2_PRINTFLN(PS2data[i], HEX);
                }
            #endif
        }


        if(PS2data[1] == 0x79) {  //if controller is in full data return mode, get the rest of data
            for (int i = 0; i < 12; i++) {
                PS2data[i + 9] = _gamepad_shiftinout(dword2[i]);
            }
        }

        ATT_SET(); // HI disable joystick
        
        // Check to see if we received valid data or not.  We should be in analog mode for our data
        // to be valie
        PS2_PRINT("\tCheck analog mode ((PS2data[1] & 0xf0 == 0x70)): ");
        PS2_PRINTLN((PS2data[1] & 0xf0) == 0x70 ? "true" : "false");
        
        if ((PS2data[1] & 0xf0) == 0x70)
            break;

        // If we got to here, we are not in analog mode, try to recover...
        PS2_PRINTLN("\treconfiguring gamepad");
        
        reconfig_gamepad();	// try to get back into Analog mode.
        delay(read_delay);
    }
  
    // If we get here and still not in analog mode, try increasing the read_delay...
    if ((PS2data[1] & 0xf0) != 0x70) {
        if (read_delay < 10)
            PS2_PRINTLN("\tincrease read delay");
            read_delay++;	// see if this helps out...
    }

	#ifdef PS2X_COM_DEBUG
        PS2_PRINTLN("\tOUT:IN");
        PS2_PRINT("\t");
		for(int i=0; i<9; i++){
			PS2_PRINTF(dword[i], HEX);
			PS2_PRINT(":");
			PS2_PRINTF(PS2data[i], HEX);
			PS2_PRINT(" ");
		}
		for (int i = 0; i<12; i++) {
			PS2_PRINTF(dword2[i], HEX);
			PS2_PRINT(":");
			PS2_PRINTF(PS2data[i+9], HEX);
			PS2_PRINT(" ");
		}
        PS2_PRINTLN("");	
	#endif
	
    last_buttons = buttons; //store the previous buttons states

    #if defined(__AVR__)
        buttons = *(uint16_t*)(PS2data+3);   //store as one value for multiple functions
    #else
        buttons =  (uint16_t)(PS2data[4] << 8) + PS2data[3];   //store as one value for multiple functions
    #endif
    last_read = millis();
    
    bool tmp = ((PS2data[1] & 0xf0) == 0x70);
    PS2_PRINT("exit read_gamepad ((PS2data[1] & 0xf0) == 0x70): "); PS2_PRINTLN(tmp ? "true" : "false");
    
    return tmp;
}

byte PS2X::config_gamepad(uint8_t clk, uint8_t cmd, uint8_t att, uint8_t dat) {
	return config_gamepad(clk, cmd, att, dat, false, false);
}


byte PS2X::config_gamepad(uint8_t clk, uint8_t cmd, uint8_t att, uint8_t dat, bool pressures, bool rumble) {
    PS2_PRINTLN("config_gamepad");
    
    byte temp[sizeof(type_read)];
    
#ifdef __AVR__
    PS2_PRINTLN("\tdefined __AVR__");
    _clk_mask = digitalPinToBitMask(clk);
    _clk_oreg = portOutputRegister(digitalPinToPort(clk));
    _cmd_mask = digitalPinToBitMask(cmd);
    _cmd_oreg = portOutputRegister(digitalPinToPort(cmd));
    _att_mask = digitalPinToBitMask(att);
    _att_oreg = portOutputRegister(digitalPinToPort(att));
    _dat_mask = digitalPinToBitMask(dat);
    _dat_ireg = portInputRegister(digitalPinToPort(dat));
#elif defined(__SAM3X8E__) || defined(__arm__)
    PS2_PRINTLN("\tdefined (__SAM3X8E__) || defined(__arm__)");
	// Defines for Arduino Due or Teensy 3.
	_clk = clk;
	_cmd = cmd;
	_att = att;
	_dat = dat;
#else
    PS2_PRINTLN("\tdefined OTHER");
	uint32_t            lport;                   // Port number for this pin
	_clk_mask = digitalPinToBitMask(clk); 
	lport = digitalPinToPort(clk);
	_clk_lport_set = portOutputRegister(lport) + 2;
	_clk_lport_clr = portOutputRegister(lport) + 1;

	_cmd_mask = digitalPinToBitMask(cmd); 
	lport = digitalPinToPort(cmd);
	_cmd_lport_set = portOutputRegister(lport) + 2;
	_cmd_lport_clr = portOutputRegister(lport) + 1;

	_att_mask = digitalPinToBitMask(att); 
	lport = digitalPinToPort(att);
	_att_lport_set = portOutputRegister(lport) + 2;
	_att_lport_clr = portOutputRegister(lport) + 1;
  
	_dat_mask = digitalPinToBitMask(dat); 
	_dat_lport = portInputRegister(digitalPinToPort(dat));

#endif  
    
    PS2_PRINT("\tclk: ");PS2_PRINTBYTE(clk);PS2_PRINTLN("");
    PS2_PRINT("\tatt: ");PS2_PRINTBYTE(att);PS2_PRINTLN("");
    PS2_PRINT("\tcmd: ");PS2_PRINTBYTE(cmd);PS2_PRINTLN("");
    pinMode(clk, OUTPUT); //configure ports
    pinMode(att, OUTPUT);
    pinMode(cmd, OUTPUT);

#if defined(__AVR__)
    PS2_PRINT("\tdat: ");PS2_PRINTBYTE(dat);PS2_PRINTLN(" INPUT");
    pinMode(dat, INPUT);
    digitalWrite(dat, HIGH); //enable pull-up 
#elif defined(__SAM3X8E__) || defined(__arm__)
    PS2_PRINT("\tdat: ");PS2_PRINTBYTE(dat);PS2_PRINTLN(" INPUT_PULLUP");
    pinMode(dat, INPUT_PULLUP);
#endif
    
   CMD_SET(); // SET(*_cmd_oreg,_cmd_mask);
   CLK_SET();
   
   //new error checking. First, read gamepad a few times to see if it's talking
   read_gamepad();
   read_gamepad();
   
   //see if it talked
   if(PS2data[1] != 0x41 && PS2data[1] != 0x71 && PS2data[1] != 0x73 && PS2data[1] != 0x79){ //see if mode came back. If still anything but 41, 73 or 79, then it's not talking
        PS2_PRINTLN("Controller mode not matched or no controller found");
        PS2_PRINT("Expected 0x41 or 0x73, got ");
        PS2_PRINTFLN(PS2data[1], HEX);
        
        //while(true);
        return 1; //return error code 1
	}
  
  //try setting mode, increasing delays if need be. 
  read_delay = 1;
  
  for(int y = 0; y <= 10; y++)
  {
   sendCommandString(enter_config, sizeof(enter_config)); //start config run
   
   //read type
   	delayMicroseconds(CTRL_BYTE_DELAY);

	CMD_SET();
    CLK_SET();
    ATT_CLR(); // low enable joystick
	
    delayMicroseconds(CTRL_BYTE_DELAY);

    for (int i = 0; i<9; i++) {
	  temp[i] = _gamepad_shiftinout(type_read[i]);
    }

	ATT_SET(); // HI disable joystick
	
	controller_type = temp[3];
   
   sendCommandString(set_mode, sizeof(set_mode));
   if(rumble){ sendCommandString(enable_rumble, sizeof(enable_rumble)); en_Rumble = true; }
   if(pressures){ sendCommandString(set_bytes_large, sizeof(set_bytes_large)); en_Pressures = true; }
   sendCommandString(exit_config, sizeof(exit_config));
   
   read_gamepad();
   
   if(pressures){
	if(PS2data[1] == 0x79)
		break;
	if(PS2data[1] == 0x73)
		return 3;
   }
   
    if(PS2data[1] == 0x73)
      break;
      
    if(y == 10){
		PS2_PRINTLN("Controller not accepting commands");
		PS2_PRINT("mode stil set at");
		PS2_PRINTFLN(PS2data[1], HEX);
        return 2; //exit function with error
    }
    
    read_delay += 1; //add 1ms to read_delay
  }
   
 return 0; //no error if here
}



void PS2X::sendCommandString(byte string[], byte len) {
    #ifdef PS2X_COM_DEBUG
        PS2_PRINTLN("sendCommandString");
        
        byte temp[len];
        ATT_CLR(); // low enable joystick
        delayMicroseconds(CTRL_BYTE_DELAY);

        for (int y=0; y < len; y++)
            temp[y] = _gamepad_shiftinout(string[y]);

        ATT_SET(); //high disable joystick  
        delay(read_delay);                  //wait a few

        PS2_PRINTLN("\tOUT:IN Configure");
        PS2_PRINT("\t");
        for(int i=0; i<len; i++){
            PS2_PRINTF(string[i], HEX);
            PS2_PRINT(":");
            PS2_PRINTF(temp[i], HEX);
            PS2_PRINT(" ");
        }
        PS2_PRINTLN("");
        PS2_PRINTLN("exit sendCommandString");
    #else
        ATT_CLR(); // low enable joystick
        for (int y=0; y < len; y++)
            _gamepad_shiftinout(string[y]);
        
        ATT_SET(); //high disable joystick  
        delay(read_delay);                  //wait a few
    #endif
}

 

byte PS2X::readType() {
/*
	byte temp[sizeof(type_read)];
	
	sendCommandString(enter_config, sizeof(enter_config));
	
	delayMicroseconds(CTRL_BYTE_DELAY);

	CMD_SET();
    CLK_SET();
    ATT_CLR(); // low enable joystick
	
    delayMicroseconds(CTRL_BYTE_DELAY);

    for (int i = 0; i<9; i++) {
	  temp[i] = _gamepad_shiftinout(type_read[i]);
    }
	
	sendCommandString(exit_config, sizeof(exit_config));
	 
	if(temp[3] == 0x03)
		return 1;
	else if(temp[3] == 0x01)
		return 2;
	
	return 0;
	*/
	
	if(controller_type == 0x03)
		return 1;
	else if(controller_type == 0x01)
		return 2;
	
	return 0;
	
}

void PS2X::enableRumble() {
  
     sendCommandString(enter_config, sizeof(enter_config));
     sendCommandString(enable_rumble, sizeof(enable_rumble));
     sendCommandString(exit_config, sizeof(exit_config));
     en_Rumble = true;
  
}

bool PS2X::enablePressures() {
    sendCommandString(enter_config, sizeof(enter_config));
    sendCommandString(set_bytes_large, sizeof(set_bytes_large));
    sendCommandString(exit_config, sizeof(exit_config));
	 
	read_gamepad();
	read_gamepad();
	 
    if(PS2data[1] != 0x79)
		return false;
		
    en_Pressures = true;
	return true;
}

void PS2X::reconfig_gamepad(){
    sendCommandString(enter_config, sizeof(enter_config));
    sendCommandString(set_mode, sizeof(set_mode));
    if (en_Rumble)
      sendCommandString(enable_rumble, sizeof(enable_rumble));
    if (en_Pressures)
        sendCommandString(set_bytes_large, sizeof(set_bytes_large));
    sendCommandString(exit_config, sizeof(exit_config));
}


#if defined(__AVR__)
inline void  PS2X::CLK_SET(void) {
	
   register uint8_t old_sreg = SREG;
   cli();
   *_clk_oreg |= _clk_mask;
   SREG = old_sreg;
}

inline void  PS2X::CLK_CLR(void) {
   register uint8_t old_sreg = SREG;
   cli();
   *_clk_oreg &= ~_clk_mask;
   SREG = old_sreg;
}

inline void  PS2X::CMD_SET(void) {
   register uint8_t old_sreg = SREG;
   cli();
   *_cmd_oreg |= _cmd_mask; // SET(*_cmd_oreg,_cmd_mask);
   SREG = old_sreg;
}

inline void  PS2X::CMD_CLR(void) {
   register uint8_t old_sreg = SREG;
   cli();
   *_cmd_oreg &= ~_cmd_mask; // SET(*_cmd_oreg,_cmd_mask);
   SREG = old_sreg;
}

inline void  PS2X::ATT_SET(void) {
   register uint8_t old_sreg = SREG;
   cli();
  *_att_oreg |= _att_mask ; 	
   SREG = old_sreg;
}

inline void PS2X::ATT_CLR(void) {
   register uint8_t old_sreg = SREG;
   cli();
  *_att_oreg &= ~_att_mask; 
   SREG = old_sreg;
}

inline bool PS2X::DAT_CHK(void) {
	return (*_dat_ireg & _dat_mask)? true : false;
}

#elif defined(__SAM3X8E__) || defined(__arm__)
inline void  PS2X::CLK_SET(void) {
    digitalWrite(_clk, HIGH);
}

inline void  PS2X::CLK_CLR(void) {
	digitalWrite(_clk, LOW);
}

inline void  PS2X::CMD_SET(void) {
    digitalWrite(_cmd, HIGH);
}

inline void  PS2X::CMD_CLR(void) {
	digitalWrite(_cmd, LOW);
}

inline void  PS2X::ATT_SET(void) {
    digitalWrite(_att, HIGH);
}

inline void PS2X::ATT_CLR(void) {
    digitalWrite(_att, LOW);
}

inline bool PS2X::DAT_CHK(void) {
	return digitalRead(_dat);
}

#else
// On pic32, use the set/clr registers to make them atomic...
inline void  PS2X::CLK_SET(void) {
	*_clk_lport_set |= _clk_mask;
}

inline void  PS2X::CLK_CLR(void) {
	*_clk_lport_clr |= _clk_mask;
}

inline void  PS2X::CMD_SET(void) {
	*_cmd_lport_set |= _cmd_mask;
}

inline void  PS2X::CMD_CLR(void) {
	*_cmd_lport_clr |= _cmd_mask;
}

inline void  PS2X::ATT_SET(void) {
	*_att_lport_set |= _att_mask;
}

inline void PS2X::ATT_CLR(void) {
	*_att_lport_clr |= _att_mask;
}

inline bool PS2X::DAT_CHK(void) {
	return (*_dat_lport & _dat_mask)? true : false;

}

#endif
