#ifndef _MCP4261_H_
#define _MCP4261_H_

#include <Arduino.h>
#include <SPI.h>

const static uint8_t WRITE_W0  = 0x00;
const static uint8_t WRITE_W1  = 0x10;
const static uint8_t WRITE_W0NV  = 0x20;
const static uint8_t WRITE_W1NV  = 0x30;
const static uint8_t TCON_WRITE  = 0x40;
const static uint8_t READ_W0  = 0x0C;
const static uint8_t READ_W1  = 0x1C; 
const static uint8_t READ_W0NV  = 0x2C;
const static uint8_t READ_W1NV  = 0x3C;   
const static uint8_t TCON_READ  =  0x4C;
const static uint8_t STATUS_READ  =  0x5C;

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
