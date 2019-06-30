/****************************

  (working) title: Wave Translator (receiving-sketch)
  date: 29-06-2018
  author: Devon Ward
  website: https://devon-ward.com
  description: sketch to receive 3-axis acceleration data
  from a Arduino 1 with xbee and translate data into
  disc motor movements.
  
  notes: project was created in a week during the 
  2018 Digital Naturalism Conference in Thailand. 

  link for Xbee setup:
  https://learn.sparkfun.com/tutorials/xbee-wifi-hookup-guide/all
  
  usage: use this code however you like.

******************************/

String sentDataString = "";

unsigned long previousMillis = 0; 
const long interval = 60;

int motorPinX1 = 3;         // pin for motor 1, x-axis top motor
int motorPinX2 = 5;         // pin for motor 2, x-axis bottom motor
int motorPinY1 = 6;         // pin for motor 3, y-axis top motor
int motorPinY2 = 8;         // pin for motor 4, y-axis bottom motor
int motorPinZ1 = 10;        // pin for motor 5, z-axis top motor
int motorPinZ2 = 11;        // pin for motor 6, z-axis bottom motor

int motorValX1 = 0;         
int motorValX2 = 0;
int motorValY1 = 0;
int motorValY2 = 0;
int motorValZ1 = 0;
int motorValZ2 = 0;

String xString = "";
String yString = "";
String zString = "";

int x = 0;
int xSum = 0;
int xAvg = 0;
int y = 0;
int ySum = 0;
int yAvg = 0;
int z = 0;
int zSum = 0;
int zAvg = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("starting...");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
    if (Serial.available() > 0) {

        // take 5 readings and then average them to get a more stable value
        for (int i=0; i<5; i++) {
          String xString  = Serial.readStringUntil(',');
          Serial.read(); 
          String yString = Serial.readStringUntil(',');
          Serial.read();
          String zString  = Serial.readStringUntil(';');
          //sentDataString = Serial.readStringUntil(';');
          
          x = xString.toInt();
          y = yString.toInt();
          z = zString.toInt();
          
          xSum = xSum + x;
          ySum = ySum + y;
          zSum = zSum + z; 
        }
        xAvg = xSum/5;
        yAvg = ySum/5;
        zAvg = zSum/5;
        // sends positive x values to motor 1 and negative x values to motor 2 
        if (xAvg >= 0 ) {
          motorValX1 = map(xAvg, 0, 600, 0, 255);
          if (motorValX1 > 255) motorValX1 = 255;
          motorValX2 = 0;
        } else {
          motorValX2 = map(abs(xAvg), 0, 600, 0, 255);
          if (motorValX2 > 255) motorValX2 = 255;
          motorValX1 = 0;
        }
        // sends positive y values to motor 3 and negative y values to motor 4 
        if (yAvg >= 0 ) {
          motorValY1 = map(yAvg, 0, 600, 0, 255);
          if (motorValY1 > 255) motorValY1 = 255;
          motorValY2 = 0;
        } else {
          motorValY2 = map(abs(yAvg), 0, 600, 0, 255);
          if (motorValY2 > 255) motorValY2 = 255;
          motorValY1 = 0;
        }
        // sends positive z values to motor 5 and negative x values to motor 6 
        if (zAvg >= 0 ) {
          motorValZ1 = map(zAvg, 0, 600, 0, 255);
          if (motorValZ1 > 255) motorValZ1 = 255;
          motorValZ2 = 0;
        } else {
          motorValZ2 = map(abs(zAvg), 0, 600, 0, 255);
          if (motorValZ2 > 255) motorValX2 = 255;
          motorValZ1 = 0;
        }

        analogWrite(motorPinX1, motorValX1);
        analogWrite(motorPinX2, motorValX2);
        analogWrite(motorPinY1, motorValY1);
        analogWrite(motorPinY2, motorValY2);
        analogWrite(motorPinZ1, motorValZ1);
        analogWrite(motorPinZ2, motorValZ2); 
         
        Serial.print(xAvg);
        Serial.print(", ");
        Serial.print(yAvg);
        Serial.print(", ");
        Serial.println(zAvg);
        xSum = 0;
        ySum = 0;
        zSum = 0;
        xAvg = 0;
        yAvg = 0;
        zAvg = 0;
  
    }  
  }
}
