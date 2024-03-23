bits 32

global _st        

extern _fopen
extern _fclose
extern _fscanf
extern _printf

segment data public data use32

; Se citesc din fisierul numere.txt mai multe numere (pozitive si negative). Sa se creeze 2 siruri rezultat N si P astfel: N - doar numere negative si P - doar numere pozitive. Afisati cele 2 siruri rezultate pe ecran.

    nr_curent dd 0
    format_citire db "%d", 0
    des dd 0
    acces db "r", 0
    nr_poz dd 0
    nr_neg dd 0
    fisier db "numere9.txt", 0
    len_poz dd 0
    len_neg dd 0
    
segment code public data use32
    start:
    _st:
        ; C
        push ebp
        mov ebp, esp
        
        ;sub esp, 4 * 3
        
        mov eax, [ebp + 8]
        mov [nr_poz], eax
        mov eax, [ebp + 12]
        mov [nr_neg], eax
        mov eax, [ebp + 16]
        mov [len_neg], eax
        mov eax, [ebp + 20]
        mov [len_poz], eax
        
        ;afisare sumplimentara
        push dword 2
        push dword format_citire
        call _printf
        add esp, 4 * 2
        
    
        ; deschiderea fisierului
        push dword acces
        push dword fisier
        call _fopen
        add esp, 4 * 2
        cmp eax, 0
        je final ; verificam daca s-a deschis cu succes fisierul
        mov [des], eax
        
        ; initializari
        mov esi, [nr_poz] ; esi = adresa de inceput a sirului de numere pozitive
        mov edi, [nr_neg] ; edi = adresa de inceput a sirului de numere negative
        cld
        
        ; parcurgerea numerelor din fisier si adaugarea lor in siruri
    Inceput:
        ; citirea numarului curent
        push dword nr_curent
        push dword format_citire
        push dword [des]
        call _fscanf
        add esp, 4 * 3
        cmp dword [nr_curent], 0 ; sirul de numere se va incheia cu 0
        je final_prelucrare
        
        ; compararea cu 0 si adaugarea numarului curent la unul din siruri
        cmp dword [nr_curent], 0 ; vrem sa aflam cum e numarul in comparatie cu 0 (pozitiv sau negativ)
        jg nr_pozitiv ; daca numarul e mai mare decat 0 => numar pozitiv
    nr_negativ:
        mov eax, [nr_curent] ; eax = numarul curent
        stosd ; se pune, la adresa lui edi, cuvantul curent; edi += 4
        jmp Inceput
    nr_pozitiv:
        xchg esi, edi ; edi = adresa pe care se va pune urmatorul numar pozitiv, esi = adresa pe care se va pune urmatorul numar negativ
        mov eax, [nr_curent] ; eax = numarul curent
        stosd ; se pune, la adresa lui edi, cuvantul curent; edi += 4
        xchg esi, edi ; esi = adresa pe care se va pune urmatorul numar pozitiv, edi = adresa pe care se va pune urmatorul numar negativ
        jmp Inceput
    final_prelucrare:
        
        
        ; modificarea lungimilor
        sub esi, [nr_poz]
        mov [len_poz], esi ; 
        sub edi, [nr_neg]
        mov [len_neg], edi ; 
        
    
        ; inchiderea fisierului
        push dword [des]
        call _fclose
        add esp, 4 * 1
        
    final:
    
        ;add esp, 4 * 3
    
        mov esp, ebp
        pop ebp
        ret 4 * 4
    
