#include <stdlib.h>
#include <stdio.h>
#include "../arraylist/arraylist.h"

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

void cpyTuple(tuple* newCopy, tuple* current)
{
	newCopy = createTuple(current->x,current->y);
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

//This only is an implementation for us.
//it will not have all the linearCombinations posible
//it only appends linear combination of each scalated with 1 and -1
//of 2 vectors

void linearCombination(tuple* vectors[], ArrayList* storage )
{
	int scalars[8] = {1,1 ,-1,-1, -1,1, 1,-1};
	tuple* copy[2];
	cpyTuple(copy[0],vectors[0]);
	cpyTuple(copy[1],vectors[1]);
		
	for (int index_array = 0; index_array < 8;index_array+=2 ) //this counter is to use scalars
		{
			scaleTuple(copy[0],scalars[index_array]);
			scaleTuple(copy[1],scalars[index_array+1]);
			
			sumTuple(copy[0],copy[1]);
			
			append(storage,copy[0]);
			nullifyTuple(copy[0]); nullifyTuple(copy[1]);
			//restore data
			cpyTuple(copy[0],vectors[0]);
			cpyTuple(copy[1],vectors[1]);
		}
	//delete data used in function
	nullifyTuple(copy[0]); nullifyTuple(copy[1]);
}

int cmpTuple(tuple* first,tuple* second)
{
	
	if (first->x == second->x)
		if (first->y == second->y)
			return 1;
	//<else
	return 0;	
}


/*int main()
{
	printf("Testing\n");
	tuple* mov[2];
	mov[0] = createTuple(0,1);
	mov[1] = createTuple(1,0);

	ArrayList* New = createList();
	linearCombination(mov, New);

	
	for (int i  = 0; i < get_size(New); i++)
		printf("%2d,%d",*get(New,i)->x,*get(New,i)->y);
	
}*/