#define RXD2 27
#define TXD2 26
unsigned long cur_time, old_time;

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  //Serial1.begin(115200);
  delay(1000);
  Serial2.println("AT+IPR=4800");delay(100);
  wRespon(2000);
  Serial2.begin(4800, SERIAL_8N1, RXD2, TXD2);
  Serial2.println("AT&W");
  wRespon(2000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("AT");
  Serial2.println("AT+IPR?");
  wRespon(1000);
  delay(1000);
}
void wRespon(long waktu){
  cur_time = millis();
  old_time = cur_time;
  while(cur_time - old_time < waktu ){
    cur_time = millis();
    while(Serial2.available()>0){
    Serial.print(Serial2.readString());
    } 
  }
}
