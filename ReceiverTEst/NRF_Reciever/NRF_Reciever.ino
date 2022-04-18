// SimpleRx - the slave or the receiver
//Libraries =====================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
//=================================================

//Radio ===========================================
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
//===================================================

//Servo =============================================
//Values for ESC pins
byte escFL = 35;
byte escFR = 33;
byte escBL = 31;
byte escBR = 29;
// Initialize ESCs (Done as Servos to facilitate PWM signals)
Servo ESC_FL;
Servo ESC_FR;
Servo ESC_BL;
Servo ESC_BR;
//===================================================

void setup() {
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

  ESC_FR.writeMicroseconds(1000);
  ESC_FL.writeMicroseconds(1000);
  ESC_BR.writeMicroseconds(1000);
  ESC_BL.writeMicroseconds(1000);
  //================================================
}

//=============

void loop() {
<<<<<<< Updated upstream
    getData();
    showData();
    if(newData){
      ESC_FR.writeMicroseconds(map(dataReceived, 215, 255, 1000, 2000));
      ESC_FL.writeMicroseconds(1000);
      ESC_BR.writeMicroseconds(1000);
      ESC_BL.writeMicroseconds(1000);
    }
=======
  
  getData();
//  showData();
  M1 = mapped.throttle + mapped.yaw - mapped.pitch + mapped.roll;
  M2 = mapped.throttle + mapped.yaw - mapped.pitch - mapped.roll;
  M3 = mapped.throttle + mapped.yaw + mapped.pitch + mapped.roll;
  M4 = mapped.throttle + mapped.yaw + mapped.pitch - mapped.roll;

  Serial.print("After: ");
  Serial.print(M1);
  Serial.print(" ");
  Serial.print(M2);
  Serial.print(" ");
  Serial.print(M3);
  Serial.print(" ");
  Serial.print(M4);
  Serial.print("\n");
  
  ESC_FR.writeMicroseconds(1000 + minMax(M1,100,1000));
  ESC_FL.writeMicroseconds(1000 + minMax(M1,100,1000)+100);
  ESC_BR.writeMicroseconds(1000 + minMax(M1,100,1000));
  ESC_BL.writeMicroseconds(1000 + minMax(M1,100,1000)+200);

//  Serial.println( 
>>>>>>> Stashed changes
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
<<<<<<< Updated upstream
=======
        mapped.yaw = map( dataReceived.yaw, 0, 255, -100, 100 );
        mapped.pitch = map( dataReceived.pitch, 0, 255, -100, 100 );
        mapped.roll = map( dataReceived.roll, 0, 255, -100, 100 );
        mapped.throttle = map(dataReceived.throttle, 0, 255, 100, 800 );
//        Serial.print("Before: ");
//        Serial.print(mapped.yaw);
//        Serial.print(mapped.pitch);
//        Serial.print(mapped.roll);
//        Serial.print(mapped.throttle);
//        Serial.print("\n");
>>>>>>> Stashed changes
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.print("\nYaw: " );
        Serial.print((int)dataReceived.yaw);
        Serial.print("\nPitch: ");
        Serial.print((int)dataReceived.pitch);
        Serial.print("\nRoll: ");
        Serial.print((int)dataReceived.roll);
        Serial.print("\nThrottle: ");
        Serial.print((int)dataReceived.throttle);
        Serial.print("\n");
        newData = false;
    }
}
