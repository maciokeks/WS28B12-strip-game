/*
MIT License

Copyright (c) 2021 maciokeks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#include <FastLED.h>
#define LED_PIN D7
#define LED_NUM 93 // number of leds
CRGB pixels[LED_NUM];
const int strip_len = 40; // number of leds
unsigned int bounce_times = 1;
unsigned int score = 1;
const byte but_pin = D8;
unsigned int snake_s = 150;
bool is_clicked = false;
bool snake_bounce = false;
#define buzzer_pin D5
//Variables with fresh positions of snake
int snake_location[] = {0,0,0};
int rand_num[] = {0,0,0,0,0};
//Variables saved in a moment of interrupt
int snake_location_new[] = {0,0,0};
int rand_num_new[] = {0,0,0,0,0};
bool on_buzzer = true; // Turn on or off sound effects

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
void setup() {
  Serial.begin(115200);
  pinMode(buzzer_pin,OUTPUT);
  FastLED.addLeds<WS2812B,LED_PIN,GRB>(pixels,LED_NUM);
  FastLED.setBrightness(20);
  FastLED.clear();
  Serial.println("--- Starting game ---");
  pinMode(but_pin,INPUT);
  attachInterrupt(digitalPinToInterrupt(but_pin),INT1, HIGH);
  bounce_times = 0;
  score = 0;
  Serial.println(bounce_times);
  Serial.println(score);
  Game_red_strip(strip_len); //Generate location for red strip 
}
void Game(const int strip_length,int snake_speed,int length_tail){
  for(int i=0;i<strip_length;i++){
    if(is_clicked == true){
      Game_check(strip_len); 
      goto game_check;
    }
    pixels[rand_num[0]].setRGB(255,0,0);
    pixels[rand_num[1]].setRGB(255,0,0);
    pixels[rand_num[2]].setRGB(255,0,0);
    pixels[rand_num[3]].setRGB(255,0,0);
    pixels[rand_num[4]].setRGB(255,0,0);
    FastLED.show();
    if(length_tail == 1){
      pixels[i].setRGB(0,255,0);
      FastLED.show();  
    }else if(length_tail == 2){
      pixels[i].setRGB(0,255,0);    
      pixels[i-1].setRGB(0,255,0);
      FastLED.show();
    }else if(length_tail ==3){
      pixels[i].setRGB(0,255,0);    
      pixels[i-1].setRGB(0,255,0);
      pixels[i+1].setRGB(0,255,0);
      FastLED.show();
      snake_location[0] = i+1;
      snake_location[1] = i;
      snake_location[2] = i-1;
    }else{
      Serial.println("error");
    }
     delay(snake_speed);
//   Serial.print(snake_location[0]);
//   Serial.print(snake_location[1]);
//   Serial.print(snake_location[2]);
//   Serial.println(" ");
     FastLED.clear();
  }
  for(int i=strip_length;i>0;i--){
    if(is_clicked == true){
      Game_check(strip_len); 
      goto game_check; 
      }
    pixels[rand_num[0]].setRGB(255,0,0);
    pixels[rand_num[1]].setRGB(255,0,0);
    pixels[rand_num[2]].setRGB(255,0,0);
    pixels[rand_num[3]].setRGB(255,0,0);
    pixels[rand_num[4]].setRGB(255,0,0);
    FastLED.show();
    if(length_tail == 1){
      pixels[i].setRGB(0,255,0);
      FastLED.show();
    }else if(length_tail == 2){
      pixels[i].setRGB(0,255,0);    
      pixels[i+1].setRGB(0,255,0);
      FastLED.show();
    }else if(length_tail == 3){
      pixels[i].setRGB(0,255,0);    
      pixels[i-1].setRGB(0,255,0);
      pixels[i+1].setRGB(0,255,0);
      FastLED.show();
      snake_location[0] = i+1;
      snake_location[1] = i;
      snake_location[2] = i-1;
    }else{
      Serial.println("error");
    }
    delay(snake_speed);
    //Serial.print(snake_location[0]);
    //Serial.print(snake_location[1]);
    //Serial.print(snake_location[2]);
    //Serial.println(" ");
    FastLED.clear();
  }
  game_check:
  bounce_times++;
  //Serial.println(bounce_times);
  //Serial.println("Goto check function");
}
void Game_red_strip(int strip_length){
   //Create location for red strip
   int random_num  = random (3,strip_length-3);
   rand_num[0] = random_num+2;
   rand_num[1] = random_num+1;
   rand_num[2] = random_num;
   rand_num[3] = random_num-1;
   rand_num[4] = random_num-2;   
 }
void loop() {
    Game(strip_len,snake_s,3);
}
ICACHE_RAM_ATTR void INT1(){
    is_clicked = true;
    //  Game_stop(strip_len); 
    Game_save_location(strip_len);
}
void Game_save_variable(){
  snake_location_new[0] = snake_location[0];
  snake_location_new[1] = snake_location[1];
  snake_location_new[2] = snake_location[2];
  rand_num_new[0] = rand_num[0];
  rand_num_new[1] = rand_num[1];
  rand_num_new[2] = rand_num[2];
  rand_num_new[3] = rand_num[3];
  rand_num_new[4] = rand_num[4];
}
void Game_save_location(int strip_length){
  Game_save_variable();//Save location
}
void Game_check(int strip_length){
    if(is_clicked == true){  
    FastLED.clear();
    Serial.println("Snake stopped");
    //snake
    pixels[snake_location_new[0]].setRGB(0,255,0);    
    pixels[snake_location_new[1]].setRGB(0,255,0);
    pixels[snake_location_new[2]].setRGB(0,255,0);
    //Serial.print(snake_location_new[1]); // For checking position of the snake
    //red strip
    pixels[rand_num_new[0]].setRGB(255,0,0);    
    pixels[rand_num_new[1]].setRGB(255,0,0);
    pixels[rand_num_new[2]].setRGB(255,0,0);
    pixels[rand_num_new[3]].setRGB(255,0,0);
    pixels[rand_num_new[4]].setRGB(255,0,0);
    FastLED.show();
    delay(1000);
    FastLED.clear();
    if(snake_location_new[0]<= rand_num_new[0] && snake_location_new[2]>=rand_num_new[4]){
      snake_s = snake_s - 10;
      if(score == 14){
        Serial.println("You win this game !!!");
        win_sound_end;
        snake_s = 150;
        score = 0;
      }
      win_sound();
      Serial.print("Speed of snake: ");
      Serial.print(snake_s);
      Serial.println(" ");
      fill_solid(pixels,strip_length,CRGB(0,255,0));
      FastLED.show();
      //Serial.println("Cool you win");
      Serial.print("Your score: ");
      Serial.print(score);
      Serial.println(" ");
      score++;
      delay(3000);
    }else{
      lose_sound();
      fill_solid(pixels,strip_length,CRGB(255,0,0));
      FastLED.show();
      Serial.println("Sorry but you didn't win");
      score = 0;
      snake_s = 150;
      delay(3000);
    }
    Game_red_strip(strip_len);
    is_clicked = false;
  }   
}
void win_sound(){
  if(on_buzzer == true){
  tone(buzzer_pin, 1000);
  delay(200);
  tone(buzzer_pin, 1400);
  delay(200);
  tone(buzzer_pin, 2000);
  delay(300);
  noTone(buzzer_pin);
  }
}
void win_sound_end(){
  if(on_buzzer == true){
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzer_pin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzer_pin);
  }
  }
}
void lose_sound(){
  if(on_buzzer == true){
  tone(buzzer_pin, 800);
  delay(200);
  tone(buzzer_pin, 500);
  delay(200);
  tone(buzzer_pin, 100);
  delay(300);
  noTone(buzzer_pin);
  }
}
