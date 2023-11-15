#include <Arduino.h>
// Pines para encoder
//FD//
const int A1enc = 4; // Señal A del encoder
const int B1enc = 5; // Señal B del encoder
//FI//
const int A2enc = 6; // Señal A del encoder
const int B2enc = 7; // Señal B del encoder
//LI//
const int A3enc = 15; // Señal A del encoder
const int B3enc = 16; // Señal B del encoder
//LD //
const int A4enc = 17; // Señal A del encoder
const int B4enc = 18; // Señal B del encoder
//const int pinPWM = 25; // Señal PWM

//Constantes calculo de velocidad
const int mH = 16; // Cuentas por rev
const int s = 4; // Posibles estados
const int r = 50; // Reducción de la caja
const int R = mH*s*r; // Reducción de la caja

static volatile int n[4]= {0,0,0,0};
volatile int ant[4] = {0,0,0,0};
volatile int act[4] = {0,0,0,0};

//int P[4]={0,0,0,0};
//static float N[4]={0,0,0,0};

void IRAM_ATTR encoderFD() {
  ant[0] = act[0];
  bitWrite(act[0],1,digitalRead(A1enc));
  bitWrite(act[0],0,digitalRead(B1enc));

  if(ant[0]==0 && act[0] == 1) n[0]++;
  if(ant[0]==1 && act[0] == 3) n[0]++;
  if(ant[0]==2 && act[0] == 0) n[0]++;
  if(ant[0]==3 && act[0] == 2) n[0]++;

  if(ant[0]==0 && act[0] == 2) n[0]--;
  if(ant[0]==1 && act[0] == 0) n[0]--;
  if(ant[0]==2 && act[0] == 3) n[0]--;
  if(ant[0]==3 && act[0] == 1) n[0]--;

}
void IRAM_ATTR encoderFI() {
  ant[1] = act[1];
  bitWrite(act[1],1,digitalRead(A2enc));
  bitWrite(act[1],0,digitalRead(B2enc));

  if(ant[1]==0 && act[1] == 1) n[1]--;
  if(ant[1]==1 && act[1] == 3) n[1]--;
  if(ant[1]==2 && act[1] == 0) n[1]--;
  if(ant[1]==3 && act[1] == 2) n[1]--;

  if(ant[1]==0 && act[1] == 2) n[1]++;
  if(ant[1]==1 && act[1] == 0) n[1]++;
  if(ant[1]==2 && act[1] == 3) n[1]++;
  if(ant[1]==3 && act[1] == 1) n[1]++;

}
void IRAM_ATTR encoderTD() {
  ant[2] = act[2];
  bitWrite(act[2],1,digitalRead(A3enc));
  bitWrite(act[2],0,digitalRead(B3enc));

  if(ant[2]==0 && act[2] == 1) n[2]--;
  if(ant[2]==1 && act[2] == 3) n[2]--;
  if(ant[2]==2 && act[2] == 0) n[2]--;
  if(ant[2]==3 && act[2] == 2) n[2]--;

  if(ant[2]==0 && act[2] == 2) n[2]++;
  if(ant[2]==1 && act[2] == 0) n[2]++;
  if(ant[2]==2 && act[2] == 3) n[2]++;
  if(ant[2]==3 && act[2] == 1) n[2]++;

}
void IRAM_ATTR encoderTI() {
  ant[3] = act[3];
  bitWrite(act[3],1,digitalRead(A4enc));
  bitWrite(act[3],0,digitalRead(B4enc));

  if(ant[3]==0 && act[3] == 1) n[3]++;
  if(ant[3]==1 && act[3] == 3) n[3]++;
  if(ant[3]==2 && act[3] == 0) n[3]++;
  if(ant[3]==3 && act[3] == 2) n[3]++;

  if(ant[3]==0 && act[3] == 2) n[3]--;
  if(ant[3]==1 && act[3] == 0) n[3]--;
  if(ant[3]==2 && act[3] == 3) n[3]--;
  if(ant[3]==3 && act[3] == 1) n[3]--;

}

void setup_encoder(){
  pinMode(A1enc,INPUT);
  pinMode(B1enc,INPUT);
  pinMode(A2enc,INPUT);
  pinMode(B2enc,INPUT);
  pinMode(A3enc,INPUT);
  pinMode(B3enc,INPUT);
  pinMode(A4enc,INPUT);
  pinMode(B4enc,INPUT);
  attachInterrupt(digitalPinToInterrupt(A1enc),encoderFD,CHANGE);
  attachInterrupt(digitalPinToInterrupt(B1enc),encoderFD,CHANGE);

  attachInterrupt(digitalPinToInterrupt(A2enc),encoderFI,CHANGE);
  attachInterrupt(digitalPinToInterrupt(B2enc),encoderFI,CHANGE);

  attachInterrupt(digitalPinToInterrupt(A3enc),encoderTD,CHANGE);
  attachInterrupt(digitalPinToInterrupt(B3enc),encoderTD,CHANGE);

  attachInterrupt(digitalPinToInterrupt(A4enc),encoderTI,CHANGE);
  attachInterrupt(digitalPinToInterrupt(B4enc),encoderTI,CHANGE);
}


void calcular_Vel(long lastTime,float* ptr_data){
    //P=(n*360.0)/R;
    for(int ID=0;ID<4;ID++){
      ptr_data[ID]=(n[ID]*60.0*1000.0)/((millis()-lastTime)*R);// Velocidad en RPM
      n[ID]=0;// Inicializamos los pulsos
    }
}
