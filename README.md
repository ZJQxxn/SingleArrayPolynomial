# SingleArrayPolynomial
class 'Polynomial' implement by using a single array to store all the coefficients and exponents.

##struct:'Term'
struct:'Term' stores data of a polynomial term

    struct Term
    {
        float coef;
        int exp;
    }


##class:'Polynomial'
###Introduction
I store nonzeor terms of all the polynomials into s single array  *termArray*
 
>The member variables should be: 

    private:
        static Term* termArray;
        static int free;
        int start,finish;

>Static variable `free` is the index of next avalible space.`start` and `finish` points at the start position and finish position of a polynomial. 
###Operations
- `addTerm(float coef,int exp)`

>Add a term into polynomial by passing coefficient and exponent(should be positive) 

- `add(Polynomial another)` 
>Add this polynomial to another and return the result(class:'Polynomial)

- `multi(Polynomial)`
>Multiply this polynomial to another,and return the result(class:'Polynomial')

- `multi(float n)`
>Multiply this polynomial to a float number,and return the result(class:'Polynomial')

-`divide(Polynomial another)`
>Divide this polynomial by another(actually just simplify the fraction),return a pair of instance of class:'Polynomial',whose first is numerator and second is denominator.

-`divide(float n)`
>Divide this polynomial by a float number,return the result(class:'Polynomial')

- `calculate(float x0)`
>Given the x0,calculate this polynomial

- `print()`
>Print this polynomial




##Tips:
Because of the weakness of designing class:'Polynomial', you can't create more than one instance of class:'Polynomial' at once.You must create only one instance when you need,
    
    Polynomial poly1;
    Polynomial poly2;
    poly1.addTerm(1,1);
    poly2.addTerm(2,1);

Method above is not proper.It can cause mess in storing polynomials.You can use it like this:
    
    Polynomial poly1;
    poly1.addTerm(1,1);
    Polynomial poly2;
    poly2.addTrm(2,1);
    poly1.addTerm(2,2);

 
10/12/2017 8:26:33 PM 
