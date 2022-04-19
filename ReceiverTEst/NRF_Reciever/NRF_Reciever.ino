// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
<<<<<<< Updated upstream
=======
#include <Servo.h>
#include <Wire.h>
//=================================================
>>>>>>> Stashed changes

#define CE_PIN   9
#define CSN_PIN 10

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

typedef struct {
  byte yaw;
  byte pitch;
  byte roll;
  byte throttle;
}conData;

conData dataReceived; // this must match dataToSend in the TX
bool newData = false;

//===========

//===================================================
byte highByte, lowByte;
int count;
int acc_raw[3], gyro_raw[3];
int temperature;
double gyro_offset[3];
#define X           0     // X axis
#define Y           1     // Y axis
#define Z           2     // Z axis
//===================================================

void setup() {
<<<<<<< Updated upstream
=======

  // Start I2C communication
  Wire.begin();
  Wire.setClock(400000); // set I2C speed to 400000 Hz
  setupMpu6050Registers();
  calculateMpu6050Offsets();

  
  // Radio =========================================
  Serial.begin(9600);

  Serial.println("SimpleRx Starting");
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.startListening();
  //================================================
  
  //Servo Setup ====================================
  // Attach Servos to corresponding Pins
  ESC_FL.attach(escFL);
  ESC_FR.attach(escFR);
  ESC_BL.attach(escBL);
  ESC_BR.attach(escBR);
>>>>>>> Stashed changes

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//=============

void loop() {
<<<<<<< Updated upstream
=======

  getData();
  STARTSTOP();
  if(started == true)
  {
  
//  showData();
  
  M1 = mapped.throttle + mapped.yaw - mapped.pitch + mapped.roll;
  M2 = mapped.throttle + mapped.yaw - mapped.pitch - mapped.roll;
  M3 = mapped.throttle + mapped.yaw + mapped.pitch + mapped.roll;
  M4 = mapped.throttle + mapped.yaw + mapped.pitch - mapped.roll;

//  Serial.print("After: ");
//  Serial.print(1000 + minMax(M1,100,1000));
//  Serial.print(" ");
//  Serial.print(1000 + minMax(M2,100,1000));
//  Serial.print(" ");
//  Serial.print(1000 + minMax(M3,100,1000));
//  Serial.print(" ");
//  Serial.print(1000 + minMax(M4,100,1000));
//  Serial.print("\n");

//Serial.print("After: ");
//  Serial.print(M1);
//  Serial.print(" ");
//  Serial.print(M2);
//  Serial.print(" ");
//  Serial.print(M3);
//  Serial.print(" ");
//  Serial.print(M4);
//  Serial.print("\n");
  
  ESC_FR.writeMicroseconds(1000 + minMax(M1,100,1000));
  ESC_FL.writeMicroseconds(1000 + minMax(M1,100,1000)+100);
  ESC_BR.writeMicroseconds(1000 + minMax(M1,100,1000));
  ESC_BL.writeMicroseconds(1000 + minMax(M1,100,1000)+200);
  }
  else
  {
    while(started == false)
    {
    ESC_FR.writeMicroseconds(1000);
    ESC_FL.writeMicroseconds(1000);
    ESC_BR.writeMicroseconds(1000);
    ESC_BL.writeMicroseconds(1000);
>>>>>>> Stashed changes
    getData();
    showData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(dataReceived.yaw);
        newData = false;
    }
}
<<<<<<< Updated upstream
=======

void STARTSTOP()
{
    if(dataReceived.button_left == 0 && started == false)
    {
       started = true;
    }
    else if (dataReceived.button_right == 0 && started == true)
    {
       started = false;
    }
}

int minMax(int value, int min_value, int max_value) {
    if (value > max_value) {
        value = max_value;
    } else if (value < min_value) {
        value = min_value;
    }

    return value;
}

void setupMpu6050Registers() {
    // Configure power management
    Wire.beginTransmission(0x68); // Start communication with MPU
    Wire.write(0x6B);                    // Request the PWR_MGMT_1 register
    Wire.write(0x00);                    // Apply the desired configuration to the register
    Wire.endTransmission();              // End the transmission

    // Configure the gyro's sensitivity
    Wire.beginTransmission(0x68); // Start communication with MPU
    Wire.write(0x1B);                    // Request the GYRO_CONFIG register
    Wire.write(0x08);                    // Apply the desired configuration to the register : ±500°/s
    Wire.endTransmission();              // End the transmission

    // Configure the acceleromter's sensitivity
    Wire.beginTransmission(0x68); // Start communication with MPU
    Wire.write(0x1C);                    // Request the ACCEL_CONFIG register
    Wire.write(0x10);                    // Apply the desired configuration to the register : ±8g
    Wire.endTransmission();              // End the transmission

    // Configure low pass filter
    Wire.beginTransmission(0x68); // Start communication with MPU
    Wire.write(0x1A);                    // Request the CONFIG register
    Wire.write(0x03);                    // Set Digital Low Pass Filter about ~43Hz
    Wire.endTransmission();              // End the transmission
}

void calculateMpu6050Offsets(){
    for (count = 0; count < 2000 ; count ++){                           //Take 2000 readings for calibration.
    readSensor();                                                       //Read the gyro output.
    gyro_offset[X] += gyro_raw[X];                                       //Ad roll value to gyro_roll_cal.
    gyro_offset[Y] += gyro_raw[Y];                                       //Ad pitch value to gyro_pitch_cal.
    gyro_offset[Z] += gyro_raw[Z];                                       //Ad yaw value to gyro_yaw_cal.
    //We don't want the esc's to be beeping annoyingly. So let's give them a 1000us puls while calibrating the gyro.
    ESC_FR.writeMicroseconds(1000);
    ESC_FL.writeMicroseconds(1000);
    ESC_BR.writeMicroseconds(1000);
    ESC_BL.writeMicroseconds(1000);
    delay(3);                                                               //Wait 3 milliseconds before the next loop.
  }
  //Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
  gyro_offset[X] /= 2000;                                                 //Divide the roll total by 2000.
  gyro_offset[Y] /= 2000;                                                 //Divide the pitch total by 2000.
  gyro_offset[Z] /= 2000;                                                 //Divide the yaw total by 2000.
}

void readSensor() {
    Wire.beginTransmission(0x68); // Start communicating with the MPU-6050
    Wire.write(0x3B);                    // Send the requested starting register
    Wire.endTransmission();              // End the transmission
    Wire.requestFrom(0x68,14);    // Request 14 bytes from the MPU-6050

    // Wait until all the bytes are received
    while(Wire.available() < 14);

    acc_raw[X]  = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the acc_raw[X] variable
    acc_raw[Y]  = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the acc_raw[Y] variable
    acc_raw[Z]  = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the acc_raw[Z] variable
    temperature = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the temperature variable
    gyro_raw[X] = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the gyro_raw[X] variable
    gyro_raw[Y] = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the gyro_raw[Y] variable
    gyro_raw[Z] = Wire.read() << 8 | Wire.read(); // Add the low and high byte to the gyro_raw[Z] variable

//    if(count == 2000){
//    gyro_raw[X] -= gyro_offset[X];                                       //Only compensate after the calibration.
//    gyro_raw[Y] -= gyro_offset[Y];                                       //Only compensate after the calibration.
//    gyro_raw[Z] -= gyro_offset[Z];                                       //Only compensate after the calibration.
//  }
}
>>>>>>> Stashed changes
