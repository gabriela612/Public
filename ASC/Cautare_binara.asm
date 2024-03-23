bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    format_sir db "%s", 0
    format_numar db "%d", 0
    format_char db "%c", 0
    sir times 50 dd 0
    ceva dd 0
    char dd 0

; our code starts here
segment code use32 class=code
    start:
        
        ; citire sir
        push dword sir
        push dword format_sir
        call [scanf]
        add esp, 4 * 2
        
        ; citire spatiu / endline
        push dword ceva
        push dword format_char
        call [scanf]
        add esp, 4 * 2
        
        ; citire caracter
        push dword char
        push dword format_char
        call [scanf]
        add esp, 4 * 2
        
        
        ; if sir[0] > char
        mov eax, [sir]
        cmp eax, [char]
        ja Negasit
        
        ; if sir[-1] < char
        mov edi, sir ; edi = adresa de inceput a sirului
        cld ; df = 0
        mov eax, 0 ; eax = 0
        mov ecx, -1 ; ecx = max
        repne scasb ; while al != [edi] edi ++
        sub edi, 2 ; revenim cu edi pe ultimul caracter din sir
        mov al, [char] ; al = char
        scasb ; cmp al, [edi]
        ja Negasit
        
        
        
        
        
        
    Negasit:
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
