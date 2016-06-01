#include "SPI.h" 
#include "MCP4261.h" 

#define on LOW
#define off HIGH

const int sd_poti = 9;                                   // SHDN Poti
const int cs_poti = 10;                                  // CS Poti
const int rw_poti = 11;                                  // RST / WP Poti

MCP4261 poti = MCP4261(cs_poti, sd_poti, rw_poti);

int incomingByte = 0; 

void setup(){
 Serial.begin(115200);
 
 poti.setW0Pos(10);
 poti.setW1Pos(15);

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
      poti.setW1Pos(5);
   }

   if(incomingByte == '1'){
      poti.setW0Pos(25);
      poti.setW1Pos(30);
   }

   if(incomingByte == '2'){
      poti.setW0Pos(100);
      poti.setW1Pos(105);
   }

   if(incomingByte == '3'){
      poti.setW0Pos(150);
      poti.setW1Pos(155);
   }

   if(incomingByte == '4'){
      poti.setW0Pos(200);
      poti.setW1Pos(205);
   }


   if(incomingByte == '5'){
      poti.setW0Pos(250);
      poti.setW1Pos(255);
   }

   if(incomingByte == 't'){
      uint16_t tcon = poti.readTcon();
       Serial.print("Tcon: ");        
       Serial.println(tcon,BIN);     
   }

   if(incomingByte == 'e'){
    poti.potEnable(on);
   }
   
   if(incomingByte == 'x'){
    poti.potEnable(off);
   }
   
   if(incomingByte == 'a'){
    poti.wiperOn(on, off);
   }
   
   if(incomingByte == 'b'){
    poti.wiperOn(off, on);
   }
   
   if(incomingByte == 'c'){
    poti.wiperOn(on, on);
   }
   
   if(incomingByte == 'd'){
    poti.wiperOn(off, off);
   }
   
 }

}
