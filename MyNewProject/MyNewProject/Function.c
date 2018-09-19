#pragma once
#include"Function.h"



// This initialize a stack with default values
void initStack(aStack * myStack) {

	myStack->TOP = 0; // The stack is empty
	myStack->ArrayStr = NULL;

}

// This fuction verifies if the stack is empty or there is something in already
BOOL isEmptyStack(aStack * iStack) {

	BOOL result = FALSE;
	if ((iStack->TOP == 0) && (iStack->ArrayStr == NULL)) {
		result = TRUE;
	}
	else {
		result = FALSE;
	}

	return result;
}


// Make the push function a Boolean in order to verify if the push is succesful

BOOL push(aStack *myStack, char aWord[]) {

	BOOL result = FALSE; // By default the push fails


	if (isEmptyStack(myStack) == TRUE) {
		/*The stack is empty we just add an element in a 2D array*/

		/*Dynamically allocate the memory */
		myStack->ArrayStr = (char**)malloc(sizeof(char*));

		/*Check if the memory is correctly allocated
		if the memory is available then proceed */

		if (myStack->ArrayStr != NULL) {
			/*The memory was properly allocated*/


			myStack->ArrayStr[myStack->TOP] = (char*)malloc(strlen(aWord) * sizeof(char));

			if (myStack->ArrayStr != NULL) {
				/* We have successfully allocated memory for the word*/
				strcpy_s(myStack->ArrayStr[myStack->TOP], strlen(aWord)+1, aWord);
				myStack->TOP = myStack->TOP + 1;

				result = TRUE;
			}
			else {
				printf("ERROR (PUSHFUNCT): Memory allocation failed");
				result = FALSE;
			}



		}
		else {
			printf("ERROR (PUSHFUNCT): Memory allocation failed");
			result = FALSE;
		}



	}
	else {

		/* The Stack is not empty we need to copy the content
		of the smaller stack to a bigger one (one more element)*/

		/*Copy the link to the actual memory path*/
		char ** thePath = myStack->ArrayStr;

		/*Create a Bigger array (one more element to accomadate the Push)*/

		char ** NewArray = NULL;

		NewArray = (char **)malloc((myStack->TOP + 1) * sizeof(char*));

		/* If the memory is properly allocated copy the content of the old array to
		the newly allocated memory*/

		if (NewArray != NULL) {

			int LOOP;
			//char WordCopied;
			for (LOOP = 0; LOOP < myStack->TOP; LOOP++) {
				int wordLength = 1;
				//wordLength = strlen(myStack->ArrayStr[LOOP]);
				wordLength = strlen(myStack->ArrayStr[LOOP]);

				/* We first need to create the 2nd dimention of the array*/
				NewArray[LOOP] = (char *)malloc((wordLength + 1) * sizeof(char));

				/*Before processing make sure the memory is properly allocated*/
				if (NewArray[LOOP] != NULL) {

					//strcpy(NewArray[LOOP], myStack->ArrayStr[LOOP]);
					strcpy_s(NewArray[LOOP], (wordLength + 1), myStack->ArrayStr[LOOP]);
					*(thePath + LOOP) = myStack->ArrayStr[LOOP];/* Keep the address of this memory location*/

				}
				else {
					printf("ERROR (PUSH): DYNAMIC MEMORY ALLOCATION FAILED\n");
					return FALSE;
				}




			}/*End of the for loop*/


			 /* After the loop, the entire array is copied to the new location
			 We also need to insert the new valus

			 This is where we actually execute the push

			 */
			NewArray[LOOP] = (char *)malloc(strlen(aWord) * sizeof(char));

			if (NewArray[LOOP] != NULL) {

				strcpy_s(NewArray[LOOP], strlen(aWord)+1, aWord);
				/* Now Swap the old array with the newly created on*/
				myStack->ArrayStr = NewArray;
				/*Increment the size*/
				myStack->TOP = myStack->TOP + 1;

				/*Now do the cleaning free the space on memory
				used by the old array*/

				/*
				int j;
				for (j = 0;j < myStack->TOP - 1; j++) {
				free(thePath[j]);
				}
				free(thePath);
				*/
			}
			else {

				printf("ERROR (PUSH): DYNAMIC MEMORY ALLOCATION FAILED\n");
				return FALSE;
			}




		}
		else {
			printf("ERROR (PUSH): DYNAMIC MEMORY ALLOCATION FAILED\n");
			return FALSE;
		}

	}

	return result;

}


