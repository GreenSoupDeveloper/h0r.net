segment _ENTRY class=CODE
extern cstart
global entry

entry:
mov ah,09h
mov al,'N'
mov bh,0
mov bl,4
mov cx,1
int 10h
call cstart
jmp $