/*MCP41xxx Tutorial
http://henrysbench.capnfatz.com/henrys-bench/arduino-output-devices/mcp41010-digital-potentiometer-arduino-user-manual/
http://www.arduino-projekte.de/index.php?n=65

adapted by Nicu FLORICA (aka niq_ro) - http://www.tehnic.go.ro 
& http://www.arduinotehniq.com/
*/

#include <SPI.h>  
//const int CS = 10;  // Uno
const int CS = 53;   // mega
int PotWiperVoltage = 0;
int RawVoltage = 0;
float Voltage = 0;

#include <Wire.h>                 
#include <LiquidCrystal_I2C.h>    
LiquidCrystal_I2C lcd(0x27, 16, 2);

int scurt = 500;
 
void setup() {
  pinMode (CS, OUTPUT);   
  Serial.begin(9600);
  SPI.begin();   
 
lcd.begin();  
lcd.backlight(); 

lcd.setCursor(3, 0);   
lcd.print("MCP41xxx"); 
lcd.setCursor(1, 1);   
lcd.print("test by niq_ro"); 
delay(3000);           
lcd.clear();          
 
  
}
 
void loop() {
  // move the potentiometer in one direction
  for (int level = 0; level <= 255; level++) 
  {
    MCP41010Write(level);
    delay(scurt);
    RawVoltage = analogRead(PotWiperVoltage);
    Voltage = (RawVoltage * 5.0 )/ 1024.0;
    Serial.print("Level = " );                      
    Serial.print(level);      
    Serial.print("\t Voltage = ");
    Serial.println(Voltage,3);  
    
    lcd.setCursor(0, 0);
    lcd.print("level = ");
    if (level < 100) lcd.print(" ");
    if (level < 10) lcd.print(" ");
    lcd.print(level);
    lcd.print("/256");
    lcd.setCursor(0, 1);
    lcd.print("U = ");
    lcd.print(Voltage,3);
    lcd.print("/5.000V");
  }
  delay(2000);  // wait a couple seconds
  // Now mover potentiometer in other directions
  
  for (int level = 255; level >= 0; level--) 
  {
    MCP41010Write(level);
    delay(scurt
    );
    RawVoltage = analogRead(PotWiperVoltage);
    Voltage = (RawVoltage * 5.0 )/ 1024.0;
    Serial.print("Level = " );                      
    Serial.print(level);      
    Serial.print("\t Voltage = ");
    Serial.println(Voltage,3); 
    lcd.setCursor(0, 0);
    lcd.print("level = ");
    if (level < 100) lcd.print(" ");
    if (level < 10) lcd.print(" ");
    lcd.print(level);
    lcd.print("/256");
    lcd.setCursor(0, 1);
    lcd.print("U = ");
    lcd.print(Voltage,3);
    lcd.print("/5.000V");


  }
   delay(2000);
}
 
void MCP41010Write(byte value) 
{
  // Note that the integer vale passed to this subroutine
  // is cast to a byte
  
  digitalWrite(CS,LOW);
  SPI.transfer(B00010001); // This tells the chip to set the pot
  SPI.transfer(value);     // This tells it the pot position
  digitalWrite(CS,HIGH); 
}
