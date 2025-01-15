/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#ifndef __COMM_WIFI_H__
#define __COMM_WIFI_H__

void printMacAddress(byte mac[]);
void printCurrentNet();
void printWifiData();
void printEncryptionType(int thisType);
void listNetworks();
void wifi_begin(String ssid_name, String ssid_pwd);
void checkStatus();
void sendMsgESP();


#endif