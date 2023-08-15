#include <Servo.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

RF24 radio(9 , 10); 

const byte address[6] = "00001"; 
Servo myservo,meservo,clservo,swservo,Lmoter,Rmoter,base,UD;

int targetAngle= constrain(targetAngle,45, 180);
int RargetAngle= constrain(RargetAngle,35,120);
int clEnd = constrain(clEnd,25,100);
int pwm,pwm1;
int xm,ym;



void setup() {
  
  Serial.begin(9600);
  myservo.attach(5); 
    myservo.write(45);//r
   meservo.attach(6); 
  meservo.write(70);//f
 swservo.attach(7);
  swservo.write(90);
  clservo.attach(4);
  clservo.write(25);
  Rmoter.attach(8);
  Rmoter.write(90);
  Lmoter.attach(2);
  Lmoter.write(90);
  base.attach(3);
  base.write(90);
  UD.attach(A0);
  UD.write(90);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(true);
   radio.enableDynamicPayloads();
  radio.startListening(); 
  
}

void loop() {
    
  if (radio.available()) {
    
    
    int joystickValues[4];
    int sw=swservo.read();
    int currentAngle = myservo.read();
    int kurrentAngle = meservo.read();
    int clawPos = clservo.read();
    int U=UD.read();
   
    radio.read(&joystickValues, sizeof(joystickValues)); // 讀取從發送端傳來的訊號
    int n=joystickValues[0];
    int x=joystickValues[1];
    int y=joystickValues[2];
    int g=joystickValues[3];
    
    if (n==3 && currentAngle<180) { 
      myservo.attach(5);
       
       targetAngle = currentAngle + 1;
      myservo.write(targetAngle); //3
      delay(5);
    }

      else if (n==4 && currentAngle>45) {
              myservo.attach(5);
           
              int targetAngle = currentAngle - 1;
              myservo.write(targetAngle); //4
               delay(5);
    }
    

    else if (n !=3&&n !=4 ||currentAngle==45 ||currentAngle==180 ) { 
              
              myservo.detach();
               
              
    }

     if (n==6 && kurrentAngle<170) { 
      meservo.attach(6);
     
       RargetAngle = kurrentAngle + 1;
      meservo.write(RargetAngle); 
      delay(5);//6
    }

      else if (n==5 && kurrentAngle>70) {
              meservo.attach(6);
            
               RargetAngle = kurrentAngle - 1;
              meservo.write(RargetAngle); //5
               delay(5);
    }
    

    else if ( n !=6&& n !=5 || kurrentAngle ==170 ||kurrentAngle ==70 ) { 
              
              meservo.detach();
               
              
    }

      if (n==7 && clawPos<170) { 
      clservo.attach(4);
       
       clEnd = clawPos + 1;
      clservo.write(clEnd); // 7
      delay(5);
    }

      else if (n==8 && clawPos>25) {
              clservo.attach(4);
           
              clEnd = clawPos - 1;
              clservo.write(clEnd);//8 
               delay(5);
    }
    

    else if (n !=7&&n !=8 ||clawPos==25 ||clawPos==180 ) { 
              
              clservo.detach();
               
              
    }

    if(n==1&&sw<180){
      swservo.attach(7);
      sw=sw+1;
      swservo.write(sw);//1
      delay(5);
      
    }
    else if(n==2&&sw>0){
      swservo.attach(7);
      sw=sw-1;
      swservo.write(sw);//1
      delay(5);//2
      
    }
    else if (n !=1&&n !=2||sw==180||sw==0 ){
     swservo.detach();
    }

    if(g==0){
      base.write(90);
      UD.detach();
    }
    else if(g==1){
      base.write(97);
    }
    else if(g==2){
      base.write(83);
    }
    else if(g==3&&U<180){
      base.write(90);
      UD.attach(A0);
      UD.write(U+1);
      delay(5);
    }
    else if(g==4&&U>0){
      base.write(90);
       UD.attach(A0);
      UD.write(U-1);
      delay(5);
    }
    
    if(x>=180){
      if(y>=80&&y<=180){
      xm=180;
      Rmoter.write(xm);
      Lmoter.write(xm);
      }
      else if(y>=180){
        xm=180;
        ym=map(y,180,225,180,90);
        Rmoter.write(xm);
      Lmoter.write(ym);
      
    }
    else{
      xm=180;
      ym=map(y,80,0,180,90);
        Rmoter.write(ym);
      Lmoter.write(xm);
    }
    }
    else if(x<=80){
       if(y>=80&&y<=180){
      xm=0;
      Rmoter.write(xm);
      Lmoter.write(xm);
      }
      else if(y>=180){
        xm=0;
        ym=map(y,180,225,0,90);
        Rmoter.write(xm);
      Lmoter.write(ym);
      
    }
    else{
      xm=0;
      ym=map(y,80,0,0,90);
        Rmoter.write(ym);
      Lmoter.write(xm);
    }
      
    }
    else{
      Rmoter.write(90);
      Lmoter.write(90);
      
    }
    
   
      
    }

    }
    
    
    
    
    
   
   
    
    

    
    


    
  
