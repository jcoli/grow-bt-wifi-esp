/**
Version: 0a
Tecnocoli - 04/2024
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
espwroom32 - Grown
**/

#include <Arduino.h>

#include <WiFi.h>
#include <ArduinoHA.h> //MQTT
#include "BluetoothSerial.h"
#include <WiFiUdp.h>
#include <TimeLib.h>


#include "defines.h"
#include "io_defines.h"
#include "variables.h"
#include "tools.h"
#include "comm_wifi.h"
#include "comm_bt.h"
#include "control.h"
#include "mqtt_control.h"
#include "receive_bt.h"
#include "receive_mqtt.h"


TaskHandle_t Task1;
TaskHandle_t Task2;
// SemaphoreHandle_t i2cSemaphore;
BluetoothSerial BTSERIAL;
WiFiUDP Udp;



// NTPClient timeClient(ntpUDP,"168.181.126.108", -10800);
// static const char ntpServerName[] = "168.181.126.108";
static const char ntpServerName[] = "54.232.82.232";
const int timeZone = -3; 
unsigned int localPort = 8888;
const int NTP_PACKET_SIZE = 48; 
byte packetBuffer[NTP_PACKET_SIZE]; 
time_t prevDisplay = 0;


void serialEvent();
void serialEvent1();
void serialEvent2();

time_t getNtpTime();
void sendNTPpacket(IPAddress &address);
void printDigits(int digits);
void digitalClockDisplay();
void serialEventRun(void);
void printDeviceAddress();
void Task_1( void * pvParameters );
void Task_2( void * pvParameters );

void serialEventRun(void)
{
  if (serialEvent2 && ESP_SERIAL.available())
  {
    serialEvent2();
  }
  if (serialEvent && Serial.available())
  {
    serialEvent();
  }
  if (serialEvent1 && BT_SERIAL.available()) {
    serialEvent1();
  }
}

// void createSemaphore(){
//     i2cSemaphore = xSemaphoreCreateMutex();
//     xSemaphoreGive( ( i2cSemaphore) );
// }

// void lockVariable(){
//     xSemaphoreTake(i2cSemaphore, portMAX_DELAY);
// }

// void unlockVariable(){
//     xSemaphoreGive(i2cSemaphore);
// }




void setup() {
    Serial.begin(115200);
    ESP_SERIAL.begin(115200, SERIAL_8N1, RXp2, TXp2);
    BT_SERIAL.begin(28800);
    delay(10000);

    pinMode(LED_PIN, OUTPUT);

    BT_SERIAL.begin("GrowBT Master");
    
    delay(3000);
    Serial.println("wifi");
    xTaskCreate(
          Task_1,      
          "Task_1",    
          9000,       
          NULL,         
          1,            
          &Task1//,       
          // 0             
    );
    delay(500);
    xTaskCreate(
          Task_2,      
          "Task_2",    
          9000,       
          NULL,        
          2,           
          &Task2//,      
          // 1            
    );
    loopDelay = millis();
    loopDelay_first = millis();
    loopDelay_update = millis();
    loopDelay_mqtt = millis();
    loopDelay_bt = millis();
    loopDelay_ntp = millis();
    loopDelay_test = millis();
    delay(10000);
    loopDelay_first = millis();
    Serial.println("wifi2");
    ESP_SERIAL.print("1,0x06,0x00,1,#");
    loopDelay = millis();
    loopDelay_first = millis();
    loopDelay_update = millis();
    loopDelay_mqtt = millis();
    loopDelay_bt = millis();
    loopDelay_ntp = millis();
    loopDelay_test = millis();
    // delay(5000);
    // if (wifi_connected){ 
    //       if (!udp_setup){ 
    //         Udp.begin(localPort);
    //         setSyncProvider(getNtpTime);
    //         setSyncInterval(300);
    //         udp_setup=true;
    //       }else{  
    //           if (timeStatus() != timeNotSet) {
    //           if (now() != prevDisplay) { //update the display only if time has changed
    //             prevDisplay = now();
    //             digitalClockDisplay();
    //           }
    //         }
    //       }  
    // }
    // loopDelay = millis();
    // loopDelay_first = millis();
    // loopDelay_update = millis();
    // loopDelay_mqtt = millis();
    // loopDelay_bt = millis();
    // loopDelay_ntp = millis();
    // loopDelay_test = millis(); 
    
}

void loop() {

  

  
}

