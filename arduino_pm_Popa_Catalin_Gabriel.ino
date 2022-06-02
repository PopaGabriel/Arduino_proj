#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

// Inti the lcd screen
LiquidCrystal_I2C lcd(0x27, 17, 2);

// Delay for the debounce and debounce timer
int last_debounce = 0;
int debounce_delay = 300;

// The Pin of the Button
const int buttonPin = 2;

// The Pin of the Button
const int lightPin = 7;
// The Pins for the servos
const int servoPin1 = 8;
const int servoPin2 = 9;

// Initial state for the button
int currentState = 0;
int lastSteadyState = 0;      // the previous steady state from the input pin
int lastFlickerableState = 0; // the previous flickerable state from the input pin

// variable for water
bool water_present = 1;

// Init the servos
Servo Servo_water;
Servo Servo_curtain;

void setup()
{
  Wire.begin();
  pinMode(lightPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  Servo_water.attach(servoPin1);
  Servo_water.write(90);

  Servo_curtain.attach(servoPin2);
  Servo_curtain.write(0);

  lcd.init();
  lcd.backlight();
}

void writeI2CRegister8bit(int addr, int value)
{
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

unsigned int readI2CRegister16bit(int addr, int reg)
{
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  delay(1100);
  Wire.requestFrom(addr, 2);
  unsigned int t = Wire.read() << 8;
  t = t | Wire.read();
  return t;
}

// checks temperature and moves the servo
void check_humidity(int humidity)
{
  if (humidity == HIGH)
  {
    Servo_water.write(0);
    water_present = 0;
  }
  else
  {
    Servo_water.write(90);
  }
}

// Checks the light and moves the servos
void check_light(int light)
{
  if (light == LOW)
  {
    Servo_curtain.write(90);
  }
  else
  {
    Servo_curtain.write(0);
  }
}

// Solve the water and light
void solve_problem_water_light()
{
  int light = digitalRead(lightPin);
  check_light(light);

  delay(300);
  print_lcd(light);
}

// print to lcd
void print_lcd(int light)
{
  lcd.setCursor(0, 0);
  lcd.print("Intensity  ");
  if (light == LOW)
    lcd.print(HIGH);
  else
    lcd.print(LOW);

  lcd.setCursor(0, 1);
  lcd.print("Humidity  ");
  // The senzor not work :(
  lcd.print(LOW);
}

// Checks button state
void check_button()
{
  currentState = digitalRead(buttonPin);

  // If the switch/button changed, due to noise or pressing:
  if (currentState != lastFlickerableState)
  {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastFlickerableState = currentState;
  }

  if ((millis() - last_debounce) > debounce_delay)
  {
    if (currentState == HIGH && water_present == 1 && lastSteadyState == HIGH && currentState == LOW)
    {
      water_present = 0;
      Servo_water.write(0);
      delay(300);
    }
    else if (lastSteadyState == LOW && currentState == HIGH)
    {
      Servo_water.write(90);
    }
  }
}

void loop()
{
  solve_problem_water_light();
  Serial.print(readI2CRegister16bit(0x20, 0));
  check_button();
}