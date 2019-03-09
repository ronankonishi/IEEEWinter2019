#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <SoftwareSerial.h>

#define LSM9DS1_M  0x1E
#define LSM9DS1_AG  0x6B
#define DECLINATION 11.50

#define trigPin 3
#define echoPin 4
#define buzzer 8
#define hm_txd 11
#define hm_rxd 12

SoftwareSerial mySerial(hm_txd,hm_rxd);
LSM9DS1 imu;

long duration;
int distance;
double acceleration_x, acceleration_y, acceleration_z;

void setup() {
  mySerial.begin(9600);   
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;

  while (!imu.begin()) {
    Serial.println("Failed to communicate with LSM9DS1.");
    delay(100);
  }
}
void loop() {
  //ULTRASONIC SENSOR
  ping();
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance= duration*0.034/2;

  //ACCELEROMETER
  if (imu.gyroAvailable()){
    imu.readGyro();
  } 
  if (imu.accelAvailable()){
    imu.readAccel();
  }
  if (imu.magAvailable()){
    imu.readMag();
  }

  updateGyro();
  updateAccel();
  printData();

  // Buzz and send data for appropriate distance and acceleration thresholds
  if (distance <= 15 && (acceleration_x > 1 || acceleration_x < -1) && 
                        (acceleration_y > 1 || acceleration_y < -1)){
    tone(buzzer,1000);
    mySerial.write("0");
  } else {
    noTone(buzzer);
    mySerial.write("1");
  }
}

void updateGyro() {
  imu.calcGyro(imu.gx);
  imu.calcGyro(imu.gy);
  imu.calcGyro(imu.gz);
}

void updateAccel() {
  acceleration_x = imu.calcAccel(imu.ax);
  acceleration_y = imu.calcAccel(imu.ay);
  acceleration_z = imu.calcAccel(imu.az);
}

void printData() {
  Serial.print(distance);
  Serial.print(",");
  Serial.print(acceleration_x);
  Serial.print(",");
  Serial.print(acceleration_y);
  Serial.print(",");
  Serial.println(acceleration_z);
}

void ping() {
  //send echo signal from ultrasonic at 100ms
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
}

