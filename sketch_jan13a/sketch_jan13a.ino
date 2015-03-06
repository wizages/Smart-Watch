//#include <Arduino.h>
//#include <Wire.h>
//#include <MicrOledPro.h>

#include <ssd1306xled.h>
#include <font6x8.h>
#include "watchicons.h"

SSD1306Device lcd;

String bufferdude = "";
  short int hour1 = 0;
short int hour2 = 3;
short int minute1 = 5;
short int minute2 =5;
//short int messages = 0;
short int calls = 0;
short int email = 0;
short int count = 0;
//short int other = 0;
//short int snapchat = 0;
//short int unknown = 0;
char temp_uids[5];
String uids = "";
bool phone = false;
bool startup = false;
char test;
bool timeset = false;

void setup() {


  lcd.init();
  lcd.ssd1306_fillscreen(0x00);
  Serial.begin(9600);
  //Wait for bluetooth connection...
  while (!phone) {
    if (Serial.available()) {
      //bufferdude += (char) Serial.read()
      test = Serial.read();
      Serial.print(test);
      bufferdude += test;
      //lcd.ssd1306_char_font6x8(test);
      if (bufferdude.indexOf( "OK+ANCSN") != -1) {
        phone = true;
        bufferdude = "";
        lcd.print("Connected");
      }
      //delay(1);
    }

  }
  //Sort through initial notifations
  while (!startup) {

    if (Serial.available()) {
      //bufferdude += (char) Serial.read();
      test = Serial.read();
      Serial.print(test);
      bufferdude += test;
      //lcd.ssd1306_char_font6x8(test);
      //lcd.setCursor(0,0);
      //lcd.print(bufferdude.length());

      if (bufferdude.indexOf( "SD") != -1) {
        //bufferdude="";
        // lcd.setCursor(0, 0);
        lcd.print("Ready to go");
        delay(1000);
        startup = true;
        //bufferdude = "";
        //Serial.flush();
      }
      else if (bufferdude.length() == 16) {
        categorize();
        bufferdude = "";
      }
    }

  }
  //lcd.ssd1306_fillscreen(0x00)

  lcd.ssd1306_fillscreen(0x00);
  lcd.setCursor(0, 0);
  bufferdude = "";

}

void loop() {

  
  //Display initial notifications
  bool nonotify = true;
  while ( uids.length() / 4 > 0) {
    //bufferdude = String(uids.length()/4);
    //bufferdude.toCharArray(temp_uids, 5);
    //lcd.print(temp_uids);
    //Serial.print("length of uids = " + uids.length());
    uids.substring(0, 4).toCharArray(temp_uids, 5);
    //lcd.print(temp_uids);
    //getAppName(uids.substring(0, 4));
    getAppName(uids.substring(0, 4));
    nonotify = false;
    uids = uids.substring(4);
    if (uids.length() / 4 == 0) {
      //lcd.print("End");
      if (timeset){
      delay(1000);
      }
      //drawIcons(1, messages);
    }
  }
  if (Serial.available()) {
    bool nothing = false;
    //bufferdude += (char) Serial.read();
    while(!nothing){
    test = Serial.read();
    if(test>31){
    Serial.print(test);
    bufferdude += test;
    //lcd.ssd1306_char_font6x8(test);
    }
    //lcd.ssd1306_char_font6x8(test);
    //lcd.setCursor(0,0);
    //lcd.print(bufferdude.length());
    if (bufferdude.length() == 16) {
      //lcd.print("something dun fucked up");
      if (bufferdude.charAt(8) == '0') {
        categorize();
        nothing = true;
      }
      else {
        //demote something :P
        //lcd.ssd1306_fillscreen(0x00);
        //lcd.ssd1306_char_font6x8(bufferdude.charAt(8));
      }
      bufferdude = "";
    }
    else if (bufferdude.indexOf("clearscreen") != -1) {
      //lcd.print("something dun fucked up");
      lcd.ssd1306_fillscreen(0x00);
      lcd.setCursor(0, 0);
      bufferdude = "";
      nothing = true;
    }
    else if (bufferdude.charAt(5) == 't') {
     // lcd.print("something dun fucked up");
      hour1 = bufferdude.charAt(0) - '0';
      hour2 = bufferdude.charAt(1) - '0';
      minute1 = bufferdude.charAt(3) - '0';
      minute2 = bufferdude.charAt(4) - '0';
      timeset = true;
      nothing = true;
      bufferdude="";
      count = 238;
    }
    }
  }
  if (timeset && nonotify) {
    //bufferdude="";
    tellTime();
  }
}



void draw(short int number, short int locationx, short int locationy) {
  switch (number) {
    case 1:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, one);
      break;
    case 2:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, two);
      break;
    case 3:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, three);
      break;
    case 4:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, four);
      break;
    case 5:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, five);
      break;
    case 6:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, six);
      break;
    case 7:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, seven);
      break;
    case 8:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, eight);
      break;
    case 9:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, nine);
      break;
    case 0:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, zero);
      break;
    default:
      lcd.draw(locationx, locationy, locationx + 64, locationy + 4, blank);
      break;
  }
}
void tellTime(){
  if(count == 238){
  if (hour1 == 1) {
      draw(hour1, 60, 0);
    }
    else {
      lcd.draw(60, 0, 124, 4, blank);
    }
    draw(hour2, 60 , 4);
    draw(minute1, 0, 0);
    draw(minute2, 0, 4);
    //delay(60020);
    delay(250);
    count = 0;
    minute2 = minute2 + 1;
    if (minute2 == 10) {
      minute2 = 0;
      minute1 = minute1 + 1;
      if (minute1 == 6) {
        minute1 = 0;
        hour2 = hour2 + 1;
        if (hour2 == 10) {
          hour1 = 1;
          hour2 = 0;
        }
        if (hour1 == 1 && hour2 == 3) {
          hour2 = 1;
          hour1 = 0;
        }
      }
    }
  }
  else{
    delay(250);
    count++;
  }
}
void drawIcons(short int icon, short int number) {
  short int notifaction1 = 0;
  short int notifaction2 = 0;
  switch (icon) {
    case 1:
      lcd.draw(0, 0, 64, 8, message);
      break;
    default:
      lcd.draw(0, 0, 64, 4, message);
      break;
  }
  notifaction1 = number / 10;
  notifaction2 = number - (10 * notifaction1);
  draw(notifaction1, 60, 0);
  draw(notifaction2, 60, 4);
}

