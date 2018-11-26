.model small
.stack 300h
.data
array1 db 50 dup(0)
msg1 db 0AH,0DH,'Enter size of the array: $'
msg2 db 0AH,0DH,'Enter numbers: $'
msg3 db 0AH,0DH,'2nd Max = $ '
msg4 db 0AH,0DH,'2nd Min = $'
endl db 0AH,0DH,'$'
se db 00h
count db 00H

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
	mov count, al
	mov cl, count
	mov bx, 00h
	
	print msg2
	rdnxt: ;  input the array
		print endl
		call readnum
		mov array1[bx],al
		inc bx
	loop rdnxt
	
	mov bl, 00h
	mov bh, 255
	mov dl, 00h
	mov dh, 255
	mov cl, count
	lea si, array1
	
	loop1:
		mov al,[si]
		cmp al,bl
		jb min
		mov dl, bl
		mov bl,al
		min:
		cmp al,bh
		ja next
		mov dh, bh
		mov bh,al
		next:
		inc si
	loop loop1
	
	mov al,dl
	print msg3
	call writenum
	print endl
	mov al,dh
	print msg4
	call writenum
		
		
 
end1:
	mov ah, 4ch
	int 21h

main endp

print_array proc near
	; this procedure will print the elements of a given array
	; input : SI=offset address of the array
	;       : BX=size of the array
	; output : none

	push ax                        
	push cx                        
	push dx                        
	push si
	mov cx, bx                     

	@print_array:                  
		xor ah,ah                  
		mov al, [si]               

		call writenum              

		mov ah, 2                  
		mov dl, 20h                
		int 21h                    

		inc si                     
	loop @print_array              

	pop si
	pop dx                         
	pop cx                         
	pop ax                         

	ret                            
print_array endp


readnum proc near
	; this procedure will take a number as input from user and store in AL
	; input : none
	
	; output : AL

	
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

