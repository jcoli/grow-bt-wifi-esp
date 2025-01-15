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
#include "control.h"

// BluetoothSerial BT_SERIAL;

void bt_begin();
void bt_status();
void BTconnectionCheck();
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t*param);
void sendMsgBT();

extern float intTemp;
extern float eco2_ext;
extern float eco2_int;
extern float temp_int;
extern float hum_int;
extern float temp_ext;
extern float hum_ext;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float soil_4_hum;
extern float light_1_int;


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

extern float fan1_inf_pwm;
extern float fan2_inf_pwm;
extern float fan3_inf_pwm;
extern float light_pwm;

extern int dutyCycle1;
extern int dutyCycle2;
extern int dutyCycle3;
extern int dutyCycle4;

extern bool bt_connected;
extern bool wifi_connected;
extern bool mqtt_connected;
extern bool bt_rec;
extern bool esp_rec;


extern BluetoothSerial BTSERIAL;

void bt_begin(){
    // Serial.println("on_bt_init");
    BT_SERIAL.register_callback(callback);
    BT_SERIAL.println("2,0,0,0,#");

}

void bt_status(){
     
    BTconnectionCheck();
    

}

void BTconnectionCheck(){
    

//    BT_SERIAL.register_callback(callback);
  if (BT_SERIAL.connected()){
    // Serial.println("BlueTooth Connect");
    bt_connected = true;
  } else{
    bt_connected = false;
  } 

  if (bt_connected == true){
    // bluetoothConnected();
    // Serial.println("2,5,0,BTConn,#");
    // BT_SERIAL.print("2,5,1,BTConn,#\n"); 
    // ESP_SERIAL.print("2,0x03,0x22,1,#");    
  }

  else {
    // Serial.println("2,5,0,BTNotConn,#");
    // // BT_SERIAL.println("2,5,3,BTNotConn,#");
    // ESP_SERIAL.print("2,0x03,0x22,0,#");    
  }
}

void sendMsgBT(){
  if ((!bt_rec) && (!esp_rec)){
      if (bt_connected){
          // Serial.println("Bluetooth Connected");
          BT_SERIAL.print("3,0x02,0x00,"+ String(temp_ext)+",#\n"); 
          delay(100);
          BT_SERIAL.print("3,0x02,0x02,"+String(hum_ext)+",#\n"); 
          delay(100);
          BT_SERIAL.print("3,0x02,0x01,"+ String (temp_int)+",#\n"); 
          delay(100);
          BT_SERIAL.print("3,0x02,0x03,"+String(hum_int)+",#\n"); 
          delay(100);
          BT_SERIAL.print("3,0x02,0x04,"+String(eco2_ext)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x02,0x05,"+String(eco2_int)+",#\n");
          delay(100);
          // BT_SERIAL.print("3,0x02,0x09,"+String(water_irrig_1_level)+",#\n");
          // delay(200);
          // BT_SERIAL.print("3,0x02,0x0A,"+String(water_irrig_1_level)+",#\n");
          // delay(200);
          BT_SERIAL.print("3,0x02,0x12,"+String(soil_1_hum)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x02,0x13,"+String(soil_2_hum)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x02,0x14,"+String(soil_3_hum)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x02,0x15,"+String(soil_4_hum)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x02,0x11,"+String(light_1_int)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x03,0x06,"+String(water_irrig_1_level)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x03,0x07,"+String(water_hum_1_level)+",#\n");
          delay(100);
          if (fan1_inf_on){
            BT_SERIAL.print("3,0x04,0x01,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x01,0,#\n");
          }
          delay(100);
          if (fan2_inf_on){
            BT_SERIAL.print("3,0x04,0x02,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x02,0,#\n");
          }
          delay(100);
          if (fan3_inf_on){
            BT_SERIAL.print("3,0x04,0x03,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x03,0,#\n");
          }
          delay(100);
          if (light_on){
            BT_SERIAL.print("3,0x04,0x06,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x06,0,#\n");
          }
          delay(100);
          if (pump_irr_on){
            BT_SERIAL.print("3,0x04,0x0B,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x0B,0,#\n");
          }
          delay(100);
          if (relay1_on){
            BT_SERIAL.print("3,0x04,0x0E,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x0E,0,#\n");
          }
          delay(100);
          if (relay2_on){
            BT_SERIAL.print("3,0x04,0x0F,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x0F,0,#\n");
          }
          delay(100);
          if (relay3_on){
            BT_SERIAL.print("3,0x04,0x10,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x10,0,#\n");
          }
          delay(100);
          if (relay4_on){
            BT_SERIAL.print("3,0x04,0x11,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x11,0,#\n");
          }
          delay(100);
          if (out1_on){
            BT_SERIAL.print("3,0x04,0x12,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x12,0,#\n");
          }
          delay(100);
          if (out2_on){
            BT_SERIAL.print("3,0x04,0x13,1,#\n");
          }else{
            BT_SERIAL.print("3,0x04,0x13,0,#\n");
          }
          delay(100);
          BT_SERIAL.print("3,0x05,0x01,"+String(fan1_inf_pwm)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x05,0x02,"+String(fan2_inf_pwm)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x05,0x03,"+String(fan3_inf_pwm)+",#\n");
          delay(100);
          BT_SERIAL.print("3,0x05,0x06,"+String(light_pwm)+",#\n");
          // Serial.print("Light PWM: ");
          // Serial.println(light_pwm);
          delay(100);
      }else{
        // Serial.println("bt not connected");
      }
  }
}


void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t*param){
  
  if(event == ESP_SPP_SRV_OPEN_EVT){
    // Serial.println("Bluetooth Connected");
    
    bt_connected = true;
  }

  else {
    bt_connected = false;
  }
}