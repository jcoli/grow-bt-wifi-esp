/**
Version: 0a
Tecnocoli - 09/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#ifndef __RECEIVE_MQTT_H__
#define __RECEIVE_MQTT_H__
#include <Arduino.h>
#include <ArduinoHA.h> 

void on_fan1_1_on(bool state, HASwitch* sender);
void on_fan2_1_on(bool state, HASwitch* sender);
void on_fan3_1_on(bool state, HASwitch* sender);
void on_light_1_on(bool state, HASwitch* sender);
void on_led_general(HANumeric number, HANumber* sender);
void on_led_red(HANumeric number, HANumber* sender);
void on_led_green(HANumeric number, HANumber* sender);
void on_led_blue(HANumeric number, HANumber* sender);
void on_fan1_slider(HANumeric number, HANumber* sender);
void on_fan2_slider(HANumeric number, HANumber* sender);
void on_fan3_slider(HANumeric number, HANumber* sender);



#endif