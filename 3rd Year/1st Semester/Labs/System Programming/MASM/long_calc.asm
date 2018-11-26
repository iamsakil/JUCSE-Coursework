.model small
.stack 300h
.data
msg1 db 0AH,0DH,'Enter 2 numbers: $'
msg2 db 0AH,0DH,'Number is palindrome $'
msg3 db 0AH,0DH,'Number is not palindrome $'
msg4 db 0AH,0DH,'Reverse: $'
endl db 0AH,0DH,'$'
val1 dw 2 dup(?)
val2 dw 2 dup(?)

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

main proc
	mov ax,@data
	mov ds,ax
	
	start:
	
	print msg1
	
	call readnum
	mov bx,ax
	mov cx,dx
	call readnum
	
	;call writenum
	;print endl
	;mov ax,dx
	;call writenum
	;print endl
	;mov ax,bx
	;mov dx,cx
	
	;call writenum
	;print endl
	;mov ax,dx
	;call writenum
	;print endl
	
	;ADD
	push ax
	push dx
	
	add ax,bx
	push ax
	mov ax,dx
	adc ax,cx
	
	;DISPLAY
	call writenum
	print endl
	pop ax
	call writenum
	print endl
	
	pop dx
	pop ax
	
	;SUB
	push ax
	push dx
	
	sub  ax,bx
	push ax
	mov ax,dx
	sbb ax,cx
	
	;DISPLAY
	call writenum
	print endl
	pop ax
	call writenum
	print endl
	
	
	
	;mov val, ax
	
	exit:
    mov ah, 4ch
    int 21h
main endp

readnum proc near
	; this procedure will take a number as input from user and store in AX
	; input : none
	
	; output : [DX:AX]

	
	push bx
	push cx
	
	mov dx,0000h
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
		push dx
		mov ax,bx
		mul cx
		mov bx,ax
		mov ax,dx
		pop dx
		push ax
		mov ax, dx
		mul cx
		mov dx, ax
		pop ax
		add dx,ax
		pop ax
		mov ah,00h
		add bx,ax
		jnc no1
		inc dx
		no1:
	jmp loopnum
	
	skip:
	mov ax,bx
	pop cx
	pop bx
	ret
readnum endp

writenum proc near
	; this procedure will display a decimal number
	; input : [DX:AX]
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
