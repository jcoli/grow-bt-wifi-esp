/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#include <Arduino.h>
#include <ArduinoHA.h> 
#include "BluetoothSerial.h"

#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "comm_wifi.h"
#include "mqtt_control.h"
#include "receive_bt.h"
#include "service_01_bt.h"

void on_receive_master(String line_in);
void update_variables(String line);
void update_variables_service0(String line);
void update_variables_service1(String line);
void update_variables_service2(String line);
void update_variables_service3(String line);
void update_variables_service4(String line);
void update_variables_service5(String line);
void update_variables_service6(String line);
void update_variables_service7(String line);
void on_bit_alive_bt();
void on_bit_connected_bt();
void decoder_one();
void decoder_two();
void decoder_three();
void decoder_four();
void decoder_five();

extern String wifi_ssid;
extern String wifi_pwd;

extern bool wifi_connected;
extern bool mqtt_connected;

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;

extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;

extern String line;
extern String line1;
extern String line2;
extern bool stringComplete;
extern bool string1Complete;
extern bool string2Complete;

extern float eco2_ext;
extern float eco2_int;
extern float temp_int;
extern float hum_int;
extern float press_int;
extern float temp_ext;
extern float hum_ext;
extern float press_ext;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float soil_4_hum;
extern float light_1_int;

extern bool water_irrig_1_level;
extern bool water_hum_1_level;

extern bool fan_dehum_on;
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;
extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool hum_on;
extern bool hum_1_on;
extern bool hum_2_on;
extern bool hum_3_on;
extern bool hum_4_on;
extern bool dehum_1_on;
extern bool relay1_on;
extern bool relay2_on;
extern bool relay3_on;
extern bool relay4_on;
extern bool doorState;
extern bool out1_on;
extern bool out2_on;

extern float fan_dehum_pwm;
extern float fan1_inf_pwm;
extern float fan2_inf_pwm;
extern float fan3_inf_pwm;
extern float fan_dehum_pwm;
extern float fan_hum_pwm;
extern float light_pwm;
extern float hum_1_pwm;
extern float dehum_1_pwm;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5]; 

extern String ipaddress;
extern String gateway;
extern String subnet;

extern IPAddress broker_ip;
extern String username_broker;
extern String password_broker;
extern String name_device;
extern String ip_broker;

extern String owner_name;
extern String owner_pass;



extern HANumber fan1_inf_pwm_ha;
extern HANumber fan2_inf_pwm_ha;
extern HANumber fan3_inf_pwm_ha;
extern HANumber light_pwm_ha;

extern HASwitch switch_fan1_inf_on_ha;
extern HASwitch switch_fan2_inf_on_ha;
extern HASwitch switch_fan3_inf_on_ha;
extern HASwitch switch_light_on_ha;
extern HASwitch switch_pump_irr_on_ha;
extern HASwitch switch_hum_on_ha;
extern HASwitch switch_relay1_ha;
extern HASwitch switch_relay2_ha;
extern HASwitch switch_relay3_ha;
extern HASwitch switch_relay4_ha;


void on_bit_alive_bt(){
    if (!bt_alive){
        bt_enabled = false;
        tim_alive = 0;
        // Serial.println("on_bit_alive");
    }
}

void on_bit_connected_bt(){
    if (!bt_connected){
      tim_conn = 0;
      Serial2.println("0,3,22,0,#");
        // Serial.println("on_bit_conn");
    }else{
      tim_conn = 1;
      Serial2.println("0,3,22,1,#");
    }
}




void on_receive_master(String line_in){
    split_msg_5(line_in);
    // Serial.print("on_receive: ");
    // Serial.println(line_in);
    int i = retMsg5[0].toInt();
    // Serial.println(i);
    

    switch (i) {
        case 0:
          Serial.println("wifi - case 0");
          // Serial.print("on_receive: ");
          // Serial.println(line_in);
          wifi_ssid = retMsg5[2];
          wifi_pwd = retMsg5[3];  
          
          break;
        case 1:
          // Serial.println("wifi - case 1");
          listNetworks();
          break; 
        case 3:
          // Serial.println("update variables - case 3");
          update_variables(line_in);
          break;  
        case 4:
          Serial.println("update variables - case 4");
          ip_broker = retMsg5[1];
          password_broker = retMsg5[2];
          username_broker = retMsg5[3];
          
          broker_ip.fromString(ip_broker.c_str());
          wifi_begin(wifi_ssid, wifi_pwd);
          break;  
    }    
}

