#ifndef MCP4141_H
#define MCP4141_H

#include "Arduino.h"
#include "SPI.h" 




const static uint8_t WRITE_W0  = B00000000;
const static uint8_t WRITE_W1  = B00010000;
const static uint8_t READ_W0  = B00001100;  
const static uint8_t READ_W1  = B00011100;    
const static uint8_t INC_W0  = B00000100;
const static uint8_t INC_W1  = B00010100;
const static uint8_t DEC_W0  = B00001000;
const static uint8_t DEC_W1  = B00011000;

const static uint8_t TCON_READ  =  B01001100;
const static uint8_t TCON_WRITE  = B01000000;


 const static uint8_t WP_DIS = B11110100;
 const static uint8_t WP_EN =  B11111000;

                               
 //EEprom write adresses
 const static uint8_t EEPROM_W[] = {B01100000,B01110000,B10000000,B10010000,B10100000,B10110000,B11000000,B11010000,B11100000,B11110000};
 //EEprom read adresses
 const static uint8_t EEPROM_R[] = {B01101111,B01111111,B10001111,B10011111,B10101111,B10111111,B11001111,B11011111,B11101111,B11111111};





class MCP4261{

public:

MCP4261(int cs);
int  getW0Pos();
int  getW1Pos();
void incW0();
void incW1();
void decW0();
void decW1();
void setW0Pos(uint16_t pos);
void setW1Pos(uint16_t pos);
void saveW0Pos(int num);
void saveW1Pos(int num);
void  restoreW0Pos(int num);
void  restoreW1Pos(int num);
void  mute(boolean mute);

uint16_t readTcon();
void writeTcon(uint16_t tcon);


private:

void write(byte cmd_byte, byte data_byte);
uint16_t read(byte cmd_byte);
uint16_t byte2uint16(byte high_byte, byte low_byte);
int cs; 


};

#endif
