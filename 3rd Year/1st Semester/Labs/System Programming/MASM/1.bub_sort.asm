.MODEL SMALL
.STACK 300H
.DATA
	msg1 db 10,13,'Enter the limit::$'
	msg2 db 10,13,'Enter the numbers::$'
	msg3 db 10,13,'The numbers in ascending order is::$'
	space db ' $'
	newline db 10,13,'$'
	count db ?
	tab1 db 20 dup(0)
.CODE
	printstring MACRO msg
	push AX
	push DX
	mov AH,09H
	mov DX,OFFSET msg
	int 21H
	pop DX
	pop AX
	ENDM
	MAIN PROC
	mov AX,@DATA
	mov DS,AX

	printstring msg1
	call readnumtoAX
	mov count,AL
	mov CL,count
	mov CH,00
	mov BX,1
	printstring msg2
	rdnxt:
		printstring newline
		call readnumtoAX
		mov tab1[BX],AL
		inc BX
		loop rdnxt
	mov CL,count
	mov CH,00
	cmp CX,1
	je DONE
	nextpass:
	mov DL,00
	mov BX,01
nextj:
  mov AL,tab1[BX]
  mov AH,tab1[BX + 1]
  cmp AL,AH
  jle skip
  mov tab1[BX],AH
  mov tab1[BX + 1],AL
  mov DL,1
skip:
  inc BX
  cmp BX,CX
  jl nextj
  dec CX
  jz done
  cmp DL,01H
  je nextpass
done:
  mov CL,count
  mov CH,00
  mov BX,01
  printstring msg3
 prnnxt:
  mov AX,00
  mov AL,tab1[BX]
  call displayAX
  printstring space
  inc BX
  loop prnnxt
  mov AH,4CH
  mov AL,00H
  int 21H
  main endp
  
readnumtoAX PROC NEAR
  push BX
  push CX
  mov CX,10
  mov BX,00
bac:
  mov AH,01H
  int 21H
  cmp AL,'0'
  JB skip1
  cmp AL,'9'
  JA skip1
  SUB AL,'0'
  push AX
  mov AX,BX
  MUL CX
  mov BX,AX
  pop AX
  mov AH,00
  ADD BX,AX
  JMP bac
skip1:
  mov AX,BX
  pop CX
  pop BX
  RET
 readnumtoAX ENDP
displayAX PROC NEAR
  push DX
  push CX
  push BX
  push AX
  mov CX,0
  mov BX,10
 back1:
  mov DX,0
  DIV BX
  push DX
  inc CX
  OR AX,AX
  JNZ back1
back2:
  pop DX
  ADD DL,30H
  mov AH,02H
  int 21H
  loop back2
  pop AX
  pop BX
  pop CX
  pop DX
  RET
displayAX ENDP
END MAIN

