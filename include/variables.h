/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#ifndef __VARIABLES_H__
#define __VARIABLES_H__

#include <Arduino.h>

int tim_alive = 0;
int tim_conn = 0;
int tim_sleep = 0;

String owner_name;
String owner_pass;

String ipaddress;
String gateway;
String subnet;
long rssi;
bool wifi_enabled = false;
bool wifi_alive = false;
bool wifi_connected = false;
String wifi_ssid;
String wifi_pwd;

IPAddress broker_ip = (192,168,61,85);
String ip_broker;
String username_broker;
String password_broker;
String name_device = "Grow Master";
String manufacturer = "GreenTomate";

String model = "1f";

bool startGrow = false;

bool mqtt_connected = false;
bool bt_rec = false;
bool esp_rec = false;

bool bt_enabled = false;
bool bt_connected = false;
bool bt_alive = false;

String line = "";
String line1 = "";
String line2 = "";

bool stringComplete = false;
bool string1Complete = false;
bool string2Complete = false;

// String comm_frame[5];
// String Ssid_name[10];
// String Rssi[10];
char ssid[20];
char pwd[20];
byte mac[6];



unsigned long loopDelay = millis();
unsigned long loopDelay_first = millis();
unsigned long loopDelay_update = millis();
unsigned long loopDelay_mqtt = millis();
unsigned long loopDelay_bt = millis();
unsigned long loopDelay_ntp = millis();
unsigned long loopDelay_test = millis();

bool first_run = true;
bool udp_setup = false;

int temp_int_min_stp = 0;
int temp_int_max_stp = 0;

int hum_int_on_stp = 0;

int hum_int_min_stp = 0;
int hum_int_max_stp = 0;

int vpd_int_min_stp = 0;
int vpd_int_max_stp = 0;

int soil_hum_min_stp = 0;
int soil_hum_max_stp = 0;
int ph_irrig_stp = 0;
int ph_hum_stp = 0;

int light_hr_on_stp = 0;
int light_min_on_stp = 0;
int light_hr_off_stp = 0;
int light_min_off_stp = 0;

int pump_irr_on_stp = 0;
int pump_hr_irr_on_stp = 0;
int pump_min_irr_on_stp = 0;
int pump_hr_irr_off_stp = 0;
int pump_min_irr_off_stp = 0;

int irr_interval_stp = 0;
int irr_time_stp = 0;
int irr_interval_on_stp = 0;


int irr_1_hr_stp = 0;
int irr_1_min_stp = 0;
int irr_2_hr_stp = 0;
int irr_2_min_stp = 0;
int irr_3_hr_stp = 0;
int irr_3_min_stp = 0;
int irr_4_hr_stp = 0;
int irr_4_min_stp = 0;
int irr_5_hr_stp = 0;
int irr_5_min_stp = 0;
int irr_6_hr_stp = 0;
int irr_6_min_stp = 0;

int light_pwm_stp = 0;
int fan1_inf_pwm_stp = 0;
int fan2_inf_pwm_stp = 0;
int fan3_inf_pwm_stp = 0;

int fan1_inf_pwm_light_stp = 0;
int fan2_inf_pwm_light_stp = 0;
int fan3_inf_pwm_light_stp = 0;

float eco2_ext = 0.00;
float eco2_int = 0.00;
float temp_int = 0.00;
float hum_int = 0.00;
float temp_ext = 0.00;
float hum_ext = 0.00;
float soil_1_hum = 0.00;
float soil_2_hum = 0.00;
float soil_3_hum = 0.00;
float soil_4_hum = 0.00;
float light_1_int = 0.00;

bool water_irrig_1_level = false;
bool water_hum_1_level = false;

bool fan_dehum_on = false;
bool fan1_inf_on = false;
bool fan2_inf_on = false;
bool fan3_inf_on = false;
bool fan_hum_on = false;
bool light_on = false;
bool pump_irr_on = false;
bool hum_on = false;
bool hum_1_on = false;
bool hum_2_on = false;
bool hum_3_on = false;
bool hum_4_on = false;
bool dehum_1_on = false;
bool relay1_on = false;
bool relay2_on = false;
bool relay3_on = false;
bool relay4_on = false;
bool out1_on = false;
bool out2_on = false;

bool doorState = false;

float fan_dehum_pwm = 0.00;
float fan1_inf_pwm = 0.00;
float fan2_inf_pwm = 0.00;
float fan3_inf_pwm = 0.00;
float fan_hum_pwm = 0.00;
float fanP_dehum_pwm = 0.00;
float fanP_hum_pwm = 0.00;
float light_pwm = 0.00;

#endif
