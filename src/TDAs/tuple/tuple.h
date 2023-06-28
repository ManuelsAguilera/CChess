#ifndef tuple_h
#define tuple_h
#include <stdio.h>
#include <stdlib.h>
#include "../arraylist/arraylist.h"

typedef struct tuple {
	int x;
	int y;
} tuple;

tuple* createTuple(int,int);
void nullifyTuple(tuple* T);
void cpyTuple(tuple* newCopy, tuple* current);
//operations
tuple* sumTuple(tuple* summand1,tuple* summand2);
tuple* substractTuple(tuple* minuend, tuple* subtrahend);
tuple* multiplyTuple(tuple* multiplicand,tuple* multiplier);
tuple* scaleTuple(tuple* T,int scalar);
tuple* divideTuple(tuple* dividend,tuple* divisor);

void linearCombination(tuple* vectors[], ArrayList* storage );
//comparation
int cmpTuple(tuple* first,tuple* second);



#endif