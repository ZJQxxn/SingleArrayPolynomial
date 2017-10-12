//Polynomial.cpp: Implementations of class:"Polynomial'
#include "Polynomial.h"
#include <iostream>
#include <cmath>
using std::pow;
using std::cout;
using std::endl;

#define INIT_SPACE	100;
#define MIN(a,b)	(a<b?a:b)

//Initialize static menber
int Polynomial::capacity = INIT_SPACE;
Term* Polynomial::termArray = new Term[Polynomial::capacity];
int Polynomial::free = 0;


//Constructor
Polynomial::Polynomial()
{
	start = free;
	finish = start - 1;
}


//Private Operations:
/*
	Description: Double current capacity when there is no more space.
	Return: void
*/
void Polynomial::_enlargeCap()
{
	int curSpace = capacity;
	int newSpace = capacity * 2;
	Term *newArray = new Term[newSpace];

	//Transfer current data
	for (int i = 0; i < curSpace; i++)
	{

		newArray[i] = termArray[i];
	}
}

/*
	Description: Determine whether termArray is full.
	Return: bool
*/
bool Polynomial::_arrayFull()
{
	return free > capacity;
}

/*
	Description:Determine whether a polynomial is empty;
	Return: bool
*/
bool Polynomial::_polyEmpty()
{
	return start > finish;
}

/*
	Description:Compare two terms' exps.Return positive for a>b;
				0 for a==b; negative for a<b.
	Parameter:a  struct:'Term'	First term you want to compare
	Parameter:b	 struct:'Term'	Second term you want to compare
	Return:int
*/
int Polynomial::_compare(Term &a,Term &b)
{
	return (a.exp - b.exp);
}

/*
	Description:Find the index of exp,return -1 when can't find.
	Parameter:exp	int		Exp you want to locate
	Return:int		Target index
*/
int Polynomial::_at(int exp)
{
	for (int index = start; index <= finish; index++)
	{
		if (termArray[index].exp == exp)
		{
			return index;
		}
	}
	return -1;
}


//Public Operations
/*
Description:Get polinomial length
Return: int		Polynomial length
*/
int Polynomial::getLength()
{
	return (finish - start) + 1;
}

/*
	Description:Add a term in polynomial.If exp is exists,
				just add the coefficients.
	Parameter:coef	float	Term's coefficient
	Parameter:exp	int		Term's exp
	Return: void
*/
void Polynomial::addTerm(float coef, int exp)
{
	int i = _at(exp);
	//This exp already exists
	if (i!= -1)
	{
		termArray[i].coef += coef;
	}

	else
	{
		Term t;
		t.coef = coef;
		t.exp = exp;

		//Enlarge when no more space.
		if (_arrayFull())
		{
			_enlargeCap();
		}

		//Insert the first term of polynomial into termArray.
		if (_polyEmpty() || termArray[start].exp==-1)
		{
			termArray[start] = t;
		}

		else
		{

			//Move backward all the polynomials who are behind current one.
			int index = free - 1;
			for (; index > finish; index--)
			{
				termArray[index + 1] = termArray[index];
				termArray[index].exp = -1;	//Mark as an empty term.
			}

			//Insert term in aceding order.
			for (; index >= start; index--)
			{
				if (termArray[index].exp > t.exp)
				{
					termArray[index + 1] = termArray[index];
					termArray[index].exp = -1;	//Mark as an empty term.
				}
				else
				{
					termArray[index + 1] = t;
					break;
				}
			}
		}
		//Array and polynomial size increment by 1.
		finish++;
		free++;
	}
}

/*
	Description:Delete a term whose exponent is exp
	Parameter:exp	int		Exponent of the term you want to delete.
	Return:void

void Polynomial::deleteTerm(int exp)
{
	int loc_index = _at(exp);
	//If this term exists
	if (loc_index != -1)
	{
		//Move all the terms behind this location forward a step 
		for (; loc_index < free;loc_index++)
		{
			termArray[loc_index] = termArray[loc_index + 1];
		}
		termArray[free-1].exp = -1;	//Mark as an empty term
		//Decrement by 1
		finish--;
		free--;
	}
}
*/

