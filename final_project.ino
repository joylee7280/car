/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#define DEBUG // debug flag

// for BlueTooth
#include<SoftwareSerial.h>
// for RFID
#include <SPI.h>
#include <MFRC522.h>

/*===========================define pin & create module object================================*/
// BlueTooth
#define tx 7
#define rx 8
SoftwareSerial BT(tx,rx);   // TX,RX on bluetooth module, 請按照自己車上的接線寫入腳位
// L298N, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
#define IRM A3
#define IRr1 A2
#define IRr2 A1
#define IRl1 A4
#define IRl2 A5
#define left1 2
#define left2 3
#define right1 4
#define right2 A0
#define EnA 6
#define EnB 5
// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN      0        // 讀卡機的重置腳位
#define SS_PIN       10       // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件
/*===========================define pin & create module object===========================*/

/*============setup============*/
void setup()
{
   //bluetooth initialization
   pinMode(tx,INPUT);
   pinMode(rx,OUTPUT);
   BT.begin(9600);
   //Serial window
   Serial.begin(9600);
   //RFID initial
   SPI.begin();
   mfrc522.PCD_Init();
   //L298N pin
   pinMode(IRM,INPUT);
   pinMode(IRl2,INPUT);
   pinMode(IRl1,INPUT);
   pinMode(IRr1,INPUT);
   pinMode(IRr2,INPUT);
   pinMode(left1,OUTPUT);
   pinMode(left2,OUTPUT);
   pinMode(right1,OUTPUT);
   pinMode(right2,OUTPUT);
   pinMode(EnA,OUTPUT);
   pinMode(EnB,OUTPUT);
   Serial.begin(9600);
#ifdef DEBUG
  Serial.println("Start!");
#endif
}
/*============setup============*/

/*=====Import header files=====*/
#include "RFID.h"
#include "track.h"
#include "bluetooth.h"
#include "node.h"
/*=====Import header files=====*/

/*===========================initialize variables===========================*/
int r2=0,r1=0,r3=0,l3=0,l1=0,l2=0; //紅外線模組的讀值(0->white,1->black)
//int _Tp=90; //set your own value for motor power
int count=0;
String str="";
//bool state=false; //set state to false to halt the car, set state to true to activate the car
//BT_CMD _cmd = NOTHING; //enum for bluetooth message, reference in bluetooth.h line 2
/*===========================initialize variables===========================*/

/*===========================declare function prototypes===========================*/
void Search();// search graph
/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void loop()
{
   int r2 = digitalRead(IRr2);
   int r1 = digitalRead(IRr1);
   int irM = digitalRead(IRM);
   int l1 = digitalRead(IRl1);
   int l2 = digitalRead(IRl2);
   
   Search();
   //Serial.println(str);
   tracking(l2,l1,irM,r1,r2);
   if(l2+l1+irM+r1+r2>=4 && count<=59 ){
    char action = str[count];
    count++;
    switch(action){
      case 'g':
        forward();
        delay(500);
        tracking(l2,l1,irM,r1,r2);
        break;
      case 'u':
        reverse();
        break;
      case 'r':
        turnright();
        break;
      case 'l':
        turnleft();
        break;
      case's':
        MotorWriting(0,0);
        delay(8000);
    }
   }
   //checkpoint
   /*if(r2+r1+irM+l1+l2!=5) tracking(l2,l1,irM,r1,r2);
   else if(count<12) {
      count+=1;
      if(count==1 || count==2||count==3)
      {
        tp=53;
        forward();
        delay(600);
      }
      else if(count==4||count==9){
        tp=65;
        turnright();
//        MotorWriting(-83,-75);
//        delay(800);
//        MotorWriting(80,88);
//        delay(1000);
//        backback();
//        Search();
//        count++;
//        MotorWriting(-70,-70);
//        delay(500);
      }
      else if(count==5 || count==10) {
        backback();
        //count++;
      }
      else if(count==7) turnright();
      else if(count==6||count==11) reverse();
      else if (count==8) turnleft();
  }else MotorWriting(0,0);
  delay(50);*/
  delay(20);
}

void Search()
{
  // TODO:
  // 1. Get command from bluetooth 
  // 2. Change state ifneed
  byte idSize;
  byte* rf=rfid(idSize);
  if(rf!=NULL){ 
    send_byte(rf,idSize);
    Serial.print("This is RFID:");
    Serial.println(*rf);
  }
    
    char  _cmd = 'a';
    _cmd=ask_BT();
    if(_cmd){
      Serial.println(_cmd);
      //forward();
      //delay(1000);
    }
  if(_cmd>='0' && _cmd<='9'){
    Serial.print("This is _cmd:");
    Serial.println(_cmd);
    switch(_cmd){
      case '1':
        str+="g";
        break;
      case '2':
        str+="u";
        break;
      case '3':
        str+="r";
        break;
      case '4':
        str+="l";
        break;
      case '5':
        str+="s";
        break;
    }
  }
}
  //checkpoint
  /*if(readrfid==true){
    backback();
    readrfid=false;
  }*/
 
  
  /*if(r2+r1+irM+l1+l2!=5) tracking(l2,l1,irM,r1,r2);
  else if(count<12) {
    Serial.print(count);
      count+=1;
      if(count==1 || count==2)
      {
        MotorWriting(0,0);
        delay(100);
        forward();
      }
      else if(count==4 || count==7) backback();
      else if(count==3||count==5||count==8) turnright();
      else if(count==10||count==11) reverse();
      else if (count==6 || count==9) turnleft();
  }else MotorWriting(0,0);*/
  

  /*tracking(l2,l1,irM,r1,r2);
  if(detectblack())
  {
    backback();
  }
  delay(50);
  
}*/
