# WetterBox
Die Wetterbox verschickt alle 30min aktuelle Wetterdaten des Sensors per Telegram.

![](https://images.vexels.com/media/users/3/205087/isolated/preview/a41d84a485d960a7d929fd95ece1acf1-wetter-schlag-symbol-by-vexels.png)

### Benötigte Teile
- ESP8266 (egal welches Modell: Hier wurde der ESP8266 D1 Mini verwendet)
- DHT11 Temperatur/Feuchtigkeitsensor
- Optional: Batterie

### Anpassungen des Codes:
- WLAN Einstellungen müssen angepasst werden
- Telegram Bot Token muss hinterlegt werden
- Chat ID muss hinterlegt werden
- Optional: Zeit des DeepSleeps kann geändert werden

### Verkabelung:
- DHT11 Sensor: + an 5V | - an GND | DataPin an D1 vom ESP8266 D1 Mini
- Batterie: + an 5V | - an GND

### Support:
- Bei Fragen etc kannst du mir gerne bei Discord schreiben: Renax#6191
