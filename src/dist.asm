%include "lib.inc"

global find_word
global get_value

section .text

; Пройдёт по всему словарю в поисках подходящего ключа.
; Если подходящее вхождение найдено, вернёт адрес начала
; вхождения в словарь (не значения), иначе вернёт 0.
find_word:
  .iter:
    test rdi, rdi
    je .err
    push rdi
    add rdi, 0x8
    push rsi
    call string_equals
    pop rsi
    pop rdi
    test rax, rax
    jne .break
    mov rdi, [rdi]
    jmp .iter
  .break:
    mov rax, rdi
    ret
  .err:
    xor rax, rax
    ret

; Принимает адрес начала вхождения в словарь
; Вернет адрес начало слова (значение)
get_value:
    add rdi, 0x8
    push rdi
    call string_length
    pop rdi
    add rax, rdi
    inc rax
    ret
