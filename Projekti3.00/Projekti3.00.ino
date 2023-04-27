/*
 Käytettii PS2 ohjaimen koodia ja koitettii saaha se sulautettua meiä ohjaimelle
 */

#include <Gamepad.h>

//initialize a centers of axises for calibration
int Xkeskikohta = 512;
int Ykeskikohta = 512;
double multipXakseli = 0.248;
double multipYakseli = 0.248;

//Initializing a Gamepad
Gamepad gp;
void setup() {
  //initializing inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(2,  INPUT_PULLUP); //YLÄNAPPI B
  pinMode(3,  INPUT_PULLUP); //OIKEANAPPI D
  pinMode(4,  INPUT_PULLUP); //ALANAPPI A
  pinMode(5,  INPUT_PULLUP); //VASENNAPPI C
  pinMode(6,  INPUT_PULLUP); // nappiE
  pinMode(7,  INPUT_PULLUP); // nappiF
  pinMode(8,  INPUT_PULLUP); //JoyK
  calibrate();
}

void loop() {
  int Xakseli, Yakseli;
  Xakseli = analogRead(A0);
  Yakseli = 1023 - analogRead(A1);
  //we need to convert a 0-1000 to -127 - 127
  Xakseli = floor((Xakseli - Xkeskikohta) * multipXakseli);
  Yakseli = floor((Yakseli - Ykeskikohta) * multipYakseli);
  if(Xakseli > 127) Xakseli = 127;
  if(Yakseli > 127) Yakseli = 127;
  gp.setXakseli(Xakseli);
  gp.setYakseli(Yakseli);
  
  int  OIKEANAPPI, VASENNAPPI, YLANAPPI, ALANAPPI, nappiE, nappiF, JoyK;
  OIKEANAPPI = digitalRead(3);
  VASENNAPPI = digitalRead(5);
  YLANAPPI = digitalRead(2);
  ALANAPPI = digitalRead(4);
  nappiE = digitalRead(6);
  nappiF = digitalRead(7);
  JoyK = digitalRead(8);

  if(OIKEANAPPI == LOW)
    gp.setButtonState(1, true);
  else
    gp.setButtonState(1, false);
  
  if(VASENNAPPI == LOW)
    gp.setButtonState(3, true);
  else
    gp.setButtonState(3, false);  
  
  if(YLANAPPI == LOW)    
    gp.setButtonState(0, true);
  else
    gp.setButtonState(0, false);

  if(ALANAPPI == LOW)
    gp.setButtonState(2, true);
  else
    gp.setButtonState(2, false);

    
  if( nappiE == LOW)
    gp.setButtonState(4, true);
  else
    gp.setButtonState(4, false); 

  if( nappiF == LOW)
    gp.setButtonState(5, true);
  else
    gp.setButtonState(5, false);  
    
           
  if( JoyK == LOW)
    gp.setButtonState(6, true);
  else
    gp.setButtonState(6, false);  

  delay(20);
}

void calibrate()
{
  int Xakseli, Yakseli;
  int i = 0;
  while(i < 8)
  {
    Xakseli = analogRead(A0);
    Yakseli = 1023 - analogRead(A1);
    bool validLX = Xakseli > (Xkeskikohta - 100) && Xakseli < (Xkeskikohta + 100);
    bool validLY = Yakseli > (Ykeskikohta - 100) && Yakseli < (Ykeskikohta + 100);
    if(validLX && validLY)
    {
      i++;
      
    }
    else i = 0;
    delay(20);
  }
  Xkeskikohta = Xakseli;
  Ykeskikohta = Yakseli;
  multipXakseli = (double)127 / (double)Xakseli;
  multipYakseli = (double)127 / (double)Yakseli;
}
