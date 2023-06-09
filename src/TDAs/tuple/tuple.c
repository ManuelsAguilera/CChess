#include <stdlib.h>
typedef struct tuple {
	int null;
	int x;
	int y;
} tuple;

tuple createTuple(int x,int y) //constructor
{
	tuple new;
	new.x=x;
	new.y=y;
	new.null=0;
	return new;
}

void nullifyTuple(tuple T)
{
	private T.null  = 1;
	T.x=0;
	T.y=0;
}

int isnull(tuple T)
{
	return (T.null);
}

tuple sumTuple(tuple summand1,tuple summand2)
{
	tuple new;
	//check if there are null summands
	if ( isnull(summand1) | isnull(summand2) )
		return nullifyTuple(new);
	//else
	new.x = summand1.x + summand2.x;
	new.y = summand1.y + summand2.y;
	return new;
}

tuple substractTuple(tuple minuend, tuple subtrahend)
{
	tuple new;
	if ( isnull(minuend) | isnull(subtrahend))
		return nullifyTuple(new);
	//else
	new.x = minuend.x - subtrahend.x;
	new.y = minuend.y - subtrahend.y;
	return new;
}

tuple multiplyTuple(tuple multiplicand,tuple multiplier)
{
	tuple new;
	if ( isnull(multiplicand) | isnull(multiplier))
		return nullify(new);
	//else
	new.x = multiplicand.x * multiplier.x;
	new.y = multiplicand.y * multiplier.y;
	return new;
}

tuple scaleTuple(tuple T,int scalar)
{
	if (isnull(T)) return T;
	T.x*=escalar;
	T.y*=escalar;
	return T;
}


tuple divideTuple(tuple dividend,tuple divisor) //this is int division
	{
		tuple new;
		if ( isnull(dividend) | isnull(divisor))
			return nullifyTuple(new);
		//else
		new.x = dividend.x / divisor.x;
		new.y = dividend.y / divisor.y;
		return new;
	}

int cmpTuple(tuple first,tuple second)
{
	if (first.null == second.null)
		if (first.x == second.x)
			if (first.y == second.y)
				return 1;
	//else
	return 0;	
}