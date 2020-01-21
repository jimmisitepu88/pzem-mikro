#define BLYNK_PRINT Serial
#define SerialAT Serial2
#define RXD2 27
#define TXD2 26

#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

TinyGsm modem(SerialAT);

char auth[] = "your-token-blynk";
char apn[]  = "YourAPN";
char user[] = "";
char pass[] = "";

void init_modem(){
  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
  //--------change baud to 4800 ------------
    SerialAT.println("AT+IPR=4800");
  while(SerialAT.available()>0){
    Serial.print(SerialAT.readString());
  }
  delay(2000);
  SerialAT.println("AT&W");
  while(SerialAT.available()>0){
    Serial.print(SerialAT.readString());
  }
  delay(2000);
  SerialAT.begin(4800, SERIAL_8N1, RXD2, TXD2);
  SerialAT.println("AT+IPR?");
  while(Serial1.available()>0){
    Serial.print(Serial1.readString());
  }
  delay(2000);
  //--------------------
  
  Serial.println("Initializing modem...");
  modem.restart();
  Blynk.begin(auth, modem, apn, user, pass);
}

