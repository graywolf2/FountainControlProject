// int sensorPin = A0; // input pin
// int sensorValue = 0; // variable to store the value coming from the sensor

// void(* resetFunc) (void) = 0; // declare reset function at address 0
/*
// this function will return the number of bytes currently free in RAM
// written by David A. Mellis
// based on code by Rob Faludi http://www.faludi.com
int availableMemory() {
  int size = 2048; // 1024; // Use 2048 with ATmega328
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL);
  free(buf);
  return size;
}
*/
void blinkLed(int n) { // Функція blinkLed блимає світлодіодом n раз.1
    for (int i = 0; i < n; i++) {
      if (i) delay(300); // На першому такті пауза не потрібна.
      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);
    }
}

void setup() {
  Serial.begin(9600); // Відкриваємо порт. 
  blinkLed(1); // 1 раз блимаємо світлодіодом - повідомляємо що програма запустилась
}

void loop() {         
  int i = 0;
  char buffer[100];
  char c;

  // Якщо є дані, читаємо.
  if (Serial.available()) {
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
                
    // Показуємо отриману команду.
    Serial.print("Received command: ");
    Serial.print(buffer);
    Serial.println();
    
    if (!strcmp(buffer, "turn on fountain 1")) { // Якщо отримали команду "turn on fountain 1".
      // Даємо імпульс 300 мс на вихід 1.
      digitalWrite(1, HIGH);
      delay(300);
      digitalWrite(1, LOW);
      
    // Якщо отримали команду "turn off fountain 1".
    } else if (!strcmp(buffer, "turn off fountain 1")) {
      // Даємо імпульс 300 мс на вихід 2.
      digitalWrite(2, HIGH);
      delay(300);
      digitalWrite(2, LOW);
    }

    /*    
    c = buffer[0];
    if (c == 'b') { // якщо отримано команду b
      // якщо після b вказано пробіл то блимаємо світлодіодом визначеною кількостю раз.
      if (buffer[1] == ' ') blinkLed(atoi(&buffer[2]));
      else blinkLed(1); // інакше 1 раз блимаємо світлодіодом
 
    } else if (c == 's') { // якщо отримано команду s

      // показуємо час роботи програми
      Serial.print("Run time: ");
      Serial.print(millis() / 1000);
      Serial.print(" seconds");
      Serial.println();

      // показуємо значення аналового входу 0
      sensorValue = analogRead(A0);
      Serial.print("Analog input 0 value: ");
      Serial.print(sensorValue);
      Serial.println();

      // показуємо скільки вільно памяті
      Serial.print("Free memory: ");
      Serial.print(availableMemory());
      Serial.print(" bytes");
      Serial.println();

    } else if (c == '1') digitalWrite(13, HIGH); // якщо отримано команду 1, вмикаємо світлодіод
    else if (c == '0') digitalWrite(13, LOW); // якщо отримано команду 0, вимикаємо світлодіод
    else if (c >= '2' && c <= '9') // якщо отримано команду 2 - 9
      blinkLed(c - '0'); // блимаємо світлодіодом 2 - 9 раз відповідно команди 
    else if (c == 'r') resetFunc(); // якщо отримано команду r, перезавантажуємо ардуїно

    else if (c == 'h') { // якщо отримано команду h
      Serial.println("Help");
      Serial.println("b : blink the led 1 time");
      Serial.println("b number : blink the led number times");
      Serial.println("2 - 9 : blink the led number times");
      Serial.println("1 : turn the led on");
      Serial.println("0 : turn the led off");
      Serial.println("s : show state");
      Serial.println("r : reset arduino");
      Serial.println("h : help");

    } else Serial.println("Unknown command"); // Якщо команда невідома.
    */
  } // if (i)
}
// Sergiy Vovk. 2017.

