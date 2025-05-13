/***************************************************************************/
// File			  [track.h]
// Author		  [Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions  [MotorWriting, MotorInverter, tracking]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>


/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/

/*===========================import variable===========================*/
int extern tp;
double w1=0.3;//1;
double w2=0.6;//3;
int kp=70;//35;
int tp=70;//50;
int b=-75;//-70;
int strong=55;
int goback=0;
double kd=43;
double ki=1.1;
double laste = 0;
double sumerror=0;
double adj_R=0.9, adj_L=1; // 馬達轉速修正係數。MotorWriting(_Tp,_Tp)如果歪掉就要用參數修正。
    
/*===========================import variable===========================*/

// Write the voltage to motor.
void MotorWriting(double vL, double vR) {
  // TODO: use L298N to control motor voltage & direction
  if(vL>=0){
    digitalWrite(left1,HIGH);
    digitalWrite(left2,LOW);
  }else{
    digitalWrite(left1,LOW);
    digitalWrite(left2,HIGH);
    vL=-vL;
  }
  if(vR>=0){
    digitalWrite(right1,HIGH);
    digitalWrite(right2,LOW);
  }else{
    digitalWrite(right1,LOW);
    digitalWrite(right2,HIGH);
    vR=-vR;
  }
  analogWrite(EnA,vL);
  analogWrite(EnB,vR);
}// MotorWriting

