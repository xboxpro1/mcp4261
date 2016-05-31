#include <MCP4261.h>



MCP4261::MCP4261(int chipSelect){
  SPI.begin(); 
  SPI.setBitOrder(MSBFIRST);
  cs = chipSelect;
  pinMode(cs, OUTPUT); 
  digitalWrite(cs, HIGH); 
  getW0Pos();
  getW1Pos();
 restoreW0Pos(9);
 restoreW1Pos(9);
}



void MCP4261::write(byte cmd_byte, byte data_byte)
{
  digitalWrite(cs, LOW);  
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(data_byte);
  digitalWrite(cs, HIGH);
  bool result = ~low_byte;
}

uint16_t MCP4261::read(byte cmd_byte)
{
  digitalWrite(cs, LOW); 
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(0xFF);
  digitalWrite(cs, HIGH);
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


int  MCP4261::getW1Pos(){
 int pos =   0x01FF &  read(READ_W1);
 return pos;
}



void MCP4261::setW0Pos(uint16_t pos){
      write(WRITE_W0, pos);
}


void MCP4261::setW1Pos(uint16_t pos){
      write(WRITE_W1, pos);
}




uint16_t MCP4261::readTcon(){
  return  read(TCON_READ);
}
void MCP4261::writeTcon(uint16_t tcon){
    write(TCON_WRITE,tcon);
}




void MCP4261::mute(boolean mute){
    if(mute)
      writeTcon(B11011101);
    else 
      writeTcon(B11111111);
}



void  MCP4261::incW0(){
   write(INC_W0, 0);
}

void  MCP4261::incW1(){
   write(INC_W1, 0);
}

void  MCP4261::decW0(){
   write(DEC_W0, 0);
}

void  MCP4261::decW1(){
   write(DEC_W1, 0);
}


 
void  MCP4261::saveW0Pos(int num){
     if(num > 9) num =9;
     uint16_t  d = read(READ_W0);
     write(EEPROM_W[num], d);
     delay(10);
 }
 
void  MCP4261::saveW1Pos(int num){
     if(num > 9) num =9;
     uint16_t  d = read(READ_W1);
     write(EEPROM_W[num], d);
     delay(10);
 }




void  MCP4261::restoreW0Pos(int num){
     if(num > 9) num =9;
     uint16_t  d = read(EEPROM_R[num]);
     write(WRITE_W0, d);
 }

void  MCP4261::restoreW1Pos(int num){
     if(num > 9) num =9;
     uint16_t  d = read(EEPROM_R[num]);
     write(WRITE_W1, d);
 }
