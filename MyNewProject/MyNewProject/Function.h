#pragma once
#include<stdlib.h>
#include<string.h>
#include<stdio.h>



typedef int BOOL;
#define FALSE 1
#define TRUE 0

typedef struct {

	char **ArrayStr;
	int TOP;

}aStack;

void initStack(aStack * myStack);
BOOL push(aStack *myStack, char aWord[]);
BOOL destroyArrayStack(aStack * myStack);
void displayStack(aStack *myStack);
void pop(aStack *myStack);
char Preprocess(aStack *myStack);
BOOL isNumber(char achar);

