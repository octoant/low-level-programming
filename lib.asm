section .text

; Принимает код возврата и завершает текущий процесс
exit:
    xor rax, rax
    ret

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax            ; nullifying accumulator
  .iter:
    cmp [rdi+rax], byte 0x0
    je .end
    inc rax                 ; incrementing <rax>
    jmp .iter
  .end:
    ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    call string_length
  .print:
    mov rsi, rdi            ; setting string address
    mov rdi, 0x1            ; setting <stdout> descriptor
    mov rdx, rax            ; setting string length in bytes
    mov rax, 0x1            ; setting <write> system call number
    syscall
  .end:
    ret

; Принимает код символа и выводит его в stdout
print_char:
    push rdi                ; pushing character ASCII-code to the stack
  .print:
    mov rax, 0x1            ; setting <write> system call number
    mov rdi, 0x1            ; setting <stdout> descriptor
    mov rsi, rsp            ; setting character address at the stack
    mov rdx, 0x1            ; setting number of bytes to write
    syscall
  .end:
    add rsp, 0x8            ; restoring stack state
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    xor rax, rax
    ret

; Выводит беззнаковое 8-байтовое число в десятичном формате
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    mov rax, rdi            ; loading number to accumulator
  .alloc:
    mov rcx, rsp            ; creating pointer to the buffer
    sub rsp, 0x16           ; allocating 22 bytes in the stack for keeping decimal number digits' ASCII-code
    dec rcx
    mov [rcx], byte 0x0     ; setting code of null-terminator to the end of allocated buffer
    mov r10, 0xA
  .iter:
    xor rdx, rdx            ; nullifying <rdx>
    div r10
    add rdx, 0x30
    dec rcx
    mov [rcx], dl
    test rax, rax
    jne .iter
  .print:
    mov rdi, rcx            ; setting the argument of function print_string
    call print_string
  .end:
    add rsp, 0x16           ; restoring stack state
    ret

; Выводит знаковое 8-байтовое число в десятичном формате
print_int:
    test rdi, rdi
    jns .pos
  .neg:
    neg rdi                 ; inverting sign of the number
    push rdi
    mov rdi, 0x2D           ; storing dash ASCII-code
    call print_char         ; printing minus char
    pop rdi
  .pos:
    call print_uint
  .end:
    ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    xor rax, rax
    ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    push 0x0
  .read:
    xor rax, rax            ; setting <read> system call number
    xor rdi, rdi            ; setting <stdin> descriptor
    mov rsi, rsp            ; setting address at the stack for keeping character
    mov rdx, 0x1            ; setting number of bytes to read
    syscall
  .end:
    pop rax                 ; storing read character to the accumulator
    ret

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
read_word:
    xor rax, rax
    ret

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    xor rax, rax
    ret

; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был)
; rdx = 0 если число прочитать не удалось
parse_int:
    xor rax, rax
    ret

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
    call string_length
  .copy:
    xor rcx, rcx            ; nullifying <rcx>
  .iter:
    cmp rcx, rdx
    je .err
    mov r8b, [rdi+rcx]      ; reading a character from the string
    mov [rsi+rcx], r8b      ; writing the next character to the buffer
    cmp rcx, rax
    je .end
    inc rcx                 ; incrementing <rcx>
    jmp .iter
  .err:
    xor rax, rax            ; nullifying accumulator
  .end:
    ret
