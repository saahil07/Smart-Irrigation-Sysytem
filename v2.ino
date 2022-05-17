#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long previousMillis;

#define MoistureSensor A0
#define rainSensor A1

int moisture = 0;
int rain = 0;
float temp;

#define motor 10


int flag = 0;

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float h;

#include <OneWire.h>
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin A0 on the Arduino
#define ONE_WIRE_BUS 3
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


int r1 = 4;
int g1 = 5;

int r2 = 6;
int g2 = 7;

int find_rain()
{
  int i;
  long avg_val = 0;
  for (i = 0; i < 10; i++)
  {
    avg_val += analogRead(MoistureSensor);
  }
  avg_val /= 10;
  moisture = avg_val;
  moisture = map(moisture, 2, 1022, 100, 1);

  int j;
  long avg_val1 = 0;
  for (j = 0; j < 10; j++)
  {
    avg_val1 += analogRead(rainSensor);
  }
  avg_val1 /= 10;
  rain = avg_val1;
  rain = map(rain, 2, 1022, 100, 1);

  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);

  h = dht.readHumidity();
  if(h > 20)
  {
    digitalWrite(r1, HIGH);digitalWrite(r2, LOW);
    digitalWrite(g1, LOW);digitalWrite(g2, HIGH);
  }
  else
  {
    digitalWrite(r1, LOW);digitalWrite(r2, HIGH);
    digitalWrite(g1, HIGH);digitalWrite(g2, LOW);
  }
  lcd.setCursor(0, 0); lcd.print("M:      T:      ");
  lcd.setCursor(2, 0); lcd.print(moisture); lcd.print("%");
  lcd.setCursor(10, 0); lcd.print(temp, 1); lcd.print(" ");
  lcd.setCursor(0, 1); lcd.print("R:      H:      ");
  lcd.setCursor(2, 1); lcd.print(rain); lcd.print("%");
  lcd.setCursor(10, 1); lcd.print(h, 1); lcd.print(" ");

  return moisture;
  return rain;
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  sensors.begin();
  dht.begin();
  pinMode(r1, OUTPUT);  pinMode(r2, OUTPUT);
  pinMode(g1, OUTPUT);  pinMode(g2, OUTPUT);
  digitalWrite(r1, LOW);digitalWrite(r2, LOW);
  digitalWrite(g1, LOW);digitalWrite(g2, LOW);
  
  pinMode(MoistureSensor , INPUT);
  pinMode(motor, OUTPUT); digitalWrite(motor, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   IoT Smart    ");
  lcd.setCursor(0, 1);
  lcd.print("Irrigation Syste");//IoT Smart Irrigation System
  delay(2000);
  lcd.clear();
}

void loop()
{
  find_rain();
  if (millis() - previousMillis > 1000)
  {
    Serial.print("<A"); Serial.print(moisture); Serial.print(">");
    Serial.print("<B"); Serial.print(rain); Serial.print(">");
    Serial.print("<C"); Serial.print(temp, 1); Serial.print(">");
    Serial.print("<D"); Serial.print(h, 1); Serial.print(">");
    previousMillis = millis();
  }

  // temp >40
  if (temp > 40)
  {
    if (rain > 50)
    {
      // Nothig
      digitalWrite(motor, LOW);
      lcd.clear();
      lcd.print("   Heavy Rain   ");
      delay(1000);
    }
    else
    {
      if (moisture > 30 && moisture < 70)
      {
        digitalWrite(motor, HIGH);
        if (flag == 0)
        {
          Serial.print("<X>");
          flag = 1;
        }
      }
      else
      {
        digitalWrite(motor, LOW);
        if (flag == 1)
        {
          Serial.print("<Y>");
          flag = 0;
        }
      }
    }
  }

  // temp < 40
  if (temp < 40)
  {
    if (rain > 50)
    {
      // Nothig
      digitalWrite(motor, LOW);
      lcd.clear();
      lcd.print("   Heavy Rain   ");
      delay(1000);
    }
    else
    {
      if (moisture > 20 && moisture < 60)
      {
        digitalWrite(motor, HIGH);
        if (flag == 0)
        {
          Serial.print("<X>");
          flag = 1;
        }
      }
      else
      {
        digitalWrite(motor, LOW);
        if (flag == 1)
        {
          Serial.print("<Y>");
          flag = 0;
        }
      }
    }
  }
}
