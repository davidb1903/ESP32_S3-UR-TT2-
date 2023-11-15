#include "encoder.h"
#include "comPiSerial.h"
#include "sensores.h"

unsigned long lastTime = 0;// Tiempo anterior
unsigned long sampleTime = 1;// Tiempo de muestreo
static float data_stream[8]={0,0,0,0,0,0,0,0};
static float print_stream[8]={0,0,0,0,0,0,0,0};
static float* ptr_data= data_stream;
void setup() {
  Serial.begin(115200);
 // setup_Serial();
  setup_encoder();
  setup_sensores();
}

void loop() {
  if(millis() - lastTime >= sampleTime){ // Se actualiza cada sampleTime (milisegundos)
    for(int i=0;i<8;i++){
      //Serial.print(data_stream[i]);  //Enviar
      //Serial.print(",");
      imprimirBytes(print_stream[i]);  //Enviar
    }
    //Serial.println(data_stream[7]);  //Enviar
    calcular_Vel(lastTime,ptr_data);
    medir_energia(ptr_data);
    medir_angulo(ptr_data);
    lastTime = millis();// Almacenamos el tiempo actual.
    //Serial2.write(byte(N));
    //Serial2.print("RPM:")
    //Serial2.println(N);
    //Serial2.write(byte("A"));
  }
}