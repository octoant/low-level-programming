%include "lib.inc"
%include "words.inc"
%include "dict.inc"
%include "messages.inc"

%assign size 256            ; размер буфера

global _start
section .data
buffer: times size db 0     ; буфер

section .text
_start:
    call print_newline
    mov rdi, keyword
    call print_string
    mov rdi, buffer
    mov rsi, size
    call read_line          ; прочитаем всю строку до символа с кодом 0x20
    test rax, rax
    je .empty_string        ; если функция вернет ноль, то сообщаем о том,
                            ; что пустая строка не допускается
    js .buffer_overflow     ; если функция завершена неуспешна, т.е. прочитанное слово
                            ; не влез в буфер, то сообщаем об ошибке
    mov rdi, buffer
    call trim_string        ; удаляем начальные и конечные пробелы
    mov rdi, head
    mov rsi, buffer
    call find_word          ; ищем в словаре подходящего ключа
    test rax, rax
    je .not_found           ; если ключ не найден, то сообщаем об этом пользователю
    mov rdi, rax            ; иначе помещаем найденное вхождение в регистр данных и
    call get_value          ; находим адрес начало слова (значение)
    mov rdi, rax
    call print_string       ; записываем найденное слово в stdin
    call print_newline
    jmp _start
  .empty_string:
    mov rdi, empty_string
    call print_string2
    jmp _start
  .buffer_overflow:
    mov rdi, buffer_overflow
    call print_string2
    jmp _start
  .not_found:
    mov rdi, not_found
    call print_string2
    jmp _start
