/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#ifndef __MQTT_CONTROL_H__
#define __MQTT_CONTROL_H__
#include <Arduino.h>
#include <ArduinoHA.h> 

void mqtt_begin();
void mqtt_loop();
void mqtt_update();
void printValues();
void on_fan1(bool state, HASwitch* sender);
void on_fan2(bool state, HASwitch* sender);
void on_light(bool state, HASwitch* sender);
void on_pump_irr(bool state, HASwitch* sender);
void on_fan1a_slider(HANumeric number, HANumber* sender);
void on_fan2a_slider(HANumeric number, HANumber* sender);
void on_lighta_slider(HANumeric number, HANumber* sender);
void on_relay1(bool state, HASwitch* sender);
void on_relay2(bool state, HASwitch* sender);
void on_relay3(bool state, HASwitch* sender);
void on_relay4(bool state, HASwitch* sender);
void change_data(String service, String pid, String value);



void printValues();



#endif