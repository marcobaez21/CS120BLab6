/*	Author: Marco Baez
 *  Partner(s) Name: NA
 *	Lab Section: 021
 *	Assignment: Lab #6  Exercise #2
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

enum States{init, lightA, waitA, lightB, waitB, lightC, waitC}state;
unsigned char temp = 0x00;
unsigned char temp2 = 0x00;

void Tick(){
	switch(state){
		case init:
			state=lightA;
			break;
		case lightA:
			if(temp){
				state=waitA;}
			else{
				state=lightB;}
			break;
		case waitA:
			if(temp){
				state=lightA;}
			else{
				state=waitA;}
			break;
		case lightB:
			if(temp){
				state=waitB;}
			else{
				state=lightC;}
			break;
		case waitB:
			if(temp){
				state=lightB;}
			else{
				state=waitB;}
			break;
		case lightC:
			if(temp){
				state=waitC;}
			else{
				state=lightA;}
			break;
		case waitC:
			if(temp){
				state=lightC;}
			else{
				state=waitC;}
			break;
	}

	switch(state){
		case lightA:
			temp2 = 0x01;
			break;
		case waitA:
			temp2 = 0x01;
			break;
		case lightB:
			temp2 = 0x02;
			break;
		case waitB:
			temp2 = 0x02;
			break;
		case lightC:
			temp2 = 0x04;
			break;
		case waitC:
			temp2 = 0x04;
			break;

	}
}

int main(void) {
    
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    TimerSet(300);
    TimerOn();
    state=init;

    while (1) {
	    temp=~PINA&0x08;
	    Tick();
	    while(!TimerFlag);
	    TimerFlag = 0;
	    PORTC = temp;
    }
    return 0;
}
