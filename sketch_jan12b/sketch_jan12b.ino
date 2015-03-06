#include <Arduino.h>
#include <Wire.h>
#include <MicrOledPro.h>
//#include <SoftwareSerial.h>

//LCD_SH1106 lcd; /* for SH1106 OLED module */
LCD_SSD1306 lcd; /* for SSD1306 OLED module */
char TestData;

//1SoftwareSerial mySerial(6,7);
void setup() {
  // put your setup code here, to run once:
  //lcd.begin();
  //lcd.clear();
  
  Serial.begin(9600);
  Serial.write("testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest1");
  delay(1000);
  Serial.write("AT+NAMEsams_watch\r\n");
  delay(1000);
//  Serial.write("AT+TYPE3\r\n");
//  delay(2000);
//  Serial.write("AT+ANCS1\r\n");
//  delay(2000);
//  Serial.write("AT+PASS402878\r\n");
//  delay(2000);
//  Serial.write("AT+RESET\r\n");
//  delay(2000);
//  Serial.write("AT");
//  delay(2000);

}
void loop() {
//  
//  //Serial.println("testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttest");
   //Serial.print("AT");
   
   //delay(2000);
   //delay(1000);
   //lcd.clear();
   if(Serial.available() > 0)
   {
     //Serial.println("Data received");
     TestData = Serial.read();
     Serial.write(TestData);
   }
}
