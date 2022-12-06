.MODEL SMALL
.STACK 100H
.DATA
   
   INP DW ?
   INP_FLAG DB ?
   ENT_FLAG DB ?
   LINEFEED DB 13, 10, "$"
   SZ1 DW 0
   SZ2 DW 0
   CNT DW -2
   ARA DW 25 DUP (?)
   ARB DW 25 DUP (?)
   
.CODE
MAIN PROC
    MOV AX,@DATA
    MOV DS,AX
    
    LEA SI,ARA
    
    CALL INP_ARA
    CALL PRINT_NEWLINE
    
    LEA SI,ARB
    CALL INP_ARA
    CALL PRINT_NEWLINE
    
    LOOP1:
    CMP SZ1,0
    JE BR1
    DEC SZ1
    INC CNT
    INC CNT
    MOV SI,CNT
    MOV AX,ARA[SI]
    LEA SI,ARB
    MOV CX,SZ2
    LOOP2:
    CMP CX,0
    JE PRNT
    CMP AX,[SI]
    JE LOOP1
    DEC CX
    ADD SI,2
    JMP LOOP2
    
    PRNT:
       CALL PRINT_AX_DECIMAL
       MOV AH,2
       MOV DL,' '
       INT 21H
       JMP LOOP1
       
    BR1:
    ;MOV AX,INP
    ;CALL PRINT_AX_DECIMAL
    MOV AH,4CH
    INT 21H    
    
MAIN ENDP

INPUT_DECIMAL PROC
     
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    
    MOV BX,0
    MOV CH,0
    MOV INP_FLAG,0
    MOV ENT_FLAG,0
 WHILE1:
 
    MOV AH,1
    INT 21H
    CMP AL,'-'
    JE MINUS
    CMP AL,0Dh
    JE  ENTER_
    CMP AL,'0'
    JL FINAL1
    CMP AL,'9'
    JG FINAL1
    
    SUB AL,'0'
    MOV CL,AL
    MOV AX,10
    MUL BX
    ADD AX,CX
    MOV BX,AX
    JMP WHILE1
    
 MINUS:
    MOV CH,INP_FLAG
    CMP CH,1
    JE FINAL1
    MOV INP_FLAG,1
    JMP WHILE1
    
 ENTER_:
    MOV ENT_FLAG,1
    JMP FINISH1
 
 FINAL1:
    MOV CH,INP_FLAG
    CMP CH,0
    JE FINISH1
    NOT BX
    ADD BX,1    
    
 FINISH1:
    MOV INP,BX
    POP DX
    POP CX
    POP BX
    POP AX
    RET
    
INPUT_DECIMAL ENDP

PRINT_AX_DECIMAL PROC

    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    
    MOV CL,0
    CMP AX,0
    JGE WHILE2
    MOV BX,AX
    MOV AH,2
    MOV DL,'-'
    INT 21H
    MOV AX,BX
    NOT AX
    INC AX
    
 WHILE2:
    CMP AX,0
    JE PRINT_
    MOV DX,0
    MOV BX,10
    DIV BX
    PUSH DX
    INC CL
    JMP WHILE2 
 
 PRINT_:
    CMP CL,0
    JE FINISH2
    POP DX
    ADD DX,'0'
    MOV AH,2
    INT 21H
    DEC CL
    JMP PRINT_
    
 FINISH2:
    POP DX
    POP CX
    POP BX
    POP AX
    RET       
    
PRINT_AX_DECIMAL ENDP

PRINT_NEWLINE PROC
    PUSH AX
    PUSH DX
    MOV AH,09
    MOV DX, OFFSET LINEFEED
    INT 21H
    POP DX
    POP AX
    RET
PRINT_NEWLINE ENDP

INP_ARA PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV CX,0
    
    POPULATE:
    ;MOV AH,1
    ;INT 21H
    ;CMP AL,0DH
    ;JE END_
    CALL INPUT_DECIMAL
    MOV AX,INP
    MOV [SI],AX
    ;CALL PRINT_AX_DECIMAL
    INC CX
    CMP ENT_FLAG,1
    JE END_
    ADD SI,2
    JMP POPULATE
    
    END_:
       CMP SZ1,0
       JNE ST
       MOV SZ1,CX
    ST:
        MOV SZ2,CX
        POP AX
        POP BX
        POP CX
        POP DX
        RET
        
INP_ARA ENDP
    

END MAIN