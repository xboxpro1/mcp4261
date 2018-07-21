

#include <SPI.h>
#include "mcp4261.h" 

#define on LOW
#define off HIGH

const int sd_poti = 9;                                   // SHDN Poti
const int cs_poti = 10;                                  // CS Poti
const int wp_poti = 16;                                  // WP Poti

MCP4261 poti = MCP4261(cs_poti, sd_poti, wp_poti);

String dataIN;
String crIN;
short CR = 10;

void setup(){
 Serial.begin(115200);
 
 poti.setW0Pos(10);
 poti.setW1Pos(15);
 poti.wiperOn(true, true);
 poti.protectNV(on);
 poti.enable(on);
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
    Serial.println("p -> protect Non Volatile");
    Serial.println("n -> non protect Non Volatile");
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
   dataIN = Serial.readStringUntil(CR);
   crIN = Serial.readString();

   if(dataIN == 'g'){
        Serial.print("Left: ");
        Serial.print(poti.getW0Pos());
        Serial.print("  -  Right: ");        
        Serial.println(poti.getW1Pos());     
   }

   if(dataIN == '0'){
      poti.setW0Pos(0);
      poti.setW1Pos(5);
   }

   if(dataIN == '1'){
      poti.setW0Pos(25);
      poti.setW1Pos(30);
   }

   if(dataIN == '2'){
      poti.setW0Pos(100);
      poti.setW1Pos(105);
   }

   if(dataIN == '3'){
      poti.setW0Pos(150);
      poti.setW1Pos(155);
   }

   if(dataIN == '4'){
      poti.setW0Pos(200);
      poti.setW1Pos(205);
   }


   if(dataIN == '5'){
      poti.setW0Pos(250);
      poti.setW1Pos(255);
   }

   if(dataIN == 't'){
      int tcon = poti.readTcon();
       Serial.print("TCON: ");        
       Serial.println(tcon,BIN);     
   }
   
   if(dataIN == 's'){
      int stat = poti.readStatus();
       Serial.print("Status: ");        
       Serial.println(stat,BIN);     
   }
   
   if(dataIN == 'e'){
    poti.enable(on);
   }
   
   if(dataIN == 'p'){
    poti.protectNV(on);
   }

   if(dataIN == 'n'){
    poti.protectNV(off);
   }
   
   if(dataIN == 'x'){
    poti.enable(off);
   }
   
   if(dataIN == 'a'){
    poti.wiperOn(true, false);
   }
   
   if(dataIN == 'b'){
    poti.wiperOn(false, true);
   }
   
   if(dataIN == 'c'){
    poti.wiperOn(true, true);
   }
   
   if(dataIN == 'd'){
    poti.wiperOn(false, false);
   }
   
   if(dataIN == 'h'){
    help();
   }
   
 }

}
