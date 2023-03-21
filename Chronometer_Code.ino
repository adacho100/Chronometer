#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27, 16, 2); //LCD with I2C implementation


int timer1;
int timer2;
float Time;
int speed;
int flag1 = 0; // reset 1
int flag2 = 0; // reset 2

float distance = 0.2030; // distance between photocells

int ir_s1 = A0; // first sensor port A0
int ir_s2 = A1; // second sensor port A1

int green_LED = 13; // green LED port 13
int red_led = 12; // red LED port 12

void setup(){
pinMode(ir_s1, INPUT);
pinMode(ir_s2, INPUT); 
pinMode(green_LED, OUTPUT);
pinMode(red_led, OUTPUT);
lcd.backlight();
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" Chronograph ");  
lcd.setCursor(0,1);
lcd.print("Optoelectronics");
 delay(2000);
 lcd.clear();
 } 
 void loop() {
 if(digitalRead (ir_s1) ==  HIGH && flag1==0){timer1 = millis(); flag1=1;} // reading first photocell

 if(digitalRead (ir_s2) == HIGH && flag2==0){timer2 = millis(); flag2=1;} //  reading second photocell

 if (flag1==1 && flag2==1){
     if(timer1 > timer2){Time = timer1 - timer2;} // comparing times between cells and resets
 else if(timer2 > timer1){Time = timer2 - timer1;}
 Time=Time/1000; //convert millisecond to second
 speed=(distance/Time); //v=d/t

 }

 if(speed==0){ 
 lcd.setCursor(0, 1); 
 if(flag1==0 && flag2==0){lcd.print("Awaiting shot   ");}
                     else{lcd.print("Sensor Error    ");digitalWrite(red_led, HIGH);} // condition where 
                    //IR_1 or IR_2 didn't read the value
 }
else{
  digitalWrite(red_led, LOW);
  lcd.clear(); 
lcd.setCursor(0, 0); 
    lcd.print("Speed:");
   lcd.print(speed,1);
   lcd.print("m/s  ");
   lcd.setCursor(0, 1); 
  if(speed > 0.5){lcd.print("   Shot counted   "); digitalWrite(green_LED, HIGH);} // condition 
                                                                      ///where both IR's read the value
           else{lcd.print("                 "); }    
   delay(3000);
    digitalWrite(green_LED, LOW);
    speed = 0;
   flag1 = 0;
   flag2 = 0;    
 }
 }