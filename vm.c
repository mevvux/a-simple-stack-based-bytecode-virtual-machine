#include "vm.h"
//this is just a test to see whether i wasted hour of my life or not
int main(void) {
    int code[] = { PUSH, 5, PUSH, 5, ADD, HALT };//IT HAS TO THROW OUT A 10
    return run(code, sizeof code / sizeof code[0]);
}
