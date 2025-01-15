/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoHA.h> 
#include "BluetoothSerial.h"

#include "defines.h"
#include "io_defines.h"
#include "comm_wifi.h"
#include "comm_bt.h"
#include "tools.h"
#include "receive_mqtt.h"

void mqtt_begin();
void mqtt_loop();
void mqtt_update();
void printValues();
void on_fan1(bool state, HASwitch* sender);
void on_fan2(bool state, HASwitch* sender);
void on_fan3(bool state, HASwitch* sender);
void on_light(bool state, HASwitch* sender);
void on_pump_irr(bool state, HASwitch* sender);
void on_fan1_slider(HANumeric number, HANumber* sender);
void on_fan2_slider(HANumeric number, HANumber* sender);
void on_fan3_slider(HANumeric number, HANumber* sender);
void on_light_slider(HANumeric number, HANumber* sender);
void on_hum(bool state, HASwitch* sender);
void on_relay1(bool state, HASwitch* sender);
void on_relay2(bool state, HASwitch* sender);
void on_relay3(bool state, HASwitch* sender);
void on_relay4(bool state, HASwitch* sender);
void change_data(String service, String pid, String value);

extern float intTemp;
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
extern float eco2_int;
extern float eco2_ext;

extern bool water_irrig_1_level;
extern bool water_hum_1_level;

extern byte mac[6];
extern bool wifi_connected;
extern bool mqtt_connected;
extern bool bt_rec;
extern bool esp_rec;

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

extern float fan_dehum_pwm;
extern float fan1_inf_pwm;
extern float fan2_inf_pwm;
extern float fan3_inf_pwm;
extern float fan_hum_pwm;
extern float light_pwm;
extern float pump_irr_pwm;
extern float hum_1_pwm;
extern float dehum_1_pwm;

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;

extern IPAddress broker_ip;
extern String ip_broker;
extern String username_broker;
extern String password_broker;
extern String name_device;
extern String manufacturer;
extern String model;




extern BluetoothSerial BTSERIAL;

extern byte mac[6];
byte unique[6];

WiFiClient wifiClient1;

HADevice device;
HAMqtt mqtt(wifiClient1, device, 50);

// HABinarySensor fan1_inf_state_ha("fan_insuflation_1");
// HABinarySensor fan2_inf_state_ha("fan_insuflation_2");
// HABinarySensor fan3_inf_state_ha("fan_insuflation_3");
// HABinarySensor light_state_ha("light_on_1");
// HABinarySensor pump_irr_state_ha("pump_irr_on_1");
// HABinarySensor hum_1_state_ha("hum_on_1");
// HABinarySensor dehum_1_state_ha("dehum_on_1");
HABinarySensor door_state_ha("door_on_1");
HABinarySensor water_hum_1_level_state_ha("water_hum_level_1");
HABinarySensor water_irrig_1_level_state_ha("water_irrig_level_1");

HASensorNumber eco2_ext_ha("CO2_1", HASensorNumber::PrecisionP1);
HASensorNumber eco2_int_ha("CO2_2", HASensorNumber::PrecisionP1);
HASensorNumber temp_ext_ha("temp_ext", HASensorNumber::PrecisionP1);
HASensorNumber hum_ext_ha("hum_ext", HASensorNumber::PrecisionP1);
HASensorNumber temp_int_ha("temp_int", HASensorNumber::PrecisionP1);
HASensorNumber hum_int_ha("hum_int", HASensorNumber::PrecisionP1);
HASensorNumber soil_1_hum_ha("soil_hum_1", HASensorNumber::PrecisionP1);
HASensorNumber soil_2_hum_ha("soil_hum_2", HASensorNumber::PrecisionP1);
HASensorNumber soil_3_hum_ha("soil_hum_3", HASensorNumber::PrecisionP1);
HASensorNumber soil_4_hum_ha("soil_hum_4", HASensorNumber::PrecisionP1);
HASensorNumber light_1_int_ha("light_1_int_1", HASensorNumber::PrecisionP1);

