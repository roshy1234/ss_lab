data segment
    msg1 db 10,13, 'Enter the character to search: $'
    msg2 db 10,13, 'Character found in the string$'
    msg3 db 10,13, 'Character not found in the string$'  ; Removed extra space before $
    search_char db ?                                     ; Variable to store the search character
    msg4 db 10,13, 'Starting the program$'
    string db 'Hello, World$'                            ; Ensured no newline before the terminator
data ends

code segment
ASSUME cs:code, ds:data

start:
    mov ax, data
    mov ds, ax
    
    lea dx, msg4       ; Printing "Starting the program"
    mov ah, 09h
    int 21h       
    
    lea dx, msg1       ; Printing prompt to input the character
    mov ah, 09h
    int 21h  
    
    mov ah, 01h        ; Accepting user input for the character
    int 21h
    mov search_char, al
    
    lea si, string     ; Loading the string "Hello, World" into SI
    
search_loop:    
    mov al, [si]       ; Load the current character from the string
    cmp al, '$'        ; Check if end of string is reached
    je not_found       ; If yes, character not found
    cmp al, search_char
    je found           ; If match, jump to 'found'
    inc si             ; Move to the next character in the string
    jmp search_loop    ; Repeat the search loop

found:
    lea dx, msg2       ; Load "Character found in the string" message
    mov ah, 09h
    int 21h
    jmp end

not_found:
    lea dx, msg3       ; Load "Character not found in the string" message
    mov ah, 09h
    int 21h

end:
    mov ah, 4ch        ; Exit the program
    int 21h

code ends
end start
