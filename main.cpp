//Main.cpp : Main funtion to test class:'Polynomial'
#include "Polynomial.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	//Test addTerm operation
	Polynomial poly1;
	poly1.addTerm(1, 1);
	poly1.addTerm(2, 2);
	poly1.addTerm(2, 1);
	poly1.addTerm(4, 7);
	Polynomial poly2;
	poly2.addTerm(2,1);
	poly2.addTerm(3, 6);

	//poly1.print();
	

	//Test print operation
	cout << "Polynomial 1: ";
	poly1.print();
	cout << "Polynomial 2: ";
	poly2.print();

	//Test divided operation
	Poly_Fraction fraction = poly1.divide(poly2);
	cout << "Poly1 / Poly 2:\n";
	cout << "\tnumerator : ";
	fraction.first.print();
	cout << "\tdenominator : ";
	fraction.second.print();

	//Test delete operation
	//cout << "After delete x^7 , Poly1 : ";
	//poly1.deleteTerm(7);
	//poly1.print();
	//cout << "Polynomial 2: ";
	//poly2.print();

	//Test add operation
	Polynomial poly3 = poly1.add(poly2);
	cout << "Poly1 + Poly2: ";
	poly3.print();

	//Test multiply by a polynomial 
	cout << "Poly1 * Poly2: ";
	Polynomial poly4 = poly1.multi(poly2);
	poly4.print();

	//Test multiply by a float number
	Polynomial poly5 = poly2.multi(2.5);
	cout << "Poly2 multiply 2.5 : ";
	poly5.print();

	//Test divided by a float number
	Polynomial poly6 = poly2.divide(1.2);
	cout << "Poly2 divided by 1.2 : ";
	poly2.print();

	//Test calculate operation
	float x;
	cout << "Input x for poly1:";
	cin >> x;
	cout << "When x=" << x << ", Poly1 = " << poly1.calculate(x) << endl;

	
	system("pause");
	return 0;
}
