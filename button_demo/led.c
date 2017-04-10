#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "libTimer.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "switches.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;
char speed;
static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void buzzer_init(){
    timerAUpmode();
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7;
    P2SEL |= BIT6;
    P2DIR = BIT6;
}

void buzzer_set_period(short cycles)
{
    
    CCR0 = cycles;
    CCR1 = cycles >> 1;
}

void led_init()
{

  P1DIR |= LEDS;	// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  /* UPDATES THE BLINKY LIGHT */
  //if(low_music_note){
        
    // how_fast = 1;
   // led_blinkTimer();
   // }
   if (switch_state_changed == 1) {
        char ledFlags = 0; /* by default, no LEDs on */
    if(speed > 1){
   
  
        ledFlags = redVal[red_on] | greenVal[green_on];
        P1OUT &= (0xff^LEDS) | ledFlags;
        P1OUT |= ledFlags;
        led_changed = 0;
    }
    else {
        speed = 0;
        
    }
  
    // ledFlags |= switch_state_down ? LED_GREEN: 0;
     //ledFlags |= switch_state_down ? 0 : LED_RED;
     //how_fast = ledFlags;
     //P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
     //P1OUT |= ledFlags;         // set bits for on leds
     buzzer_set_period(low_music_note);
    // If P1OUT = 0000, LED1 Displays Red; If P1OUT = 0110, LED2 Displays Green
   }
    //switch_state_changed = 0;
  // 
}
void led_blinkTimer(){
  
}


