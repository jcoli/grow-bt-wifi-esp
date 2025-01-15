/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#include <Arduino.h>
#include <WiFi.h>
#include "BluetoothSerial.h"

#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "comm_wifi.h"
#include "control.h"
#include "mqtt_control.h"


void listNetworks();
void wifi_begin(String ssid_name, String ssid_pwd);
void checkStatus();
void printMacAddress(byte mac[]);
void printCurrentNet();
void printWifiData();
void printEncryptionType(int thisType);
void sendMsgESP();

extern bool bt_enabled;
extern bool bt_connected;
extern bool bt_alive;
extern bool startGrow;

extern bool mqtt_connected;

extern int tim_alive;
extern int tim_conn;
extern int tim_sleep;

extern String ipaddress;
extern long rssi;
extern bool wifi_enabled ;
extern bool wifi_alive;
extern bool wifi_connected;
extern String wifi_ssid;
extern String wifi_pwd;
extern IPAddress broker_ip;
extern String ip_broker;
extern String username_broker;
extern String password_broker;
extern String name_device;

extern char ssid[20];
extern char pwd[20];

extern BluetoothSerial BTSERIAL;

int status = WL_IDLE_STATUS;

void wifi_begin(String ssid_name, String ssid_pwd){

  // ssid_name = "Area51";
  // ssid_pwd = "shady6565";
  // WiFi.config(LOCAL_IP, GATEWAY, SUBNET);
  // WiFi.config(DHCP);
  Serial.print("Attempting to connect to WPA SSID1: ");
  Serial.print(ssid_name);
  Serial.print(" , ");      
  Serial.println(ssid_pwd);
  // WiFi.config();
  if ((!ssid_name.isEmpty()) && (!ssid_pwd.isEmpty())){
      Serial.print("Connect to WPA SSID: ");

      wifi_ssid = ssid_name;
      wifi_pwd = ssid_pwd;

      wifi_ssid.toCharArray(ssid, ssid_name.length()+1);
      wifi_pwd.toCharArray(pwd, ssid_pwd.length()+1);
      WiFi.mode(WIFI_STA);
      
      int tent = 0;
      while ((status != 1) && (tent<30)) {
          tent++;
          WiFi.begin(ssid, pwd);
          delay(5000);
          status = WiFi.isConnected();
      }
      delay(2000);
      if (status == 1){
          wifi_connected = true;
      }
        delay(5000);
      if (wifi_connected){  
        if ((!username_broker.isEmpty()) && (!password_broker.isEmpty()) && (!broker_ip.toString().isEmpty())){
          mqtt_begin();
          startGrow = true;
          Serial.println("send do mqtt begin");
        }else{
          Serial.println("NOT send do mqtt begin");
        }
      }else{
        Serial.println("wifi not connect");
      }
        // mqtt_update();
  }else{
    Serial.println("cant connect to wifi");
  }
}

void checkStatus(){
  if (status == WL_CONNECTED){
    wifi_connected = true;
  }else{
    wifi_connected = false;
  }
}


void listNetworks() {
  // scan for nearby networks:
  

  int numSsid = WiFi.scanNetworks();
  // Serial.println("** Scan Networks **");
  if (numSsid == -1) {
    // Serial.println("Couldn't get a wifi connection");
    
  }
  if (numSsid>9){
    numSsid = 9;
  }
 
  // print the list of networks seen:
  // Serial.print("number of available networks:");
  // Serial.println(numSsid);
  // ESP_SERIAL.print("w,l,Scan Networks,9,#");
  // ESP_SERIAL.print("number of available networks: ");
  ESP_SERIAL.print("1,5,0,"+String(numSsid)+",#");
  BT_SERIAL.print("1,5,0,"+String(numSsid)+",#");
  delay(300);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    if (WiFi.SSID(thisNet).indexOf("#") != -1){
      thisNet++;
    }
    if (thisNet < numSsid){
      // Serial.print(thisNet);
      // ESP_SERIAL.print("0,0,0,"+WiFi.SSID(thisNet)+",#");
      // delay(500);
      // Serial.print(" - ");
      // Serial.print(WiFi.SSID(thisNet));
      // Serial.print("\tSignal: ");
      // Serial.print(WiFi.RSSI(thisNet));
      ESP_SERIAL.print("0,0,"+WiFi.SSID(thisNet)+","+String(WiFi.RSSI(thisNet))+",#");
      BT_SERIAL.print("0,0,"+WiFi.SSID(thisNet)+","+String(WiFi.RSSI(thisNet))+",#");

      // Serial.print(" dBm");
      // Serial.println("");
      delay(1200);
    }  
  }
  // delay(300);
  
  // ESP_SERIAL.print("2,0,0,0,#");
  // BT_SERIAL.print("2,0,0,0,#");
}

void sendMsgESP(){
  if (wifi_connected){
    ESP_SERIAL.print("2,0x03,0x21,1,#");
  }else{
    ESP_SERIAL.print("2,0x03,0x21,0,#");
  }
  delay(100);
  if (bt_connected){
    ESP_SERIAL.print("2,0x03,0x22,1,#");    
  }else {
    ESP_SERIAL.print("2,0x03,0x22,0,#");    
  }
  delay(100);
  if (mqtt_connected){
    ESP_SERIAL.print("2,0x03,0x23,1,#");  
  }else{
    ESP_SERIAL.print("2,0x03,0x23,0,#");  
  }
  delay(300);
  

}


void printEncryptionType(int thisType) {
  // // read the encryption type and print out the name:
  // switch (thisType) {
  //   case ENC_TYPE_WEP:
  //     Serial.println("WEP");
  //     break;
  //   case ENC_TYPE_TKIP:
  //     Serial.println("WPA");
  //     break;
  //   case ENC_TYPE_CCMP:
  //     Serial.println("WPA2");
  //     break;
  //   case ENC_TYPE_NONE:
  //     Serial.println("None");
  //     break;
  //   case ENC_TYPE_AUTO:
  //     Serial.println("Auto");
  //     break;
  //   case ENC_TYPE_UNKNOWN:
  //   default:
  //     Serial.println("Unknown");
  //     break;
  // }
}

void printWifiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  // Serial.print("IP Address: ");
  // Serial.println(ip);
  // Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  // Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // // print the SSID of the network you're attached to:
  // Serial.print("SSID: ");
  // Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial2.print("IP Address: ");
  Serial2.println(ip);

  // // print the MAC address of the router you're attached to:
  // byte bssid[6];
  // WiFi.BSSID(bssid);
  
  // Serial.print("BSSID: ");
  // printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial2.print("signal strength (RSSI):");
  Serial2.println(rssi);

  // print the encryption type:
  // byte encryption = WiFi.encryptionType();
  // Serial.print("Encryption Type:");
  // Serial.println(encryption, HEX);
  // Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      // Serial.print("0");
    }
    // Serial.print(mac[i], HEX);
    if (i > 0) {
      // Serial.print(":");
    }
  }
  // Serial.println();
}

 

