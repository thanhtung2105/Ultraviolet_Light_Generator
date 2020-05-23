#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

int button_setTime_plus = 4;
int button_setTime_minus = 5;
int button_start = 6;
int button_reset = 7;
int relay_UV = 8;
int buzzer_alert = 9;
int setTime_led = 10;
int waiting_led = 11;
int done_led = 12;

boolean click_setTime(int GPIO_to_read);
boolean isButton_Click(int GPIO_to_read);
void forceStop();

LiquidCrystal_I2C lcd(0x27, 16, 2);

String set_time = "Set Time: ";
String waiting = "Wait a while ^_^";
String done = "Done! ;)";

uint8_t clock[8] = {0x00, 0x0E, 0x15, 0x15, 0x17, 0x11, 0x0E, 0x00};
uint8_t hourglass[8] = {0x00, 0x1F, 0x11, 0x0E, 0x04, 0x0A, 0x11, 0x1F};
uint8_t arrow[8] = {0x00, 0x04, 0x02, 0x1F, 0x02, 0x04, 0x00, 0x00};

unsigned int holdButton = 250;      //The holding time to plus 5 min
unsigned int remaining_time = 0;    //Setting time to count down
unsigned int x_time;                //Time to plus or minus

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("UV generator .by Thanh Tung");
  pinMode(button_setTime_plus, INPUT);
  pinMode(button_setTime_minus, INPUT);
  pinMode(button_start, INPUT);
  pinMode(button_reset, INPUT);
  pinMode(relay_UV, OUTPUT);
  pinMode(buzzer_alert, OUTPUT);
  pinMode(setTime_led, OUTPUT);
  pinMode(waiting_led, OUTPUT);
  pinMode(done_led, OUTPUT);

  lcd.createChar(0, clock);
  lcd.createChar(1, hourglass);
  lcd.createChar(2, arrow);
  lcd.home();
}

void loop()
{
  digitalWrite(setTime_led, HIGH);
  lcd.setCursor(2, 0);
  lcd.printByte(0);
  lcd.setCursor(4, 0);
  lcd.print(set_time);
  lcd.setCursor(3, 1);
  lcd.printByte(2);
  lcd.setCursor(7, 1);
  lcd.print(":");
  if (remaining_time < 10)
  {
    lcd.setCursor(5, 1); 
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

  if (check_Button_setTime_plus)
  {
    remaining_time += x_time;
    if (remaining_time >= 99)
    {
       remaining_time = 99;
    }
  }

  if (check_Button_setTime_minus)
  {
    if (remaining_time == 0)
    {
      lcd.setCursor(5, 1); 
      lcd.print("00");
      lcd.setCursor(8, 1);
      lcd.print("00");
    }
    else if ((remaining_time < 5) && (x_time == 5))
    {
      remaining_time = 0;
      lcd.setCursor(5, 1); 
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
    lcd.clear();
    remaining_time = 0;
  }

  if (check_Button_start)
  {
    digitalWrite(setTime_led, LOW);
    digitalWrite(waiting_led, HIGH);
    digitalWrite(relay_UV, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(waiting);
    lcd.setCursor(4, 1);
    lcd.printByte(1);
    remaining_time *= 60;
    while (remaining_time > 0)
    {
      forceStop();
      lcd.setCursor(6, 1);
      lcd.print(remaining_time);
      lcd.print("     ");
      remaining_time--;
      delay(1000);
    }

    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print(done);
    lcd.setCursor(1, 1);
    lcd.print("K16 Thanh Tung");
    digitalWrite(relay_UV, LOW);
    digitalWrite(waiting_led, LOW);
    digitalWrite(done_led, HIGH);

    while (digitalRead(button_reset) == LOW)
    {
      digitalWrite(buzzer_alert, HIGH);
      delay(800);
      digitalWrite(buzzer_alert, LOW);
      delay(200);
      digitalWrite(buzzer_alert, HIGH);
      delay(400);
      digitalWrite(buzzer_alert, LOW);
      delay(600);
    }
    digitalWrite(done_led, LOW);
    remaining_time = 0;
  }
}

boolean click_setTime(int GPIO_to_read)
{
  int out = 0;
  unsigned long timer;
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

void forceStop()
{
  if (digitalRead(button_reset))
  {
    digitalWrite(relay_UV, LOW);
    digitalWrite(waiting_led, LOW);
    asm volatile ("jmp 0");  
  }
}
