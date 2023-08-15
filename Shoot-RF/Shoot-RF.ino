#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "paj7620.h"
/*#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
//Adafruit_SH1106 display(OLED_RESET);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);*/


RF24 radio(9, 10); 

const byte address[6] = "00001"; 

int x = A0;
int y = A1;
int n = 0;
int yt =A2;
int xt =A3;
int b =6;
int bf = 0;
int bs =0;
int pt =0;
int l=3;
int r=4;
int br=5;
int g=0;


void setup() {
  Serial.begin(9600);
    paj7620Init();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(true);
  radio.enableDynamicPayloads();
  radio.stopListening();
  /*lcd.init(); 
  lcd.backlight();
  lcd.clear();
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(1);*/
  pinMode(b,INPUT);
  pinMode(br,INPUT);
  pinMode(l,INPUT);
  pinMode(r,INPUT);
  digitalWrite(br,HIGH);
  digitalWrite(l,HIGH);
 digitalWrite(r,HIGH);
 
 
}

void loop() {
      
  
  
      int dt[6];
      int joystickValues[4];
      dt[0] = map(analogRead(A0),0,1023,0,225);
     dt[1] = map(analogRead(A1),0,1023,0,225);
     dt[2] = map(analogRead(A3),0,1023,0,225);
     dt[3] = map(analogRead(A2),0,1023,0,225);
     dt[4] = map(analogRead(A6),0,1023,0,225);
     dt[5] = map(analogRead(A7),0,1023,0,225);
       bs =digitalRead(b);
  if(bs==0&&bf==1){
    pt=1-pt;
    
  }
  bf =bs;
  delay(1);
  int ld = digitalRead(l);
int rd = digitalRead(r);
int bd = digitalRead(br);
if ((ld == 0 && bd == 0) || (rd == 0 && bd == 0) || (ld == 1 && rd == 1 && bd == 1)) {
  g = 0;
}
else if (ld == 0 && rd == 1) {
  g = 1;
}
else if (rd == 0 && ld == 1) {
  g = 2;
}
else if (rd == 0 && ld == 0) {
  g = 3;
}
else if (bd == 0) {
  g = 4;
}

      
 
 
      uint8_t data = 0;
    if(pt==1){
      
     paj7620ReadReg(0x43, 1, &data);
       
      switch(data){
        case GES_RIGHT_FLAG:
                delay(200);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_LEFT_FLAG) {
                    n=20;
                    delay(50);
                }
              else {
                    n=1;
                    
                }
                break;
            case GES_LEFT_FLAG:
                delay(200);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_RIGHT_FLAG) {
                    n=20;
                    delay(50);
                }  
                else {
                    n=2;
                }
                break;
                
            case GES_UP_FLAG:
                delay(200);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_DOWN_FLAG) {
                   n=20;
                   delay(50);
                } 
                else {
                    n=3;
                }
                break;
            case GES_DOWN_FLAG:
                delay(200);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_UP_FLAG) {
                    n=20;
                    delay(50);
                } 
                else {
                    n=4;
                }
                break;
        case GES_FORWARD_FLAG:
         n=5;
         delay(50);
         break;
        case GES_BACKWARD_FLAG:
         n=6;
         delay(50);
         break;
                  
      }
 
   
    }
    else if(pt==0){
    
   
   
     if(dt[0]>=180){
      n=3;
     }
     else if(dt[0]<=80){
      n=4;
     }
     else if(dt[1]>=180){
      n=6;
     }
     else if(dt[1]<=80){
      n=5;
     }
     else if(dt[2]>=180){
      n=7;
     }
     else if(dt[2]<=80){
      n=8;
     }
     else if(dt[3]>=180){
      n=1;
     }
     else if(dt[3]<=80){
      n=2;
     }
     else{
      n=0;
     }
    }
/*switch(n) {
  case 0: case 20:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Stop");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Stop");
    break;

  case 1:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Right");
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Right");
    break;

  case 2:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Left");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Left");
    break;

  case 3:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Down");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Down");
    break;

  case 4:
   display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Up");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Up");
    break;

  case 5:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Forth");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Forth");
    break;

  case 6:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Back");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Back");
    break;

  case 7:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Release");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Release");
    break;

  case 8:
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 30);
    display.print("Catch");
     lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Catch");
    break;
}
display.display();*/

    
     joystickValues[0]=n;
     joystickValues[1]=dt[4];
     joystickValues[2]=dt[5];
     joystickValues[3]=g;
     
  radio.write(&joystickValues, sizeof(joystickValues));
  
  
 
    
    
     
      
     
       
      
    
    
    
    delay(10);
  
}
