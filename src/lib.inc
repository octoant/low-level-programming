section .text

; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
    xor rax, rax
  .iter:
    cmp byte[rdi+rax], 0x0
    je .break
    inc rax
    jmp .iter
  .break:
    ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
    call string_length
  .print:
    mov rsi, rdi
    mov rdi, 0x1
    mov rdx, rax
    mov rax, 0x1
    syscall
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov rdi, 0xa

; Принимает код символа и выводит его в stdout
print_char:
    push rdi
    mov rax, 0x1
    mov rdi, 0x1
    mov rsi, rsp
    mov rdx, 0x1
    syscall
    pop rdi
    ret

; Выводит знаковое 8-байтовое число в десятичном формате
print_int:
    test rdi, rdi
    jns print_uint
    neg rdi
    push rdi
    mov rdi, 0x2d
    call print_char
    pop rdi

; Выводит беззнаковое 8-байтовое число в десятичном формате
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    mov rax, rdi
    mov rcx, rsp
    sub rsp, 0x16
    dec rcx
    mov [rcx], byte 0x0
    mov r10, 0xa
  .iter:
    xor rdx, rdx
    div r10
    add rdx, 0x30
    dec rcx
    mov [rcx], dl
    test rax, rax
    jne .iter
    mov rdi, rcx
    call print_string
    add rsp, 0x16
    ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    xor rcx, rcx
    xor r8, r8
    mov rax, 0x1
  .iter:
    mov r8b, [rdi+rcx]
    cmp r8b, [rsi+rcx]
    jne .err
    cmp r8b, 0x0
    je .end
    inc rcx
    jmp .iter
  .err:
    xor rax, rax
  .end:
    ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    push 0x0
    xor rax, rax
    xor rdi, rdi
    mov rsi, rsp
    mov rdx, 0x1
    syscall
    pop rax
    ret

; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
read_word:
    push rsi-0x1            ; помещаем значения аргументов (-1 для нуль-терминатора) в стек,
    push rdi                ; чтобы не потерять их после вызова read_char
    xor r8, r8
    xor r9, r9
  .iter:
    call read_char          ; прочитаем очередной символ из стандартного потока ввода
    mov rdi, [rsp]          ; восстанавливаем значения аргументов используя стек,
    mov rsi, [rsp+0x1]      ; так как они уже там находятся
    cmp rax, 0x9
    je .check
    cmp rax, 0xa
    je .check
    cmp rax, 0x20
    je .check
    mov r9, 0x1             ; устанавливаем флаг того, что было прочитано не пробельный символ
    cmp rax, 0x0            ; сравниваем очередной символ с нуль-терминатором
    je .check               ; если они равны, то выходим из цикла (успешно из подпрограммы)
    cmp r8, rsi             ; сравниваем значение регистра <r8> с размером буфера
    je .err                 ; если они равны, то выходим из цикла (неуспешно из подпрограммы,
                            ; так как прочитанное слово не вмещается в буфер)
    mov [rdi+r8], al        ; иначе прописываем очередной символ в буфер
    inc r8                  ; увеличиваем размер на единицу, так как очередной символ прочитано
                            ; успешно
    jmp .iter
  .check:
    test r9, r9             ; проверяем того, что было ли прочитано не пробельный символ
    je .iter                ; если нет, то продолжаем цикл прочтения, иначе
    mov [rdi+r8], byte 0x0  ; дописываем к слову нуль-терминатор
    mov rax, rdi            ; записываем в аккумулятор адрес начала буфера
    mov rdx, r8             ; записываем в регистр данных длина прочитанной слова
    jmp .end
  .err:
    xor rax, rax
  .end:
    pop rdi                 ; восстанавливаем состояние стека,
    pop rsi                 ; которое было в начале подпрограммы
    ret

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    xor rax, rax
    xor r8, r8
    xor r9, r9
    mov r10, 0xa
  .iter:
    mov r9b, [rdi+r8]
    cmp r9b, 0x30
    jb .break
    cmp r9b, 0x39
    ja .break
    sub r9b, 0x30
    mul r10
    add rax, r9
    inc r8
    jmp .iter
  .break:
    mov rdx, r8
    ret

; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был)
; rdx = 0 если число прочитать не удалось
parse_int:
    cmp byte[rdi], 0x2d
    jne parse_uint
    inc rdi
    call parse_uint
    neg rax
    inc rdx
    ret

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
    xor rax, rax
  .iter:
    cmp rax, rdx
    je .err
    mov r8b, [rdi+rax]
    mov [rsi+rax], r8b
    test r8b, r8b
    je .break
    inc rax
    jmp .iter
  .err:
    xor rax, rax
  .break:
    ret

; Принимает код возврата и завершает текущий процесс
exit:
    mov rax, 0x3c
    syscall