void Task_1( void * pvParameters ){
    for(;;){
      delay(100);
      // lockVariable();
      if (millis() - loopDelay_first > TIMER_FIRST){
        // Serial.println("wifi3");
        loopDelay_first = millis();
        first_run = false;
      } 
      if (millis() - loopDelay_ntp > TIMER_NTP){
        // Serial.println("NTP");
        loopDelay_ntp = millis();
        if (wifi_connected){ 
          if (!udp_setup){ 
            Udp.begin(localPort);
            setSyncProvider(getNtpTime);
            setSyncInterval(300);
            udp_setup=true;
            startGrow = true;
            // Serial.println("ntp no setup");
            digitalClockDisplay();
          }else{  
              if (timeStatus() != timeNotSet) {
              if (now() != prevDisplay) { //update the display only if time has changed
                prevDisplay = now();
                digitalClockDisplay();
              }
            }
          }  
        } 
        
      }
      
      // unlockVariable();
      // vTaskDelay(100);   
    }
  
}
void Task_2( void * pvParameters ){
  for(;;){
    delay(10);
    // lockVariable();
    if ((millis() - loopDelay_mqtt > TIMER_MQTT) & (startGrow)){
        // Serial.println("wifi6");
        loopDelay_mqtt = millis();
        mqtt_loop();
    }
    if ((millis() - loopDelay > TIMER_SEND_MQTT) & (startGrow)){
      // Serial.println("wifi7");
      // Serial.print("Send Mqtt");
      // String datetime = String (day())+"/"+String(month())+"/"+String(year())+" - "+String(hour())+":"+String(minute())+":"+String(second());
      // Serial.println(datetime);
      
      loopDelay = millis();
      
      if (wifi_connected){ 
          if (!first_run){
            mqtt_update();
          }
      }
    }  
    if ((millis() - loopDelay_bt > TIMER_BT) & (startGrow)){
        loopDelay_bt = millis();
        // Serial.print("Send BT: ");
        // String datetime = String (day())+"/"+String(month())+"/"+String(year())+" - "+String(hour())+":"+String(minute())+":"+String(second());
        // Serial.println(datetime);
        
        if (!bt_connected){
          bt_status();
          sendMsgBT();
        }else{
          sendMsgBT();
          // Serial.println("bt");
        }
        sendMsgESP();
    }
    
    // unlockVariable();
    // vTaskDelay(100);
  }
  if ((millis() - loopDelay_update > TIMER_INPUT)){
      loopDelay_update = millis();
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
  }
  
}

void digitalClockDisplay()
{
  // digital clock display of the time

  // Serial.print(hour());
  // ESP_SERIAL.print("");
  // printDigits(minute());
  // printDigits(second());
  // Serial.print(" ");
  // Serial.print(weekday());
  // Serial.print(".");
  // Serial.print(day());
  // Serial.print(".");
  // Serial.print(month());
  // Serial.print(".");
  // Serial.print(year());
  // Serial.println("");
  String datetime = String (day())+","+String(month())+","+String(year())+","+String(hour())+","+String(minute())+","+String(second());
  String msg = "9,0x09,"+String(weekday())+","+datetime+",#";
  ESP_SERIAL.print(msg);
}


void printDigits(int digits)
{
  // utility for digital clock display: prints preceding colon and leading 0
  // Serial.print(":");
  // if (digits < 10)
  //   Serial.print('0');
  // Serial.print(digits);
}

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  // Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  // Serial.print(ntpServerName);
  // Serial.print(": ");
  // Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP); 
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      // Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  // Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

void serialEvent()
{
  while (Serial.available())
  {
    // delay(30);
    char inChar = (char)Serial.read();
    line += inChar;
    if (inChar == '#')
    {
      stringComplete = true;
      // Serial.print(line);
    }
  }
  if (stringComplete){
    // BT_SERIAL.println(line);
    // Serial2.println(line1);
    stringComplete = false;
    line = "";
  }  
}

void serialEvent1()
{
  // Serial.print("serial 1: ");
  while (BT_SERIAL.available() && !string1Complete)
  {
    // delay(50);
    char inChar = (char)BT_SERIAL.read();
    line1 += inChar;
    // Serial.println(line1);
    if ((inChar == '#'))
    {
      string1Complete = true;
      // Serial.print("serial uC: ");
      // Serial.println(line1);
      
    }
  }
  // on_receive(line1);
  if (string1Complete){
    bt_rec = true;
    // Serial.print("serial BT: ");
    // BT_SERIAL.println(line1);
    on_receive_bt(line1);
    // Serial.println(line1);
    bt_connected = true;
    ESP_SERIAL.print(line1);
    string1Complete = false;
    line1 = "";
    bt_rec = false;
  }  
}

void serialEvent2()
{
  while (ESP_SERIAL.available() && !string2Complete)
  {
    esp_rec = true;
    char inChar = (char)ESP_SERIAL.read();
    line2 += inChar;
    // Serial.println(line2);
    if ((inChar == '#'))
    {
      string2Complete = true;
    }
  }
  if (string2Complete){
    // Serial.print("serial 2: ");
    // Serial.println(line2);
    on_receive_master(line2);
    string2Complete = false;
    line2 = "";
    esp_rec = false;
  }
}


// void printDeviceAddress() {

//   const uint8_t* point = esp_bt_dev_get_address();
//   for (int i = 0; i < 6; i++) {
//     char str[3];
//     sprintf(str, "%02X", (int)point[i]);
//     // Serial.print(str);
//     btAddress = btAddress + (str);
//     if (i < 5){
//       // Serial.print(":");
//       btAddress = btAddress + ":";  
//     }

//   }
//   // Serial.println("--");
// }