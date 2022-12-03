#include <MQ2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd( 0x27 ,16 ,2); // CHANGE 0X3F TO 0X27 AS LCD ADDRESS
int Analog_Input = A0;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);

#include <Servo.h>
Servo window;  
int pos = 0;
const int kipas = 4;
int buzzer = 11;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  lcd.begin();
  lcd.backlight();
  mq2.begin();
  window.attach(9);  // attaches the servo on pin 9 to the servo object
  pos=0;
  window.write(0);
  pinMode(kipas, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("Calibrating");
  for(int i=0; i<11; i++){
    if (i==5){
      lcd.setCursor(0,1);
    }
    else {
     lcd.print(".");
     delay(500);
    }
  }
  lcd.setCursor(5,1);
  lcd.print("DONE");
  delay(1000);
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("SENSOR ACTIVE");
  delay(1500);
  lcd.clear();
}
void loop() {
  float* values = mq2.read(true); //set it false if you don't want to print the values in the Serial
  //lpg = values[0];
  lpg = mq2.readLPG();
  //co = values[1];
  co = mq2.readCO();
  //smoke = values[2];
  smoke = mq2.readSmoke();
  delay(100);
  lcd.clear();
  if (smoke>400){  
    lcd.setCursor(0, 0);
    lcd.print("ASAP : ");
    lcd.setCursor(6,0);
    lcd.print(smoke);
    lcd.print(" PPM");
    lcd.setCursor(0,1);
    lcd.print("UDARA KOTOR");
    digitalWrite(kipas, HIGH);
    digitalWrite(buzzer, HIGH);
    if(pos==0){
        for(pos=0;pos<=90;pos+=1){
          window.write(pos);                  // sets the servo position according to the scaled value
          delay(50);                           // waits for the servo to get there
        }
        
      }
      pos=90;
  }
  else {  
    lcd.setCursor(0, 0);
    lcd.print("ASAP : ");
    lcd.print(smoke);
    lcd.print(" PPM");
    lcd.setCursor(0,1);
    lcd.print("UDARA BERSIH");
    digitalWrite(kipas, LOW);
    digitalWrite(buzzer, LOW);
    if(pos==90){
        for(pos=90;pos>=0;pos-=1){
          window.write(pos);                  // sets the servo position according to the scaled value
          delay(50);                           // waits for the servo to get there
        }
        
      }
      pos=0;
  }
}
