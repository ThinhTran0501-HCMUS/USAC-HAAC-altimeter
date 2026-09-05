#include <Wire.h>
#include <U8g2lib.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include "image.h"

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

Adafruit_BMP280 bmp;

float maxAltitude = -9999.0;
bool bmpFound = false;

int setSeaLevel = 9; // đặt sea level làm 0m
int setCurrent = 3; // đặt hiện tại làm 0m 

// Áp suất tại mặt nướcc biển
float referencePressure = 1013.25;

// debounce state
bool lastStateZero = HIGH;
bool lastStateSea  = HIGH;


void setup() {
  Serial.begin(115200);
  Wire.begin();
  u8g2.begin();


  pinMode(setCurrent, INPUT_PULLUP);
  pinMode(setSeaLevel, INPUT_PULLUP);

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    u8g2.firstPage();
    do {
      u8g2.drawXBMP(0, 0, 128, 64, epd_bitmap_logo_12864);
    } while (u8g2.nextPage());
  }

  if (bmp.begin(0x76)) {
    bmpFound = true;

bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                Adafruit_BMP280::SAMPLING_X2,     // Nhiệt độ X2
                Adafruit_BMP280::SAMPLING_X16,    // Áp suất X16 (Lấy độ chính xác cao nhất)
                Adafruit_BMP280::FILTER_X4,       // Lọc IIR X4 (Vừa lọc nhiễu vừa không bị trễ)
                Adafruit_BMP280::STANDBY_MS_63);  // Nghỉ 62.5ms giữa các lần đo

    maxAltitude = bmp.readAltitude(referencePressure);
  } else {
    Serial.println(F("Khong tim thay BMP280!"));
  }
}

void loop() {
  bool currentStateZero = digitalRead(setCurrent);
  bool currentStateSea  = digitalRead(setSeaLevel);

  if (lastStateZero == HIGH && currentStateZero == LOW) {
    if (bmpFound) {
      referencePressure = bmp.readPressure() / 100.0F; // Đọc áp suất hPa hiện tại làm mốc
      maxAltitude = 0.0;                              // Reset Max Altitude về 0m
    }
    delay(50); // debounce
  }
  lastStateZero = currentStateZero;

  // Trở về mốc mực nước biển 
  if (lastStateSea == HIGH && currentStateSea == LOW) {
    if (bmpFound) {
      referencePressure = 1013.25;
      maxAltitude = bmp.readAltitude(referencePressure); // Cập nhật lại Max Altitude theo mốc mới
    }
    delay(50); 
  }
  lastStateSea = currentStateSea;

  float temp = 0;
  float pressure = 0;
  float altitude = 0;

  if (bmpFound) {
    temp = bmp.readTemperature();
    pressure = bmp.readPressure() / 100.0F; 
  
altitude = bmp.readAltitude(referencePressure);

    if (altitude > maxAltitude) {
      maxAltitude = altitude;
    }
  }
  
  char tempStr[10];
  char pressStr[10];
  char altStr[10];
  char maxAltStr[10];

  dtostrf(temp, 4, 1, tempStr);
  dtostrf(pressure, 6, 1, pressStr);
  dtostrf(altitude, 6, 1, altStr);
  dtostrf(maxAltitude, 6, 1, maxAltStr);

  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tf);

    if (!bmpFound) {
      u8g2.drawStr(0, 20, "Loi: Khong thay BMP!");
      u8g2.drawStr(0, 40, "Kiem tra lai I2C");
    } else {
      char buffer[30];

      sprintf(buffer, "Temp:  %s \260C", tempStr);
      u8g2.drawStr(5, 10, buffer);

      sprintf(buffer, "Press: %s hPa", pressStr);
      u8g2.drawStr(5, 20, buffer);

      sprintf(buffer, "Alt:   %s m", altStr);
      u8g2.drawStr(5, 30, buffer);

      sprintf(buffer, "Max:   %s m", maxAltStr);
      u8g2.drawStr(5, 40, buffer);

      u8g2.drawLine(0, 43, 127, 43); //giải phân cách

      u8g2.drawStr(0, 52, "<- Current as 0m");

      u8g2.drawStr(20, 62, "Sea level as 0m ->");

    }
  } while (u8g2.nextPage());

  delay(10); 
}