HANumber fan1_inf_pwm_ha("fan1_inf_pwm_ha");
HANumber fan2_inf_pwm_ha("fan2_inf_pwm_ha");
HANumber fan3_inf_pwm_ha("fan3_inf_pwm_ha");
HANumber light_pwm_ha("light_pwm_ha");

HASwitch switch_fan1_inf_on_ha("switch_fan1_inf_on");
HASwitch switch_fan2_inf_on_ha("switch_fan2_inf_on");
HASwitch switch_fan3_inf_on_ha("switch_fan3_inf_on");
HASwitch switch_light_on_ha("switch_light_on");
HASwitch switch_pump_irr_on_ha("switch_pump_irr_on");
HASwitch switch_hum_on_ha("switch_hum_on");
HASwitch switch_relay1_ha("switch_relay1_on");
HASwitch switch_relay2_ha("switch_relay2_on");
HASwitch switch_relay3_ha("switch_relay3_on");
HASwitch switch_relay4_ha("switch_relay4_on");

void mqtt_begin(){
     device.enableLastWill();
     unique[0] = 89;
     unique[1] = 34;
     unique[2] = 67;
     unique[3] = 32;
     unique[4] = 78;
     unique[5] = 21;

     WiFi.macAddress(mac);

     device.setUniqueId(unique, 6);
     device.setName(name_device.c_str());
     device.setSoftwareVersion(version);
     device.setManufacturer(manufacturer.c_str());
     device.setModel(model.c_str());
     device.enableSharedAvailability();

     // fan1_inf_state_ha.setName("Fan 1");
     // fan1_inf_state_ha.setIcon("mdi:fan");

     // fan2_inf_state_ha.setName("Fan 2");
     // fan2_inf_state_ha.setIcon("mdi:fan");

     // fan3_inf_state_ha.setName("Fan 3");
     // fan3_inf_state_ha.setIcon("mdi:fan");     

     // light_state_ha.setName("lights");
     // light_state_ha.setIcon("mdi:led-on");      

     // hum_1_state_ha.setName("Humidificador");
     // hum_1_state_ha.setIcon("mdi:power-plug");

     // dehum_1_state_ha.setName("Desumidificador");
     // dehum_1_state_ha.setIcon("mdi:power-plug");

     water_hum_1_level_state_ha.setName("Nivel Agua Hum");
     water_hum_1_level_state_ha.setIcon("mdi:water-alert");

     water_irrig_1_level_state_ha.setName("Nivel Agua Rega");
     water_irrig_1_level_state_ha.setIcon("mdi:water-alert");

     // pump_irr_state_ha.setName("Bomba Irr");
     // pump_irr_state_ha.setIcon("mdi:pump");

     door_state_ha.setName("Porta");
     door_state_ha.setDeviceClass("door");
     door_state_ha.setIcon("mdi:door");

     switch_fan1_inf_on_ha.setName("Fan 1");
     switch_fan1_inf_on_ha.onCommand(on_fan1);
     switch_fan1_inf_on_ha.setIcon("mdi:fan"); 
     switch_fan1_inf_on_ha.setState(fan1_inf_on);  

     switch_fan2_inf_on_ha.setName("Fan 2");
     switch_fan2_inf_on_ha.onCommand(on_fan2);
     switch_fan2_inf_on_ha.setIcon("mdi:fan"); 
     switch_fan2_inf_on_ha.setState(fan2_inf_on);  

     switch_fan3_inf_on_ha.setName("Fan 3");
     switch_fan3_inf_on_ha.onCommand(on_fan3);
     switch_fan3_inf_on_ha.setIcon("mdi:fan"); 
     switch_fan3_inf_on_ha.setState(fan3_inf_on);

     switch_light_on_ha.setName("Light");
     switch_light_on_ha.onCommand(on_light);
     switch_light_on_ha.setIcon("mdi:led-on"); 
     switch_light_on_ha.setState(light_on);  

     switch_pump_irr_on_ha.setName("Irr Pump");
     switch_pump_irr_on_ha.onCommand(on_pump_irr);
     switch_pump_irr_on_ha.setIcon("mdi:pump"); 
     switch_pump_irr_on_ha.setState(pump_irr_on);  

     switch_hum_on_ha.setName("Umidificador");
     switch_hum_on_ha.onCommand(on_hum);
     switch_hum_on_ha.setIcon("mdi:power-plug");
     switch_hum_on_ha.setState(hum_on);

     switch_relay1_ha.setName("Rele 1");
     switch_relay1_ha.onCommand(on_relay1);
     switch_relay1_ha.setIcon("mdi:power-plug");
     switch_relay1_ha.setState(relay1_on);

     switch_relay2_ha.setName("Rele 2");
     switch_relay2_ha.onCommand(on_relay2);
     switch_relay2_ha.setIcon("mdi:power-plug");
     switch_relay2_ha.setState(relay2_on);

     switch_relay3_ha.setName("Rele 3");
     switch_relay3_ha.onCommand(on_relay3);
     switch_relay3_ha.setIcon("mdi:power-plug");
     switch_relay3_ha.setState(relay3_on);

     switch_relay4_ha.setName("Rele 4");
     switch_relay4_ha.onCommand(on_relay4);
     switch_relay4_ha.setIcon("mdi:power-plug");
     switch_relay4_ha.setState(relay4_on);

     eco2_ext_ha.setName("C02 Extern");
     eco2_ext_ha.setUnitOfMeasurement("ppm");
     
     eco2_int_ha.setName("C02 Intern");
     eco2_int_ha.setUnitOfMeasurement("ppm");

     temp_int_ha.setName("Temp Intern");
     temp_int_ha.setUnitOfMeasurement("°C");

     temp_ext_ha.setName("Temp Extern");
     temp_ext_ha.setUnitOfMeasurement("°C");

     hum_int_ha.setName("Hum Intern");
     hum_int_ha.setUnitOfMeasurement("%");

     hum_ext_ha.setName("Hum Extern");
     hum_ext_ha.setUnitOfMeasurement("%");

     soil_1_hum_ha.setName("Soil Hum 1");
     soil_1_hum_ha.setUnitOfMeasurement("%");

     soil_2_hum_ha.setName("Soil Hum 2");
     soil_2_hum_ha.setUnitOfMeasurement("%");

     soil_3_hum_ha.setName("Soil Hum 3");
     soil_3_hum_ha.setUnitOfMeasurement("%");

     soil_4_hum_ha.setName("Soil Hum 4");
     soil_4_hum_ha.setUnitOfMeasurement("%");

     light_1_int_ha.setName("Light Int");
     light_1_int_ha.setUnitOfMeasurement("%");

     fan1_inf_pwm_ha.setName("Fan 1");
     fan1_inf_pwm_ha.onCommand(on_fan1_slider);
     fan1_inf_pwm_ha.setIcon("mdi:fan"); 
     fan1_inf_pwm_ha.setUnitOfMeasurement("%");

     fan2_inf_pwm_ha.setName("Fan 2"); 
     fan2_inf_pwm_ha.onCommand(on_fan2_slider);
     fan2_inf_pwm_ha.setIcon("mdi:fan"); 
     fan2_inf_pwm_ha.setUnitOfMeasurement("%");

     fan3_inf_pwm_ha.setName("Fan 3"); 
     fan3_inf_pwm_ha.onCommand(on_fan3_slider);
     fan3_inf_pwm_ha.setIcon("mdi:fan"); 
     fan3_inf_pwm_ha.setUnitOfMeasurement("%");

     light_pwm_ha.setName("Lights"); 
     light_pwm_ha.onCommand(on_light_slider);
     light_pwm_ha.setUnitOfMeasurement("%");
     light_pwm_ha.setIcon("mdi:led-on");

    if (wifi_connected){
        if (mqtt.begin(broker_ip, username_broker.c_str(), password_broker.c_str()) == true){
             Serial.println("Connected to MQTT broker");
             mqtt_connected = true;
          } else {
            Serial.println("Could not connect to MQTT broker");
             mqtt_connected = false;
        }
        
        delay(500); 
    } else {
          Serial.println("Wifi not connect - broker");
    }
     // if (mqtt.isConnected()){
     //      Serial.println("mqtt conn 1");
     // }else{
     //      Serial.println("mqtt not conn 1");
     // }
     

}



