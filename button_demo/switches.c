#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "switches.h"
#include "led.h"

char switch_state_down, switch_state_changed;
short low_music_note;
short how_fast;
char speed;

static char 
switch_update_interrupt_sense()
{
  
  char p1val = P2IN;                /* PORT P2 input. Get the value */
                                    /* update switch interrupt to detect changes from current buttons */
     P2IES |= (p1val & SWITCHES);    /* PORT P2 interrupt edge. select if switch up, sense down */
     P2IES &= (p1val | ~SWITCHES);   /* PORT P2 interrupt edge. if switch down, sense up */
     
  return p1val;
}

void 
switch_init()			/* setup SWITCHES = 0011 */
{  
  P2REN |= SWITCHES;	       /* = BIT 0011  PORT P2 Resistor enable*/
  P2IE = SWITCHES;	       /* = BIT 0011  PORT P2 interrupt enable */
  P2OUT |= SWITCHES;	       /* = BIT 0011  PORT P2 OUTPUT */
  P2DIR &= ~SWITCHES;	       /* = BIT 1100  PORT P2 Direction */

  switch_update_interrupt_sense(); 
  switch_interrupt_handler();     /*   to initially read the switches */ 
}

void switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
    char button1 = (p1val & SW1) ? 0:1;
    char button2 = (p1val & SW2) ? 0:1;
    char button3 = (p1val & SW3) ? 0:1;
    char button4 = (p1val & SW4) ? 0:1;
    
    if(button1){
      low_music_note = 11110; 
      switch_state_down = button1;
      speed = 40;
      led_update();
     // led_blinkTimer();
    }
    if(button2){
      low_music_note = 10100;
      speed = 20;
      switch_state_down = button2;
      led_update();
    }
    if(button3){
      low_music_note = 1111;
      speed = 10;
      switch_state_down = button3;
      led_update();
    }
    if(button4){
      low_music_note = 1000;
      speed = 5;
      switch_state_down = button4;
      led_update();
    }
}
