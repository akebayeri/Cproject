#pragma once
#include "Function.h"




int main() {




	aStack testStack;
	aStack Expression;



	initStack(&testStack);
	initStack(&Expression);
	char TheWord[256] = "FOND";




	push(&testStack, TheWord);

	//char **aPointer = NULL;
	//aPointer = &testStack;

	push(&testStack, "ELEMENT2");
	push(&testStack, "()");
	push(&testStack, "+");

	push(&testStack, "/");
	push(&testStack, "19");

	displayStack(&testStack);

	pop(&testStack);

	displayStack(&testStack);


	char Test = Preprocess((&Expression));

	displayStack(&Expression);

	system("pause");
	return 0;
}