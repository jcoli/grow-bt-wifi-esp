/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#include <Arduino.h>
#include "BluetoothSerial.h"

#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "comm_wifi.h"
#include "mqtt_control.h"
#include "receive_bt.h"

void com_bt01_0x00(int command);
void com_bt01_0x01(int command);
void com_bt01_0x02(int command);
void com_bt01_0x03(int command);
void com_bt01_0x04(int command);
void com_bt01_0x05(int command);
void com_bt01_0x06(int command);
void com_bt01_0x07(int command);
void com_bt01_0x08(int command);
void com_bt01_0x09(int command);
void com_bt01_0x0A(int command);
void com_bt01_0x0B(int command);
void com_bt01_0x0C(int command);
void com_bt01_0x0D(int command);
void com_bt01_0x0E(int command);
void com_bt01_0x0F(int command);
void com_bt01_0x10(int command);
void com_bt01_0x11(int command);
void com_bt01_0x12(int command);
void com_bt01_0x13(int command);
void com_bt01_0x14(int command);
void com_bt01_0x15(int command);
void com_bt01_0x16(int command);
void com_bt01_0x17(int command);
void com_bt01_0x18(int command);
void com_bt01_0x19(int command);
void com_bt01_0x1A(int command);
void com_bt01_0x1B(int command);
void com_bt01_0x1C(int command);
void com_bt01_0x1D(int command);
void com_bt01_0x1E(int command);
void com_bt01_0x1F(int command);
void com_bt01_0x20(int command);
void com_bt01_0x21(int command);
void com_bt01_0x22(int command);
void com_bt01_0x23(int command);
void com_bt01_0x24(int command);
void com_bt01_0x25(int command);

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

extern int temp_int_min_stp;
extern int temp_int_max_stp;

extern int hum_int_on_stp;

extern int hum_int_min_stp;
extern int hum_int_max_stp;

extern int vpd_int_min_stp;
extern int vpd_int_max_stp;

extern int soil_hum_min_stp;
extern int soil_hum_max_stp;
extern int ph_irrig_stp;
extern int ph_hum_stp;

extern int light_hr_on_stp;
extern int light_min_on_stp;
extern int light_hr_off_stp;
extern int light_min_off_stp;

extern int pump_irr_on_stp;
extern int pump_hr_irr_on_stp;
extern int pump_min_irr_on_stp;
extern int pump_hr_irr_off_stp;
extern int pump_min_irr_off_stp;

extern int irr_interval_stp;
extern int irr_time_stp;
extern int irr_interval_on_stp;

extern int irr_1_hr_stp;
extern int irr_1_min_stp;
extern int irr_2_hr_stp;
extern int irr_2_min_stp;
extern int irr_3_hr_stp;
extern int irr_3_min_stp;
extern int irr_4_hr_stp;
extern int irr_4_min_stp;
extern int irr_5_hr_stp;
extern int irr_5_min_stp;
extern int irr_6_hr_stp;
extern int irr_6_min_stp;

extern int light_pwm_stp;
extern int fan1_inf_pwm_stp;
extern int fan2_inf_pwm_stp;
extern int fan3_inf_pwm_stp;

extern int fan1_inf_pwm_light_stp;
extern int fan2_inf_pwm_light_stp;
extern int fan3_inf_pwm_light_stp;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5]; 