void update_variables(String line){
    split_msg_5(line);
     String recHex = retMsg5[1];
     long i = strtol( recHex.c_str(), NULL, 16);
     switch (i) {
        case 0x00:
          update_variables_service0(line);
          break;
        case 0x01:
          update_variables_service1(line);
          break;  
        case 0x02:
          update_variables_service2(line);
          break;  
        case 0x03:
          update_variables_service3(line);
          break;  
        case 0x04:
          // Serial.println("update variables 4 A");
          update_variables_service4(line);
          break;
        case 0x05:
          update_variables_service5(line);
          break;  
        case 0x06:
          update_variables_service6(line);
          break;              

     }  


}

void update_variables_service0(String line){
    split_msg_5(line);
    String recHex = retMsg5[2];
    long i = strtol( recHex.c_str(), NULL, 16);
     switch (i) {
        case 0x03:
          bt_connected = retMsg5[3];
          break;
     }
}

void update_variables_service1(String line){
    //  split_msg_5(line);
    //  String recHex = retMsg5[2];
    //  long i = strtol( recHex.c_str(), NULL, 16);
    on_service_01_bt(line);


}


void update_variables_service2(String line){
     split_msg_5(line);
     String recHex = retMsg5[2];
     long i = strtol( recHex.c_str(), NULL, 16);
    //  Serial.println("updates variables service 2a");
    //  Serial.println(i);
     switch (i) {
        case 0x00:
          temp_ext = retMsg5[3].toFloat();
          break;
        case 0X01:
          temp_int = retMsg5[3].toFloat();
          break; 
        case 0x02:
          hum_ext = retMsg5[3].toFloat();
          break; 
        case 0x03:
          hum_int = retMsg5[3].toFloat();
          break;   
        case 0x04:
          eco2_ext = retMsg5[3].toFloat();
          break;    
        case 0x05:
          eco2_int = retMsg5[3].toFloat();          
          break;      
        case 0x06:
          // soil_1_hum = retMsg5[3].toFloat();
          break;      
        case 0x09:
          water_irrig_1_level = retMsg5[3].toFloat();
          break; 
        case 0x0A:
          water_hum_1_level = retMsg5[3].toFloat();
          break;
        case 0x11:
          light_1_int = retMsg5[3].toFloat();         
          break;
        case 0x12:
          soil_1_hum = retMsg5[3].toFloat();
          break; 
        case 0x13:
          soil_2_hum = retMsg5[3].toFloat();
          break;
        case 0x14:
          soil_3_hum = retMsg5[3].toFloat();
          break;
        case 0x15:
          soil_4_hum = retMsg5[3].toFloat();
          break;                               
        
        
    }  
}

void update_variables_service3(String line){
    split_msg_5(line);
    String recHex = retMsg5[3];
    long i = strtol( recHex.c_str(), NULL, 16);
    switch (i) {
        case 0x06:
          water_irrig_1_level = retMsg5[3].toInt();
          break;
        case 0x07:
          water_hum_1_level = retMsg5[3].toInt();
          break;  
        case 0x0D:
          doorState = retMsg5[3].toInt();
          break;
        case 0x21:
          wifi_connected = retMsg5[3].toInt();
          break;  
        case 0x22:
          bt_connected = retMsg5[3].toInt();
          break;    
        case 0x23:
          mqtt_connected = retMsg5[3].toInt();
          break;    
    }      
}

