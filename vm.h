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
#define END 0x03 //changed halt to end because it sounds too medieval
#define SUB 0x04
#define MUL 0x05
#define DIV 0x06 // is there a diffrence between copying and printing
#define PRNT 0x07 
#define DUP 0x08

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

static bool stack_peek(const Stack *stack, int *value){// will be used for the cpr and print
    if (stack->Count == 0)
    {
        fprintf(stderr, "ERROR : UNDERFLOW\n");
        return false;
    }
    *value = stack->Values[stack->Count - 1];
    return true;
}
// more functions and shit

//shit i got make seperate functions 

static int PUSH_FUNC(Stack *stack, size_t *pc, size_t len, const int *code) {
    if (*pc >= len) {
        fprintf(stderr, "BITCH ASS DROP AN OPERAND\n");
        return 1;
    }
    if (!stack_push(stack, code[(*pc)++])) return 1;
    return 0;
}

static int POP_FUNC(Stack *stack){
    int discard;
    if (!stack_pop(stack, &discard)){ 
        return 1;}
    return 0;
}

static int ADD_FUNC(Stack *stack){
    int a,b;
    if (!stack_pop(stack,&b))
            {
                return 1;
            }
            
            if (!stack_pop(stack,&a))
            {
                return 1;
            }
            
            if (!stack_push(stack,a+b))
            {
                return 1;
            }
        return 0;
}

static int SUB_FUNC(Stack *stack){
    int a,b;
    if (!stack_pop(stack,&b))
            {
                return 1;
            }
            
            if (!stack_pop(stack,&a))
            {
                return 1;
            }
            
            if (!stack_push(stack,a-b))
            {
                return 1;
            }
        return 0;

}

static int MUL_FUNC(Stack *stack){
    int a,b;
    if (!stack_pop(stack,&b))
            {
                return 1;
            }
            
            if (!stack_pop(stack,&a))
            {
                return 1;
            }
            
            if (!stack_push(stack,a*b))
            {
                return 1;
            }
        return 0;
}

static int DIV_FUNC(Stack *stack){
    int a,b;
    if (!stack_pop(stack,&b)){
            return 1;}
    if (b == 0)
    {
        fprintf(stderr, "ERROR : DIVISION BY ZERO\n");
        return 1;
    }
    
    if (!stack_pop(stack,&a)){
        return 1;}
    if (!stack_push(stack,a/b)){
        return 1;}
    return 0;
}

static bool DUP_FUNC(Stack *stack) {
    int a;
    if (!stack_peek(stack, &a)){ 
        return false;}   
    if (!stack_push(stack, a)){ 
        return false;}
    return true;
}

static bool PRNT_FUNC(Stack *stack){ // im about o do something stupid hhhh
    int a;
    if (!DUP_FUNC(stack)){
        return false;
    }
    if (!stack_pop(stack, &a)){
        return false;
    }
    printf("%d \n", a);
    return true;
}

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
            if(PUSH_FUNC(&stack, &pc, len,code)){
                return 1;
            }
            break;
        case POP:
            if(POP_FUNC(&stack)){
                return 1;
            };
            break;
        case ADD:
            if (ADD_FUNC(&stack))
            {
                return 1;
            }
            break;
        case SUB:
            if (SUB_FUNC(&stack))
            {
                return 1;
            }
            break;
        case MUL:
            if (MUL_FUNC(&stack))
            {
                return 1;
            }
            break;
        
        case DUP:
            if (!DUP_FUNC(&stack)) // im fucking stupid why switch to bool
            {
                return 1;
            }
            break;
        
        case PRNT:
            if (!PRNT_FUNC(&stack))
            {
                return 1;
            }
            break;
        case DIV:
            if (DIV_FUNC(&stack))
            {
                return 1;
            }
            break;
        case END: // ill make it a function later
            int result;
            if (!stack_pop(&stack, &result)) {
                return 1;}
            printf("%d\n", result);
            return 0;
        default:
            fprintf(stderr, "THE FUCK HAVE YOU WROTE %d\n", code[pc - 1]);
            return 1;
        }
    }
    
}

#endif
