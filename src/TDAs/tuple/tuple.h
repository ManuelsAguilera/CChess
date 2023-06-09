#ifndef tuple_h
#define tuple_h

typedef struct tuple tuple;

tuple createTuple(int,int);
void nullifyTuple(tuple); 
int isnull(tuple); //returns 1 if it is

//operations
tuple sumTuple(tuple summand1,tuple summand2);
tuple substractTuple(tuple minuend, tuple subtrahend);
tuple multiplyTuple(tuple multiplicand,tuple multiplier);
tuple scaleTuple(tuple T,int scalar);
tuple divideTuple(tuple dividend,tuple divisor);
//comparation
int cmpTuple(tuple first,tuple second);



#endif