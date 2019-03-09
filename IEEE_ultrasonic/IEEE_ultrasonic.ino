#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

LSM9DS1 imu;

//I2C setup
#define LSM9DS1_M  0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

//#define PRINT_CALCULATED
#define PRINT_SPEED 250 // 250 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract 
// a declination to get a more accurate heading. Calculate 
// your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION 11.50 //declination (in degrees) La Jolla,SD,CA 

// defines pins numbers
const int trigPin = 3;
const int echoPin = 4;
int Buzzer = 8;
// defines variables
long duration;
int distance;
double acceleration_x, acceleration_y, acceleration_z;

void setup() 
{
  Serial.begin(115200); // Starts the serial communication
  //define output and inputs
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(Buzzer, OUTPUT);

  //Setting device communication mode and address
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;

  //imu.begin()checks for communication with IMU
  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                  "work for an out of the box LSM9DS1 " \
                  "Breakout, but may need to be modified " \
                  "if the board jumpers are.");
    while (1);
  }

}
void loop() 
{
  //ULTRASONIC SENSOR
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  
  //ACCELEROMETER
  if ( imu.gyroAvailable() )
  {
    // readGyro()update the gx, gy, and gz variables with the most current data.
    imu.readGyro();
  }
  if ( imu.accelAvailable() )
  {
    // readAccel()update the ax, ay, and az variables with the most current data.
    imu.readAccel();
  }
  if ( imu.magAvailable() )
  {
    // readMag()update mx, my, and mz variables with the most current data.
    imu.readMag();
  }

  if ((lastPrint + PRINT_SPEED) < millis())
  {
    Serial.print("Distance: ");
    Serial.println(distance);
    printGyro();  // Print "G: gx, gy, gz"
    printAccel(); // Print "A: ax, ay, az"
 
    Serial.println();
    
    lastPrint = millis(); // Update lastPrint time
  }

  Serial.print("D: ");
  Serial.println(distance);
  Serial.print("x: ");
  Serial.println(acceleration_x);
  Serial.print("y: ");
  Serial.println(acceleration_y);
  if (distance <= 15)
  {
    if (acceleration_x > 1 || acceleration_x < -1) 
    {
      if (acceleration_y > 1 || acceleration_y < -1) 
      {
      //Serial.println(distance);
      tone(Buzzer,1000); //HZ
      }
    }
  }
  else
  {
  //Serial.println(distance);
    noTone(Buzzer);
  }
}

void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
//  Serial.print("G: ");
//#ifdef PRINT_CALCULATED
  Serial.print(imu.calcGyro(imu.gx), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gy), 2);
  Serial.print(", ");
  Serial.print(imu.calcGyro(imu.gz), 2);
  Serial.println(" deg/s");
//#elif defined PRINT_RAW
//  Serial.print(imu.gx);
//  Serial.print(", ");
//  Serial.print(imu.gy);
//  Serial.print(", ");
//  Serial.println(imu.gz);
//#endif
}



void printAccel()
{  
//  Serial.print("A: ");
//#ifdef PRINT_CALCULATED
  acceleration_x = imu.calcAccel(imu.ax);
  acceleration_y = imu.calcAccel(imu.ay);
  acceleration_z = imu.calcAccel(imu.az);
//  Serial.print(acceleration_x, 2);
//  Serial.print(", ");
//  Serial.print(acceleration_y, 2);
//  Serial.print(", ");
//  Serial.print(acceleration_z, 2);
//  Serial.println(" g");
//#elif defined PRINT_RAW 
//  Serial.print(imu.ax);
//  Serial.print(", ");
//  Serial.print(imu.ay);
//  Serial.print(", ");
//  Serial.println(imu.az);
//#endif
}