BOOL destroyArrayStack(aStack * myStack) {

	BOOL state = FALSE;

	if (isEmptyStack(myStack) == FALSE) {

		int LOOP;
		for (LOOP = 0; LOOP < myStack->TOP; LOOP++) {

			if (myStack->ArrayStr[LOOP] != NULL) {
				free(myStack->ArrayStr[LOOP]);
				myStack->ArrayStr[LOOP] = NULL;
			}

		}

		free(myStack->ArrayStr);
		myStack->ArrayStr = NULL;

		state = TRUE;

	}
	else {
		printf("WARNING: THE STACK IS EMPTY. NOTHING TO CLEAN\n");
		state = TRUE;
	}

	return state;

}


void displayStack(aStack *myStack) {



	printf("\t_______\n");
	int i;
	for (i = myStack->TOP - 1; i >= 0; i--) {
		printf("\t%s\n", myStack->ArrayStr[i]);
	}

	printf("\t_______\n");


}




void pop(aStack *myStack) {

	if (isEmptyStack(myStack)==TRUE) {
        /*The Stack is empty there is nothing to pop out*/

		printf("(INFO POP): The stack is empty there is nothing to pop Out\n");

	}
	else {
		/* There is something to process*/

		char **thePath; /*Used to save the path of the current array*/
		thePath = myStack->ArrayStr;

		char ** NewArray;
		NewArray = (char**)malloc(sizeof(char*)*(myStack->TOP-1));
		if (NewArray != NULL) {

			int LOOP;
			for (LOOP = 0;LOOP < myStack->TOP - 1; LOOP++) {
				int wordLength = strlen(myStack->ArrayStr[LOOP]);
				NewArray[LOOP] = (char *)malloc((myStack->TOP-1) * sizeof(char));
				strcpy_s(NewArray[LOOP], (wordLength+1), myStack->ArrayStr[LOOP]);
				*(thePath + LOOP) = myStack->ArrayStr[LOOP];
			}
		}
		else {
			printf("(INFO POP): 1 Dynamic allocation Failed\n");
		}
		myStack->ArrayStr = NewArray;
		myStack->TOP--;

		/*We need to do the free here*/
	}

}


char Preprocess(aStack *myStack) {

	char anExpression[100];
	printf("Enter an Expression: ");
	scanf_s("%[^\n]", anExpression, sizeof(anExpression));

	printf("You have entered: %s\n", anExpression);
	int expLen = strlen(anExpression);

	// Remove space from the expression

	//Create a buffer to hold the new expression: The space should be removed
	// since we dont know the size of the word in advance we dynamically allocate memory
	char *newExpression = (char*)malloc(sizeof(char)*expLen);

	char *np = newExpression, *op = anExpression;
	do {
		if (*op != ' ')
			*np++ = *op;
	} while (*op++);

	printf("The new processed String is : %s\n", newExpression);

	char aChar[2];
	aChar[1] = '\0';


	int LOOP;
	for (LOOP = 0; LOOP < strlen(newExpression);LOOP++) {
	

		aChar[0] = newExpression[LOOP];

		if (isEmptyStack(myStack)== TRUE) {
			/*The stack is empty just push*/
			push(myStack, aChar);

		}
		else {
			/*The stack is not Empry */
			if (isNumber(aChar[0])==TRUE) {
				/* The cursor is a number*/
				char myTop[2];
				 myTop[1] = '\0';
				myTop[0] = myStack->ArrayStr[myStack->TOP - 1];

				if (isNumber(myTop[0])==TRUE) {
					int strsize = strlen(myStack->ArrayStr[myStack->TOP - 1]);
					char *TopEl = (char*)malloc(sizeof(char)*strsize);

					if (TopEl != NULL) {

						strcpy_s(TopEl, strsize + 1, myStack->ArrayStr[myStack->TOP - 1]);
					}
					else {
						/*Dynamic alloc failed*/
						printf("Dynamic allocation failed\n");
					}
				}
				else {
					/*The TOp element is not a number*/
					push(myStack, aChar);
				}

			}
			else {
				/*The Cursor is not a number so we just push it in*/
				push(myStack, aChar);
			}

		}
		
	
	}




	return "TEST";
}


BOOL isNumber(char achar) {
	BOOL  result = FALSE;

	if (achar >= '0' && achar <='9') {
		result = TRUE;
	}
	else {
		result = FALSE;
	}
	return result;
}