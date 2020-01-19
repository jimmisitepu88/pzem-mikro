#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "your-token-blynk";
char ssid[] = "ssid-wifi";
char pass[] = "pass-wifi";

void init_modem(){
  Blynk.begin(auth, ssid, pass);
}
