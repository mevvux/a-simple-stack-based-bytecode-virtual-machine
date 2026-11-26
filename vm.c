#include <stdio.h>
#include "vm.h"

int main(void) {
    int code[] = {
        PUSH, 5,
        PUSH, 5,
        ADD,
        PRNT,
        PUSH, 6,
        SUB,
        PRNT,
        PUSH,4,
        MUL,
        PRNT,
        PUSH, 2,
        DIV,
        END };//IT HAS TO THROW OUT A 8
    return run(code, sizeof code / sizeof code[0]);
}
