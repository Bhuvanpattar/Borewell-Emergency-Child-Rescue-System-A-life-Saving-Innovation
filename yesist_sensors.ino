#include <DHT.h>

#define DHTPIN 2        // Pin connected to DHT11 sensor
#define DHTTYPE DHT11   // Define sensor type as DHT11
#define SOUND_PIN A0    // Analog pin connected to the sound sensor

#define TRIG_PIN 3      // Pin connected to the Trigger pin of the ultrasonic sensor
#define ECHO_PIN 4      // Pin connected to the Echo pin of the ultrasonic sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  dht.begin();         // Initialize DHT sensor

  pinMode(TRIG_PIN, OUTPUT); // Set Trigger pin as output
  pinMode(ECHO_PIN, INPUT);  // Set Echo pin as input

  // Print column headers for data
  Serial.println("Time (ms), Temperature (°C), Humidity (%), Sound Level, Distance (cm)");
}

void loop() {
  // Read temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Read the analog value from the sound sensor
  int soundLevel = analogRead(SOUND_PIN);

  // Measure distance using ultrasonic sensor
  long duration;
  float distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0343) / 2; // Convert duration to distance in cm

  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Error reading from DHT sensor!");
    
  }

  // Print data to serial monitor
  unsigned long currentTime = millis(); // Get elapsed time in milliseconds
  //Serial.print(currentTime);
  //Serial.print(", ");
  Serial.print(temperature);
  Serial.print(", ");
  Serial.print(humidity);
  Serial.print(", ");
  Serial.print(soundLevel);
  Serial.print(", ");
  Serial.print(distance);
  Serial.println();
  delay(2000); // Log data every 2 seconds
}
