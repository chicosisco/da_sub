; This assembly code connects a switch 2 (SW2) to PORTC2, and connects PORTB2 to an LED. When the switch closes, 
; PORC2 gets pull down and sees a zero value, which triggers PB2 to go high and turn off the LED for a about 1.25s.
; This switch is control by a push down switch, so when the user press down on the swithc the LED turns on.
;
; DA2A_part_2.asm
;
; Created: 3/2/2019 3:59:44 AM
; Author : Francisco Mata Carlos
;
.org 0

.include <m328pdef.inc>

	;CBI DDRC, 2   ;make PC2 an input
	CBI DDRC, 2   ;make PC2 an input
	;SBI DDRB, 2   ;make PB2 an output
	SBI DDRB, 2   ;make PB2 an output

AGAIN: SBIS PINC, 2  ;skip next if PC2 is high
;AGAIN: SBIS PINC, 2  ;skip next if PC2 is high

	RJMP OVER     ; jump to lable OVER	
	SBI PORTB, 2   
	RJMP AGAIN    ; jump to label AGAIN

OVER: CBI PORTB, 2  ; make port B2 high
;OVER: SBI PORTB, 2  ; make port B2 high
    
    
	LDI R20,5 ;set clock prescaler to 1024
	STS TCCR1B,R20

	begin:
	LDI R20,0x00 ;resetting the counter to 0
	STS TCNT1H,R20
	STS TCNT1L,R20

delay:
	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28

	CPI R28,0x4A ;comparing if lower 8 bits of timer is 0x4A
	BRSH body ;if lower bits of timer have reached desired amount, check the upper bits

	RJMP delay ;otherwise, keep checking lower bits

body:
	CPI R29,0x4C ;check to see if upper timer bits have reached the desired value
	BRLT delay ;if not, recheck the lower bits
	RET ;once the timer reached the desired value, toggle the LED

	RJMP AGAIN    ; jump to label AGAIN
	