bool detectblack()
{
  int r2 = digitalRead(IRr2);
  int r1 = digitalRead(IRr1);
  int irM = digitalRead(IRM);
  int l1 = digitalRead(IRl1);
  int l2 = digitalRead(IRl2);
  if(irM==1&& r1==1&& r2==1 &&l1==1 &&l2==1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool detectwhite()
{
  int r2 = digitalRead(IRr2);
  int r1 = digitalRead(IRr1);
  int irM = digitalRead(IRM);
  int l1 = digitalRead(IRl1);
  int l2 = digitalRead(IRl2);
  if(irM==0&& r1==0&& r2==0 &&l1==0 &&l2==0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
void backback()
{
  MotorWriting(-80,-65);
  /*if(detectblack())
  {
    MotorWriting(0,0);
  }*/
  delay(2000);
  
}
void turnright()
{
  MotorWriting(0,0);
  delay(400);
//  MotorWriting(85,80);
//  delay(500);
  MotorWriting(95,0);
  delay(500);
  Serial.println("hR");
  while (true){
    int r2 = digitalRead(IRr2);
    int r1 = digitalRead(IRr1);
    int irM = digitalRead(IRM);
    int l1 = digitalRead(IRl1);
    int l2 = digitalRead(IRl2);
    if(r2+r1+irM+l1+l2>0)
      break;
    else
      MotorWriting(90,-20);
  }
  /*while (true){
    int r2 = digitalRead(IRr2);
    int r1 = digitalRead(IRr1);
    int irM = digitalRead(IRM);
    int l1 = digitalRead(IRl1);
    int l2 = digitalRead(IRl2);
    if(r2+r1+irM+l1+l2>0)
      break;
    else
      MotorWriting(90,25);
  }*/
  MotorWriting(0,0);
  delay(500);
}
void turnleft()
{
  MotorWriting(0,0);
  delay(400);
  MotorWriting(0,90);
  delay(700);
  //Serial.println("hL");
  //MotorWriting(-70,200);
  //delay(240);
  while (true){
    int r2 = digitalRead(IRr2);
    int r1 = digitalRead(IRr1);
    int irM = digitalRead(IRM);
    int l1 = digitalRead(IRl1);
    int l2 = digitalRead(IRl2);
    if(r2+r1+irM+l1+l2>0)
      break;
    else
      MotorWriting(-20,80);
  }
  /*while (true){
    int r2 = digitalRead(IRr2);
    int r1 = digitalRead(IRr1);
    int irM = digitalRead(IRM);
    int l1 = digitalRead(IRl1);
    int l2 = digitalRead(IRl2);
    if(r2+r1+irM+l1+l2>0)
      break;
    else
      MotorWriting(30,100);
  }*/
  MotorWriting(0,0);
  delay(200);
}
//倒車

//迴轉180
void reverse()
{
  MotorWriting(0,0);
  delay(100);
  MotorWriting(-70,-65);
  delay(300);
  MotorWriting(0,80);
  delay(1000);
//  MotorWriting(-50,-50);
//  delay(300);
//  MotorWriting(0,0);
//  delay(100);
//  MotorWriting(20,-40);
//  delay(100);
  MotorWriting(-85,0);
  delay(500);
  while (true){
    int r2 = digitalRead(IRr2);
    int r1 = digitalRead(IRr1);
    int irM = digitalRead(IRM);
    int l1 = digitalRead(IRl1);
    int l2 = digitalRead(IRl2);
    if(r2+r1+irM+l1+l2>0)
      break;
    else
      MotorWriting(-96,0);
  }
   //MotorWriting(0,-180);
  //delay(500);
  MotorWriting(0,0);
  delay(200);
}
/*void reverse()
{
  MotorWriting(0,0);
  delay(100);
  //MotorWriting(-230,230);
  //delay(240);
  MotorWriting(80,-70);
  delay(1400);
//  MotorWriting(-50,-50);
//  delay(300);
  MotorWriting(0,0);
  delay(100);
//  MotorWriting(20,-40);
//  delay(100);
  while (true){
    int r2 = digitalRead(IRr2);
    int r1 = digitalRead(IRr1);
    int irM = digitalRead(IRM);
    int l1 = digitalRead(IRl1);
    int l2 = digitalRead(IRl2);
    if(r2+r1+irM+l1+l2>0)
      break;
     else
      MotorWriting(30,-80);
  }
   //MotorWriting(0,-180);
  //delay(500);
  MotorWriting(0,0);
  delay(200);
}*/

void forward()
{
  MotorWriting(0,0);
  delay(1000);
  MotorWriting(75,72);
  delay(30);
  
}
// Handle negative motor_PWMR value. 
void MotorInverter(int motor, bool& dir) {
  //Hint: the value of motor_PWMR must between 0~255, cannot write negative value.
}// MotorInverter

// P/PID control Tracking
void tracking(int l2,int l1,int irM,int r1,int r2){
  // find your own parameters!
  
  // TODO: complete your P/PID tracking code
  if(r2 + r1 + irM + l1 + l2 == 0 ){//&& laste==0 && goback>=3) {
      MotorWriting(b,b);
    }
//  else if(r2 + r1 + irM + l1 + l2 == 0){
//    goback+=1;
//    MotorWriting(30-laste,30+laste);
//    if(goback==2) laste=0;
//  }
//   if(irM==1&&r2+r1+l1+l2==0){
//    MotorWriting(strong,strong);
//    goback=0;
//  }
  if(l2 && l1 && irM && !r1 && !r2){
     goback=0;
     MotorWriting(0,strong);
  }else if(r2 && r1 && irM && !l1 && !l2){
     goback=0;
     MotorWriting(strong,0);
  }
  else{
    double error = l2*(-w2)+l1*(-w1)+r1*w1+r2*w2
                +0.5*(w1+w2)*(l2 == l1 && l2 == 1)+0.35*w1*(irM == l1 && irM == 1)
                -0.5*(w1+w2)*(r2 == r1 && r2 == 1)-0.35*w1*(irM == r1 && irM == 1);//0.8,0.5
    sumerror+=error;
    double derror = error - laste;
    double power = kp*error + kd*derror;
    //ki*sumerror
    int vR =  tp - power;                
    int vL = tp+power;
    if(vR>255) vR = 255;
    else if(vR<-255) vR = -255;
    if(vL>255) vL = 255;
    else if(vL<-255)vL = -255;
    laste=error;
    MotorWriting(adj_L*vL, adj_R*vR);
  }
// end TODO

}// tracking
