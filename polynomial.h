
//////////////////////////////////////////////////////////////////////////
//
// Class: Polynomial
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


struct Variable {
  int      power;   // power of variable
  int      coefficient;  // coefficient of variable
  struct Variable* next;
};
class Polynomial {
public:
  Polynomial dx() const;                                // Derivative of Polynomial
  
  float operator()(const float x) const;                // Evaluate Polynomial
  Polynomial operator+(const Polynomial& p) const;      // Add 
  Polynomial operator*(const Polynomial& p) const;      // Multiply
  void operator=(const Polynomial& p);                  // Assignment
  bool operator==(const Polynomial& p) const;           // Equality (relative, not exact, since float coeff)
  
  Polynomial(const Polynomial& p);                      // Copy constructor
  Polynomial(int degree, const Variable& vars);    // Create from a variable linked list
  ~Polynomial();                                        // Destructor: get rid of the coeff array

private:
 
  float evaluate(const float x) const;                  // Evaluate Polynomial
  Polynomial add(const Polynomial& p) const;            // Add (from struct)
  Polynomial derivative() const;                        // Derivative (from struct) 

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);  // Polynomial printing
  
  int    _degree;
  int    _numvariables;
  Variable* _variables;
};


std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
  if (p._degree < 0) {
    std::cerr << "Error: Attempted to output deleted polynomial; exiting";
    exit(-1);
  }
  Variable* var = p._variables;
  while (p._var-> next != nullptr){
    if (p._var-> coefficient == 1) 
      os << "x";
    else
      os << p._var-> coefficient  << "x";
    if ( p._var-> power > 1) 
      os <<  "^" << p._var-> power;
    os << " + ";
    var = var-> next;

  }
  os << var->coefficient;
  return os;
}

#endif