/*
	Description:Add two polynomial.
	Parameter:another	class:'Polynomial'	 Another polynomial you want to add.
	Return:Polynomial	The result polynomial.
*/
Polynomial Polynomial::add(Polynomial &another)
{
	Polynomial result;
	int cur_index = start;
	int ano_index = another.start;
	bool goOn = true;	//Flag to control loop
	while (goOn)
	{
		float coef;
		int exp;
		//Add less term when terms' exps are not same,
		//add summation when terms' exps are the same.
		if (_compare(termArray[cur_index], termArray[ano_index]) < 0)
		{
			coef = termArray[cur_index].coef;
			exp = termArray[cur_index].exp;
			cur_index++;
		}
		else if (_compare(termArray[cur_index], termArray[ano_index]) == 0)
		{
			coef = termArray[cur_index].coef + termArray[ano_index].coef;
			exp = termArray[cur_index].exp;
			cur_index++;
			ano_index++;
		}
		else if (_compare(termArray[cur_index], termArray[ano_index]) > 0)
		{
			coef = termArray[ano_index].coef;
			exp = termArray[ano_index].exp;
			ano_index++;
		}
		result.addTerm(coef, exp);
		goOn = cur_index != (finish + 1) && ano_index != (another.finish + 1);
	}

	//There are some terms not used
	if (getLength() > another.getLength())
	{
		for (; cur_index <= finish; cur_index++)
		{
			result.addTerm(termArray[cur_index].coef, termArray[cur_index].exp);
		}
	}
	else if (getLength() > another.getLength())
	{
		for (; ano_index <= another.finish; ano_index++)
		{
			result.addTerm(termArray[ano_index].coef, termArray[ano_index].exp);
		}
	}

	return result;
}

/*
	Description: Multiply two polynomials.
	Parameter:another	class:'Polynomial'	 Another polynomial you want to multiply with.
	Return:Polynomial	Result polynomial.
*/
Polynomial Polynomial::multi(Polynomial &another)
{
	Polynomial result;
	int cur_index = start;
	for (; cur_index <= finish; cur_index++)
	{
		int ano_index = another.start;
		for (; ano_index <= another.finish; ano_index++)
		{
			float coef = termArray[cur_index].coef*termArray[ano_index].coef;
			int exp = termArray[cur_index].exp + termArray[ano_index].exp;
			result.addTerm(coef, exp);
		}
	}
	return result;
}

/*
Description: Multiply a polynomial by a float number.
Parameter:n		float		A float number you want to multiply with plynomial
Return:Polynomial	Result polynomial.
*/
Polynomial Polynomial::multi(float n)
{
	Polynomial result;
	for (int index = start; index <= finish; index++)
	{
		float coef = termArray[index].coef *= n;;
		int exp = termArray[index].exp;
		result.addTerm(coef, exp);
	}
	return result;
}

/*
	Description:Divide polynomial by a float number
	Parameter:n	float	The float number
	Return:Polynomial	Result polynomial
*/
Polynomial Polynomial::divide(float n)
{
	Polynomial result;
	for (int index = start; index <= finish; index++)
	{
		float coef = termArray[index].coef /= n;;
		int exp = termArray[index].exp;
		result.addTerm(coef, exp);
	}
	return result;
}

/*
	Description:Simply divide two polys.
	Parameter:another	class:'Polynomial'	The poly you want to divide with
	Return:typedef:'Poly_Fration'		A pair of class:'Polynomial' instances,
										first is the numerator and second is 
										the denominator.
*/
Poly_Fraction Polynomial::divide(Polynomial &another)
{
	Polynomial numerator;
	int least_exp = MIN(termArray[start].exp, termArray[another.start].exp);
	float coef;
	int exp;

	//Simplify numerator
	for (int cur_index = start; cur_index <= finish; cur_index++)
	{
		coef = termArray[cur_index].coef;
		exp = termArray[cur_index].exp - least_exp;
		numerator.addTerm(coef, exp);
	}

	//Simplify denominator
	Polynomial denominator;
	for (int ano_index = another.start; ano_index < another.finish; ano_index++)
	{
		coef = termArray[ano_index].coef;
		exp = termArray[ano_index].exp - least_exp;
		denominator.addTerm(coef, exp);
	}

	return Poly_Fraction(numerator, denominator);
}


/*
	Description:Calculate the value of polynomial when x=x0
	Parameter:x0	float	Value of x
	Return:float	Value of result
*/
float Polynomial::calculate(float x0)
{
	float result = 0;
	for (int index = start; index <= finish; index++)
	{
		result += termArray[index].coef*pow(x0, termArray[index].exp);
	}
	return result;
}

/*
	Description: Print a polynomial.
	Return: void
*/
void Polynomial::print()
{
	
	if (!_polyEmpty())
	{
		cout << termArray[start].coef << "x^" << termArray[start].exp;
		for (int index = start+1; index <= finish; index++)
		{
			if (termArray[index].coef != 0)
			{
				cout << '+' << termArray[index].coef << "x^" << termArray[index].exp;
			}
		}
		cout << endl;
	}
	else
	{
		cout << "The polynomial is empty" << endl;
	}
	
}
