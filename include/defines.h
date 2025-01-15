/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/


#ifndef __DEFINES_H__
#define __DEFINES_H__

/* defines */
#define V03_MAX 3.6
#define V03_MIN 3.1
#define V05_MAX 5.5
#define V05_MIN 4.8
#define VBAT_MAX 8.4
#define VBAT_MIN 6.6  

#define TEMP_MAX 50
#define TEMP_MIN 10

static const char version[] = "0.0b";
static const char develop[] =  "jcoli-Tecnocoli";
static const char email_develop[] = "jcoli@tecnocoli.com.br";
static const char processor[] = "espwroom32";

#define RXp2 16
#define TXp2 17

#define ESP_SERIAL Serial2
#define BT_SERIAL BTSERIAL 

#define BROKER_ADDR  IPAddress(192,168,61,85)
#define BROKER_USERNAME     "mqtt_user" 
#define BROKER_PASSWORD     "shady55"
#define DEVICE_NAME "Grow_4a"


#define TIME_OUT 8000000
#define TIMER_SLEEP 600000
#define TIMER_ANALOG 5000
#define TIMER_MQTT 80
#define TIMER_BT 30000
#define TIMER_SEND_MQTT 30000
#define TIMER_INPUT 500
#define TIMER_UPDATE 30000
#define TIMER_FIRST 150000
#define TIMER_NTP 60000
 
#endif