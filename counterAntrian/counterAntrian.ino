#include <LiquidCrystal_I2C.h>

// C++ code
//
#define btnTeller1 2
#define btnTeller2 4
#define btnService 7

LiquidCrystal_I2C lcd1(0x20,16,2);
LiquidCrystal_I2C lcd2(0x21,16,2);
LiquidCrystal_I2C lcd3(0x22,16,2);
unsigned long millisPrint, millisBtn, millisSerial;
int serviceCount = 0;
int tellerCount = 0;
int tellerStack = 0, teller1Stack = 0,teller2Stack = 0;
int serviceStack = 0;

void setup()
{
  Serial.begin(9600);
  initLCD();
  pinMode(btnTeller1, INPUT_PULLUP);
  pinMode(btnTeller2, INPUT_PULLUP);
  pinMode(btnService, INPUT_PULLUP);
}

void loop()
{
  if(millis()>millisSerial+1000){
    String data = "";
    bool stop = false; 
    while(Serial.available()>0){
      char c = Serial.read();
      if(c != '#' && stop == false){
        data+= char(c);
      }else{
        stop = true;
      }
    }
    data.trim();
    Serial.println("data = " + data);
    
    String dataIndex[2];
    int index = 0;
    for(int i = 0 ; i<= data.length(); i++){
      if(data[i]=='&'){
        index++;
      }else{
        dataIndex[index] += char(data[i]); 
      }
    }
    if(dataIndex[0]!=""){
      serviceCount = dataIndex[0].toInt();
    }
    
    if(dataIndex[1]!=""){
      tellerCount = dataIndex[1].toInt();
    }
    Serial.println("Service = " + String(serviceCount) + ", Teller = " + String(tellerCount));
    
    millisSerial=millis();
  }
  if(millis()>millisPrint+200){
    printTeller1();
    printTeller2();
    printService();
    millisPrint = millis();
  }
  
  if(millis()>millisBtn+200){
    if(!digitalRead(btnService)){
      if(serviceCount>serviceStack){
        serviceStack++;
      }
    }

    if(!digitalRead(btnTeller1)){
      if(tellerCount>tellerStack){
        teller1Stack = tellerStack;
        teller1Stack++;
        tellerStack = teller1Stack;
      }
    }

    if(!digitalRead(btnTeller2)){
      if(tellerCount>tellerStack)
        teller2Stack = tellerStack;
        teller2Stack++;
        tellerStack = teller2Stack;
    }
    Serial.println(String(serviceStack)+"#"+String(tellerStack));
    millisBtn = millis();
  }
}

void printTeller1(){
  lcd1.setCursor(0,0);
  lcd1.print("Antrian Teller 1");
  lcd1.setCursor(0,1);
  lcd1.print("Antrian No " + String(teller1Stack));
}
void printTeller2(){
  lcd2.setCursor(0,0);
  lcd2.print("Antrian Teller 2");
  lcd2.setCursor(0,1);
  lcd2.print("Antrian No " + String(teller2Stack));
}
void printService(){
  lcd3.setCursor(0,0);
  lcd3.print("Antrian Service");
  lcd3.setCursor(0,1);
  lcd3.print("Antrian No = " + String(serviceStack));
}
void initLCD(){
  lcd1.init();
  lcd1.backlight();
  lcd2.init();
  lcd2.backlight();
  lcd3.init();
  lcd3.backlight();
}
