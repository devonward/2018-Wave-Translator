/****************************

  (working) title: Wave Translator (sending-sketch)
  date: 29-06-2018
  author: Devon Ward
  website: https://devon-ward.com
  description: sketch to read 3-axis acceleration data
  from a DIY weather buoy with the H3LIS331DL accelerometer
  and send data to another Arduino using two Xbees.
  
  notes: project was created in a week during the 
  2018 Digital Naturalism Conference in Thailand. 

  other sketches used here:
  + Sparkfun's example I2C sketch for the H3LIS331DL.
  + link: https://learn.sparkfun.com/tutorials/h3lis331dl-accelerometer-breakout-hookup-guide/all

  usage: use this code however you like.

******************************/

#include <Wire.h>
#include <SparkFun_LIS331.h>

LIS331 xl;

String dataString = "";
int16_t x, y, z;

unsigned long previousMillis = 0; 
const long interval = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(9,INPUT);       // Interrupt pin input
  Wire.begin();
  xl.setI2CAddr(0x19);    // This MUST be called BEFORE .begin() so 
                          //  .begin() can communicate with the chip
  xl.begin(LIS331::USE_I2C); // Selects the bus to be used and sets
                          //  the power up bit on the accelerometer.
                          //  Also zeroes out all accelerometer
                          //  registers that are user writable.
  // This next section configures an interrupt. It will cause pin
  //  INT1 on the accelerometer to go high when the absolute value
  //  of the reading on the Z-axis exceeds a certain level for a
  //  certain number of samples.
  xl.intSrcConfig(LIS331::INT_SRC, 1); // Select the source of the
                          //  signal which appears on pin INT1. In
                          //  this case, we want the corresponding
                          //  interrupt's status to appear. 
  xl.setIntDuration(50, 1); // Number of samples a value must meet
                          //  the interrupt condition before an
                          //  interrupt signal is issued. At the
                          //  default rate of 50Hz, this is one sec.
  xl.setIntThreshold(2, 1); // Threshold for an interrupt. This is
                          //  not actual counts, but rather, actual
                          //  counts divided by 16.
  xl.enableInterrupt(LIS331::Z_AXIS, LIS331::TRIG_ON_HIGH, 1, false);
                          // Enable the interrupt. Parameters indicate
                          //  which axis to sample, when to trigger
                          //  (in this case, when the absolute mag
                          //  of the signal exceeds the threshold),
                          //  which interrupt source we're configuring,
                          //  and whether to enable (true) or disable
                          //  (false) the interrupt.
  Serial.begin(115200);
}

void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis;
  
    xl.readAxes(x, y, z);  // The readAxes() function transfers the
                             //  current axis readings into the three
                             //  parameter variables passed to it.
  
    dataString = String(x) + "," + String(y) + "," + String(z) + ";";
    Serial.println(dataString);
    
  }
}
