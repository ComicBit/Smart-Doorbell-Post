#include <WiFi.h>
#include <HTTPClient.h>

#define DOORBELL_PIN 4
#define DEBOUNCE_DELAY 50          // Debounce delay in ms
#define COOLDOWN_TIME 30000        // Cooldown time in ms

const char* ssid = "<Your Network SSID>";
const char* password = "<Your Network Password>";

volatile bool doorbellRang = false;
bool sleepModeEnabled = false; // Set to false to disable sleep mode
int postCount = 0; // Counter for POST calls

void setup() {
  Serial.begin(115200);
  pinMode(DOORBELL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DOORBELL_PIN), doorbellRing, FALLING);

  connectToWiFi();
}

void loop() {
  if (doorbellRang) {
    doorbellRang = false; // Reset the flag
    sendNotification();
    postCount++; // Increase POST counter
    WiFi.disconnect();
    delay(COOLDOWN_TIME); // Cooldown period
  }

  // Check Serial input
  while (Serial.available()) {
    String inputString = Serial.readStringUntil('\n');

    if (inputString == "netstats") {
      printNetworkStatus();
    } else if (inputString == "pinstate") {
      printPinState();
    } else if (inputString == "postcount") {
      Serial.println("HTTP POST has been called " + String(postCount) + " times.");
    } else if (inputString == "sleepmode y") {
      sleepModeEnabled = true;
      Serial.println("Sleep mode enabled");
    } else if (inputString == "sleepmode n") {
      sleepModeEnabled = false;
      Serial.println("Sleep mode disabled");
    } else if (inputString == "ring") {
      doorbellRang = true;
      Serial.println("Doorbell ring simulated");
    }
  }

  if (sleepModeEnabled) {
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, LOW); //1 = High, 0 = Low
    esp_deep_sleep_start();
  }
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
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);

    Serial.println("Connecting to WiFi...");
    unsigned long startTime = millis();

    // Try to connect for up to 30 seconds
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 30000) {
      delay(500);
      Serial.print(".");
    }

    // If we couldn't connect within 30 seconds, print an error message
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Failed to connect to WiFi");
    } else {
      Serial.println("Connected to WiFi");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP().toString());
    }
  }
}

void sendNotification() {
  connectToWiFi(); // Check the WiFi connection

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

void printNetworkStatus() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi network");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP().toString());
  } else {
    Serial.println("Not connected to WiFi network");
  }
}

void printPinState() {
  if (digitalRead(DOORBELL_PIN) == HIGH) {
    Serial.println("Doorbell pin is HIGH");
  } else {
    Serial.println("Doorbell pin is LOW");
  }
}
