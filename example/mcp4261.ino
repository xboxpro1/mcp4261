#include "SPI.h" 
#include "MCP4261.h" 

#define on LOW
#define off HIGH

const int sd_poti = 9;                                   // SHDN Poti
const int cs_poti = 10;                                  // CS Poti
const int wp_poti = 11;                                  // WP Poti

MCP4261 poti = MCP4261(cs_poti, sd_poti, wp_poti);

int incomingByte = 0; 

void setup(){
 Serial.begin(115200);
 
 poti.setW0Pos(10);
 poti.setW1Pos(15);
 help();

}

void help(){
    Serial.println("MCP4261 - Test");
    Serial.println("g -> get Wiper Value");
    Serial.println("0 -> set Wiper 0/5");
    Serial.println("1 -> set Wiper 25/30");
    Serial.println("2 -> set Wiper 100/105");
    Serial.println("3 -> set Wiper 150/155");
    Serial.println("4 -> set Wiper 200/205");
    Serial.println("5 -> set Wiper 250/255");
    Serial.println("t -> read TCON-Register");
    Serial.println("s -> read Setup-Register");
    Serial.println("e -> enable Poti");
    Serial.println("x -> disable Poti");
    Serial.println("a -> W0-ON W1-OFF");
    Serial.println("b -> W0-OFF W1-ON");
    Serial.println("c -> W0-ON W1-ON");
    Serial.println("d -> W0-OFF W1-OFF");
    Serial.println("h -> this Text");
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
       Serial.print("TCON: ");        
       Serial.println(tcon,BIN);     
   }
   
   if(incomingByte == 's'){
      uint16_t stat = poti.readStatus();
       Serial.print("Status: ");        
       Serial.println(stat,BIN);     
   }
   
   if(incomingByte == 'e'){
    poti.potEnable(on);
   }
   
   if(incomingByte == 'x'){
    poti.potEnable(off);
   }
   
   if(incomingByte == 'a'){
    poti.wiperOn(true, false);
   }
   
   if(incomingByte == 'b'){
    poti.wiperOn(false, true);
   }
   
   if(incomingByte == 'c'){
    poti.wiperOn(true, true);
   }
   
   if(incomingByte == 'd'){
    poti.wiperOn(false, false);
   }
   
   if(incomingByte == 'h'){
    help();
   }
   
 }

}
