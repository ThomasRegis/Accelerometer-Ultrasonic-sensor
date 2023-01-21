#include"Accelerometre.hpp"
#include<Arduino.h>
Accelerometre::Accelerometre(){};
float g = 9.80665;
float erreur_X = 0;
float erreur_Y =0;
float pos_X,V_x =0;
float pos_Y,V_y =0;

float Accelerometre::calcule_position(){
  temps = millis();
  delta = millis()-temps;
  while (delta<temps_echantillonage){delta = millis()-temps;}
  Test_X=(Wire.read()<<8|Wire.read());
  Test_Y=(Wire.read()<<8|Wire.read());
  Acc_X = (Test_X/2048)*g + erreur_X;
  Acc_Y = (Test_Y/2048)*g + erreur_Y;
  pos_X += Acc_X*pow(delta,2) + V_x*delta;
  pos_Y += Acc_Y*pow(delta,2) + V_y*delta;
  V_x += (Acc_X*delta);
  V_y += (Acc_X*delta);
  Serial.print("Position_X = ");Serial.print(pos_X);
  Serial.print("Position_Y =");Serial.print(pos_Y);
  Serial.println();
  return pos_X,pos_Y; 

}