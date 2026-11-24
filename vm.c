#include "vm.h"

int main(void) {
    int code[] = { PUSH, 5, PUSH, 5, ADD, HALT };//IT HAS TO THROW OUT A 10
    return run(code, sizeof code / sizeof code[0]);
}