void on_service_01_bt(String line_in){
    split_msg_5(line1);
    int i = toHexc(retMsg5[2]);
    // Serial.println("Receive Service 1");

     switch (i) {
        case 0x00:
            // Serial.println("Status Temp Ext 0x03 0x00");
            com_bt01_0x00(retMsg5[3].toInt()); 
            break;
        case 0x01:
            // Serial.println("Status Temp int 0x03 0x01");
            com_bt01_0x01(retMsg5[3].toInt());
            break;    
        case 0x02:
            // Serial.println("Status Hum Ext 0x03 0x02");
            com_bt01_0x02(retMsg5[3].toInt());
            break;
        case 0x03:
            // Serial.println("Status Hum Ext 0x03 0x03");
            com_bt01_0x03(retMsg5[3].toInt());
            break;    
        case 0x04:
            // Serial.println("Status C02 Ext 0x03 0x04");
            com_bt01_0x04(retMsg5[3].toInt());
            break;    
        case 0x05:
            // Serial.println("Status C02 int 0x03 0x05");
            com_bt01_0x05(retMsg5[3].toInt());
            break;    
        case 0x06:
            // Serial.println("Status Fan desum 0x03 0x06");
            com_bt01_0x06(retMsg5[3].toInt());
            break;    
        case 0x07:
            // Serial.println("Status Fan1 0x03 0x07");
            com_bt01_0x07(retMsg5[3].toInt());
            break;    
        case 0x08:
            // Serial.println("Status Fan2 0x03 0x08");
            com_bt01_0x08(retMsg5[3].toInt());
            break;    
        case 0x09:
            // Serial.println("Status Light 0x03 0x09");
            com_bt01_0x09(retMsg5[3].toInt());
            break;    
        case 0x0A:
            // Serial.println("Status Fan Peltier Insu 0x03 0x0A");
            com_bt01_0x0A(retMsg5[3].toInt());
            break;    
        case 0x0B:
            // Serial.println("Status Fan Peltier Desum 0x03 0x0B");
            com_bt01_0x0B(retMsg5[3].toInt());
            break;    
        case 0x0C:
            // Serial.println("Status Light 0x03 0x0C");
            com_bt01_0x0C(retMsg5[3].toInt());
            break;
        case 0x0D:
            // Serial.println("Status Door 0x03 0x0D");
            com_bt01_0x0D(retMsg5[3].toInt());
            break;       
        case 0x0E:
            // Serial.println("Status Water Level irrigation 0x03 0x0E");
            com_bt01_0x0E(retMsg5[3].toInt());
            break;
        case 0x0F:
            // Serial.println("Status Water Level Hum 0x03 0x0F");
            com_bt01_0x0F(retMsg5[3].toInt());
            break;         
        case 0x10:
            // Serial.println("Status Fan Petier 0x03 0x10");
            com_bt01_0x10(retMsg5[3].toInt());
            break;
        case 0x11:
            // Serial.println("Status Fan Petier 0x03 0x11");
            com_bt01_0x11(retMsg5[3].toInt());
            break;
        case 0x12:
            // Serial.println("Status Pump Desum 0x03 0x12");
            com_bt01_0x12(retMsg5[3].toInt());
            break;
        case 0x13:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x13(retMsg5[3].toInt());
            break;
        case 0x14:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x14(retMsg5[3].toInt());
            break;    
        case 0x15:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x15(retMsg5[3].toInt());
            break;    
        case 0x16:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x16(retMsg5[3].toInt());
            break;    
        case 0x17:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x17(retMsg5[3].toInt());
            break;    
        case 0x18:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x18(retMsg5[3].toInt());
            break;    
        case 0x19:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x19(retMsg5[3].toInt());
            break;    
        case 0x1A:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x1A(retMsg5[3].toInt());
            break;    
        case 0x1B:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x1B(retMsg5[3].toInt());
            break;    
        case 0x1C:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x1C(retMsg5[3].toInt());
            break;    
        case 0x1D:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x1D(retMsg5[3].toInt());
            break;    
        case 0x1E:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x1E(retMsg5[3].toInt());
            break;    
        case 0x1F:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x1F(retMsg5[3].toInt());
            break;    
        case 0x20:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x20(retMsg5[3].toInt());
            break;    
        case 0x21:
            // Serial.println("Fan 3 Intensidade (PMW)");
            com_bt01_0x21(retMsg5[3].toInt());
            break;    
        case 0x22:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x22(retMsg5[3].toInt());
            break;        
        case 0x23:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x23(retMsg5[3].toInt());
            break;        
        case 0x24:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x24(retMsg5[3].toInt());
            break;        
        case 0x25:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x25(retMsg5[3].toInt());
            break;  
        case 0xFF:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_bt01_0x25(retMsg5[3].toInt());
            break;              
        
     }
}


void com_bt01_0x00(int command){
    Serial.println("serv 01 - 00");
    temp_int_max_stp = command;    
}

void com_bt01_0x01(int command){
    Serial.println("serv 01 - 01");
    temp_int_min_stp = command;
}

void com_bt01_0x02(int command){
    Serial.println("serv 01 - 02");
    hum_int_max_stp = command;
}

void com_bt01_0x03(int command){
    Serial.println("serv 01 - 03");
    hum_int_min_stp = command;    
}

void com_bt01_0x04(int command){
    Serial.println("serv 01 - 04");
    soil_hum_max_stp = command;
}

void com_bt01_0x05(int command){
    Serial.println("serv 01 - 05");
    soil_hum_min_stp = command;
}

void com_bt01_0x06(int command){
    Serial.println("serv 01 - 06");
    ph_irrig_stp  = command;
}

void com_bt01_0x07(int command){
    Serial.println("serv 01 - 07");
    ph_hum_stp = command;
}

void com_bt01_0x08(int command){
    Serial.println("serv 01 - 08");
    light_hr_on_stp = command;
}

void com_bt01_0x09(int command){
    Serial.println("serv 01 - 09");
    light_min_on_stp = command;
}

void com_bt01_0x0A(int command){
    Serial.println("serv 01 - 0A");
    light_hr_off_stp = command;
}

