#include "mcp4261.h"


MCP4261::MCP4261(int chipSelect){
  _cs = chipSelect;
  _pe = 99;
  _nv = 99;
  pinMode(_cs, OUTPUT); 
  digitalWrite(_cs, HIGH); 
  SPI.begin();
}

MCP4261::MCP4261(int chipSelect, int potE, int proNV){
  _cs = chipSelect;
  _pe = potE;
  _nv = proNV;
  pinMode(_cs, OUTPUT); 
  digitalWrite(_cs, HIGH); 
  pinMode(_pe, OUTPUT); 
  digitalWrite(_pe, HIGH);
  pinMode(_nv, OUTPUT); 
  digitalWrite(_nv, HIGH);
  SPI.begin();
}

void MCP4261::write(byte cmd_byte, byte data_byte)
{
  #ifdef SPI_HAS_TRANSACTION
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  #endif
  digitalWrite(_cs, LOW);  
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(data_byte);
  digitalWrite(_cs, HIGH);
  #ifdef SPI_HAS_TRANSACTION
    SPI.endTransaction();
  #endif
  bool result = ~low_byte;
}

uint16_t MCP4261::read(byte cmd_byte)
{
  #ifdef SPI_HAS_TRANSACTION
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  #endif
  digitalWrite(_cs, LOW); 
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(0xFF);
  digitalWrite(_cs, HIGH);
  #ifdef SPI_HAS_TRANSACTION
    SPI.endTransaction();
  #endif
  return byte2uint16(high_byte, low_byte);
}

uint16_t MCP4261::byte2uint16(byte high_byte, byte low_byte)
{
  return (uint16_t)high_byte<<8 | (uint16_t)low_byte;
}

int  MCP4261::getW0Pos(){
 int pos =   0x01FF &  read(READ_W0);
 return pos;
}

int  MCP4261::getW0NVPos(){
 int pos =   0x01FF &  read(READ_W0NV);
 return pos;
}

int  MCP4261::getW1Pos(){
 int pos =   0x01FF &  read(READ_W1);
 return pos;
}

int  MCP4261::getW1NVPos(){
 int pos =   0x01FF &  read(READ_W1NV);
 return pos;
}

void MCP4261::setW0Pos(uint16_t pos){
      write(WRITE_W0, pos);
}

void MCP4261::setW0NVPos(uint16_t pos){
      write(WRITE_W0NV, pos);
      delay(5);
}

void MCP4261::setW1Pos(uint16_t pos){
      write(WRITE_W1, pos);
}

void MCP4261::setW1NVPos(uint16_t pos){
      write(WRITE_W1NV, pos);
      delay(5);
}

void MCP4261::enable(uint8_t pen){
      if(_pe != 99){
        digitalWrite(_pe, pen);
      }
}

void MCP4261::protectNV(uint8_t nvp){
      if(_nv != 99){
        digitalWrite(_nv, nvp);
      }
}

int MCP4261::readTcon(){
  int con =   0x01FF &  read(TCON_READ);
  return con;
}

void MCP4261::writeTcon(uint16_t tcon){
    write(TCON_WRITE,tcon);
}

int MCP4261::readStatus(){
  int sta =   0x01FF &   read(STATUS_READ);
  return sta;
}

void MCP4261::wiperOn(uint8_t on0, uint8_t on1){
  uint16_t won = 0x00;
  if(on1 == 1){
    won = 0x70;
    }
  if(on0 == 1){
    won = won + 0x07;
    }
  writeTcon(won);
}

