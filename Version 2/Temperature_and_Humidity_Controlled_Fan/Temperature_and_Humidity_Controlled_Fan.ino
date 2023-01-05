// CREATED BY TOUTATISS, 30/12/2022
// CODE IS FREE TO USE
// FURTHER DISCUSSION: jankoclock.wordpress.com

/* Libraries */
#include <DHT.h>

/* Pin Definitions */
#define dhtDataPin 8
#define fanEnablePin 3 
#define powerOnLEDPin 9
#define highTempLEDPin 10
#define highHumLEDPin 11

/* DHT22 Sensor Definition */
#define DHT_Type DHT22
DHT dht(dhtDataPin, DHT_Type);

/* Temperature and Humidity Thresholds */
const float humLimit = 70.00;
const float tempLimit = 25.00;

/* Variables */
float hum;
float temp;
bool state;

void setup() {
//  Serial.begin(9600); // Serial for testing and debugging

  /* Pin Setups */
  pinMode(fanEnablePin, OUTPUT);
  pinMode(powerOnLEDPin, OUTPUT);
  pinMode(highTempLEDPin, OUTPUT);
  pinMode(highHumLEDPin, OUTPUT);

  /* Load Default States */
  analogWrite(powerOnLEDPin, 70);
  digitalWrite(fanEnablePin, LOW);

  dht.begin();
}

void loop() {
  getTempHum();       // Measure the temperature and humidity
  monitorFanState();  // Check temp and humidity against thresholds, power fans on/off
  getLightSettings();
  delay(5000);
}

void monitorFanState() {
  analogWrite(fanEnablePin, (((temp > tempLimit)||(hum > humLimit)) ? 0 : 255)); // if either threshold is exceeded, the fan will be switched on
}

void  getTempHum() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  /* Serial Block for Testing and Debugging */
//  Serial.print(hum);
//  Serial.print(" % RH\n");
//  Serial.print(temp);
//  Serial.print(" degrees C\n\n");
}

void getLightSettings() {
  analogWrite(highTempLEDPin,0);
  analogWrite(highHumLEDPin,0);
  
  if (temp > tempLimit) {
    analogWrite(highTempLEDPin,10);
  }
  
  if (hum > humLimit) {
    analogWrite(highHumLEDPin,50);
  }

}
