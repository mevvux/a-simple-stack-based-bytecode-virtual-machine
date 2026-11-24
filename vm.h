#ifndef VM_H
#define VM_H
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>


//test opcode hhh
#define PUSH 0x00
#define ADD 0x01
#define POP 0x02
#define HALT 0x03

//stack time (im going to steal it from my previus uni project)

#define MAX_STACK_SIZE 256
typedef struct 
{
    int Values[MAX_STACK_SIZE];
    size_t Count;
}Stack;

static bool stack_push(Stack *stack,int value){
    if (stack->Count >=MAX_STACK_SIZE)
    {
        fprintf(stderr, "ERROR : OVERFLOW\n");
        return false;
    }
    stack->Values[stack->Count++] = value;
    return true;
}

static bool stack_pop(Stack *stack, int* value){
    if (stack->Count == 0)
    {
        fprintf(stderr, "ERROR : UNDERFLOW\n");
        return false;
    }
    stack->Count--;
    *value = stack->Values[stack->Count];
    return true;
}
// more functions and shit
static int run(const int *code, size_t len){
    Stack stack = {0};
    size_t pc = 0;
    for (;;)
    {
        if (pc >= len)
        {
            fprintf(stderr, "ERROR : PC OUT OF RANGE\n");
            return 1;
        }
        switch (code[pc++])
        {
        case PUSH:
            if (pc >= len) { 
                fprintf(stderr, "ERROR : MISSING OPERAND\n");
                return 1; }
            if (!stack_push(&stack, code[pc++])){ 
                return 1;}
            break;
        case POP:
            int discard;
            if (!stack_pop(&stack, &discard)) {
                return 1;}
            break;
        case ADD:
            int a,b;
            if (!stack_pop(&stack,&b))
            {
                return 1;
            }
            
            if (!stack_pop(&stack,&a))
            {
                return 1;
            }
            
            if (!stack_push(&stack,a+b))
            {
                return 1;
            }


            break;

            
        case HALT:
            int result;
            if (!stack_pop(&stack, &result)) {
                return 1;}
            printf("%d\n", result);
            return 0;
        default:
            fprintf(stderr, "ERROR : BAD OPCODE %d\n", code[pc - 1]);
            return 1;
        }
    }
    
}

#endif