#include <DHT.h>

#define DHTPIN 2  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11 sensor type

#define RELAY_PIN 3 // Digital pin connected to the relay module

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  delay(2000);  // Delay between sensor readings

  float temperature = dht.readTemperature(); // Read temperature from DHT sensor
  float humidity = dht.readHumidity(); // Read humidity from DHT sensor
  
  if (isnan(temperature) || isnan(humidity)) { // Check if any reading failed
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Check if temperature is above a certain threshold
  if (temperature > 33) {
    digitalWrite(RELAY_PIN, LOW); // Turn on the water pump
    Serial.println("Water pump turned ON.");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Turn off the water pump
    Serial.println("Water pump turned OFF.");
  }
}
