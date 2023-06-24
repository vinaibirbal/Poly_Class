#include <iostream>
#include <math.h>
#include "polynomial.h"
using namespace std;

#define ACCURACY 0.001

///////////////////////////////////////////////////////////////////////////
//
// Public operators and methods


Polynomial Polynomial::dx() const
{
	return derivative();
}

float Polynomial::operator()(const float x) const 
{
	return evaluate(x);
}

Polynomial Polynomial::operator+(const Polynomial& p) const 
{
	return add( p);
}

Polynomial Polynomial::operator*(const Polynomial& p) const 
{
	if(p._degree < 0 || _degree < 0)
	{
		return Polynomial(0, NULL);
	}
	int degree = _degree + p._degree;
	Variable* coeff = (struct Variable*) malloc(sizeof(struct Variable));
    Variable* vop1 = _variables;
    Variable* vop2 = p._variables;

	for(int j = 0; j <= _numvariables; j++)
	{
		for(int a = 0; a <= p._numvariables; a++)
		{
			int d = a + j;
            int newcoeff = vop1->coefficient * vop2->coefficient;
			insertspecial(coeff, newcoeff, d)
            vop2 = vop2->next;
		}
        vop1 = vop1-> next;
	}
	Polynomial pOut(degree, coeff);
	return pOut;
}

void Polynomial::operator=(const Polynomial& p) 
{
    Variable* var1 = _variables;
    Variable* var2 = p._variables;
	_degree = p._degree;
    _numvariables = p._numvariables;
	for(int i = 0; i < _numvariables; i++)
	{
		var2->coefficient = var1->coefficient;
        if(var1-> next = nullptr;) {
            insert((&Variable old_var, int new_coefficient, int new_power))
        }
        else{
            var2 = var2-> next;
        }
        var1 = var1->next;
	}
}

bool Polynomial::operator==(const Polynomial& p) const 
{
	if(p._degree < 0 || _degree < 0)
	{
		return false;
	}
	if (p._degree != _degree)
	{
		return false;
	}
	for (int i = 0; i < _degree + 1; i++)
	{
		if(fabs(p._coeff[i] - _coeff[i]) > ACCURACY)
		{
			return false;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
//
// Constructors and Destructor
//
// Note: no default constructor
//

Polynomial::Polynomial(const Polynomial& p)
 {
	_degree = p._degree;
	_coeff = new float[_degree+1];
	for(int i = 0; i <= p._degree; i++)
	{
		_coeff[i] = p._coeff[i];
	}
}

Polynomial::Polynomial(const int degree, const float coeff[]) 
{
	if(degree < 0)
	{
		_degree = -1;
		_coeff = NULL;
	}
		
	else
	{
		_degree = degree;
		_coeff = new float[_degree+1];
	
		for(int i = 0; i <= degree; i++)
		{
			_coeff[i] = coeff[i];
		}
	}
}

Polynomial::~Polynomial() 
{
	_degree = -1;
	delete []_coeff;
}

///////////////////////////////////////////////////////////////////////////
//
// Private Methods
//

float Polynomial::evaluate(const float x) const 
{
	double f;
	if(_degree < 0 || _coeff == NULL)
	{
		return -1;
	}
	else if(_degree > 0)
	{
		f = _coeff[0] * x;
	}
	else if(_degree == 0)
	{
		f = _coeff[0];
	}
	for(int i = 1; i < _degree ; i++)
	{
		f = x * (_coeff[i] + f);
	}
	f += _coeff[_degree];
	return f;
}

Polynomial Polynomial::add(const Polynomial& pIn) const 
{
	int pd1 = 0;
	int pd2 = 0;
	int degree = 0;
	if(_degree < 0 || pIn._degree < 0)
	{
		return Polynomial(-1, NULL);
	}
	else if( _degree > pIn._degree)
	{
		degree = _degree;
		pd2 = degree - pIn._degree;
	}
	else if (pIn._degree > _degree)
	{
		degree = pIn._degree;
		pd1 = degree - _degree;
	}
	else
	{
		degree = _degree;
	}
	int pd = 0;
	if(pd1)
	{
		pd = pd1;
	}
	if(pd2)
	{
		pd = pd2;
	}
	float* coeff = new float[degree + 1];
	for(int i = 0; i < pd; i++)
	{
		if(pd1)
		{
			coeff[i] = pIn._coeff[i];
		}
		else if (pd2)
		{
			coeff[i] = _coeff[i];
		}
		else
		{
			coeff[i] = pIn._coeff[i] + _coeff[i];
		}
	}
	for(int i = pd; i < degree + 1; i++)
	{
		if(pd1)
		{
			coeff[i] += _coeff[i - pd] + pIn._coeff[i];
		}
		else if (pd2)
		{
			coeff[i] += pIn._coeff[i - pd] + _coeff[i];
		}
		else
		{
			coeff[i] = pIn._coeff[i] + _coeff[i];
		}
	}
	Polynomial pOut(degree, coeff);
	delete[] coeff;
	return pOut;
}

Polynomial Polynomial::derivative() const {

	if(_degree < 0)
	{
		return Polynomial(-1, NULL);
	}
	if(_degree == 0)
	{
		float* coeff = new float[1];
		coeff[0] = 0;
		Polynomial pOut(-1, coeff);
		delete[] coeff;
		return pOut;
	}
	int degree = _degree;
	float* coeff = new float[_degree - 1];
	for(int i = 0; i < _degree ; i++)
	{
		coeff[i] = _coeff[i] * degree;
		degree --;
	}
	Polynomial pOut(_degree - 1, coeff);
	delete[] coeff;
	return pOut;
}
Variable* insert(&Variable old_var, int new_coefficient, int new_power) { 
    struct Variable* new_node = (struct Variable*) malloc(sizeof(struct Variable)); 
    new_node->coefficient = new_coefficient; 
    new_node->coefficient = new_power;
    new_node->next = old_var->next ; 
    old_var-> next = new_node;
    
   return new_node;
}

Variable* insertspecial(&Variable previous_var, int new_coefficient, int new_power) { 
    Variable* nextvar = previous_var;
    while( nextvar-> next != nullptr && nextvar -> power < new_power)
    {
        nextvar = nextvar -> next;
    }
    if( nextvar != nullptr && nextvar-> power == new_power)
    {
        nextvar-> coefficient = new_coefficient;
    }
    else{
     insert(next_var, int new_coefficient, int new_power);
    }
    return nextvar-> next
       
} 