void mqtt_loop(){
     if (mqtt.isConnected()){
          // Serial.println("Mqtt Loop");
          mqtt_connected = true;
          mqtt.loop();
     }else{
          // mqtt_connected = false;
          // if (mqtt.begin(BROKER_ADDR, BROKER_USERNAME, BROKER_PASSWORD)==true){
          //      mqtt_connected = true;
          //      mqtt.loop();
          // }
          int status=mqtt.begin(broker_ip, username_broker.c_str(), password_broker.c_str());
          // Serial.print("Broker: ");
          // Serial.println(status);
          // Serial.println("Mqtt Reconect");
          mqtt.loop();
          
  }

}

void mqtt_update(){
     Serial.println("mqtt_update");
     if ((!bt_rec) && (!esp_rec)){
          if (mqtt.isConnected()){
               Serial.println("mqtt conn 2");
               
               if (eco2_ext>0) eco2_ext_ha.setValue(eco2_ext);
               if (eco2_int>0) eco2_int_ha.setValue(eco2_int);
               
               if (hum_ext>0) hum_ext_ha.setValue(hum_ext);
               if (temp_ext>0) temp_ext_ha.setValue(temp_ext);
               if (hum_ext>0) hum_ext_ha.setValue(hum_ext);
               if (temp_int>0) temp_int_ha.setValue(temp_int);
               if (hum_int>0) hum_int_ha.setValue(hum_int);
               
          
               if (soil_1_hum>=0){
                         soil_1_hum_ha.setValue(soil_1_hum);
                    }else{
                         soil_1_hum_ha.setValue(0);
                    }
                    if (soil_2_hum>=0){
                         soil_2_hum_ha.setValue(soil_2_hum);
                    }else{
                         soil_2_hum_ha.setValue(0);
                    }
                    if (soil_3_hum>=0){
                         soil_3_hum_ha.setValue(soil_3_hum);
                    }else{
                         soil_3_hum_ha.setValue(0);
                    }
                    if (soil_4_hum>=0){
                          soil_4_hum_ha.setValue(soil_4_hum);
                    }else{
                         soil_4_hum_ha.setValue(0);
                    }
                    if (light_1_int>=0){
                          light_1_int_ha.setValue(light_1_int);
                    }else{
                         light_1_int_ha.setValue(0);
                    }
               switch_fan1_inf_on_ha.setState(fan1_inf_on);
               switch_fan2_inf_on_ha.setState(fan2_inf_on);
               switch_fan3_inf_on_ha.setState(fan3_inf_on);
               switch_pump_irr_on_ha.setState(pump_irr_on);
               switch_light_on_ha.setState(light_on);

               switch_relay1_ha.setState(relay1_on);
               switch_relay2_ha.setState(relay2_on);
               switch_relay3_ha.setState(relay3_on);
               switch_relay4_ha.setState(relay4_on);

               // fan1_inf_state_ha.setState(fan1_inf_on);
               // fan2_inf_state_ha.setState(fan2_inf_on);
               // fan3_inf_state_ha.setState(fan3_inf_on);

               // hum_1_state_ha.setState(hum_on);
               // dehum_1_state_ha.setState(dehum_1_on);
               // light_state_ha.setState(light_on);
               water_hum_1_level_state_ha.setState(water_hum_1_level);
               water_irrig_1_level_state_ha.setState(water_irrig_1_level);
               // pump_irr_state_ha.setState(pump_irr_on);
               door_state_ha.setState(pump_irr_on);

          //   light_pwm_ha.setCurrentState(light_pwm);
               light_pwm_ha.setState(light_pwm);
               // Serial.println(light_pwm);
               fan1_inf_pwm_ha.setState(fan1_inf_pwm);
               fan2_inf_pwm_ha.setState(fan2_inf_pwm);
               fan3_inf_pwm_ha.setState(fan3_inf_pwm);  
               // pump_irr_state_ha.setState(pump_irr_on);
               water_hum_1_level_state_ha.setState(water_hum_1_level);
               water_irrig_1_level_state_ha.setState(water_irrig_1_level);

               // Serial.print("Pump: ");
               // Serial.println(pump_irr_on);


          }else{
               mqtt_connected = false;
               Serial.println("mqtt not conn 2");
               if (mqtt.begin(broker_ip, username_broker.c_str(), password_broker.c_str())==true){
                    mqtt_connected = true;
                    // Serial.println("mqtt conn 3");
                    if (eco2_ext>=0) eco2_ext_ha.setValue(eco2_ext);
                    if (eco2_int>=0) eco2_int_ha.setValue(eco2_int);
                    
                    if (hum_ext>=0) hum_ext_ha.setValue(hum_ext);
                    if (temp_ext>=0) temp_ext_ha.setValue(temp_ext);
                    if (hum_ext>=0) hum_ext_ha.setValue(hum_ext);
                    if (temp_int>=0) temp_int_ha.setValue(temp_int);
                    if (hum_int>=0) hum_int_ha.setValue(hum_int);
               
                    if (soil_1_hum>=0){
                         soil_1_hum_ha.setValue(soil_1_hum);
                    }else{
                         soil_1_hum_ha.setValue(0);
                    }
                    if (soil_2_hum>=0){
                         soil_2_hum_ha.setValue(soil_2_hum);
                    }else{
                         soil_2_hum_ha.setValue(0);
                    }
                    if (soil_3_hum>=0){
                         soil_3_hum_ha.setValue(soil_3_hum);
                    }else{
                         soil_3_hum_ha.setValue(0);
                    }
                    if (soil_4_hum>=0){
                          soil_4_hum_ha.setValue(soil_4_hum);
                    }else{
                         soil_4_hum_ha.setValue(0);
                    }
                    if (light_1_int>=0){
                          light_1_int_ha.setValue(light_1_int);
                    }else{
                         light_1_int_ha.setValue(0);
                    }
                    switch_fan1_inf_on_ha.setState(fan1_inf_on);
                    switch_fan2_inf_on_ha.setState(fan2_inf_on);
                    switch_fan3_inf_on_ha.setState(fan3_inf_on);
                    switch_pump_irr_on_ha.setState(pump_irr_on);
                    switch_light_on_ha.setState(light_on);

                    switch_relay1_ha.setState(relay1_on);
                    switch_relay2_ha.setState(relay2_on);
                    switch_relay3_ha.setState(relay3_on);
                    switch_relay4_ha.setState(relay4_on);

                    // fan1_inf_state_ha.setState(fan1_inf_on);
                    // fan2_inf_state_ha.setState(fan1_inf_on);
                    // fan3_inf_state_ha.setState(fan1_inf_on);
                    // hum_1_state_ha.setState(hum_on);
                    // dehum_1_state_ha.setState(dehum_1_on);
                    // light_state_ha.setState(light_on);
                    water_hum_1_level_state_ha.setState(water_hum_1_level);
                    water_irrig_1_level_state_ha.setState(water_irrig_1_level);
                    // pump_irr_state_ha.setState(pump_irr_on);
                    door_state_ha.setState(doorState);
                    
                    light_pwm_ha.setState(light_pwm);
                    // Serial.println(light_pwm);
                    fan1_inf_pwm_ha.setState(fan1_inf_pwm);
                    fan2_inf_pwm_ha.setState(fan2_inf_pwm);  
                    fan3_inf_pwm_ha.setState(fan3_inf_pwm);  
                    // pump_irr_state_ha.setState(pump_irr_on);
                    // Serial.print("Pump: 1");
                    // Serial.println(pump_irr_on);

               }else{
                    // Serial.println("mqtt not conn 3");
               }
          }
          // 
     }
     
}


