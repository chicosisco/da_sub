; This assembly code designs a delay subroutine to generate a waveform on PORTB.2 with 60% DC and 0.725sec period.
; This code takes advantage of the Timer Counter (TCNT) and the Timer Control Register (TCCR) in order preset a value,
; which will be used to compared with the registers and toggle a value or bit. 
; DA2A_AS1.asm
;
; Created: 3/2/2019 1:17:44 PM
; Author : Francisco Mata Carlos



.org 0
	LDI R16,4 ;representing PB2

	OUT DDRB, R16 ;enable PB2 as output

	LDI R17,4 ;used to set or reset PB2

	LDI R20,5 ;set clock prescaler to 1024
	STS TCCR1B,R20

begin:
	LDI R20,0x00 ;resetting the counter to 0
	STS TCNT1H,R20
	STS TCNT1L,R20

	RCALL delay    ;calling timer to wait for 435ms
	EOR R17,R16 ;XOR to toggle led
	OUT PORTB,R17

	LDI R20,0x00 ;resetting the counter to 0
	STS TCNT1H,R20
	STS TCNT1L,R20

	RCALL delay2 ;calling timer to wait for 290ms

	EOR R17,R16 ;XOR to toggle led
	OUT PORTB,R17
	RJMP begin ;repeat main loop

delay:
	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28

	 CPI R28,0x8C ;comparing if lower 8 bits of timer is 0x8C
	BRSH body ;if lower bits of timer have reached desired amount, check the upper bits

	RJMP delay ;otherwise, keep checking lower bits
body:
	CPI R29,0x1A ;check to see if upper timer bits have reached the desired value
	BRLT delay ;if not, recheck the lower bits
	RET ;once the timer reached the desired value, toggle the LED

delay2:

	LDS R29, TCNT1H ;loading upper bit of counter to R29
	LDS R28, TCNT1L ;loading lower bit of counter to R28

	 CPI R28,0xB2 ;comparing if lower 8 bits of timer is 0xB2
	BRSH body2 ;if lower bits of timer have reached desired amount, check the upper bits

	RJMP delay2 ;otherwise, keep checking lower bits
body2:
	CPI R29,0x11 ;check to see if upper timer bits have reached the desired value
	BRLT delay2 ;if not, recheck the lower bits
	RET ;once the timer reached the desired value, toggle the LED
