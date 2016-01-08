#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11);
const int in1 = 2;
const int in2 = 3;
const int ena = 4;
const int in3 = 5;
const int in4 = 6;
const int enb = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(ena,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  Serial.begin(115200);
  mySerial.begin(115200);
 // mySerial.println("AT+CWJAP=\"robotcar\",\"12345678\"");  //connect wifi
 delay(3000);
  mySerial.println("AT+CIPMUX=0");  //set mode
  delay(1000);
  mySerial.println("AT+CIPSTART=\"TCP\",\"192.168.137.1\",8888");// connect server
  delay(1000);
}
void rx_empty(void) 
{
    while(mySerial.available() > 0) {
        mySerial.read();
    }
}
uint32_t recv(uint8_t *buffer, uint32_t buffer_size, uint32_t timeout)
{
    return recvPkg(buffer, buffer_size, NULL, timeout, NULL);
}
uint32_t recvPkg(uint8_t *buffer, uint32_t buffer_size, uint32_t *data_len, uint32_t timeout, uint8_t *coming_mux_id)
{
    String data;
    char a;
    int32_t index_PIPDcomma = -1;
    int32_t index_colon = -1; /* : */
    int32_t index_comma = -1; /* , */
    int32_t len = -1;
    int8_t id = -1;
    bool has_data = false;
    uint32_t ret;
    unsigned long start;
    uint32_t i;
    
    if (buffer == NULL) {
        return 0;
    }
    
    start = millis();
    while (millis() - start < timeout) {
        if(mySerial.available() > 0) {
            a = mySerial.read();
            data += a;
        }
        
        index_PIPDcomma = data.indexOf("+IPD,");
        if (index_PIPDcomma != -1) {
            index_colon = data.indexOf(':', index_PIPDcomma + 5);
            if (index_colon != -1) {
                index_comma = data.indexOf(',', index_PIPDcomma + 5);
                /* +IPD,id,len:data */
                if (index_comma != -1 && index_comma < index_colon) { 
                    id = data.substring(index_PIPDcomma + 5, index_comma).toInt();
                    if (id < 0 || id > 4) {
                        return 0;
                    }
                    len = data.substring(index_comma + 1, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                } else { /* +IPD,len:data */
                    len = data.substring(index_PIPDcomma + 5, index_colon).toInt();
                    if (len <= 0) {
                        return 0;
                    }
                }
                has_data = true;
                break;
            }
        }
    }
    
    if (has_data) {
        i = 0;
        ret = len > buffer_size ? buffer_size : len;
        start = millis();
        while (millis() - start < 2000) {
            while(mySerial.available() > 0 && i < ret) {
                a = mySerial.read();
                buffer[i++] = a;
            }
            if (i == ret) {
                rx_empty();
                if (data_len) {
                    *data_len = len;    
                }
                if (index_comma != -1 && coming_mux_id) {
                    *coming_mux_id = id;
                }
                return ret;
            }
        }
    }
    return 0;
}
void up()
{
  digitalWrite(ena,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(enb,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}
void down()
{
  digitalWrite(ena,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(enb,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void left()
{
  digitalWrite(ena,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(enb,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}
void right()
{
  digitalWrite(ena,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(enb,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  
}
void tostop()
{
  digitalWrite(ena,LOW);
  digitalWrite(enb,LOW);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
    String control;
    uint8_t buffer[128] = {0};
    uint32_t len = recv(buffer,sizeof(buffer),10000);
    if (len > 0) {
        for(uint32_t i = 0; i < len; i++) {
            control += (char)buffer[i];
      }
        Serial.println(control);
        if(control == "up")
          up();
        if(control == "down")
          down();
        if(control == "left")
          left();
        if(control == "right")
          right();
        if(control == "stop")
          tostop();
        }
        
}
