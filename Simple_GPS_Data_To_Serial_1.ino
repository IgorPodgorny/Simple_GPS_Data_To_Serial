// Простой скетч: читает данные с GPS и выводит их в Serial (количество спутников, широта, долгота, скорость, высота)

#include <TinyGPS++.h> // библиотека для работы GPS
#include <SoftwareSerial.h> // библиотека для реализации последовательного протокола на цифровых выводах Arduino
#define GPS_BAUD 9600 // определяем скорость работы GPS

unsigned long start;
bool newdata = false;

// определяем пины для обмена данными. RX на GPS соединяется с TX Arduino и наоборот

SoftwareSerial serial_connection(6, 7); //RX=pin 6, TX=pin 7

TinyGPSPlus gps;

void setup() {
  Serial.begin (9600); // включаем Serial
  serial_connection.begin (GPS_BAUD); // включаем Software Serial на той скорости, которую определили выше для работы GPS
  Serial.println("Waiting data from GPS");
  Serial.println("");
}

void loop() {
  if (millis() - start > 1000) { //установка задержки в одну секунду между обновлением данных

    while (serial_connection.available() > 0) // пока что-то поступает в Serial (GPS работает)

      newdata = gps.encode(serial_connection.read()); // читаем оттуда данные

    if (newdata)
    {
      start = millis();

      if (gps.location.isValid()) { // если данные с GPS есть, ждём секунду и выводим их в Serial
        
        Serial.print("Количество спутников: ");
        Serial.println(gps.satellites.value());
        Serial.print("Широта:  ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Долгота: ");
        Serial.println(gps.location.lng(), 6);
        Serial.print("Скорость,км/ч: ");
        Serial.println(gps.speed.kmph());
        Serial.print("Высота,м: ");
        Serial.println(gps.altitude.meters());
        Serial.println("");
      }
    }
  }
}
