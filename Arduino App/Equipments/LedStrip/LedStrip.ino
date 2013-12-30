/*
---------------------------------------------------------------------------------------------------------------------------------------
(C)2013 Thomas AUGUEY <contact@aceteam.org>
---------------------------------------------------------------------------------------------------------------------------------------
This file is part of Arduino Project (AceTeaM).

This code is free: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with WebFrameWork.  If not, see <http://www.gnu.org/licenses/>.
---------------------------------------------------------------------------------------------------------------------------------------
*/

#define REDPIN 5
#define GREENPIN 6
#define BLUEPIN 3

typedef struct _FADE_COLORS_PARAM{
  int fanSpeed;
}FADE_COLORS_PARAM;

typedef struct _FADE2_COLORS_PARAM{
  int fanSpeed;
  int v,inc,color;
  int rgb_pin[3];
}FADE2_COLORS_PARAM;
    
typedef void (*CALLBACK)(void*);
struct {
  union {
    FADE_COLORS_PARAM fade;
  };
  //
  CALLBACK loop2;
  void (*loop)(void*);
  void (*setup)(void*);
}g_param;

void fadeColors_setup(void*);
void fadeColors_loop(FADE_COLORS_PARAM*);
void fadeColors2_setup(void*);
void fadeColors2_loop(void*);
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  //
  g_param.loop2  = (CALLBACK)fadeColors_loop;
  g_param.setup = fadeColors_setup;
  
  g_param.setup(&g_param);
}

void loop() {
  g_param.loop(&g_param);
}

/*
  Version bloquante du Fade
*/

void fadeColors_setup(void* _param){
  FADE_COLORS_PARAM* param = (FADE_COLORS_PARAM*)_param;
  param->fanSpeed = 9;
}

void fadeColors_loop(void* _param){
  FADE_COLORS_PARAM* param = (FADE_COLORS_PARAM*)_param;
 int r,b,g;
  // fade from blue to violet
  for (r = 0; r < 256; r++) { 
    analogWrite(REDPIN, r);
    delay(param->fanSpeed);
  } 
  // fade from violet to red
  for (b = 255; b > 0; b--) { 
    analogWrite(BLUEPIN, b);
    delay(param->fanSpeed);
  } 
  // fade from red to yellow
  for (g = 0; g < 256; g++) { 
    analogWrite(GREENPIN, g);
    delay(param->fanSpeed);
  } 
  // fade from yellow to green
  for (r = 255; r > 0; r--) { 
    analogWrite(REDPIN, r);
    delay(param->fanSpeed);
  } 
  // fade from green to teal
  for (b = 0; b < 256; b++) { 
    analogWrite(BLUEPIN, b);
    delay(param->fanSpeed);
  } 
  // fade from teal to blue
  for (g = 255; g > 0; g--) { 
    analogWrite(GREENPIN, g);
    delay(param->fanSpeed);
  } 
}

/*
  Version non bloquante du Fade
*/
void fadeColors2_setup(void* _param){
  FADE2_COLORS_PARAM* param = (FADE2_COLORS_PARAM*)_param;
  param->fanSpeed = 9;
  param->inc = 1;
  param->color = 0;
  param->v = 0;
  param->rgb_pin[0] = REDPIN;
  param->rgb_pin[1] = GREENPIN;
  param->rgb_pin[2] = BLUEPIN;
}

void fadeColors2_loop(void* _param){
  FADE2_COLORS_PARAM* param = (FADE2_COLORS_PARAM*)_param;
  param->v += param->inc;
  if(param->v > 255 || param->v < 0){
    param->inc = -param->inc;
    param->color = (param->color+1) % 3;
  }
  analogWrite(param->rgb_pin[param->color], param->v);
  delay(param->fanSpeed);
}

