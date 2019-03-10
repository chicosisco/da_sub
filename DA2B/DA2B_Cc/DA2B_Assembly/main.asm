;
; DA2B_Assem.asm
;
; Created: 3/9/2019 2:06:22 AM
; Author : Francisco Mata Carlos
;

.include <m328pdef.inc>
.ORG 0  ;location for reset
JMP MAIN
.ORG 0x02 ;location external interrupt 0
JMP EX0_ISR
MAIN:
	SBI DDRB, 5 ;setting PB5 as output
	SBI PORTB, 5 ;settng PB5 high so led is off
	LDI R20, HIGH(RAMEND)
	OUT SPH, R20
	LDI R20, LOW(RAMEND)
	LDI R20, 0X2  ;initializing stack 

	LDI R20, 0X2 ;make INT0 falling edge triggered
	STS EICRA, R20 
	SBI DDRB, 4  ;set PORTB4 as output
	SBI PORTB, 4 ;set PORTB4 high to keep led off until interrupt
	
	SBI PORTD, 2 ;pull-up activated
	LDI R20, 1<<INT0 ; enable INT0
	OUT EIMSK, R20 ;masking specific bit

	SEI ; enable interrupts
	
HERE: JMP HERE
	
EX0_ISR:
	IN R21, PORTB ;PORTB an input
	LDI R22, (1<<4)  ;00100000
	EOR R21, R22 ;toggl led
	OUT PORTB, R21 ;turn on led
	rcall delay_1s
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_50ms
	RETI ;return to next instruction after interrupt

;=======================================================================================================================
; Below is the time delay subroutine used for the code above
;
;=======================================================================================================================
delay_1s: 
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	rcall delay_100ms
	ret

delay_100ms:
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	ret

delay_50ms:
    rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	rcall delay_10ms
	ret

delay_10ms:
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	rcall delay_1ms
	ret

delay_1ms: ;1ms per loop
	rcall delay_1ms_16
	rcall delay_1ms_16
	rcall delay_1ms_16
	rcall delay_1ms_16
	ret

delay_1ms_16:
	push r16 ;save the value in r16
	ldi  r16, 249	;3984 cycles
delay_1a: 
	nop	;1 cycle
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	dec  r16
	brne delay_1a ;2 cycles
	pop  r16 ;restore the value in r16
	ret

