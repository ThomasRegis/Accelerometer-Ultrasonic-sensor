#include"moteurs.hpp"
#include<Arduino.h>
Moteurs::Moteurs(){};

void Moteurs::avancer_robot(){

digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
digitalWrite(ENA,HIGH);
digitalWrite(ENB,HIGH);
}

void Moteurs::tourner_a_droite(){

digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
digitalWrite(ENA,HIGH);
digitalWrite(ENB,HIGH);
}

void Moteurs::tourner_a_gauche(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
digitalWrite(ENA,HIGH);
digitalWrite(ENB,HIGH);
}

void Moteurs::arreter_robot(){
digitalWrite(ENA,LOW);
digitalWrite(ENB,LOW);
}
