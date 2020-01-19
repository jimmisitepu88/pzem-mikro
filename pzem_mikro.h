/*
    create by: Jimmi Kardo Sitepu
    date: 19-jan-2020
    place: Medan
    www.mikroavr.com
*/
#ifndef pzem_mikro_h
#define pzem_mikro_h

#define RXD1 17
#define TXD1 16
#define SerialPZEM Serial1
    

class pzem_mikro
{
private:
    byte RST; unsigned int BAUD;
    
public:
    pzem_mikro(byte rst, unsigned int baud);
    void begin(byte rst, unsigned int baud);
    void rstPZEM();
    bool get_sensor();
    float frequency(); float IR(); float IS(); float IT();
    float VR(); float VS();float VT(); 
    float PFR(); float PFS(); float PFT();
    float powerR();float powerS();float powerT();
    float kwhR();float kwhS();float kwhT();
    String _data();
};
#endif