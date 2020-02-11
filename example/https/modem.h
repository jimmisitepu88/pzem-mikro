#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER 650

#define SerialAT Serial2
#define RXD2 27
#define TXD2 26

// set GSM PIN, if any
#define GSM_PIN ""
char apn[]  = "Internet";
char user[] = "";
char pass[] = "";

const char server[] = "vsh.pp.ua";
const char resource[] = "/TinyGSM/logo.txt";
const int  port = 443;

#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

TinyGsmClientSecure client(modem);
HttpClient http(client, server, port);

unsigned long mMillis, oMillis;
void wRespon(unsigned long wktModem);

void init_modem(){
  SerialAT.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
  //--------change baud to 4800 ------------
  SerialAT.println("AT+IPR=4800");
  wRespon(1000);
  SerialAT.println("AT&W");
  wRespon(1000);
  SerialAT.begin(4800, SERIAL_8N1, RXD2, TXD2);
  SerialAT.println("AT+IPR?");
  wRespon(1000);
  //--------------------
  modem.restart();
  // modem.init();

  String modemInfo = modem.getModemInfo();
  Serial.print("Modem: ");
  Serial.println(modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  if (!modem.hasSSL()) {
    Serial.println(F("SSL is not supported by this modem"));
    while(true) { delay(1000); }
  }else{
    Serial.println(F("SSL is supported"));
  }
 
}

void wRespon(unsigned long wktModem){
  mMillis = millis();
  oMillis = mMillis;
  while (mMillis - oMillis < wktModem){
    mMillis = millis();
    while(Serial1.available()>0){
    Serial.print(Serial1.readString());
  } 
  }
}