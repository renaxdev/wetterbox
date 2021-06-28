/*
 Name:		    WetterBox
 Created:	    28/06/2021
 Author:	    Maximilian Körner <maximiliankoerner07@outlook.de>

*/
//Libs
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <DHT_U.h>

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

String ssid  = "---ENTER WLAN NAME---";
String pass  = "---ENTER PASS---";
String token = "---ENTER TELEGRAM BOT TOKEN"; 
#define CHAT_ID "--- ENTER CHAT ID"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(token, secured_client);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Telegram Bot...");
// Connect to Network
  WiFi.begin(ssid, pass);
  secured_client.setTrustAnchors(&cert);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  
// Sensor Readings
  dht.begin();	
  delay(2000);
  float temp = dht.readTemperature();
  float feuchte = dht.readHumidity();
	
// Battery Voltage Measuring
  int nVoltageRaw = analogRead(A0);
  float fVoltage = (float)nVoltageRaw * 0.00486;
  float fVoltageMatrix[22][2] = {
    {4.2,  100},
    {4.15, 95},
    {4.11, 90},
    {4.08, 85},
    {4.02, 80},
    {3.98, 75},
    {3.95, 70},
    {3.91, 65},
    {3.87, 60},
    {3.85, 55},
    {3.84, 50},
    {3.82, 45},
    {3.80, 40},
    {3.79, 35},
    {3.77, 30},
    {3.75, 25},
    {3.73, 20},
    {3.71, 15},
    {3.69, 10},
    {3.61, 5},
    {3.27, 0},
    {0, 0}
  };

  int i, perc;

  perc = 100;

  for(i=20; i>=0; i--) {
    if(fVoltageMatrix[i][0] >= fVoltage) {
      perc = fVoltageMatrix[i + 1][1];
      break;
    }
  }
	
//Sending data to Telegram Account	
  bot.sendMessage(CHAT_ID, "Die Außentemperatur beträgt: " + String(temp) + "°C" + "    Die Feuchtigkeit beträgt: " + String(feuchte) + "%" + "    Akkuladung: " + String(perc)+ "%");
  delay(500);
  Serial.println("Done sending Data");
  delay(1000);
  Serial.println("Going sleep... Next Data will be send in 30 minutes");  
  ESP.deepSleep(1800e6);
}

void loop() {
 //nothing here...
}
