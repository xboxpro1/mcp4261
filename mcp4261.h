#ifndef _MCP4261_H_
#define _MCP4261_H_

#include <Arduino.h>
#include <SPI.h>

const static uint8_t WRITE_W0  = B00000000;
const static uint8_t WRITE_W1  = B00010000;
const static uint8_t READ_W0  = B00001100;
const static uint8_t READ_W1  = B00011100; 
const static uint8_t WRITE_W0NV  = B00100000;
const static uint8_t WRITE_W1NV  = B00110000;
const static uint8_t READ_W0NV  = B00101100;
const static uint8_t READ_W1NV  = B00111100;   

const static uint8_t TCON_READ  =  B01001100;
const static uint8_t TCON_WRITE  = B01000000;

const static uint8_t STATUS_READ  =  B01011100;


 const static uint8_t WP_DIS = B11110100;
 const static uint8_t WP_EN =  B11111000;

                               
 //EEprom write adresses
 const static uint8_t EEPROM_W[] = {B01100000,B01110000,B10000000,B10010000,B10100000,B10110000,B11000000,B11010000,B11100000,B11110000};
 //EEprom read adresses
 const static uint8_t EEPROM_R[] = {B01101111,B01111111,B10001111,B10011111,B10101111,B10111111,B11001111,B11011111,B11101111,B11111111};


class MCP4261{

public:

MCP4261(int cs);
MCP4261(int cs, int pe, int nv);
int  getW0Pos();
int  getW0NVPos();
int  getW1Pos();
int  getW1NVPos();
void setW0Pos(uint16_t pos);
void setW0NVPos(uint16_t pos);
void setW1Pos(uint16_t pos);
void setW1NVPos(uint16_t pos);
void enable();
void disable();
void protectNV(int nvp);
void wiperOn(bool w0_on, bool w1_on);
uint16_t readStatus();
uint16_t readTcon();
void writeTcon(uint16_t tcon);

private:

void write(byte cmd_byte, byte data_byte);
uint16_t read(byte cmd_byte);
uint16_t byte2uint16(byte high_byte, byte low_byte);
int _cs; 
int _pe;
int _nv;

};

#endif
