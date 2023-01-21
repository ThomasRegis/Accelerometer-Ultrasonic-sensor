#include"capteur_ultrason.hpp"
#include<Arduino.h>

float Capteur::mesure_distance(){

digitalWrite(trig, HIGH);
temps = millis();
while((millis()-temps) <0.01){temps = millis();}
digitalWrite(trig, LOW);
lecture_echo = pulseIn(echo, HIGH);
distance = (0.017*lecture_echo);
temps = millis();
while((millis()-temps) <60){temps = millis();}
return distance; }