void update_variables_service4(String line){
     split_msg_5(line);
     String recHex = retMsg5[2];
    //  Serial.println("updates variables service 4");
     long i = strtol( recHex.c_str(), NULL, 16);
     switch (i) {
        case 0x00:
          fan_dehum_on = retMsg5[3].toInt();

          break;
        case 0X01:
          fan1_inf_on = retMsg5[3].toInt();
          switch_fan1_inf_on_ha.setState(fan1_inf_on);
          break; 
        case 0x02:
          fan2_inf_on = retMsg5[3].toInt();
          switch_fan2_inf_on_ha.setState(fan2_inf_on);
          break; 
        case 0x03:
          fan3_inf_on = retMsg5[3].toInt();
          switch_fan3_inf_on_ha.setState(fan3_inf_on);
          break;   
        case 0x06:
          light_on = retMsg5[3].toInt();
          switch_light_on_ha.setState(light_on);
          break;      
        case 0x0B:
          pump_irr_on = retMsg5[3].toInt();
          switch_pump_irr_on_ha.setState(pump_irr_on);
          break;
        case 0x0C:
          hum_on = retMsg5[3].toInt();
          switch_hum_on_ha.setState(hum_on);
          break;
        case 0x0D:
          dehum_1_on = retMsg5[3].toInt();

          break;
        case 0x0E:
          relay1_on = retMsg5[3].toInt();
          switch_relay1_ha.setState(relay1_on);
          break; 
        case 0x0F:
          relay2_on = retMsg5[3].toInt();
          switch_relay2_ha.setState(relay2_on);
          break;
        case 0x10:
          relay3_on = retMsg5[3].toInt();
          switch_relay3_ha.setState(relay3_on);
          break;
        case 0x11:
          relay4_on = retMsg5[3].toInt();
          switch_relay4_ha.setState(relay4_on);
          break;
        case 0x12:
          out1_on = retMsg5[3].toInt();
          break;
        case 0x13:
          out2_on = retMsg5[3].toInt();
          break;                      

     }    

}

void update_variables_service5(String line){
     split_msg_5(line);
     String recHex = retMsg5[2];
    //  Serial.println("updates variables service 5");
     long i = strtol( recHex.c_str(), NULL, 16);
     switch (i) {
        case 0x00:
          fan_dehum_pwm = retMsg5[3].toInt();
          break;
        case 0X01:
          fan1_inf_pwm = retMsg5[3].toInt();
          fan1_inf_pwm_ha.setState(fan1_inf_pwm);
          break; 
        case 0x02:
          fan2_inf_pwm = retMsg5[3].toInt();
          fan2_inf_pwm_ha.setState(fan2_inf_pwm);
          break; 
        case 0x03:
          fan3_inf_pwm = retMsg5[3].toInt();
          fan3_inf_pwm_ha.setState(fan3_inf_pwm);
          break;   
        case 0x06:
          light_pwm = retMsg5[3].toInt();
          light_pwm_ha.setState(light_pwm);
          break;      
     }    

}

void update_variables_service6(String line){
    split_msg_5(line);
     String recHex = retMsg5[2];
    //  Serial.println("updates variables service 5");
     long i = strtol( recHex.c_str(), NULL, 16);
     switch (i) {
        case 0x00:
          wifi_ssid = retMsg5[3];
          break;
        case 0x01:
          listNetworks();
          break;  
     }
}

void update_variables_service7(String line){
    split_msg_5(line);
     String recHex = retMsg5[2];
     Serial.println("updates variables service 7");
     long i = strtol( recHex.c_str(), NULL, 16);
     switch (i) {
        case 0x00:
          Serial.print("updates wifi_ssid: ");
          wifi_ssid = retMsg5[3];
          Serial.println(wifi_ssid);
          break;
        case 0x01:
          Serial.print("updates wifi_pass: ");
          wifi_pwd = retMsg5[3];
          Serial.println(wifi_pwd);
          break;  
        case 0x02:
          ipaddress = retMsg5[3];
          break;    
        case 0x03:
          gateway = retMsg5[3];
          break; 
        case 0x04:
          subnet = retMsg5[3];
          break; 
        case 0x05:
          ip_broker = retMsg5[3];
          break;
        case 0x06:
          username_broker = retMsg5[3];
          break; 
        case 0x07:
          password_broker = retMsg5[3];
          break;
        case 0x08:
          name_device = retMsg5[3];
          break;  
        case 0x09:
          name_device = retMsg5[3];
          break;  
        case 0x0A:
          owner_name = retMsg5[3];
          break;    
        case 0x0B:
          owner_pass = retMsg5[3];
          break;  

     }
    
}


void send_comm(String msg){
    

}


