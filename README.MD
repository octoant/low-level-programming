## Семинары


### Введение в среду

 - Использование интерактивной оболочки
 - Переменные окружения
 - Компиляция ассемблерных программ
 - Флаги компиляции
 - Регулярные выражения, `grep`.
 - Эмулятор терминала
 - `stdin`, `stdout`, `stderr`

### Основы ассемблера и отладка

 - Разбор `Hello, world!`
 - Системные вызовы.
 - Секции
 - Важные регистры общего назначения.
 - Служебные регистры `rip`, `rsp`
 - Отладка. Настройка `gdb` для синтаксиса Intel. Файл `.gdbrc`.
 - Изучение памяти в отладчике.
 - Шаги вперёд и назад в отладчике.

### Seminar 3: Using stack

 - Writing a part of the first assignment together.
 - Stack and calling subroutines.
 - Using stack to store temporary data.
 - Calling convention violations.
 - More advanced debugging: writing functions in GDB.

### Seminar 4: Finite automata

 - Deterministic finite automata.
 - Encoding simple automata in assembly.
 - Making automata complete.
 - Coding parts of the first assignment with automata: `read_uint`.


### Seminar 5: Multiple source code files

 - Splitting programs on multiple files.
 - `extern` and `global`.
 - Include files
 - Include guards
 - First study of object files with `nm`.

### Seminar 6: GNU Make

 - `make`. Motivation.
 - Connection to declarative programming.
 - Examples of makefiles.
 - How not to rebuild everything.
 - Variables. Automatic variables.
 - How does make looks up a solution?

### Seminar 7: Virtual memory and interprocess communication

 - Virtual memory
 - Exploring a program with `procfs`
 - Regions, flags
 - Using `mmap`. Example.

### Seminar 8

 - Assignment: using `mmap` to map a file to memory, parse a number from it.
 - Shared memory vs read/writes through pipes

### Seminar 9: Compilation and loading

 - Compilation pipeline: assembly and C.
 - Exploring ELF files with `readelf`.
 - Role of `global`, `extern`, `static`.
 - Relocation table.
 - Segments and sections.
 - Observing segments in memory regions through `procfs`

### Seminar 10: Preprocessing

 - Macrodefinitions
 - Debugging macrodefinitions.
 - Linked list in assembly.
 - Generic list in C.

### Seminar 11: Syntax, semantics, pragmatics

 - Explore an AST with an IDE plugin
 - Completing a stub for a simple parser for toy programming language
 - Adding semantics to it.
 - Pragmatics: controlling alignment in C.

### Seminar 12: Architecture

 - Decomposition
 - Start with a badly written code, decompose into modules, write clean interfaces.
 - Opaque types.
 - Using structural types to simulate interfaces.

### Seminar 13: Mixing C and assembly

 - inline assembly
 - separate assembly modules
 - interfacing between assembly and C. ELF level.
 - interfacing between assembly and C++. ELF level.
 - module that uses XMM registers.

### Seminar 14: Compiler optimizations

 - Witnessing optimizations:
 - Prologue/epilogue removal
 - Red zone
 - Tail recursion optimization
 - Precomputations
 - Return value optimization
 - Effects of `restrict`.

### Seminar 15: Memory allocator

 - Writing the simplest block memory allocator
 - Strict aliasing rules

### Seminar 16: Introduction to parallelism

 - Weak memory model: witnessing compiler and hardware reorderings
 - `volatile`
 - Implement mutex
