#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "MPU6050_6Axis_MotionApps20.h"
//#include <MPU6050.h>
//#include <MPU9250.h>
 #include <Servo.h>  
 #include<I2Cdev.h>
 int i = 1;
#define LED_PIN 13
bool blinkState = true;
AudioPlaySdWav           playWav1;
// Use one of these 3 output types: Digital I2S, Digital S/PDIF, or Analog DAC
AudioOutputI2S           audioOutput;
//AudioOutputSPDIF       audioOutput;
//AudioOutputAnalog      audioOutput;
AudioConnection          patchCord1(playWav1, 0, audioOutput, 0);
AudioConnection          patchCord2(playWav1, 1, audioOutput, 1);
AudioControlSGTL5000     sgtl5000_1;

// Use these with the Teensy Audio Shield
//define SDCARD_CS_PIN    10
//define SDCARD_MOSI_PIN  7
//define SDCARD_SCK_PIN   14

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

// Use these for the SD+Wiz820 or other adaptors
//#define SDCARD_CS_PIN    4
//#define SDCARD_MOSI_PIN  11
//#define SDCARD_SCK_PIN   13
int button1, button2, button3;


MPU6050 sensor ;

int16_t ax, ay, az ;

int16_t gx, gy, gz ; 
float y = 0.0;

void setup ( ){ 


Wire.begin ( );

Serial.begin  (9600); 

Serial.println  ( "Initializing the sensor" ); 

sensor.initialize ( ); 

Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 

delay (1000); 

Serial.println ( "Taking Values from the sensor" );

delay (1000);
pinMode(LED_PIN, OUTPUT);
  pinMode(30, INPUT_PULLDOWN);
pinMode(31, INPUT_PULLDOWN);
pinMode(32, INPUT_PULLDOWN);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(8);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

}

void playFile(const char *filename)
{
  Serial.print("Playing file: ");
  Serial.println(filename);

  // Start playing the file.  This sketch continues to
  // run while the file plays.
  playWav1.play(filename);

  // A brief delay for the library read WAV info
  delay(5);

  // Simply wait for the file to finish playing.
  while (playWav1.isPlaying()) {
    // uncomment these lines if you audio shield
    // has the optional volume pot soldered
    //float vol = analogRead(15);
    //vol = vol / 1024;
    // sgtl5000_1.volume(vol);
  }
}


void loop ( ) 

{ 
button1 = digitalRead(30);
button2 = digitalRead(31);
button3 = digitalRead(32);
sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);

ax = map (ax, -17000, 17000, 0, 180) ;

Serial.println (ax);

//sg90.write (ax); 

delay (200);

//if((mpuPitch<=-62|| mpuPitch>=-58) && (mpuRoll<=-2 || mpuRoll>=0)){
if (button1==1 && button2==1 && button3==1){
  if(ax-y>=20){
    if(ax-y>=20 && ax-y<=75){
    playFile("HIHATS.wav"); }
    else{
      playFile("HIHATL.wav");
      }// WORKS
    }
} else if(button1==1 && button2==1){
     if(ax-y>=20){
     if(ax-y>=20 && ax-y<=75){
    playFile("CRASHS.wav"); }
    else{
      playFile("CRASHL.wav");
      } }// WORKS
} else if(button1==1 && button3==1){
  if(ax-y>=20){
    if(ax-y>=20 && ax-y<=75){
    playFile("HITOM2S.wav"); }
    else{
      playFile("HITOM2L.wav");
      }} //FIX IT
} else if(button1==1){
  if(ax-y>=20){
     if(ax-y>=20 && ax-y<=75){
    playFile("LOWTOM1S.wav"); }
    else{
      playFile("LOWTOM1L.wav");
      }} // WORKS // filenames are always uppercase 8.3 format
  //delay(500);
} else if(button2==1){
  if(ax-y>=20){
    if(ax-y>=20 && ax-y<=75){
    playFile("KD1S.wav"); }
    else{
      playFile("KD1.wav");
      }} // WORKS  // filenames are always uppercase 8.3 format
  //delay(500);
} else if(button3==1){ //WORKS
  if(ax-y>=20){
    if(ax-y>=20 && ax-y<=75){
    playFile("SNARE1S.wav"); }
    else{
      playFile("SNARE1L.wav");
      } }

  //delay(500);
}
if(button2==1 && button3==1){
     playFile("DRUMSET.wav");// filenames are always uppercase 8.3 format
    }
y = ax;



}
