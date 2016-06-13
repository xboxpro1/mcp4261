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


class MCP4261{

public:

MCP4261(int chipSelect);
MCP4261(int chipSelect, int potE, int proNV);
int  getW0Pos();
int  getW0NVPos();
int  getW1Pos();
int  getW1NVPos();
void setW0Pos(uint16_t pos);
void setW0NVPos(uint16_t pos);
void setW1Pos(uint16_t pos);
void setW1NVPos(uint16_t pos);
void enable(uint8_t pen);
void protectNV(uint8_t nvp);
void wiperOn(uint8_t on0, uint8_t on1);
int readStatus();
int readTcon();
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
