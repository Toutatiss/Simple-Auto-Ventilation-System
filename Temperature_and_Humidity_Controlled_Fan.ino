// CREATED BY TOUTATISS, 12/01/2022
// CODE IS FREE TO USE
// FOR FURTHER DISCUSSION AND CONTACT INFO: jankoclock.wordpress.com

#include <DHT.h>

#define dhtDataPin 2
#define fanEnablePin 6
#define powerOnLEDPin 5
#define highTempLEDPin 3
#define highHumLEDPin 4

#define DHT_Type DHT22

DHT dht(dhtDataPin, DHT_Type);

float hum;
float temp;


void setup() {
  Serial.begin(9600);
  pinMode(fanEnablePin, OUTPUT);
  
  pinMode(powerOnLEDPin, OUTPUT);
  pinMode(highTempLEDPin, OUTPUT);
  pinMode(highHumLEDPin, OUTPUT);

  // INDICATE POWER ON
  digitalWrite(powerOnLEDPin, HIGH);

  // FAN TEST
  digitalWrite(fanEnablePin, HIGH);
  delay(2000);
  digitalWrite(fanEnablePin, LOW);

  // START UP DHTSENSOR
  dht.begin();
}

void loop() {
  getTempHum();

  // FAN ENABLE:
  if ((temp > 25.00)||(hum > 98.00)) {
    digitalWrite(fanEnablePin, HIGH);
  } else {
    digitalWrite(fanEnablePin, LOW);
  }

  // INDICATOR LIGHTS:
  getLightSettings();
  
  delay(1000);
}





void  getTempHum() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print(hum);
  Serial.print(" % RH\n");
  Serial.print(temp);
  Serial.print(" degrees C\n\n");
}

void getLightSettings() {
  if ((temp > 25.00)&&(hum > 60.00)) {
    digitalWrite(highTempLEDPin, HIGH);
    digitalWrite(highHumLEDPin, HIGH);
  } else if (hum > 60.00) {
    digitalWrite(highTempLEDPin, LOW);
    digitalWrite(highHumLEDPin, HIGH);
  } else if (temp > 25.00) {
    digitalWrite(highTempLEDPin, HIGH);
    digitalWrite(highHumLEDPin, LOW);
  } else {
    digitalWrite(highTempLEDPin, LOW);
    digitalWrite(highHumLEDPin, LOW);
  }
}
