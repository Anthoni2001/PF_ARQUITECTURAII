#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

String cadenaAux;
String cadena;
int ledPINTrue=8;
int ledPINFalse=9;
const byte pinBuzzer = 10;
byte salida = 10;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(ledPINTrue , OUTPUT);
  pinMode(ledPINFalse , OUTPUT);
  cadena=cadenaAux;

}



void loop() {
   if (Serial.available()) 
   {  
    cadena= Serial.readString();
    if(cadena!=cadenaAux){
      writeLcd();
    }

    if(cadena=="yes"){
yesMode();
      
    }
    if(cadena=="no"){
      noMode();
    }
    if(cadena=="end"){

      endMode();
    }
    
    }    
    cadena=cadenaAux;

}

void yesMode(){
      digitalWrite(ledPINTrue , HIGH);
      digitalWrite(ledPINFalse , LOW); 
      analogWrite(pinBuzzer, salida);
      lcd.clear();
      String alerta = "DESPIERTA!";
      lcd.print(alerta);
      
  
}

void noMode(){
        digitalWrite(ledPINFalse , HIGH);
        digitalWrite(ledPINTrue , LOW);
        analogWrite(pinBuzzer, LOW);
        lcd.clear();
        String apagado="ALARMA INACTIVA";
        lcd.print(apagado);
  
  
  }

  void endMode(){
          digitalWrite(ledPINTrue , HIGH);
      delay(100);
      digitalWrite(ledPINTrue , LOW);
      delay(100);
      digitalWrite(ledPINFalse , HIGH);
      delay(100);
      digitalWrite(ledPINFalse , LOW);
       analogWrite(pinBuzzer, LOW);
    }

void writeLcd(){
     lcd.clear();
     lcd.setCursor(0,0);          
     lcd.print(cadena); 
}