void on_fan1(bool state, HASwitch* sender){
     fan1_inf_on = (state ? HIGH : LOW);
     sender->setState(state);
     if (state){
               change_data("0x04", "0x01", "1");
               if (bt_connected) BT_SERIAL.print("1,0x04,0x01,1,#\n");   
          }else{
               change_data("0x04", "0x01", "0");
               if (bt_connected) BT_SERIAL.print("1,0x04,0x01,0,#\n");   
     }
     Serial.println("fan 1");
}

void on_fan2(bool state, HASwitch* sender){
    fan2_inf_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x02", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x02,1,#\n");   
     }else{
          change_data("0x04", "0x02", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x02,0,#\n"); 
     }
     Serial.println("fan 2");
}

void on_fan3(bool state, HASwitch* sender){
    fan3_inf_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x03", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x03,1,#\n");   
     }else{
          change_data("0x04", "0x03", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x03,0,#\n"); 
     }
     Serial.println("fan 3");
}

void on_light(bool state, HASwitch* sender){
     light_on = (state ? HIGH : LOW);
     sender->setState(state);
     if (state){
          change_data("0x04", "0x06", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x06,1,#\n"); 
     }else{
          change_data("0x04", "0x06", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x06,0,#\n"); 
     }
     Serial.println("light 1");
}

void on_pump_irr(bool state, HASwitch* sender){
    pump_irr_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x0B", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0B,1,#\n"); 
     }else{
          change_data("0x04", "0x0B", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0B,0,#\n"); 
     }
    Serial.println("pump");
}

void on_hum(bool state, HASwitch* sender){
    hum_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x0C", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0C,1,#\n"); 
     }else{
          change_data("0x04", "0x0C", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0C,0,#\n"); 
     }
    Serial.println("hum");
    
}

