;AUTHOR: SOUMYADEEP THAKUR
;DATE: 21 OCT 2017

.model small
.stack 300h
.data
msg1 db 0AH,0DH,'Enter bin no number: $'
msg2 db 0AH,0DH,'Decimal: $'
space db ' $'
endl db 0AH,0DH,'$'
binno db 17
	  db ?
	  db 17 dup(0)

.code

val1 dw ?
val2 dw ?

.code
print macro msg
	push ax
	push dx
	mov ah, 09h
	lea dx, msg
	int 21h
	pop dx
	pop ax
endm
read macro memloc
	push ax
	push cx
	push dx
	mov ah, 0ah
	lea dx, memloc
	int 21h
	lea si, memloc + 1 ;NUMBER OF CHARACTERS ENTERED.
	mov cl, [si] ;MOVE LENGTH TO CL.
	mov ch, 0      ;CLEAR CH TO USE CX. 
	inc cx ;TO REACH CHR(13).
	add si, cx ;NOW SI POINTS TO CHR(13).
	mov al, '$'
	mov [si], al ;REPLACE CHR(13) BY '$'.            
	
	pop dx
	pop cx
	pop ax
endm

main proc
	mov ax,@data
	mov ds,ax
	
	start:
	
	print msg1
	
	read binno; bin no strored in binno
	
	print  msg2
	mov ax,0000h
	mov bx,0000h
	lea si, binno + 1
	mov cl, [si]
	mov ch, 00h
	inc  si
	;add si, cx
	mov ax,cx
	;call writenum
	;print endl
	mov ax,00h
	
	loop1:
		mov bl, [si]
		sub bl, '0'
		mov bh, 00h
		mov dx,02h
		mul dx
		add ax, bx
		;call writenum
		;print endl
		inc si
	loop loop1
	
		
	call writenum
	
	exit:
    mov ah, 4ch
    int 21h

main endp

readnum proc near
	; this procedure will take a number as input from user and store in AX
	; input : none
	
	; output : AX

	
	push bx
	push cx
	mov cx,0ah
	mov bx,00h
	loopnum: 
		mov ah,01h
		int 21h
		cmp al,'0'
		jb skip
		cmp al,'9'
		ja skip
		sub al,'0'
		push ax
		mov ax,bx
		mul cx
		mov bx,ax
		pop ax
		mov ah,00h
		add bx,ax
	jmp loopnum
	
	skip:
	mov ax,bx
	pop cx
	pop bx
	ret
readnum endp

writenum proc near
	; this procedure will display a decimal number
	; input : AX
	; output : none

	push ax
	push bx                        
	push cx                        
	push dx                        

	xor cx, cx
	mov bx, 0ah                     

	@output:                       
		xor dx, dx                   
		div bx                       ; divide AX by BX
		push dx                      ; push remainder onto the STACK
		inc cx                       
		or ax, ax                    
	jne @output                    

	mov ah, 02h                      ; set output function

	@display:                      
		pop dx                       ; pop a value(remainder) from STACK to DX
		or dl, 30h                   ; convert decimal to ascii code
		int 21h                      
	loop @display                  

	pop dx                         
	pop cx                         
	pop bx 
	pop ax

	ret                            
writenum endp

end main
