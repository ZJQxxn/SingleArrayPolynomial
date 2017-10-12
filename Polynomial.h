//Polynomial.h : Declaration of class:'Polynomial'
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
using std::pair;

class Polynomial;
typedef pair<Polynomial, Polynomial> Poly_Fraction;

//Struct:'Term': Polynomial term.
struct Term
{
	float coef;
	int exp;
};

//Class:'Polynomial': See inplementations in Polynomial.cpp
class Polynomial
{
private:
	static Term *termArray;	//Set static to store all the terms of all the polynamials
	static int capacity;	//Max size of termArray
	static int free;		//Next free location to store a term
	int start, finish;		//Not static as it represents start and finish positon of each polynomial
	void _enlargeCap();
	bool _arrayFull();
	bool _polyEmpty();
	int _compare(Term &a,Term &b);
	int _at(int exp);
public:
	Polynomial();
	int getLength();
	void addTerm(float coef,int exp);

	//By using array, deleteTerm() operation can't be implemented
	//as we can't move the start positions of polys behind current.
	//void deleteTerm(int exp);		

	Polynomial add(Polynomial& another);
	Polynomial multi(Polynomial& other);
	Polynomial multi(float n);
	Poly_Fraction divide(Polynomial& other);
	Polynomial divide(float n);
	float calculate(float x0);
	void print();
};

#endif