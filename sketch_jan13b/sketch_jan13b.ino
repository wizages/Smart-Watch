#include <Arduino.h>
#include <Wire.h>
#include <MicrOledPro.h>
#include <ssd1306xled.h>
#include <font6x8.h>

//LCD_SH1106 lcd; /* for SH1106 OLED module */
SSD1306Device lcd; /* for SSD1306 OLED module */
char test;
char temp_uids[5];
void setup() {
    lcd.init();
    lcd.ssd1306_fillscreen(0x00);
  Serial.begin(9600);
  delay(2000);
  //Serial.print("AT+ANCS0001114");
}

void loop() {
//  while(Serial.available()){
//    test = Serial.read();
//    Serial.write(test);
//    lcd.print(test);
//    
//  }
//getAppName("0001");  
//getAppName("0002");
//getAppName("0003");
getAppName("0004");
delay(3000);

}

void getAppName(String uid) {
  delay(3000);
  //char test;
  int count = 0;
  bool glitch = false;
  int appnamecount = 0;
  String appname;
  char appname2[15];
  String temp = "";
  String bufferdude = "";
  //bool ending = false;
  lcd.print("inside");
  Serial.print("AT+ANCS" + uid + "114");
  //Serial.print("AT+ANCS0001114");
  while (count < 50) { 
    if (Serial.available()) {
      //bufferdude += (char) Serial.read();
      test = Serial.read();
      //Serial.write(test);
      
//      if (temp.indexOf("WOK+ANCS:") != -1) {
//          lcd.print("DA FUCK");
//        }
      if (test > 32) {
        lcd.ssd1306_char_font6x8(test);
        temp = temp + test;
      //temp.toCharArray(appname2, 30);
      //lcd.print(appname2);
        if (temp.indexOf("WOK+ANCS:") != -1 || glitch == true) {
          //lcd.ssd1306_char_font6x8(test);
          glitch = true;
          appname += test;
          count++;
//          bufferdude = String(count);
//          bufferdude.toCharArray(temp_uids, 5);
//          lcd.print(temp_uids);
//          lcd.print(" ");
        }
      }
    }
    else if (glitch){
          count++;
//          bufferdude = String(count);
//          bufferdude.toCharArray(temp_uids, 5);
//          lcd.print(temp_uids);
//          lcd.print(" ");
    }
    
  }
  appname.toCharArray(appname2, 15);
  //appname
  //lcd.print(uids.length());
  lcd.print(appname2);
}
