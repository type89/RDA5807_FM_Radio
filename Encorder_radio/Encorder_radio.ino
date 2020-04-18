#include <Arduino.h>
#include <Wire.h>
#include <Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <radio.h>
#include <RDA5807M.h>
#define FIX_BAND     RADIO_BAND_FMWORLD
#define FIX_VOLUME   12
#define FIX_STATION  7800

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define SW 4
#if (SSD1306_LCDHEIGHT != 32) // 
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

float channel = -0.5;
float catv_channel = -0.5;
int freq = 7800;
int mode = 1;
//int flag = 0;
unsigned long lastButtonPress = 0;

Encoder myEnc(2, 3);
RDA5807M radio;   

void setup()   {                
  //Serial.begin(9600);
  radio.init();
  radio.debugEnable();
  pinMode(SW, INPUT_PULLUP); 
  radio.setVolume(FIX_VOLUME);
  radio.setMono(false);
  radio.setMute(false);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

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
  switch (int(channel)) {
  case 0:
    station = "bayFM";
    freq = 7800;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 1:
    station = "NHK_CB";
    freq = 8070;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 2:
    station = "MiniFM";
    freq = 8760;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 3:
    station = "Nack5";
    freq = 7950;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 4:
    station = "TokyoFM";
    freq = 8000;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 5:
    station = "J-WAVE";
    freq = 8130;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 6:
    station = "NHK_TK";
    freq = 8250;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 7:
    station = "Yokohama";
    freq = 8470;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 8:
    station = "Tokyo_TM";
    freq = 8660;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 9:
    station = "InterFM";
    freq= 8970;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 10:
    station = "TBS_Radio";
    freq = 9050;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 11:
    station = "QR";
    freq = 9160;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 12:
    station = "RF";
    freq = 9240;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 13:
    station = "Nippon";
    freq = 9300;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 14:
    station = "Ichihara";
    freq = 7670;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 15:
    station = "FM Fuji";
    freq = 7860;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  }
  return;
}

void set_catv_channel(float catv_channel) {
  String station;
  int channel_no = int(catv_channel);
  switch (channel_no) {
  case 0:
    station = "C_InterFM";
    freq = 7750;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 1:
    station = "C_NHK1";
    freq = 7830;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 2:
    station = "C_bayFM";
    freq = 7890;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 3:
    station = "C_TokyoFM";
    freq = 8030;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 4:
    station = "C_Nack5";
    freq = 8100;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 5:
    station = "C_NHK2";
    freq = 8160;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 6:
    station = "C_EEW";
    freq = 8210;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 7:
    station = "C_NHK_FM";
    freq = 8310;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;
  case 8:
    station = "C_J-WAVE";
    freq = 8370;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 9:
    station = "C_Yokohama";
    freq = 8430;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 10:
    station = "C_TBS";
    freq = 8500;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 11:
    station = "C_QR";
    freq = 8600;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  case 12:
    station = "C_Nippon";
    freq = 8650;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break; 
  case 13:
    station = "C_RF";
    freq = 8700;
    radio.setBandFrequency(FIX_BAND, freq);
    set_oled(station, freq);
    break;    
  }
  return;
}


void set_manual_tunig(int freq) {
  String station = "Tuning..";
  radio.setBandFrequency(FIX_BAND, freq);
  if((freq % 10) == 0){
      set_oled(station, freq);
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
    //Serial.println(float_freq);
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
    if(mode == 3){
        display.setCursor(0, 17);  
        display.println("Tuning");  
      }
    display.display();   
}

void loop() {
  
  int btnState = digitalRead(SW);
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      switch (mode) {
      case 1:
        mode = 2;
        catv_channel = float(int(catv_channel)) - 0.5;
        break;  
      case 2:
        mode = 3;
        break;  
      case 3:
        mode = 1;
        channel = float(int(channel)) - 0.5;
        break;  
      }
      //Serial.println("mode ==> " + String(mode));
      set_mode_oled(mode);
     }
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
      if(mode == 3){
        freq = freq + 5;
       if(freq > 10800){
          freq = 7600;  
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
      if(mode == 3){
        freq = freq -5;
       if(freq < 7600){
          freq = 10800;  
          }
      }
    }
    oldPosition = newPosition;
    //Serial.println("newPosition ==> " + String(newPosition));
    //Serial.println("flag ==> " + String(flag));
    if(mode == 1){
      set_channel(channel);
      }
    if(mode == 2){
      set_catv_channel(catv_channel);
      }
    if(mode == 3){
      set_manual_tunig(freq);
      }
  }
}
