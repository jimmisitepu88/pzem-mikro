#include <pzem_mikro.h>
#include "modem.h"
pzem_mikro pzem(33, 9600); // jangan rubah nilai ini

float curIR, curIS, curIT, Freq;
float voltR, voltS, voltT; 
float pfr,pfs, pft;
float PowerR, PowerS, PowerT;
float KWHR,KWHS, KWHT; 
unsigned long cur_time, old_time;

void setup(){
    Serial.begin(115200);
    init_modem();
}

void loop(){
     Blynk.run();
   cur_time = millis();
   if(cur_time - old_time >= 2000){   
      if(pzem.get_sensor()){
        curIR = pzem.IR();curIS = pzem.IS();curIT = pzem.IT();
        voltR = pzem.VR();voltS = pzem.VS();voltT = pzem.VT();
        Freq = pzem.frequency();    
        pfr = pzem.PFR();pfs = pzem.PFS();pft = pzem.PFT();
        PowerR = pzem.powerR(); PowerS = pzem.powerS(); PowerT = pzem.powerT(); 
        KWHR = pzem.kwhR();KWHS = pzem.kwhS();KWHT = pzem.kwhT();
      }else{
        Serial.println(F("connection fail"));
        pzem.rstPZEM();
      }
      print_data();     
      Blynk.virtualWrite(V0, voltR);
      Blynk.virtualWrite(V1, curIR);
      Blynk.virtualWrite(V2, pfr);
      Blynk.virtualWrite(V3, PowerR);
      Blynk.virtualWrite(V4, KWHR);
      old_time = cur_time;
  }
    delay(1000);
}
void print_data(){
    Serial.print("IR: ");Serial.print(curIR);
    Serial.print(" IS: ");Serial.print(curIS);
    Serial.print(" IT: ");Serial.println(curIT);
    
    Serial.print("VR: ");Serial.print(voltR);
    Serial.print(" VS: ");Serial.print(voltS);
    Serial.print(" VT: ");Serial.println(voltT);
    
    Serial.print("freq: ");Serial.println(Freq);
    
    Serial.print("PFR: ");Serial.print(pfr);
    Serial.print(" PFS: ");Serial.print(pfs);
    Serial.print(" PFT: ");Serial.println(pft);

    Serial.print("powerR: ");Serial.print(PowerR);
    Serial.print(" powerS: ");Serial.print(PowerS);
    Serial.print(" powerT: ");Serial.println(PowerT);
    
    Serial.print("kwhR: ");Serial.print(KWHR);
    Serial.print(" kwhS: ");Serial.print(KWHS);
    Serial.print(" kwhT: ");Serial.println(KWHT);
    Serial.println("---");

}