void on_relay1(bool state, HASwitch* sender){
    relay1_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x0E", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0E,1,#\n"); 
     }else{
          change_data("0x04", "0x0E", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0E,0,#\n"); 
     }
    Serial.println("relay 1");
    
}

void on_relay2(bool state, HASwitch* sender){
    relay2_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x0F", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0F,1,#\n"); 
     }else{
          change_data("0x04", "0x0F", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x0F,0,#\n"); 
     }
    Serial.println("relay 2");
    
}

void on_relay3(bool state, HASwitch* sender){
    relay3_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x10", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x10,1,#\n"); 
     }else{
          change_data("0x04", "0x10", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x10,0,#\n"); 
     }
    Serial.println("relay 3");
    
}

void on_relay4(bool state, HASwitch* sender){
    relay4_on = (state ? HIGH : LOW);
    sender->setState(state);
    if (state){
          change_data("0x04", "0x11", "1");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x11,1,#\n"); 
     }else{
          change_data("0x04", "0x11", "0");
          if (bt_connected) BT_SERIAL.print("1,0x04,0x11,0,#\n"); 
     }
    Serial.println("relay 4");
    
}

void on_fan1_slider(HANumeric number, HANumber* sender){
     if (!number.isSet()) {
          change_data("0x05", "0x01", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x01,"+String(number.toFloat())+",#\n"); 
     } else {
          change_data("0x05", "0x01", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x01,"+String(number.toFloat())+",#\n"); 
          fan1_inf_pwm = number.toFloat();
     }  
     sender->setState(number);   
     Serial.println("fan1 pwm");   
}

void on_fan2_slider(HANumeric number, HANumber* sender){
    if (!number.isSet()) {
          change_data("0x05", "0x02", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x02,"+String(number.toFloat())+",#\n"); 
     } else {
          change_data("0x05", "0x02", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x02,"+String(number.toFloat())+",#\n"); 
          fan2_inf_pwm = number.toFloat();
     }  
     sender->setState(number);  
     Serial.println("fan2 pwm");   
}

void on_fan3_slider(HANumeric number, HANumber* sender){
    if (!number.isSet()) {
          change_data("0x05", "0x03", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x03,"+String(number.toFloat())+",#\n"); 
     } else {
          change_data("0x05", "0x03", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x03,"+String(number.toFloat())+",#\n"); 
          fan3_inf_pwm = number.toFloat();
     }  
     sender->setState(number);  
     Serial.println("fan3 pwm");   
}

void on_light_slider(HANumeric number, HANumber* sender){
    if (!number.isSet()) {
          change_data("0x05", "0x06", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x06,"+String(number.toFloat())+",#\n"); 
     } else {
          light_pwm = number.toFloat();  
          change_data("0x05", "0x06", String(number.toFloat()));
          if (bt_connected) BT_SERIAL.print("1,0x05,0x06,"+String(number.toFloat())+",#\n"); 
     }  
    sender->setState(number); 
    Serial.println("light pwm");   
}

void change_data(String service, String pid, String value){
     // Serial.println("1,"+service+","+pid+","+value+",#");
     ESP_SERIAL.print("1,"+service+","+pid+","+value+",#");
}

void printValues() {

    // Serial.printf("%02d/%02d/%02d ", day, month, year);
    // Serial.printf("%02d:%02d\n", hours, minutes);

    // HC05_SERIAL.printf("%02d/%02d/%02d ", day, month, year);
    // HC05_SERIAL.printf("%02d:%02d\n", hours, minutes);

    // Serial.println("pot1: ");
//     Serial.println(pot1);
//     Serial.print("pot2: ");
//     Serial.println(pot2);
//     Serial.print("soil humidity: ");
//     Serial.println(soil_1_hum);
//     Serial.print("light intensity: ");
//     Serial.println(light_1_int);

    


//     Serial.print("Temperature = ");
//     Serial.print(temp_ext);
//     Serial.println(" °C");
//     Serial.print("Pressure = ");
//     Serial.print(press_ext);
//     Serial.println(" hPa");
//     Serial.print("Humidity = ");
//     Serial.print(hum_ext);
//     Serial.println(" %");
    
    

//     Serial.println("========");

//     Serial.println("AHT");

//     Serial.print("Temperature: "); 
//     Serial.println(aht_temp); 
//     Serial.print("Humidity: "); 
//     Serial.println(aht_hum); 
    
//     Serial.print("AQI: ");
//     Serial.println(aqi_ext);
//     Serial.print("TVOC: ");
//     Serial.println(tvoc_ext);
//     Serial.print("eCO2: ");
//     Serial.println(eco2_ext);
//     ESP_SERIAL.print("3,4,eco2_ext,"+String(eco2_ext)+",#"); 
    


//     Serial.println("===================");
//     Serial.println("===================");
     
    // HC05_SERIAL.println("2,1,1,"+String(aht_temp)+",#"); 
    // HC05_SERIAL.println("2,1,2,"+String(aht_hum)+",#"); 
    
    // HC05_SERIAL.println("2,2,1,"+String(aqi_ext)+",#"); 
    // HC05_SERIAL.println("2,1,2,"+String(tvoc_ext)+",#"); 
    // HC05_SERIAL.println("2,1,2,"+String(eco2_ext)+",#"); 
    
}

