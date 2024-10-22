/*********************************************************************

Jackson Philion, Oct.7.2024, jphilion@g.hmc.edu
For E155 Lab 4, Harvey Mudd College, taught by Prof Josh Brake.

This file encodes the top level functions which play the whole song,
play a note, and hold the songs (Fur Elise, shortTest, longTest, and
imperialMarch). 

It is critical that this file be used with a folder "lib" within the
source code, as a subfolder. This should contain e155_lab4.h, which
calls the 8 other files necessary to make this file run.

Note that a single variable defined within Startup requires the CMSIS
folders to be available in SEGGER. However, this code and the called
header files make no use of CMSIS.

See my full write up of this laboratory on my portfolio website here:
https://jacksonphilion.github.io/hmc-e155-portfolio/

*********************************************************************/

#include <stdio.h>
#include "lib/e155_lab4.h"

// Pitch in Hz, duration in ms
const int furElise[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	0}};

// 20 second test song that flops back and forth
const int longTest[][2] = {
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{500,1000},
{330,1000},
{0,0}
};

//Shorter test song
const int shortTest[][2] = {
{500,1000},
{330,1000},
{0,0}};

// NOTE: These notes may have incorrect sharp and flat names, I didn't realize until the end.
#define A3 220
#define B3f 233
#define B3 247
#define C4 262
#define D4f 277
#define D4 294
#define E4f 311
#define E4 330
#define F4 349
#define G4f 370
#define G4 392
#define A4f 415
#define A4 440
#define A4s 455
#define B4f 466
#define B4 494
#define C5 523
#define D5f 554
#define D5 587
#define E5f 622
#define E5 659
#define F5 698
#define G5f 741
#define G5 784
#define A5f 831
#define A5 880

// Custom Imperial March, see imperialMarch.txt in notesAndExtras for more
int imperialMarch[][2] = {
// First Section
{A4, 500},
{A4, 500},    
{A4, 500},
{F4, 350},
{C5, 150},  
{A4, 500},
{F4, 350},
{C5, 150},
{A4, 650},

{0, 500},

{E5, 500},
{E5, 500},
{E5, 500},  
{F5, 350},
{C5, 150},
{A4f, 500},
{F4, 350},
{C5, 150},
{A4, 650},

{0, 500},

// Second Section

{A5, 500},
{A4, 300},
{A4, 150},
{A5, 500},
{A5f, 325},
{G5, 175},
{G5f, 125},
{F5, 125},    
{G5f, 250},

{0, 325},

{A4s, 250},
{E5f, 500},
{D5, 325},  
{D5f, 175},  
{C5, 125},  
{B4f, 125},  
{C5, 250},  

{0, 350},

//Variant 1

{F4, 250},  
{A4f, 500},  
{F4, 350},  
{A4, 125},
{C5, 500},
{A4, 375},  
{C5, 125},
{E5, 650},

{0, 500},

// Repeat Second Section

{A5, 500},
{A4, 300},
{A4, 150},
{A5, 500},
{A5f, 325},
{G5, 175},
{G5f, 125},
{F5, 125},    
{G5f, 250},

{0, 325},

{A4s, 250},
{E5f, 500},
{D5, 325},  
{D5f, 175},  
{C5, 125},  
{B4f, 125},  
{C5, 250},  

{0, 350},

//Then Variant 2

{F4, 250},  
{A4f, 500},  
{F4, 375},  
{C5, 125},
{A4, 500},  
{F4, 375},  
{C5, 125},
{A4, 650},  

{0, 0}};

void playNote(uint32_t freq, uint32_t milliseconds) {
    if (freq>0){
        initTIM2_PWM(freq);                 // turn on PWM at given frequency "freq"
        delayMillis(milliseconds);          // leave the note on for time "milliseconds"
        initTIM2_PWM(0b0);                  // turn off PWM and TIM2 by passing in freq=0
    }
    else {delayMillis(milliseconds);}
}

void playSong(int songArray[][2]){
    /* This function takes in an array representing a song. The array should be formatted:
    {  {freq0,milSec0}, {freq1,milSec1}, etc. } */

    // Looping logic which actually plays a song
    int j = 0;
    while (!((songArray[j][1]==0)&(songArray[j][0]==0))) {
        // Add delay between similar notes for the imperial march
        if ((j!=0)&(songArray[j][0]==songArray[j-1][0])) {delayMillis(15);}
        playNote(songArray[j][0], songArray[j][1]);
        j++;
    }
}

int main(void) {
  // Start Clock, with built in PLL enable
  // Also, enable SYSCLK path out to TIM 2,3,6,7
  configureClock_AndTIM2_6();

  // Enable PWM output on Pin PA5 (defined in the function)
  pinOutputPWM();

  while (1) {
    playSong(imperialMarch);
    delayMillis(2000);
  }
}

/*************************** End of file ****************************/
