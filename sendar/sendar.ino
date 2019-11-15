#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
LiquidCrystal lcd(9, 8, 5, 4, 3, 2);
int data=A0;
int data1=A3;
const int buttonPin = 11;     // the number of the pushbutton pin
const int ledPin =  10;      // the number of the LED pin        
int buttonState = 0;
int count=0;
unsigned int temp;
int d[3];
char indata[32];
char inchar=-1;
byte index = 0;
double alpha = 0.75; 

void setup() 
{  
  Serial.begin(9600);  
  lcd.begin(16, 2);  
  pinMode(data,INPUT);  
  pinMode(data1,INPUT);    
  pinMode(ledPin, OUTPUT);  
  pinMode(buttonPin, INPUT);  
  lcd.setCursor(0, 0);  
  lcd.print("Place The Finger");  
  delay(1000); 
  lcd.clear();
}
void loop() 
{  
  String s;
  lcd.setCursor(0,0);  
  lcd.print("Calculating");  
  delay(1000);  
  digitalWrite(ledPin, HIGH);  
  buttonState = digitalRead(buttonPin);  
  if (buttonState == HIGH) 
  {    
    d[0]=1;
    digitalWrite(ledPin, HIGH);
  }   
  else   
  {
    d[0]=0;
    lcd.clear();
    lcd.print("GAS DETECTED");
    digitalWrite(ledPin, LOW);   
  }   
  int sensorValue = 0;   
  sensorValue = analogRead(data1);   
  delay(10);
  float mv = (sensorValue/1024.0)*500;   
  d[1]=(int)mv;   
  lcd.clear();   
  lcd.setCursor(0, 0);   
  lcd.print("Tem:");   
  lcd.print(d[1]); 
  /*temp=millis();  
  while(millis()<(temp+10000))   
  {      
    if(analogRead(A0)<100)       
    {          
      count=count+1;
      while(analogRead(data)<100);      
    }   
  }   
  lcd.setCursor(0,1);
  lcd.print("H:");
  lcd.print(count);*/
    lcd.setCursor(0,1);
    static double oldValue = 0; 
    static double oldChange = 0; 
    int rawValue = analogRead (data); 
    double value = alpha * oldValue + (1 - alpha) * rawValue; 
    if((int)(value/10)>60)
     {
      d[2]=(int)value/10;
      lcd.print("H:");
      lcd.print(d[2]);
      for(int i=0;i<3;i++)
      {
        if(i==0 || i==1)
         {s.concat(d[i]);s.concat(",");}
        else
         {s.concat(d[i]);s.concat(",");}
      }
      Serial.println(s);
      }
      else
      {
        lcd.print("Calibrating");
      }
      oldValue = value; 
      delay (5000);  
      //delay(3000);
      lcd.clear();
 // count=0;
  if(Serial.available())
  {
    int z = Serial.read();
    if(z==0){lcd.print("Safe-Zone");delay(2000);}
    if(z==1){lcd.print("Danger-Zone-I");delay(2000);}
    if(z==2){lcd.print("Danger-Zone-II");delay(2000);}
  }
}