void getAppName(String uid) {
  delay(3000);
  //char test;
  short int count = 0;
  bool glitch = false;
  bool isW = false;
  short int appnamecount = 0;
  short int digitsAway = 0;
  String appname;
  char appname2[15];
  //String temp = "";
  bufferdude = "";
  //bool ending = false;
  //lcd.print("inside");
  //uid.toCharArray(appname2, 15);
  //lcd.print(uids.length());
  //lcd.print(appname2);
  Serial.print("AT+ANCS" + uid + "114");

  //Serial.print("AT+ANCS0001114");
  while (count < 50) {
    if (Serial.available()) {
      //bufferdude += (char) Serial.read();
      test = Serial.read();
      Serial.write(test);
      //lcd.ssd1306_char_font6x8(test);
      //      if (temp.indexOf("WOK+ANCS:") != -1) {
      //          lcd.print("DA FUCK");
      //        }
      if (test > 31) {

        if ((test == 'W' || isW) && digitsAway < 12) {
          digitsAway++;
          isW = true;
        }

        //temp.toCharArray(appname2, 30);
        //lcd.print(appname2);
        if (digitsAway > 11 || glitch == true) {
          //lcd.ssd1306_char_font6x8(test);
          glitch = true;
          appname += test;
          count++;
        }
      }
    }
    else if (glitch) {
      count++;
      delay(100);
    }
    //lcd.print("stuck");
  }
  appname.toCharArray(appname2, 15);
  //appname
  //lcd.print(uids.length());
  
  lcd.print(appname2);
  lcd.print(" - ");
}

void categorize() {
  switch (bufferdude.charAt(9)) {
    case '1':
    case '2':
    case '3':
      calls++;
      //lcd.print("voicemail: ");
      //bufferdude.substring(12, 16).toCharArray(temp_uids, 5);
      break;
    case '4':
      //messages++;
      //lcd.print("message: ");
      bufferdude.substring(12, 16).toCharArray(temp_uids, 5);
      //lcd.print(temp_uids);
      //if(strcmp("0000", temp_uids) != 0){
      uids += temp_uids;
      //}
      break;
    case '5':
      //lcd.print("schedule: ");
      bufferdude.substring(12, 16).toCharArray(temp_uids, 5);
      //if(strcmp("0000", temp_uids) != 0){
      uids += temp_uids;
      //}
      break;
    case '6':
      email++;
      //lcd.print("email: ");
      //bufferdude.substring(12, 16).toCharArray(temp_uids, 5);
      break;
    default:
      //other++;

      //lcd.print("other: ");
      //bufferdude.substring(12, 16).toCharArray(temp_uids, 5);
      //if(strcmp("0000", temp_uids) != 0){
      //uids += temp_uids;
      //}
      //lcd.print(temp_uids);
      break;
  }
}

//    if (count == 0 && command2 != ""){
//      int notread = 0;
//      lcd.print("inside");
//      Serial.print(command2);
//      while(notread != 1){
//      while(Serial.available()){
//        test = Serial.read();
//        Serial.write(test);
//        lcd.print(test);
//        appname += test;
//        }
//        if(appname.length() >= 45 && appname.indexOf("OK+ANCS") == -1){
//          notread = 1;
//          count = 1;
//        }
////        else if(appname.length() >= 45 && appname.indexOf("OK+ANCS") != -1){
////          notread = 1;
////          lcd.print("breakout");
////          break;
////       }
//      }
//    }




//  if(buffersize <= bufferdude.length()){
//     for(;;){
//     int indexANCS8 = bufferdude.indexOf("OK+ANCS8");
//     if (indexANCS8 != -1) {lcd.print(indexANCS8);}
//     if (-1 == indexANCS8) continue;
//     boolean complete = (indexANCS8 + buffersize) <= bufferdude.length();
//     //lcd.print(complete);
//     if (!complete) continue;
//     String string = bufferdude.substring(indexANCS8, indexANCS8 + buffersize);
//     lcd.print(string);
//     bufferdude = bufferdude.substring(indexANCS8 + buffersize);
//     String newstring = "AT+ANCS";
//     newstring += string.charAt(12);
//     newstring += string.charAt(13);
//     newstring += string.charAt(14);
//     newstring += string.charAt(15);
//     newstring += "000";
//     Serial.print(newstring);
//     lcd.print(newstring);
//     delay(1000);
//     break;
//     }
//  }
//  if(bufferdude.length() > 0){
//  int indexANCS8 = bufferdude.indexOf("OK+ANCS8");
//     if (indexANCS8 != -1) {lcd.print(indexANCS8);}
//  }
//bufferdude = "";

//  else{
//    //lcd.print(bufferdude + "hit");
//    bufferdude = "";
//  }



