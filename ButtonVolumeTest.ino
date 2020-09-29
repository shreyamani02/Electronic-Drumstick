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
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playWav1;       //xy=65,166
AudioAmplifier           amp2;           //xy=233,168
AudioAmplifier           amp1;           //xy=241,127
AudioMixer4              mixer1;         //xy=384,180
AudioOutputI2S           audioOutput;    //xy=547,230
AudioConnection          patchCord1(playWav1, 0, amp1, 0);
AudioConnection          patchCord2(playWav1, 1, amp2, 0);
AudioConnection          patchCord3(amp2, 0, mixer1, 1);
AudioConnection          patchCord4(amp1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, audioOutput, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=405,433
// GUItool: end automatically generated code

// GUItool: end automatically generated code

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
const int drum1 = 33;
const int drum2 = 34;
const int drum3 = 35;
const int drum4 = 36;
const int drum5 = 37;
const int drum6 = 38;
const int drum7 = 39;
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
pinMode(drum1, OUTPUT);
pinMode(drum2, OUTPUT);
pinMode(drum3, OUTPUT);
pinMode(drum4, OUTPUT);
pinMode(drum5, OUTPUT);
pinMode(drum6, OUTPUT);
pinMode(drum7, OUTPUT);

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

if (button2==1 && button3==1){
  if(ax-y>=20){

    digitalWrite(drum7, HIGH);
digitalWrite(drum1, LOW);
digitalWrite(drum2, LOW);
digitalWrite(drum3, LOW);
digitalWrite(drum4, LOW);
digitalWrite(drum5, LOW);
digitalWrite(drum6, LOW);
      amp1.gain((ax-y)/50);
       amp2.gain((ax-y)/50);
    playFile("HIHAT.wav"); 
             }// WORKS
    
} else if(button1==1 && button2==1){
     if(ax-y>=15){
       
      digitalWrite(drum4, HIGH);
digitalWrite(drum1, LOW);
digitalWrite(drum2, LOW);
 amp1.gain((ax-y)/50);
         amp2.gain((ax-y)/50);
      playFile("CRASH.wav");
      }// WORKS
} else if(button1==1 && button3==1){
  if(ax-y>=15){
     //FIX IT
    digitalWrite(drum5, HIGH);
digitalWrite(drum1, LOW);
digitalWrite(drum3, LOW);
  amp1.gain((ax-y)/50);
       amp2.gain((ax-y)/50);
    playFile("HITOM2.wav");}
} else if(button1==1){
  if(ax-y>=15){
    
     digitalWrite(drum6, HIGH);
digitalWrite(drum2, LOW);
digitalWrite(drum3, LOW);
  amp1.gain((ax-y)/50); 
       amp2.gain((ax-y)/50);
     playFile("LOWTOM1.WAV");} // WORKS // filenames are always uppercase 8.3 format
  //delay(500);
} else if(button2==1){
  if(ax-y>=15){
      digitalWrite(drum1, HIGH);
     amp1.gain((ax-y)/220);
      amp2.gain((ax-y)/220);
    playFile("KD1.WAV");
   } // WORKS  // filenames are always uppercase 8.3 format
  //delay(500);
} else if(button3==1){ //WORKS
  if(ax-y>=15){
      digitalWrite(drum2, HIGH);
      amp1.gain( (ax-y)/50);
       amp2.gain((ax-y)/50);
    playFile("SNARE1.WAV");
    } // filenames are always uppercase 8.3 format
  //delay(500);
}
else{
  digitalWrite(drum1, LOW);
digitalWrite(drum2, LOW);
digitalWrite(drum3, LOW);
digitalWrite(drum4, LOW);
digitalWrite(drum5, LOW);
digitalWrite(drum6, LOW);
digitalWrite(drum7, LOW);
}
if(button1 ==1 && button2==1 && button3==1 ){
  if(ax-y>=15){
     digitalWrite(drum3, HIGH);
     digitalWrite(drum7, LOW);
    amp1.gain( (ax-y)/50);
       amp2.gain((ax-y)/50);
     playFile("DRUMSET.wav");
    // filenames are always uppercase 8.3 format
    }}
    else{
  digitalWrite(drum1, LOW);
digitalWrite(drum2, LOW);
digitalWrite(drum3, LOW);
digitalWrite(drum4, LOW);
digitalWrite(drum5, LOW);
digitalWrite(drum6, LOW);
digitalWrite(drum7, LOW);
}
y = ax;



}
