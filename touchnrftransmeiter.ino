  #include <SPI.h>
  #include <nRF24L01.h>
  #include <RF24.h>

  #define TOUCH_PIN 4 // Touch
  #define LED_PIN 13 // Pin LED indicator

  RF24 radio(9, 10); // CE, CSN
  const byte address[6] = "00001";

  struct touch {
    byte wasPressed = LOW;
    byte isPressed = LOW;
  };
  touch touch;

  void setup()
  {
    pinMode(TOUCH_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT); 
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_LOW);
  }

  void loop()
  {
    touch.isPressed = isTouchPressed(TOUCH_PIN);
    if (touch.wasPressed != touch.isPressed) {
      const char *message;
      if (touch.isPressed == HIGH) {
        message = "Touch pressedddd";
        Serial.println(message);
      }
      else {
        message = "Touch dilepas ";
        Serial.println(message);
      }
      Serial.print("Sending message: ");
      Serial.println(message);
      radio.write(message, strlen(message));

      digitalWrite(LED_PIN, HIGH);
      delay(200);
      digitalWrite(LED_PIN, LOW);
    }
    touch.wasPressed = touch.isPressed;
    delay(100);
  }

  bool isTouchPressed(int pin)
  {
    return digitalRead(pin) == HIGH;
  }
