/* Описание инструкций (см. предыдущий шаг) */
enum opcode { BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_STOP };

struct bc_noarg {
    enum opcode opcode;
};
struct bc_arg64 {
    enum opcode opcode;
    int64_t arg;
};
union ins {
    enum opcode opcode;
    struct bc_arg64 as_arg64;
    struct bc_noarg as_noarg;
};

/* ------------------------ */

struct vm_state {
    const union ins *ip;
    struct stack data_stack;
};

/* Начальная вместимость стека задаётся определением STACK_CAPACITY */
struct vm_state state_create(const union ins *ip) {
    return (struct vm_state) {
            .ip = ip,
            .data_stack = stack_create(STACK_CAPACITY)
    };
}

// Как правильно деинициализировать состояние, освободить все ресурсы?
void state_destroy(struct vm_state *state) {
    free(state);
}


/* Вы можете использовать эти функции: */
void print_int64(int64_t);
struct maybe_int64 maybe_read_int64();

struct stack stack_create(size_t size);
void stack_destroy(struct stack *s);
bool stack_push(struct stack *s, int64_t value);
struct maybe_int64 stack_pop(struct stack *s);

/* Опишите цикл интерпретации с выборкой и выполнением команд (пока не выполним STOP) */
void interpret(struct vm_state *state) {
    while ( true ) {
        switch ( state->ip->opcode ) {
            case BC_PUSH: {
                int64_t value = state->ip->as_arg64.arg;
                if (!stack_push(&(state->data_stack), value)) {
                    err("Command BC_PUSH failed!");
                    return;
                }
                break;
            }
            case BC_IPRINT: {
                struct maybe_int64 item = stack_pop(&(state->data_stack));
                if (item.valid) {
                    print_int64(item.value);
                } else {
                    err("Command BC_IPRINT failed!");
                    return;
                }
                break;
            }
            case BC_IREAD: {
                struct maybe_int64 item = maybe_read_int64();
                if (!item.valid || !stack_push(&(state->data_stack), item.value)) {
                    err("Command BC_IREAD failed!");
                    return;
                }
                break;
            }
            case BC_IADD: {
                struct maybe_int64 a = stack_pop(&(state->data_stack));
                struct maybe_int64 b = stack_pop(&(state->data_stack));
                if (!a.valid || !b.valid || !stack_push(&(state->data_stack), (a.value + b.value))) {
                    err("Command BC_IADD failed!");
                    return;
                }
                break;
            }
            case BC_STOP: {
                return;
            }
            default: {
                err("Command not implemented yet!");
                return;
            }
        }
        state->ip = state->ip + 1;
    }
}

void interpret_program(const union ins *program) {
    struct vm_state state = state_create(program);
    interpret(&state);
    state_destroy(&state);
}