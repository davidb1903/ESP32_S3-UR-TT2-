#include <Arduino.h>
//Define pines UART
const int  TXD2 = 44;
const int  RXD2 = 43;
//Velocidad en bps
const int velUARTmax = 2000000; // Señal B del encoder
const int velUARTtest = 115200; // Señal B del encoder

typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;


void setup_Serial(){
    //Serial.begin(velUARTtest,SERIAL_8N1,TXD2,RXD2); // Replace RX_PIN/TX_PIN with the appropriate pin numbers
    Serial.begin(velUARTmax,SERIAL_8N1,RXD2,TXD2); // Replace RX_PIN/TX_PIN with the appropriate pin numbers
}
//Envia floats como 4 bytes
void imprimirBytes(float N){
    binaryFloat Nb;
    Nb.floatingPoint = N;
    Serial.write(Nb.binary,4);
}

void imprimirFloat(float N){
    Serial.print(N);
}