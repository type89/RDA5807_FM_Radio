#include <Arduino.h>
#include <Wire.h>
#include <Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <radio.h>
#include <RDA5807M.h>
#define FIX_BAND     RADIO_BAND_FMWORLD //RADIO_BAND_FM    //Radio Band -FM
#define FIX_VOLUME   5               //Audio Volume Level 5.
#define FIX_STATION  7800 //10050            //Station Tuned = 100.50 MHz.

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define SW 4
#if (SSD1306_LCDHEIGHT != 32) // 
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

float channel = -0.5;
float catv_channel = -0.5;
int mode = 1;
unsigned long lastButtonPress = 0;
Encoder myEnc(2, 3);
RDA5807M radio;   

void setup()   {                
  Serial.begin(9600);
  Serial.println("FM Radio");
  radio.init();
  radio.debugEnable();
  pinMode(SW, INPUT_PULLUP); 
  //radio.setBandFrequency(FIX_BAND, FIX_STATION);
  radio.setVolume(FIX_VOLUME);
  radio.setMono(false);
  radio.setMute(false);
  radio.setBassBoost(true);
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  //display.display();

   // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Arduino");
  display.setCursor(0, 17);
  display.println("FM Radio");
  display.display();
  delay(2000);
}

long oldPosition  = -999;

void set_channel(float channel) {
  String station;
  int freq;
  int channel_no = int(channel);
  //Serial.println("channel_n==>" + String(channel_no));
  switch (channel_no) {
  case 0:
    station = "bayFM";
    freq = 7800;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 1:
    station = "NHK_CB";
    freq = 8070;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 2:
    station = "MiniFM";
    freq = 8760;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 3:
    station = "Nack5";
    freq = 7950;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 4:
    station = "TokyoFM";
    freq = 8000;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 5:
    station = "J-WAVE";
    freq = 8130;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 6:
    station = "NHK_TK";
    freq = 8250;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 7:
    station = "Yokohama";
    freq = 8470;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 8:
    station = "Tokyo_TM";
    freq = 8660;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 9:
    station = "InterFM";
    freq = 8970;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 10:
    station = "TBS_Radio";
    freq = 9050;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 11:
    station = "QR";
    freq = 9160;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 12:
    station = "RF";
    freq = 9240;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 13:
    station = "Nippon";
    freq = 9300;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 14:
    station = "Ichihara";
    freq = 7670;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 15:
    station = "FM Fuji";
    freq = 7860;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  default:
    Serial.println("case==>" + String(channel_no));
    // どのcaseにも一致しなかったとき実行される
  }
  return;
}

void set_catv_channel(float catv_channel) {
  String station;
  int freq;
  int channel_no = int(catv_channel);
  //Serial.println("channel_n==>" + String(channel_no));
  switch (channel_no) {
  case 0:
    station = "C_InterFM";
    freq = 7750;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 1:
    station = "C_NHK1";
    freq = 7830;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 2:
    station = "C_bayFM";
    freq = 7890;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 3:
    station = "C_TokyoFM";
    freq = 8030;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 4:
    station = "C_Nack5";
    freq = 8100;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 5:
    station = "C_NHK2";
    freq = 8160;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 6:
    station = "C_EEW";
    freq = 8210;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 7:
    station = "C_NHK_FM";
    freq = 8310;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 8:
    station = "C_J-WAVE";
    freq = 8370;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 9:
    station = "C_Yokohama";
    freq = 8430;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 10:
    station = "C_TBS";
    freq = 8500;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 11:
    station = "C_QR";
    freq = 8600;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 12:
    station = "C_Nippon";
    freq = 8650;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 13:
    station = "C_RF";
    freq = 8700;
    Serial.println("case==>" + String(channel_no));
    Serial.println(station);
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  default:
    Serial.println("case==>" + String(channel_no));
    // どのcaseにも一致しなかったとき実行される
  }
  return;
}

void set_oled(String station, int freq){
    display.clearDisplay();
   
    display.setTextSize(2);
    display.setTextColor(WHITE);

    display.setCursor(0, 0);
    display.println(station);
    display.setCursor(0, 17);
    float float_freq = float(freq) / 100;
    
    display.println(String(float_freq) + "MHz");
    display.display();   
}

void set_mode_oled(int mode){
    display.clearDisplay();
   
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("mode >>");
    if(mode == 1){
       display.setCursor(0, 17);  
       display.println("nomal");    
      }
    if(mode == 2){
        display.setCursor(0, 17);  
        display.println("CATV");  
      }
    display.display();   
}
void loop() {
  
  int btnState = digitalRead(SW);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 50ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > 50) {
      //Serial.println("Button pressed!");
      if(mode == 1){
        mode = 2;
        catv_channel = float(int(catv_channel)) - 0.5;
      }
      else{
        mode = 1;
        channel = float(int(channel)) - 0.5;
      }
      //Serial.println("mode ==> " + String(mode));
      set_mode_oled(mode);
     }
    // Remember last button press event
    lastButtonPress = millis();
  }
   
  long newPosition = myEnc.read();

  if (newPosition != oldPosition) {
    if(newPosition > oldPosition){
      if(mode == 1){
        channel = channel + 0.5;
        if(channel > 15.5){
          channel = -0.5;
          }
      }
      if(mode == 2){
        catv_channel = catv_channel + 0.5;
       if(catv_channel> 13.5){
          catv_channel = -0.5;  
          }
      }
    }else if(newPosition < oldPosition){
      if(mode == 1){
        channel = channel - 0.5;
        if(channel < 0){
          channel = 15.5;
          }
        }
      if(mode == 2){
        catv_channel = catv_channel - 0.5;
        if(catv_channel < 0){
          catv_channel = 13.5;
        }  
      }
    }
    oldPosition = newPosition;
    //Serial.println("newPosition ==> " + String(newPosition));
    if(mode == 1){
      set_channel(channel);
      }
    if(mode == 2){
      set_catv_channel(catv_channel);
      }
  }
}
