#include "SPI.h" 
#include "MCP4261.h" 


MCP4261 volumenControl = MCP4261(10);

int incomingByte = 0; 

void setup(){
 Serial.begin(9600);
 
 volumenControl.setW0Pos(10);
 volumenControl.setW1Pos(10);

}

void loop()
{

 if (Serial.available() > 0) {
   incomingByte = Serial.read();

   if(incomingByte == 'g'){
        Serial.print("Left: ");
        Serial.print(volumenControl.getW0Pos());
        Serial.print("  -  Rigth: ");        
        Serial.println(volumenControl.getW1Pos());     
   }


   if(incomingByte == '+'){
      volumenControl.incW0();
      volumenControl.incW1();
     
   }

   if(incomingByte == '-'){
      volumenControl.decW0();
      volumenControl.decW1();
   }



   if(incomingByte == '0'){
      volumenControl.setW0Pos(0);
      volumenControl.setW1Pos(1);
   }

   if(incomingByte == '1'){
      volumenControl.setW0Pos(25);
      volumenControl.setW1Pos(26);
   }

   if(incomingByte == '2'){
      volumenControl.setW0Pos(100);
      volumenControl.setW1Pos(101);
   }

   if(incomingByte == '3'){
      volumenControl.setW0Pos(150);
      volumenControl.setW1Pos(151);
   }

   if(incomingByte == '4'){
      volumenControl.setW0Pos(200);
      volumenControl.setW1Pos(201);
   }


   if(incomingByte == '5'){
      volumenControl.setW0Pos(250);
      volumenControl.setW1Pos(251);
   }


   if(incomingByte == 's'){
      volumenControl.saveW0Pos(3);
      volumenControl.saveW1Pos(4);
   }
   
   
   if(incomingByte == 'r'){
      volumenControl.restoreW0Pos(3);
      volumenControl.restoreW1Pos(4);
   }

   if(incomingByte == 'M'){
     volumenControl.mute(true);
     
   }

   if(incomingByte == 'm'){
     volumenControl.mute(false);
     
   }

   if(incomingByte == 't'){
      uint16_t tcon = volumenControl.readTcon();
       Serial.print("  -  Tcon: ");        
       Serial.println(tcon,BIN);     
   }

   if(incomingByte == 'x'){
     volumenControl.writeTcon(B00000000);
   }

   if(incomingByte == 'y'){
     volumenControl.writeTcon(B11111111);
   }

 }

}
