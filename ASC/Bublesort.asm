bits 32

global start        


extern exit
import exit msvcrt.dll


segment data use32 class=data
    sir db 5, 32, 5, 7, 9, 2
    len equ $ - sir
    i dd 0

    
segment code use32 class=code
    start:
    
    interschimbare:
    jmp continuare
    
    
    
    
        ; initializari pentru primul for
        mov esi, sir ; esi = adresa primului element din sir
        mov ecx, len - 1 ; ecx = lungimea sirului minus 1
        cld ; parcurgem ascendent
        
        ; primul for : for(i = 1; i < n; i ++)
    fori:
        lodsb ; al = sir[i]; esi ++
        dec esi ; anulam operatia de incrementare facuta de lodsb
        
        ; al doilea for : for(j = i+1; j <= n; j ++)
        ; initializari pentru al doilea for
        push ecx ; am salvat ecx pe stiva, ca sa stim cati pasi mai avem de facut
        sub esi, sir ; esi = numarul de elemente parcurse = pozitia din sir a elementului curent
        mov dword [i], esi ; i = esi
        add esi, sir ; esi = adresa elementului curent din sir
        mov ecx, len ; ecx = len
        sub ecx, [i] ; ecx = len - i
        dec ecx ; ecx = len - i - 1 (pasi se parcurg cu al doilea for)
        mov edi, sir ; edi = adresa primului element din sir
        add edi, [i] ; edi = adresa elemetului de pe pozitia i din sir
        inc edi ; edi = adresa elementului de pe pozitia i + 1 din sir
        forj:
            scasb ; se pregateste compararea lui sir[i] (al) cu sir[j] (edi) ; edi ++
            ja interschimbare
            continuare:
            loop forj
        pop ecx ; luam ecx-ul de pe stiva
        inc esi ; trecem la urmatorul element din sir
        loop fori
        
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
