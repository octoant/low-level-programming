/*

struct array_int {
  int64_t* data;
  size_t size;
};

struct stack {
  size_t count;
  struct array_int data;
};

*/

void interpret(struct vm_state* state, ins_interpreter * const  (actions)[]) {
    for (; state->ip ;) {
        const union ins* ins = state->ip;

        const struct ins_descr* ins_descr = instructions + ins->opcode;

        int64_t count = (int64_t) state->data_stack.count;
        int64_t size = (int64_t) state->data_stack.data.size;

        int64_t min = (int64_t) ins_descr->stack_min;
        int64_t delta = (int64_t) ins_descr->stack_delta;

        if (count - min < 0) {
            printf("Stack underflow\n");
            return 0;
        }

        if (count + delta > size) {
            printf("Stack overflow\n");
            return 0;
        }

        actions[ins->opcode](state);

        if (!ins_descr->affects_ip) { state->ip = state->ip + 1; }
    }
}