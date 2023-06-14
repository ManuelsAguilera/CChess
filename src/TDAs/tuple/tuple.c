#include <stdlib.h>
#include <stdio.h>

typedef struct tuple {
	int x;
	int y;
} tuple;

tuple* createTuple(int x,int y) //constructor
{
	
	tuple*  New;
	New = malloc(sizeof(tuple));
	New->x=x;
	New->y=y;
	return New;
}

void nullifyTuple(tuple* T)
{
	free(T);
	T=NULL;
}



void sumTuple(tuple* summand1,tuple* summand2)
{
	//check if a summand is null
	if (summand1 == NULL || summand2 ==NULL)
		return;
	//else
	summand1->x += summand2->x;
	summand1->y += summand2->y;
	return;
}

void substractTuple(tuple* minuend, tuple* subtrahend)
{
	if ( minuend == NULL || subtrahend == NULL)
		return;
	//else
	minuend->x += (-1)*subtrahend->x;
	minuend->y += (-1)*subtrahend->y;
	return;
}

void multiplyTuple(tuple* multiplicand,tuple* multiplier)
{
	if ( multiplicand == NULL || multiplier == NULL)
		return;
	//else
	multiplicand->x *= multiplier->x;
	multiplicand->y *= multiplier->y;
	return;
}

void scaleTuple(tuple* T,int scalar)
{
	if (T == NULL) return;
	T->x*=scalar;
	T->y*=scalar;
	return;
}


void divideTuple(tuple* dividend,tuple* divisor) //this is int division
	{
		
		if ( dividend == NULL  || divisor == NULL)
			return;
		//else
		dividend->x /= divisor->x;
		dividend->y /= divisor->y;
		return;
	}

int cmpTuple(tuple* first,tuple* second)
{
	
	if (first->x == second->x)
		if (first->y == second->y)
			return 1;
	//<else
	return 0;	
}