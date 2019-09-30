#include "exp_eval.h"

#include <iostream>
#include <vector>

using namespace std;

int main() { 
  vector<string> expressions = {
	  "10 + 2 * 6",  
	  "100 * 2 + 12",  
	  "100 * ( 2 + 12 )", 
	  "100 * ( 2 + 12 ) / 14"};

  for (int i=0; i<expressions.size(); ++i) {
    cout << expressions[i] << " = " << evaluate(expressions[i]) << endl;
  }
	return 0; 
} 
