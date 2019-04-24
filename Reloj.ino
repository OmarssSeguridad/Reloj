#include <Time.h>
#include <TimeLib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>
#include <stdint.h>

//TouchsScreen 
#define MINPRESSURE 1
#define MAXPRESSURE 1000

#define YP A3 //A1-A3
#define XM A2 //a2
#define YM 9 //7-9
#define XP 8 //6-8

short TS_MINX = 125;
short TS_MINY = 85; 
short TS_MAXX = 965;  //850
short TS_MAXY = 905;  //940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); 

int X;
int Y;
int presion; 
boolean flag_ajustes=false;

//LCD
#define  BLACK   0x0000
#define  RED     0xF800
#define  WHITE   0xFFFF
#define  BLUE    0x001F

#define LCD_CS A3
#define LCD_CD A2   
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Reloj
int second_ac=0;
int minute_ac=0;
int hour_ac=0;


void setup() {
  tft.begin(0x9341);
  menu_inicial();
 //Dibujo Boton
  
}

void loop() {
 
 lecturaPanel();
 if(presion > MINPRESSURE && presion < MAXPRESSURE){
     coordenadas();
 }
 if(flag_ajustes==true){
     if((X > 140 && X < 220) && (Y > 10 && Y < 60)&& (presion > MINPRESSURE && presion < MAXPRESSURE)){
          ajusta_segundos();//hora
     }

     if((X > 140 && X < 220) && (Y > 70 && Y < 140)&& (presion > MINPRESSURE && presion < MAXPRESSURE)){
          ajusta_minutos();
     }

     if((X > 140 && X < 220) && (Y > 160 && Y < 220)&& (presion > MINPRESSURE && presion < MAXPRESSURE)){
          ajusta_hora();//ssegundos
     }
  }else{
      actualiza();
    }
  if((X > 20 && X < 70) && (Y > 55 && Y < 230)&& (presion > MINPRESSURE && presion < MAXPRESSURE)){
    if(flag_ajustes==false){
         tft.fillRect(80,40,140,40,RED);
         tft.setCursor(90,50);
         tft.setTextColor(BLUE);
         tft.setTextSize(3);
         tft.println("  OK");
         flag_ajustes=true;
         hour_ac=hour();
         minute_ac=minute();
         second_ac=second();
         delay(150);
      }else{
         ajusta();
         menu_inicial();
         flag_ajustes=false;
      }
  }
 second_ac= second();
}

void lecturaPanel()
{
    digitalWrite(13, HIGH); 
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);
  
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    X = map(p.x, TS_MAXX, TS_MINX, tft.width(), 0);
    Y = map(p.y, TS_MAXY, TS_MINY, tft.height(), 0);
    presion = p.z;
}


void menu_ajustes()
{
  tft.setRotation(1);//0
  tft.fillRect(150,55,20,30,WHITE);
  tft.fillRect(70,55,20,30,WHITE);
  tft.fillRect(150,145,20,30,WHITE);
  tft.fillRect(70,145,20,30,WHITE);
  tft.fillRect(150,235,20,30,WHITE);
  tft.fillRect(70,235,20,30,WHITE);
}

void actualiza(){
    if(second_ac<second()){
         tft.fillRect(50,90,250,80,BLACK);
         tft.setRotation(1);
         tft.setCursor(60,100);
         tft.setTextSize(5);
         tft.setTextColor(RED);
         if(hour()<10){
           tft.print("0");
           tft.print(hour()); 
         }else{
           tft.print(hour()); 
         }
         tft.print(":");
         if(minute()<10){
           tft.print("0");
           tft.print(minute()); 
         }else{
           tft.print(minute()); 
         }
         tft.print(":");
         if(second()<10){
           tft.print("0");
           tft.print(second()); 
         }else{
           tft.print(second()); 
         }
      }  
  }
  
void ajusta_segundos(){//hora
      if(second_ac<60){
          second_ac=second_ac+1;
      }else{
          second_ac=0;
          tft.fillScreen(BLACK);
        }
      tft.setRotation(1);
      tft.fillRect(235,95,70,50,BLUE);//55,95,70,50
      tft.setCursor(245,100);//65,100
      tft.setTextSize(5);
      tft.setTextColor(RED);
      tft.print(second_ac);
      delay(50);
}

void ajusta_minutos(){
      if(minute_ac<60){
          minute_ac=minute_ac+1;
      }else{
          minute_ac=0;
          tft.fillScreen(BLACK);
      }
      tft.setRotation(1);
      tft.fillRect(145,95,70,50,BLUE);//145,95,70,50
      tft.setCursor(155,100);//155,100
      tft.setTextSize(5);
      tft.setTextColor(RED);
      tft.print(minute_ac);
      delay(50);//150
}

void ajusta_hora(){//segundos
      if(hour_ac<24){
          hour_ac=hour_ac+1;
      }else{
          hour_ac=0;
           tft.fillScreen(BLACK);
      }
      tft.setRotation(1);
      tft.fillRect(55,95,70,50,BLUE);//235,95,70,50
      tft.setCursor(65,100);//245,100
      tft.setTextSize(5);
      tft.setTextColor(RED);
      tft.print(hour_ac);
      delay(50);
}

void coordenadas(){
      tft.setRotation(1);
      tft.fillRect(10,10,150,30,WHITE);
      tft.setCursor(15,15);
      tft.setTextSize(2);
      tft.setTextColor(BLACK);
      tft.print("X=");
      tft.print(X);
      tft.print(" ");
      tft.print("Y=");
      tft.print(Y);
  }

void ajusta(){
     setTime(hour_ac,minute_ac,second_ac, day(), month(), year());
  }
  
void menu_inicial(){
   tft.fillScreen(BLACK);
   tft.setRotation(1);
         tft.setCursor(60,100);
         tft.setTextSize(5);
         tft.setTextColor(RED);
         if(hour()<10){
           tft.print("0");
           tft.print(hour()); 
         }else{
           tft.print(hour()); 
         }
         tft.print(":");
         if(minute()<10){
           tft.print("0");
           tft.print(minute()); 
         }else{
           tft.print(minute()); 
         }
         tft.print(":");
         if(second()<10){
           tft.print("0");
           tft.print(second()); 
         }else{
           tft.print(second()); 
         }
   tft.fillRect(80, 40, 140, 40, RED); //80, 40, 140, 40
   tft.setCursor(90,50);
   tft.setTextSize(3); 
   tft.setTextColor(BLUE); 
   tft.println("AJUSTAR");
  }
