#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <MPU6050_light.h>

Adafruit_INA219 ina219; 
MPU6050 mpu(Wire);

const int SDA_pin = 9;
const int SCL_pin = 8;

void setup_sensores(){
    Wire.begin(SDA_pin,SCL_pin);
    if (! ina219.begin()) {
      while (1) { delay(10); }
    }
    byte status = mpu.begin();
    while(status!=0){ } // stop everything if could not connect to MPU6050
    delay(1000);
    mpu.calcOffsets(); // gyro and accelero
  }

  void medir_energia(float* ptr_data){
    ptr_data[4] = ina219.getBusVoltage_V();
    ptr_data[5] = ina219.getCurrent_mA();
    ptr_data[6] = ina219.getPower_mW();
    //loadvoltage = busvoltage + (shuntvoltage / 1000);
  }
  
  void medir_angulo(float* ptr_data){  
    mpu.update();
    ptr_data[7]=mpu.getAngleZ();
    //mpu.getAngleY();
    //mpu.getAngleZ();
  }



