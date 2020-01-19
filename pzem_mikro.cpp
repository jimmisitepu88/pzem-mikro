#include <Arduino.h>
#include <pzem_mikro.h>

void tunggu_data(unsigned long wkt);
void parsing_str();
unsigned long cur_time_pzem, old_time_pzem;
String str_data;

String ir, is, it;
String vr, vs, vt;
String freq;
String pf_r, pf_s, pf_t;
String pr, ps, pt;
String er, es, et;
String sts;

int len_ir, len_is, len_it;
int len_vr, len_vs, len_vt;
int len_freq;

int len_pfr, len_pfs, len_pft;
int len_pr, len_ps, len_pt;
int len_er, len_es, len_et;
int len_sts;

pzem_mikro::pzem_mikro(byte rst, unsigned int baud){
    begin(rst, baud);
}
void pzem_mikro::begin(byte rst, unsigned int baud){
    RST = rst;
    BAUD = baud;
    pinMode(RST, OUTPUT);
    SerialPZEM.begin(baud, SERIAL_8N1, RXD1, TXD1);
}
void pzem_mikro::rstPZEM(){
    digitalWrite(RST, HIGH); delay(500);
    digitalWrite(RST, LOW); delay(500);
    digitalWrite(RST, HIGH); delay(500);
}
String pzem_mikro::_data(){
    String _Data;
    SerialPZEM.write('O');
    tunggu_data(4000);
    _Data = str_data;
    return _Data;
}
bool pzem_mikro::get_sensor(){
   bool _sts;
   SerialPZEM.write('O');
   tunggu_data(4000);
   parsing_str();
   if(sts == "1"){
       _sts = 1;
   }else{
       _sts = 0;
   }
   return _sts;
}
float pzem_mikro::frequency(){
    float _freq;
    _freq = freq.toFloat();
    return _freq; 
}
float pzem_mikro::IR(){
    float _IR;
    _IR = ir.toFloat();
    return _IR; 
}
float pzem_mikro::IS(){
    float _IS;
    _IS = is.toFloat();
    return _IS; 
}
float pzem_mikro::IT(){
    float _IT;
    _IT = it.toFloat();
    return _IT; 
}
float pzem_mikro::VR(){
    float _VR;
    _VR = vr.toFloat();
    return _VR;
}
float pzem_mikro::VS(){
    float _VS;
    _VS = vs.toFloat();
    return _VS;
}
float pzem_mikro::VT(){
    float _VT;
    _VT = vt.toFloat();
    return _VT;
}
float pzem_mikro::PFR(){
    float _PFR;
    _PFR = pf_r.toFloat();
    return _PFR;
}
float pzem_mikro::PFS(){
    float _PFS;
    _PFS = pf_s.toFloat();
    return _PFS;
}
float pzem_mikro::PFT(){
    float _PFT;
    _PFT = pf_t.toFloat();
    return _PFT;
}
float pzem_mikro::powerR(){
    float _powerR;
    _powerR = pr.toFloat();
    return _powerR;
}
float pzem_mikro::powerS(){
    float _powerS;
    _powerS = ps.toFloat();
    return _powerS;
}

float pzem_mikro::powerT(){
    float _powerT;
    _powerT = pt.toFloat();
    return _powerT;
}
float pzem_mikro::kwhR(){
    float _kwhR;
    _kwhR = er.toFloat();
    return _kwhR;
}
float pzem_mikro::kwhS(){
    float _kwhS;
    _kwhS = es.toFloat();
    return _kwhS;
}
float pzem_mikro::kwhT(){
    float _kwhT;
    _kwhT = et.toFloat();
    return _kwhT;
}

void tunggu_data(unsigned long wkt){
    cur_time_pzem = millis();
    old_time_pzem = cur_time_pzem;
    while(cur_time_pzem - old_time_pzem < wkt){
        cur_time_pzem = millis();
        while (SerialPZEM.available()){
            str_data = SerialPZEM.readString();
        }
      }
        
    }

void parsing_str(){
len_ir = str_data.indexOf('!');
  len_is = str_data.indexOf('@');
  len_it = str_data.indexOf('#');
  len_vr = str_data.indexOf('$');
  len_vs = str_data.indexOf('%');
  len_vt = str_data.indexOf('^');
  len_freq = str_data.indexOf('&');
  
  len_pfr = str_data.indexOf('*');
  len_pfs = str_data.indexOf('(');
  len_pft = str_data.indexOf(')');

  len_pr = str_data.indexOf('-');
  len_ps = str_data.indexOf('=');
  len_pt = str_data.indexOf('_');

  len_er = str_data.indexOf('+');
  len_es = str_data.indexOf('<');
  len_et = str_data.indexOf('>');
  len_sts = str_data.indexOf('?');
  
  ir = str_data.substring(0,len_ir);
  is = str_data.substring(len_ir+1,len_is);
  it = str_data.substring(len_is+1,len_it);
  vr = str_data.substring(len_it+1,len_vr);
  vs = str_data.substring(len_vr+1,len_vs);
  vt = str_data.substring(len_vs+1,len_vt);
  freq = str_data.substring(len_vt+1, len_freq);

  pf_r = str_data.substring(len_freq+1, len_pfr);
  pf_s = str_data.substring(len_pfr+1, len_pfs);
  pf_t = str_data.substring(len_pfs+1, len_pft);

  pr = str_data.substring(len_pft+1, len_pr);
  ps = str_data.substring(len_pr+1, len_ps);
  pt = str_data.substring(len_ps+1, len_pt);

  er = str_data.substring(len_pt+1, len_er);
  es = str_data.substring(len_er+1, len_es);
  et = str_data.substring(len_es+1, len_et);
  sts = str_data.substring(len_et+1, len_sts);
  
}