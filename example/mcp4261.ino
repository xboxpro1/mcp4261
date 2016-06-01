#include "SPI.h" 
#include "MCP4261.h" 

#define on LOW
#define off HIGH

MCP4261 poti = MCP4261(10, 11, 12);

int incomingByte = 0; 

void setup(){
 Serial.begin(115200);
 
 poti.setW0Pos(10);
 poti.setW1Pos(10);

}

void loop()
{

 if (Serial.available() > 0) {
   incomingByte = Serial.read();

   if(incomingByte == 'g'){
        Serial.print("Left: ");
        Serial.print(poti.getW0Pos());
        Serial.print("  -  Rigth: ");        
        Serial.println(poti.getW1Pos());     
   }

   if(incomingByte == '0'){
      poti.setW0Pos(0);
      poti.setW1Pos(1);
   }

   if(incomingByte == '1'){
      poti.setW0Pos(25);
      poti.setW1Pos(26);
   }

   if(incomingByte == '2'){
      poti.setW0Pos(100);
      poti.setW1Pos(101);
   }

   if(incomingByte == '3'){
      poti.setW0Pos(150);
      poti.setW1Pos(151);
   }

   if(incomingByte == '4'){
      poti.setW0Pos(200);
      poti.setW1Pos(201);
   }


   if(incomingByte == '5'){
      poti.setW0Pos(250);
      poti.setW1Pos(251);
   }

   if(incomingByte == 't'){
      uint16_t tcon = poti.readTcon();
       Serial.print("  -  Tcon: ");        
       Serial.println(tcon,BIN);     
   }

   if(incomingByte == 'e'){
    poti.potEnable(on);
   }
   
   if(incomingByte == 'x'){
    poti.potEnable(off);
   }
   
   if(incomingByte == 'a'){
    poti.potEnable(on, off);
   }
   
   if(incomingByte == 'b'){
    poti.potEnable(off, on);
   }
   
 }

}
