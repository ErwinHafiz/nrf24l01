#include <SPI.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10
// #define LED_PIN 8 


RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char receivedMessage[32] = "";
    radio.read(&receivedMessage, sizeof(receivedMessage));
    Serial.print("Received message: ");
    Serial.println(receivedMessage);

    if (strcmp(receivedMessage, "Touch pressed") == 0) {
      Serial.println("Action C");
      digitalWrite(LED_BUILTIN, HIGH);

    } else if (strcmp(receivedMessage, "Touch dilepas ") == 0) {
      Serial.println("Action D");
      digitalWrite(LED_BUILTIN, LOW);

    }
  }
}


