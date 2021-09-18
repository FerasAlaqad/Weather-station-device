
#define NUMFLAKES     10
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     4
#define SCREEN_ADDRESS 0x3C
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <SHT3x.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiManager.h>
#include "ESP32TimerInterrupt.h"

char auth[33] = "QXbg4b-l3N83ed5cAi4FS6gxeY_8783C"; //Blynk code (you have to change)

int a = 0;

// Sensor
Adafruit_BMP280 bme;
SHT3x Sensor;

//LCD

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};


//wifimanager
WiFiManager wm;
bool res;
bool resetle = false;
bool resetle2 = false;
bool resetecek = false;
int buttonSayac = 0;
boolean button = false;
int sayac = 0;






float Temp = 0;
float Hum = 0;
float basinc = 0;




void setup()
{

  //LCD
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }


  Serial.begin(9600);

  pinMode(34, INPUT_PULLUP);//you have to connect button to this pin or change pin number

  pinMode(17, OUTPUT);  //you have to connect buzzer to this pin or change pin number


  //Sensor
  Sensor.Begin();
  Serial.println(F("BME280 test"));
  unsigned status;
  status = bme.begin();

  display.clearDisplay();
  delay(10);
  robojaxText("Nanobiotek agi kulla-narak beni internete  Bagla", 0, 0, 1, true);
  //Wifi Maneger

  WiFi.mode(WIFI_STA);
  res = wm.autoConnect("Nanobiotek"); // router name

  if (!res) {
    Serial.println("Bağlantı Sağlanamadı");
    // ESP.restart();

  }
  else {
    Serial.println("Ağ Bağlantısı Kuruldu");
  }
  attachInterrupt(digitalPinToInterrupt(34), Alarmstop, CHANGE);


  //Blynk

  Blynk.config(auth, "blynk-cloud.com", 8080);

  digitalWrite(17, HIGH);
  delay(500);
  digitalWrite(17, LOW);
  delay(250);
  digitalWrite(17, HIGH);
  delay(500);
  digitalWrite(17, LOW);








}

void loop()
{

  Sensor.UpdateData();
  Blynk.run();
  Temp = (Sensor.GetTemperature() + bme.readTemperature()) / 2;
  Hum = Sensor.GetRelHumidity() ;
  basinc = bme.readPressure() / 100.0F;



  if (Hum > 70) {
    digitalWrite(17, HIGH);

  } else {
    digitalWrite(17, LOW);


  }


  Blynk.virtualWrite(V0, Temp);
  Blynk.virtualWrite(V1, Hum);
  Blynk.virtualWrite(V2, basinc);

  Serial.print(Temp);
  Serial.print(" , ");
  Serial.print(Hum);
  Serial.print(" , ");
  Serial.println(basinc);



  display.clearDisplay();
  delay(10);
  robojaxText("Nanobiotek", 0, 0, 2, true);
  display.drawLine(1, 17, 150, 17, WHITE);

  WriteTemp("Temp:", 0, 22, 1, true);
  WriteHum("Hum:", 0, 37, 1, true);
  WritePress("Pr:", 0, 53, 1, true);

  //Resetleme

  if (resetle) {
    resetle = false;
    resetle2 = true;
    display.clearDisplay();
    delay(10);
    robojaxText("Reset", 10, 25, 3, true);
    digitalWrite(17, HIGH);
    delay(500);
    digitalWrite(17, LOW);
    delay(250);
    digitalWrite(17, HIGH);
    delay(500);
    digitalWrite(17, LOW);

  }
  else if (resetle2) {
    resetle2 = false;
    display.clearDisplay();
    delay(10);
    robojaxText("Nanobiotek agi kulla-narak beni internete  Bagla", 0, 0, 1, true);
    WiFi.disconnect(true);//ESPnin bağlantısını ağdan koparıyoruz
    delay(2000);
    wm.resetSettings();//hafızadaki ağ ayarlarını temizliyoruz
    delay(3000);
    ESP.restart();//esp'ye reset atıp yeniden başlatıyoruz
    delay(5000);


  }





  delay(10000);
}



ICACHE_RAM_ATTR void Alarmstop() {
  if (!button) {
    if (digitalRead(34) == HIGH) {
      buttonSayac = millis();
      button = true;
    }
  }
  else {
    if (digitalRead(34) == LOW) {
      button = false; //butonu tekrar false a çek
      if ((millis() - buttonSayac) >= 50) {
        if ((millis() - buttonSayac) >= 3000) {
          Serial.println(">3 sn");
          resetle = true;
          resetecek = true;
        } else {
          //alarmdurdur();
          sayac = 0;
          Serial.println("<3 sn");
        }
      }
    }
  }

}


void testfillrect(void) {
  display.clearDisplay();

  for (int16_t i = 0; i < display.height() / 2; i += 3) {
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width() - i * 2, display.height() - i * 2, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}
void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Cerrahpasa"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}

void WriteTemp(String text, int x, int y, int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print(text);
  display.println(Temp);

  if (d) {
    display.display();
  }
}

void WritePress(String text, int x, int y, int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print(text);
  display.println(basinc);

  if (d) {
    display.display();
  }
}
void WriteHum(String text, int x, int y, int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.print(text);
  display.println(Hum);

  if (d) {
    display.display();
  }
}
void robojaxText(String text, int x, int y, int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(text);


  if (d) {
    display.display();
  }
}
