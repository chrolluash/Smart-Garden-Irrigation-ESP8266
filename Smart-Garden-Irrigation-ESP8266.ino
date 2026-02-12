#define BLYNK_TEMPLATE_ID "TMPL65-LkwAY_"
#define BLYNK_TEMPLATE_NAME "Garden IOT"
#define BLYNK_AUTH_TOKEN "YnL5dFThizGLu5ZZiIsAymgPTDxg9Pdf"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
//Your internet SSID
char ssid[] = "";
//Your internet password
char pass[] = "";

BlynkTimer timer;

// === PINS ===
#define soilPin A0
#define waterLevelPin A0  // sharing with soilPin (only one analog pin)
#define DHTPIN D5
#define PIRpin D6

#define buttonSoil D3   // Soil moisture button
#define buttonWater D4  // Water level button

// Motor B control pins (L298N or similar)
#define ENB D7
#define IN3 D1
#define IN4 D2

// === DHT CONFIG ===
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// === GLOBALS ===
bool MotorState = 0;

void setup() {
  Serial.begin(9600);

  // Motor driver pins
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENB, LOW); // motor off initially

  // PIR sensor
  pinMode(PIRpin, INPUT);

  // Button inputs
  pinMode(buttonSoil, INPUT_PULLUP);   // active LOW
  pinMode(buttonWater, INPUT_PULLUP);  // active LOW

  // Start sensors
  dht.begin();

  // Connect to Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  // Sensor polling
  timer.setInterval(1000L, handleAnalogSensor); // Read soil or water based on button press
  timer.setInterval(2000L, readDHT);
  timer.setInterval(1000L, readMotion);
}

// === Motor ON/OFF control ===
BLYNK_WRITE(V1) {
  MotorState = param.asInt();
  if (MotorState == 1) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 255); // Full speed
    Serial.println("Motor: ON (Blynk)");
  } else {
    analogWrite(ENB, 0); // Stop motor
    Serial.println("Motor: OFF (Blynk)");
  }
}

// === Button-based Analog Sensor Selection (Soil or Water Level) ===
void handleAnalogSensor() {
  if (digitalRead(buttonSoil) == LOW) {
    int value = analogRead(soilPin);
    int moisture = map(value, 0, 1024, 100, 0); // Inverted
    Serial.print("Soil Moisture: ");
    Serial.print(moisture);
    Serial.println(" %");
    Blynk.virtualWrite(V0, moisture);
  }

  if (digitalRead(buttonWater) == LOW) {
    int value = analogRead(waterLevelPin);
    int level = map(value, 0, 1024, 0, 100);
    Serial.print("Water Level: ");
    Serial.print(level);
    Serial.println(" %");
    Blynk.virtualWrite(V2, level);
  }
}

// === DHT Sensor ===
void readDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT Read failed!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  Blynk.virtualWrite(V3, t);
  Blynk.virtualWrite(V4, h);
}

// === PIR Sensor === 
void readMotion() {
  int motion = digitalRead(PIRpin);
  Serial.print("Motion Detected: ");
  Serial.println(motion == HIGH ? "YES" : "NO");

  Blynk.virtualWrite(V5, motion);
}

void loop() {
  Blynk.run();
  timer.run();
}
