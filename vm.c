#include "vm.h"

int main(void) {
    int code[] = {
        PUSH, 5,      
        PRNT,         
        PUSH, 1,      
        SUB,      
        DUP,      
        JNZ, 2, 
        END, 
    };
    return run(code, sizeof code / sizeof code[0]);
}
