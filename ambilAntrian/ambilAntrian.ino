#include <LiquidCrystal_I2C.h>

// C++ code
//
#define btnService 7
#define btnTeller 2

LiquidCrystal_I2C lcd(0x20,16,2);
int serviceCount = 0;
int tellerCount = 0;
unsigned long millisPrint, millisBtn;
unsigned long millisSerial;
void setup()
{
  Serial.begin(9600);
  pinMode(btnService, INPUT_PULLUP);
  pinMode(btnTeller, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  
}

void loop()
{
  if(millis()>millisPrint+200){
    lcd.setCursor(0,0);
    lcd.print("Service = " + String(serviceCount));
    lcd.setCursor(0,1);
    lcd.print("Teller = " + String(tellerCount));
    
    millisPrint = millis();
  }
  if(millis()>millisBtn+200){
    if(!digitalRead(btnService)){
     serviceCount++;
    }

    if(!digitalRead(btnTeller)){
      tellerCount++;
    }
    millisBtn = millis();
  }
  if(millis()>millisSerial+1000){
    Serial.println(String(serviceCount) + "&" + tellerCount + "#");
    millisSerial = millis();
  }
}
