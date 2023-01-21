
class Moteurs {

   public : 
      Moteurs();
      //-- MOTEUR A(droite) --
      int ENA;
      int IN1; 
      int IN2;
      //-- MOTEUR B ( gauche)--
      int ENB;
      int IN3;
      int IN4; 
   
   private : 
    
    void avancer_robot();
    void tourner_a_droite();
    void tourner_a_gauche();
    void arreter_robot();

};





