# 1 "c:\\00_MyData\\02_Youtube\\07_MusicMp3\\00_Source\\musicMp3\\musicMp3.ino"
/** Bare minimum example sketch for MP3 player.

 *

 *  Simply plays all tracks in a loop.

 *  It uses SoftwareSerial to connect to the module.

 *

 * @author James Sleeman,  http://sparks.gogo.co.nz/

 * @license MIT License

 * @file

 */
# 11 "c:\\00_MyData\\02_Youtube\\07_MusicMp3\\00_Source\\musicMp3\\musicMp3.ino"
# 12 "c:\\00_MyData\\02_Youtube\\07_MusicMp3\\00_Source\\musicMp3\\musicMp3.ino" 2
# 13 "c:\\00_MyData\\02_Youtube\\07_MusicMp3\\00_Source\\musicMp3\\musicMp3.ino" 2
# 14 "c:\\00_MyData\\02_Youtube\\07_MusicMp3\\00_Source\\musicMp3\\musicMp3.ino" 2

// Create the mp3 module object, 
//   Arduino Pin 8 is connected to TX of the JQ6500
//   Arduino Pin 9 is connected to one end of a  1k resistor, 
//     the other end of the 1k resistor is connected to RX of the JQ6500
//   If your Arduino is 3v3 powered, you can omit the 1k series resistor

SoftwareSerial mySerial(8, 9);
JQ6500_Serial mp3(mySerial);
//
const byte interruptPin = 2;
volatile byte state = 1;
byte stateTemp = 1;
//
enum
{
  Music_1 =1,
  Music_2,
 // Music_3,
  Num_Music,
};

void setup() {

  // Set Interrupt
  pinMode(interruptPin, 0x2);
  attachInterrupt(((interruptPin) == 2 ? 0 : ((interruptPin) == 3 ? 1 : -1)), changeMode, 2);
  //
  Serial.begin(9600);
  mySerial.begin(9600);
  mp3.reset();
  mp3.setVolume(7);
  mp3.setLoopMode(4);
  mp3.play();
}
void changeMode()
{
  state++;
  //delay(100);
  if(state >= Num_Music)
  {
    state = Music_1;
  }
 // mp3.playFileByIndexNumber(state); 
}
void loop() {
  // Do nothing, it's already playing and looping :-)
  if(mp3.getStatus() != 1)
  {
    mp3.playFileByIndexNumber(state);
  }
  if(stateTemp != state)
  {
    mp3.pause();
    stateTemp = state;
  }
  if(state == Music_1)
  {
    Serial.println("Music 1");
  }
  else if(state == Music_2)
  {
    Serial.println("Music 2");
  }
  //   else if(state == Music_3)
  // {
  //   Serial.println("Music 3");
  // }
}
