// exp_eval.h
// Evaluate a given experssion where tokens are separated by space.

#ifndef EXP_EVAL_H_
#define EXP_EVAL_H_
#include <stack>
#include <string>

// Function to find precedence of operators. 
int precedence(char op) { 
	if(op == '+'||op == '-') 
	  return 1; 
	if(op == '*'||op == '/') 
	  return 2; 
	return 0; 
} 

// Function to perform arithmetic operations. 
int apply_op(int a, int b, char op) { 
	switch(op){ 
		case '+': return a + b; 
		case '-': return a - b; 
		case '*': return a * b; 
		case '/': return a / b;
    default: return op;
	} 
} 

// Function that returns value of 
// expression after evaluation. 
int evaluate(std::string tokens){ 
  std::stack <int> values;  // stack to store integer values 
  std::stack <char> ops;  // stack to store operators. 
	
	for(int i = 0; i < tokens.length(); i++){ 
		if(tokens[i] == ' ')  // skip whitespace 
			continue; 
		else if(tokens[i] == '(')
			ops.push(tokens[i]); 
		else if(isdigit(tokens[i])) {  // number
			int val = 0; 
			while(i < tokens.length() && isdigit(tokens[i])) {  // keep processing digits
				val = (val*10) + (tokens[i]-'0'); 
				i++; 
			} 
			values.push(val); 
		} else if(tokens[i] == ')') {  // closing brace encountered, solve entire brace.  
			while(!ops.empty() && ops.top() != '(') {
				int val2 = values.top(); values.pop(); 
				int val1 = values.top(); values.pop(); 
				char op = ops.top(); ops.pop(); 
				values.push(apply_op(val1, val2, op)); 
			} 
			ops.pop();  // pop opening brace. 
		} else {  // operator tokens
			// While top of 'ops' has same or greater precedence to current token, which 
			// is an operator. Apply operator on top of 'ops' to top two elements in values stack. 
			while(!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) { 
				int val2 = values.top(); values.pop(); 
				int val1 = values.top(); values.pop(); 
				char op = ops.top(); ops.pop(); 
				values.push(apply_op(val1, val2, op)); 
			} 
			ops.push(tokens[i]);  // push current token to 'ops' 
		} 
	} 
	
	// Entire expression has been parsed at this point,
  // apply remaining ops to remaining values. 
	while(!ops.empty()){ 
		int val2 = values.top(); values.pop(); 
		int val1 = values.top(); values.pop(); 
		char op = ops.top(); ops.pop(); 
		values.push(apply_op(val1, val2, op)); 
	} 
	
	// Top of 'values' contains result, return it. 
	return values.top(); 
} 

#endif  // EXP_EVAL_H_
