#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
 
MPU6050 accelgyro; 

int16_t gx1, gy1, gz1;
int16_t ax1, ay1, az1;
float gx2=0, gy2=0, gz2=0;
float ax2=0, ay2=0, az2=0;
int16_t i=0;

float T_Now =0;//系统当前时间
float T_Last=0;//上次时间

float gx, gy, gz;
float ax, ay, az;

float gx_offest=0, gy_offest=0, gz_offest=0;
float ax_offest=0, ay_offest=0, az_offest=0;
float Angle_Z,Angle_AG,Angle_GG,Angle_G;

void setup() {
    Wire.begin();
    Serial.begin(38400);
    accelgyro.initialize();
    pinMode(13, OUTPUT);
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
    for(i=0;i<1000;i++)
    {
      digitalWrite(13, LOW);
      delay(10);
      accelgyro.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
      gx=gx1/131.00;gy=gy1/131.00;gz=gz1/131.00;      //FS_SEL=0
      ax=ax1/16384.00;ay=ay1/16384.00;az=az1/16384.00;  //AFS_SEL=0
//      Serial.print(gx);Serial.print(",");
//      Serial.print(gy);Serial.print(",");
//      Serial.print(gz);Serial.print(",");
//      Serial.print(ax);Serial.print(",");
//      Serial.print(ay);Serial.print(",");
//      Serial.print(az);Serial.print(",");
//      Serial.print("\n");
      gx_offest+=gx; gy_offest+=gy;gz_offest+=gz;
      ax_offest+=ax; ay_offest+=ay;az_offest+=az;
      digitalWrite(13, HIGH);
    }
    
    gx_offest/=i; gy_offest/=i; gz_offest/=i;
    ax_offest/=i; ay_offest/=i; az_offest/=i;
//    Serial.print(gx_offest);Serial.print(",");
//    Serial.print(gy_offest);Serial.print(",");
//    Serial.print(gz_offest);Serial.print(",");
//    Serial.print(ax_offest);Serial.print(",");
//    Serial.print(ay_offest);Serial.print(",");
//    Serial.print(az_offest);Serial.print(",");
//      Serial.print("\n");
    T_Last=millis()/1000.0;
}
 
void loop() {
    accelgyro.getMotion6(&ax1, &ay1, &az1, &gx1, &gy1, &gz1);
    gx=gx1/131.00;gy=gy1/131.00;gz=gz1/131.00;      //FS_SEL=0
    ax=ax1/16384.00;ay=ay1/16384.00;az=az1/16384.00;  //AFS_SEL=0
    float Angle_Z = gz-gz_offest;
    T_Now=millis()/1000.0;
    Angle_GG = Angle_GG + Angle_Z*(T_Now-T_Last);
    T_Last=millis()/1000.0;
//    Serial.print(gx-gx_offest);Serial.print(",");
//    Serial.print(gy-gy_offest);Serial.print(",");
//    Serial.print(gz-gz_offest);Serial.print(",");
//    Serial.print(ax-ax_offest);Serial.print(",");
//    Serial.print(ay-ay_offest);Serial.print(",");
//    Serial.print(az-az_offest);Serial.print(",");
    delay(50);
    Serial.print(Angle_GG);
    Serial.print("\n");
}