void com_bt01_0x0B(int command){
    Serial.println("serv 01 - 0B");
    light_min_off_stp = command;
}

void com_bt01_0x0C(int command){
    Serial.println("serv 01 - 0C");
    pump_hr_irr_on_stp = command;
}

void com_bt01_0x0D(int command){
    Serial.println("serv 01 - 0D");
    pump_min_irr_on_stp = command;    
}

void com_bt01_0x0E(int command){
    Serial.println("serv 01 - 0E");
    pump_hr_irr_off_stp = command;
}

void com_bt01_0x0F(int command){
    Serial.println("serv 01 - 0F");
    pump_min_irr_off_stp = command;
}

void com_bt01_0x10(int command){
    Serial.println("serv 01 - 10");
    irr_interval_stp = command;
}

void com_bt01_0x11(int command){
    Serial.println("serv 01 - 11");
    irr_time_stp = command;    
}

void com_bt01_0x12(int command){
    Serial.println("serv 01 - 12");
    irr_1_hr_stp = command;
}

void com_bt01_0x13(int command){
    Serial.println("serv 01 - 13");
    irr_1_min_stp = command;
}

void com_bt01_0x14(int command){
    Serial.println("serv 01 - 14");
    irr_2_hr_stp = command;
}

void com_bt01_0x15(int command){
    Serial.println("serv 01 - 15");
    irr_2_min_stp = command;
}

void com_bt01_0x16(int command){
    Serial.println("serv 01 - 16");
    irr_3_hr_stp = command;
}

void com_bt01_0x17(int command){
    Serial.println("serv 01 - 17");
    irr_3_min_stp = command;
}

void com_bt01_0x18(int command){
    Serial.println("serv 01 - 18");
    irr_4_hr_stp = command;
}

void com_bt01_0x19(int command){
    Serial.println("serv 01 - 19");
    irr_4_min_stp = command;
}

void com_bt01_0x1A(int command){
    Serial.println("serv 01 - 1A");
    irr_5_hr_stp = command;
}

void com_bt01_0x1B(int command){
    Serial.println("serv 01 - 1B");
    irr_5_min_stp = command;
}

void com_bt01_0x1C(int command){
    Serial.println("serv 01 - 1C");
    irr_6_hr_stp = command;
}

void com_bt01_0x1D(int command){
    Serial.println("serv 01 - 1D");
    irr_6_min_stp = command;
}

void com_bt01_0x1E(int command){
    Serial.println("serv 01 - 1E");
    light_pwm_stp = command;
}

void com_bt01_0x1F(int command){
    Serial.print("serv 01 - 1F: ");
    // Serial.println(command);
    fan1_inf_pwm_stp = command;
    Serial.println(fan1_inf_pwm_stp);
    // ESP_SERIAL.print("2,0x01,0x1F,"+String(fan1_inf_pwm_stp)+",#"); 
}

void com_bt01_0x20(int command){
    Serial.print("serv 01 - 20: ");
    // Serial.println(command);
    fan2_inf_pwm_stp = command;
    Serial.println(fan2_inf_pwm_stp);
    // ESP_SERIAL.print("2,0x01,0x20,"+String(fan2_inf_pwm_stp)+",#"); 
}

void com_bt01_0x21(int command){
    Serial.print("serv 01 - 21: ");
    // Serial.println(command);
    fan3_inf_pwm_stp = command;
    Serial.println(fan3_inf_pwm_stp);
    // ESP_SERIAL.print("2,0x01,0x21,"+String(fan3_inf_pwm_stp)+",#"); 
}

void com_bt01_0x22(int command){
    Serial.print("serv 01 - 22: ");
    fan1_inf_pwm_light_stp = command;
    Serial.println(fan1_inf_pwm_light_stp);
    // ESP_SERIAL.print("2,0x01,0x22,"+String(fan1_inf_pwm_light_stp)+",#"); 
}

void com_bt01_0x23(int command){
    Serial.print("serv 01 - 23: ");
    fan2_inf_pwm_light_stp = command;
    Serial.println(fan2_inf_pwm_light_stp);
    // ESP_SERIAL.print("2,0x01,0x23,"+String(fan2_inf_pwm_light_stp)+",#"); 
}

void com_bt01_0x24(int command){
    Serial.print("serv 01 - 24: ");
    fan3_inf_pwm_light_stp = command;
    Serial.println(fan3_inf_pwm_light_stp);
    // ESP_SERIAL.print("2,0x01,0x24,"+String(fan3_inf_pwm_light_stp)+",#"); 
}

void com_bt01_0x25(int command){
    Serial.println("serv 01 - 25");
    irr_interval_on_stp = command;
}

