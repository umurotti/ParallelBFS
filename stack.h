/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   stack.h
 * Author: umur
 *
 * Created on November 20, 2020, 1:28 PM
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif
struct Stack { 
    int top; 
    unsigned capacity; 
    int* array; 
}; 
  
// function to create a stack of given capacity. It initializes size of 
// stack as 0 
struct Stack* createStack(unsigned capacity);
  
// Stack is full when top is equal to the last index 
int isFull(struct Stack* stack);
  
// Stack is empty when top is equal to -1 
int isEmpty(struct Stack* stack);
  
// Function to add an item to stack.  It increases top by 1 
void push(struct Stack* stack, int item);
  
// Function to remove an item from stack.  It decreases top by 1 
int pop(struct Stack* stack);
  
// Function to return the top from stack without removing it 
int peek(struct Stack* stack);

#ifdef __cplusplus
}
#endif

#endif /* STACK_H */

