#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int button_setTime_plus = 4;
int button_setTime_minus = 5;
int button_start = 6;
int button_reset = 7;
int relay_UV = 8;
int buzzer_alert = 9;

boolean click_setTime(int GPIO_to_read);
boolean isButton_Click(int GPIO_to_read);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String set_time = "Set Time: ";
String waiting = "Remaining time ...";
String done = "Done! ;)";

uint8_t clock[] = {0x00, 0x0E, 0x15, 0x15, 0x17, 0x11, 0x0E, 0x00};
uint8_t hourglass[] = {0x00, 0x1F, 0x11, 0x0E, 0x04, 0x0A, 0x11, 0x1F};

unsigned int holdButton = 2500; //The holding time to plus 5 min
unsigned int remaining_time = 0;
unsigned int x_time; //Time to plus or minus

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(button_setTime_plus, INPUT);
  pinMode(button_setTime_minus, INPUT);
  pinMode(button_start, INPUT);
  pinMode(button_reset, INPUT);
  pinMode(relay_UV, OUTPUT);
  pinMode(buzzer_alert, OUTPUT);

  lcd.createChar(0, clock);
  lcd.createChar(1, hourglass);
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print(0);
  lcd.setCursor(4, 0);
  lcd.print(set_time);
  if (remaining_time < 10)
  {
    lcd.setCursor(5, 1); // _ _ _ _ _ 00 : 00 _ _ _ _ _ _
    lcd.print("0");
    lcd.setCursor(6, 1);
    lcd.print(remaining_time);
  }
  else
  {
    lcd.setCursor(5, 1);
    lcd.print(remaining_time);
  }
  lcd.setCursor(8, 1);
  lcd.print("00");

  boolean check_Button_setTime_plus = click_setTime(button_setTime_plus);
  boolean check_Button_setTime_minus = click_setTime(button_setTime_minus);
  boolean check_Button_start = isButton_Click(button_start);
  boolean check_Button_reset = isButton_Click(button_reset);

  do
  {
    lcd.setCursor(7, 1);
    lcd.print(":");
    delay(500);
    lcd.setCursor(7, 1);
    lcd.print(" ");
    delay(500);
  } while (!check_Button_setTime_plus || !check_Button_setTime_minus || !check_Button_start || !check_Button_reset);

  if (check_Button_setTime_plus)
  {
    remaining_time += x_time;
  }

  if (check_Button_setTime_minus)
  {
    if (remaining_time == 0)
    {
      lcd.setCursor(5, 1); // _ _ _ _ _ 00 : 00 _ _ _ _ _ _
      lcd.print("00");
      lcd.setCursor(8, 1);
      lcd.print("00");
    }
    else
    {
      remaining_time -= x_time;
    }
  }

  if (check_Button_reset)
  {
    remaining_time = 0;
  }

  if (check_Button_start)
  {
    digitalWrite(relay_UV, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(waiting);
    lcd.setCursor(2, 1);
    lcd.print(1);
    remaining_time *= 60;
    lcd.setCursor(4, 1);
    while(remaining_time>0)
    {
      lcd.print(remaining_time);
      lcd.print("     ");
      remaining_time--;
      delay(1000);
    }

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print(done);
    lcd.setCursor(0, 1);
    lcd.print("K16 Tung & Phuc");

    while(digitalRead(button_reset) == LOW)
    {
      digitalWrite(buzzer_alert, HIGH);
      delay(1000);
      digitalWrite(buzzer_alert, LOW);
      delay(400);
    }

    remaining_time = 0;
  }
}

boolean click_setTime(int GPIO_to_read)
{
  int out = 0;
  unsigned int timer;
  timer = millis();
  while (digitalRead(GPIO_to_read) == HIGH)
  {
    delay(5);
    if (millis() - timer > holdButton)
    {
      x_time = 5;
      out = 1;
    }
    else
    {
      x_time = 1;
      out = 1;
    }
  }
  return out;
}

boolean isButton_Click(int GPIO_to_read)
{
  int out = 0;
  while (digitalRead(GPIO_to_read) == HIGH)
  {
    delay(10);
    out = 1;
  }
  return out;
}
