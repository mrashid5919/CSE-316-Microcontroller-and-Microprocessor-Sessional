.MODEL SMALL 
.STACK 100H 
.DATA 
.CODE 
MAIN PROC
     
 ; input
 MOV DL,0
 MOV BX,0
 MOV AH,1
 
 WHILE_:
    MOV AH,1
    INT 21h
    CMP AL,0Dh
    JE END_WHILE
    INC DL
    SUB AL,'a'
    ADD AL,1
    MUL DL
    ADD BL,AL
    JMP WHILE_ 
 
 END_WHILE:
 MOV DL,0
 MOV CX,0
 MOV AH,1   
 WHILE2_:
    MOV AH,1
    INT 21h
    CMP AL,0Dh
    JE NX
    INC DL
    SUB AL,'a'
    ADD AL,1
    MUL DL
    ADD CL,AL
    JMP WHILE2_
    
 NX:
    CMP BL,CL
    JE TH
    MOV AH,2
    MOV DL,'N'
    INT 21H
    MOV DL,'E'
    INT 21H
    JMP EX
    
 TH:
    MOV AH,2
    MOV DL,'P'
    INT 21H
    MOV DL,'E'
    INT 21H
    JMP EX
    
 EX:
    
        
  
 ;interrupt to exit
 MOV AH, 4CH
 INT 21H 
  
MAIN ENDP 
END MAIN