/*                         EKİM 2021 TALPAY
                         TEMASSIZ ATEŞ ÖLÇER
**************************************************************************************
  LINK PINS:
  BUTTON -- D2
  LASER -- D5
  GY-906 SDA -- A4
  GY-906 SCL -- A5
  OLED SCREEN SDA -- A4
  OLED SCREEN SCL -- A5

**************************************************************************************
  REQIRED LIBRARIES:
  https://www.arduino.cc/reference/en/libraries/adafruit-mlx90614-library/
  https://www.arduino.cc/reference/en/libraries/adafruit-ssd1306/
*/

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_SSD1306.h>

const int Laser_Pin = 5;
int buttonState = 0;
const int buttonPin = 2;
unsigned long eskiZaman = 0;
unsigned long yeniZaman;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");

  pinMode(Laser_Pin, OUTPUT);
  pinMode(buttonPin, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 35);
  display.println("Initializing Temp");
  display.display();
  delay(250);
  display.clearDisplay();

  mlx.begin();

}

void loop() {
  yeniZaman = millis();
  if (yeniZaman - eskiZaman > 500) {
    buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempC());
    Serial.print("*C\tObject = ");
    Serial.print(mlx.readObjectTempC());
    Serial.println("*C");
    Serial.print("Ambient = ");
    Serial.print(mlx.readAmbientTempF());
    Serial.print("*F\tObject = ");
    Serial.print(mlx.readObjectTempF());
    Serial.println("*F");

    if (buttonState == HIGH) {
      digitalWrite(Laser_Pin, HIGH);
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(25, 10);
      display.print(mlx.readObjectTempC());
      display.setCursor(95, 10);
      display.print("C");
      display.setTextSize(2);
      display.setCursor(25, 36);
      display.print(mlx.readObjectTempF());
      display.setCursor(95, 36);
      display.print("F");
      display.display();
    }

    if (buttonState == LOW) {
      digitalWrite(Laser_Pin, LOW);
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(35, 10);
      display.print("-----");
      display.setCursor(105, 10);
      display.print("");
      display.setTextSize(2);
      display.setCursor(35, 36);
      display.print("-----");
      display.setCursor(105, 36);
      display.print("");
      display.display();
    }

    eskiZaman = yeniZaman;
    Serial.println();
  }
}
