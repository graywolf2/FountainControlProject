// Sergiy Vovk. 2017.
#include <EEPROM.h>
const int ledPin = 13; // LED connected to digital pin 13.

void blinkLed(int n) { // Функція blinkLed блимає світлодіодом n раз.
    for (int i = 0; i < n; i++) {
      if (i) delay(300); // На першому такті пауза не потрібна.
      digitalWrite(ledPin, HIGH);
      delay(300);
      digitalWrite(ledPin, LOW);
    }
}

void notifyAboutCommand(const char* command) { // Повідомляє користувачу про отриману команду.
  Serial.print("Received command: ");
  Serial.print(command);
  Serial.println();
}

inline void proccessCommand(const char* command) { // Обробляє команду.
  if (!strcmp(command, "turn on fountain 1")) { // Якщо отримали команду "turn on fountain 1".
    notifyAboutCommand(command);
    digitalWrite(1, HIGH); // Вмикаємо фонтан 1.
    digitalWrite(ledPin, HIGH);; // Вимикаємо світлодіод.
    EEPROM.write(0, 1); // Запамятовуємо стан фонтану.

  // Якщо отримали команду "turn off fountain 1".
  } else if (!strcmp(command, "turn off fountain 1")) {
    notifyAboutCommand(command);
    digitalWrite(1, LOW); // Вимикаємо фонтан 1.
    digitalWrite(ledPin, LOW); // Вимикаємо світлодіод.
    EEPROM.write(0, 0); // Запамятовуємо стан фонтану.

  } else if (!strcmp(command, "get state")) { // Якщо отримали команду "get state".
    if (EEPROM.read(0)) Serial.print("fountain 1: on");
    else Serial.print("fountain 1: off");
    Serial.println();

  } else { // Якщо команда невідома.
    Serial.print("Unknown command: ");
    Serial.print(command);
    Serial.println();
  }
} // proccessCommand

void setup() {
  Serial.begin(9600); // Відкриваємо порт.

  // Вибираємо режим роботи контактів як "вивід".
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(ledPin, OUTPUT);

  byte b = EEPROM.read(0);
  if (b) digitalWrite(1, HIGH);
  blinkLed(2); // Блимаємо світлодіодом - повідомляємо що програма запустилась.
  if (b) digitalWrite(ledPin, HIGH);
}

void loop() {
  int i = 0;
  char buffer[100];
  if (Serial.available()) { // Якщо є дані, читаємо.
    delay(100);

    // Записуємо почитане в буфер.
    while (Serial.available() && i < 99) buffer[i++] = Serial.read();

    buffer[i] = '\0'; // Закриваємо масив.
  }

  if (i) { // Якщо буфер наповнено.

    // Видаляємо можливий символ \n в кінці.
    if (buffer[i - 1] == '\n') {
      if (i == 1) return; // Пусту стрічку пропускаємо.
      buffer[i - 1] = '\0';
    }

    proccessCommand(buffer); // Обробляємо команду.
  } // if (i)
}
