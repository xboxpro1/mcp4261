#include <MCP4261.h>



MCP4261::MCP4261(int chipSelect, int potE, int nvP){
  SPI.begin(); 
  SPI.setBitOrder(MSBFIRST);
  cs = chipSelect;
  pe = potE;
  nv = nvP;
  pinMode(cs, OUTPUT); 
  digitalWrite(cs, HIGH); 
  pinMode(pe, OUTPUT); 
  digitalWrite(pe, HIGH);
  pinMode(nv, OUTPUT); 
  digitalWrite(nv, HIGH);
}



void MCP4261::write(byte cmd_byte, byte data_byte)
{
  digitalWrite(cs, LOW);  
  byte high_byte = SPI.transfer(cmd_byte);
  byte low_byte  = SPI.transfer(data_byte);
  delay(5);
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
}


void MCP4261::setW1Pos(uint16_t pos){
      write(WRITE_W1, pos);
}

void MCP4261::setW1NVPos(uint16_t pos){
      write(WRITE_W1NV, pos);
}

void MCP4261::potEnable(int enp){
      digitalWrite(pe, enp);
}


uint16_t MCP4261::readTcon(){
  return  read(TCON_READ);
}
void MCP4261::writeTcon(uint16_t tcon){
    write(TCON_WRITE,tcon);
}

void MCP4261::wiperOn(boolean w0_on, boolean w1_on){
byte w0on;
byte won;
if(w0_on)
    w0on = B1111;
else
    w0on = B1000;
if(W1_on)
    won = w0on + B11110000;
else
    won = w0on + B1000000;

writeTcon(won);
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
