/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoHA.h> 

#include "defines.h"
#include "io_defines.h"
#include "comm_wifi.h"
#include "comm_bt.h"
#include "tools.h"
#include "control.h"
#include "mqtt_control.h"

void on_receive_bt(String line_in);


extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;
extern bool startGrow;

extern float eco2_ext;
extern float eco2_int;
extern float hum_ext;
extern float temp_ext;
extern float hum_ext;
extern float temp_int;
extern float hum_int;
extern float light_1_int;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float soil_4_hum;

extern bool water_irrig_1_level;
extern bool water_hum_1_level;

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5]; 

extern bool fan_dehum_on;
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;
extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool hum_1_on;
extern bool dehum_1_on;
extern bool relay1_on;
extern bool relay2_on;
extern bool relay3_on;
extern bool relay4_on;
extern bool doorState;

extern float fan_dehum_pwm;
extern float fan1_inf_pwm;
extern float fan2_inf_pwm;
extern float fan3_inf_pwm;
extern float fan_dehum_pwm;
extern float fan_hum_pwm;
extern float light_pwm;
extern float pump_irr_pwm;
extern float hum_1_pwm;
extern float dehum_1_pwm;

extern int dutyCycle1;
extern int dutyCycle2;
extern int dutyCycle3;
extern int dutyCycle4;

extern bool bt_connected;



void on_receive_bt(String line_in){
    split_msg_5(line_in);
    String recHex = retMsg5[1];
    // Serial.println("on receive bt");
    // Serial.println(line_in);
    // Serial.println(recHex);
    long i = strtol( recHex.c_str(), NULL, 16);
    // Serial.println(i);
    
    switch (i) {
        case 0:
          // Serial.println("Device State");
          update_variables_service0(line_in);
          break;
        case 1:
          // Serial.println("Setup");
          update_variables_service1(line_in);
          break; 
        case 2:
          // Serial.println("variables - value");
          update_variables_service2(line_in);
          break; 
        case 3:
          // Serial.println("Status - bollean");
          update_variables_service3(line_in);
          break;  
        case 4:
          // Serial.println("Commands - boolean");
          update_variables_service4(line_in);
          break;      
        case 5:
          // Serial.println("Commands - PWM");
          update_variables_service5(line_in);
          break;    
        case 6:
          // Serial.println("Commands - PWM");
          update_variables_service6(line_in);
          break;    
        case 7:
          // Serial.println("Commands - PWM");
          update_variables_service7(line_in);
          break;        
    }  
     
}

