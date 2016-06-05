#include <mcp4261.h>


MCP4261::MCP4261(int chipSelect){
  cs = chipSelect;
  pe = 99;
  nv = 99;
  pinMode(cs, OUTPUT); 
  digitalWrite(cs, HIGH); 
  SPI.begin();
}
MCP4261::MCP4261(int chipSelect, int potE, int proNV){
  cs = chipSelect;
  pe = potE;
  nv = proNV;
  pinMode(cs, OUTPUT); 
  digitalWrite(cs, HIGH); 
  pinMode(pe, OUTPUT); 
  digitalWrite(pe, HIGH);
  pinMode(nv, OUTPUT); 
  digitalWrite(nv, HIGH);
  SPI.begin();
}
void MCP4261::write(byte cmd_byte, byte data_byte)
{
  #ifdef SPI_HAS_TRANSACTION
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  #endif
  digitalWrite(cs, LOW);  
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(data_byte);
  digitalWrite(cs, HIGH);
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
  digitalWrite(cs, LOW); 
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(0xFF);
  digitalWrite(cs, HIGH);
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
void MCP4261::enable(){
      if(pe != 99){
        digitalWrite(pe, LOW);
      }
}
void MCP4261::disable(){
      if(pe != 99){
        digitalWrite(pe, HIGH);
      }
}
void MCP4261::protectNV(int nvp){
      if(nv != 99){
        digitalWrite(nv, nvp);
      }
}
uint16_t MCP4261::readTcon(){
  return  read(TCON_READ);
}
void MCP4261::writeTcon(uint16_t tcon){
    write(TCON_WRITE,tcon);
}
uint16_t MCP4261::readStatus(){
  return  read(STATUS_READ);
}
void MCP4261::wiperOn(boolean w0_on, boolean w1_on){
  uint16_t won = 0x00;
  if(w1_on){
    won = 0x70;
    }
  if(W0_on){
    won = won + 0x07;
    }
  writeTcon(won);
}