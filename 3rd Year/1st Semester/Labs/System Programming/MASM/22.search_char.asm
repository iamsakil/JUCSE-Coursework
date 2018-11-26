.model small
.stack 300h
.data
array1 db 50 dup(0)
msg1 db 0AH,0DH,'Enter string: $'
msg2 db 0AH,0DH,'Enter character: $'
msg3 db 0AH,0DH,'No of occurences = $ '
msg4 db 0AH,0DH,'2nd Min = $'
endl db 0AH,0DH,'$'
se db 00h
count db 00H
buff db 26
	 db ?
	 db 26 dup(0)

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
	read buff
	
	print msg2
	call readchar
	lea si, buff + 1
	mov cl, [si]
	mov ch, 00h
	lea si, buff + 2
	mov bh, 00h
	loop1:
		mov bl, [si]
		cmp al, bl
		jnz next
		inc bh
		next:
		inc si
	loop loop1
		
	
	print msg3
	mov al,bh
	mov ah,00h
	call writenum
	
		
		
 
end1:
	mov ah, 4ch
	int 21h

main endp

readchar proc near
	; this procedure will take a number as input from user and store in AL
	; input : none
	
	; output : AL

	
	push bx
	push cx
	mov cx,0ah
	mov bx,00h
	
	mov ah,01h
	int 21h
	
	pop cx
	pop bx
	
	ret
readchar endp

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

