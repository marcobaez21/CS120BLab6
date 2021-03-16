/*	Author: Marco Baez
 *  Partner(s) Name: NA
 *	Lab Section: 021
 *	Assignment: Lab #6  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: Unfortunately i think after days of trying to debug that either the micro usb cable or programmer is bad because no matter what i get a red light, Will ask about it on tuesdays lab
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States{init, lightA, lightB, lightC}state;
unsigned char temp = 0x00;

void Tick(){
	switch(state){
		case init:
			state=lightA;
			break;
		case lightA:
			state=lightB;
			break;
		case lightB:
			state=lightC;
			break;
		case lightC:
			state=lightA;
			break;
	}

	switch(state){
		case lightA:
			temp = 0x01;
			break;
		case lightB:
			temp = 0x02;
			break;
		case lightC:
			temp = 0x03;
			break;
	}
}

int main(void) {
    
    DDRB = 0xFF; PORTB = 0x00;

    TimerSet(1000);
    TimerOn();
    state=init;

    while (1) {
	    Tick();
	    while(!TimerFlag);
	    TimerFlag = 0;
	    PORTB = temp;
    }
    return 0;
}
