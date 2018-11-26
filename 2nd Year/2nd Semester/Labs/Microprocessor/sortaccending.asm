
;<Program title>

;jmp start

;data


;code
;start: nop
	LXI H, 204Fh ; Load the total no of bits in the M register
	MOV B, M ; Take B as the counter
	DCR B ; Decrement the counter
	INX H ; Increment the content of (H)(L) register pair

LOOP: 	MOV A, M ; Move the content o M register to accumulator
	MOV D, H
	MOV E, L ; Move the (H)(L) register pair to (D)(E)
	INX H ; Increment the content of (H)(L) register pair

LOOP2: 	CMP M ; Compare the data of M with Accumulator
	JC LOOP1 ; Jump on carry to Loop1
	MOV C, M
	MOV M, A
	MOV A, C
	STAX D ; Swap the content of M and Accumulator

LOOP1: 	INX H ; Increment the content of (H)(L) register pair
	DCR B ; Decrement the content of B register
	JNZ LOOP2 ; Jump on no zero to Loop2

hlt

