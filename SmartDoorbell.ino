#include <WiFi.h>
#include <HTTPClient.h>

#define DOORBELL_PIN 4
#define DEBOUNCE_DELAY 50          // Debounce delay in ms
#define COOLDOWN_TIME 30000        // Cooldown time in ms

const char* ssid = "<Your Network SSID>";
const char* password = "<Your Network Password>";

volatile bool doorbellRang = false;

void setup() {
  pinMode(DOORBELL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DOORBELL_PIN), doorbellRing, FALLING);

  connectToWiFi();
}

void loop() {
  if (doorbellRang) {
    doorbellRang = false; // Reset the flag
    sendNotification();
    WiFi.disconnect();
    delay(COOLDOWN_TIME); // Cooldown period
  }

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, LOW); //1 = High, 0 = Low
  esp_deep_sleep_start();
}

void doorbellRing() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  // If interrupts come faster than DEBOUNCE_DELAY, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > DEBOUNCE_DELAY) {
    doorbellRang = true;
  }
  last_interrupt_time = interrupt_time;
}

void connectToWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void sendNotification() {
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;

    http.begin("http://192.168.50.150:9595/door");
    int httpResponseCode = http.POST("");  

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.println("Error on sending POST: " + http.errorToString(httpResponseCode));
    }
    http.end();
  }
  else {
    Serial.println("Error in WiFi connection");
  }
}
