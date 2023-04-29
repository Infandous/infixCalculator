#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>

#include "MyStack.h"
#include "MyVector.h"

class MyInfixCalculator{

  public:
    
    MyInfixCalculator()
    {

    }

    ~MyInfixCalculator()
    {
     
    }

    double calculate(const std::string& s)
    {
        // code begins
	MyVector<std::string> infixTokens;
	MyVector<std::string> postfixTokens;
	tokenize(s,infixTokens);
	//std::cout<<"Out of tokenize func"<<std::endl;
	/*for (int i =0; i<infixTokens.size();i++){
		std::cout<<infixTokens[i]<<" "<<infixTokens[i].size()<<std::endl;
	}*/
	infixToPostfix(infixTokens,postfixTokens);
	//std::cout<<"out of infixToPostfix"<<std::endl;
	/*for (int x = 0; x<postfixTokens.size();x++){
		std::cout<<postfixTokens[x]<<std::endl;
	}*/
	return calPostfix(postfixTokens);

        // code ends
    }

  private:

    // returns operator precedance; the smaller the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {
            case '*':
                return 2;
            case '/':
                return 2;
            case '+':
                return 3;
            case '-':
                return 3;
            default:
                return 0;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
	//std::cout<<"ornd1: "<<ornd1<<std::endl;
	//std::cout<<"Ornd2: "<<ornd2<<std::endl;
	//std::cout<<"Operator: "<<opt<<std::endl;
	//std::cout<<ornd1<<" "<<opt<<" "<<ornd2<<std::endl;
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':
                return o1 / o2;
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    // tokenizes an infix string s into a set of tokens (operands or operators)
    void tokenize(const std::string& s, MyVector<std::string>& tokens)
    {
        // code begins
	//std::cout<<"In tokenize func"<<std::endl;
	std::string temp = "";
	for (int i = 0; i<s.length(); i++){ //for every char in string s
		//std::cout<<"Looping..."<<std::endl;
		if (isDigit(s.at(i))){ //if char is a positive digit
			while (i<s.length()&&(isDigit(s.at(i))||s.at(i)=='.')){
			//while (((isDigit(s.at(i)))||(s.at(i)=='.'))&&(i<s.length())){ //while we are still getting part of the number
				//i++;
				//std::cout<<"getting positive number at index "<<i<<": "<<s.at(i)<<". Size: "<<s.length()<<std::endl;
				temp += s.at(i); //add to temp
				i++; //increment i
			}
			/*if ((i+1)==s.length()){
				//std::cout<<"breaking"<<std::endl;
				break;
			}*/
			i--; //while loop overincrements by 1
			//std::cout<<"Pushing the operand "<<temp<<" to vector"<<std::endl;
			tokens.push_back(temp); //push back temp
			if ((i+2)==s.length())
				break;
			temp = ""; //reset temp
		}else if (isValidParenthesis(s.at(i))){ //if char is a parenthesis
			//std::cout<<"Pushing parenthesis "<<std::string(1,s.at(i))<<" to vector"<<std::endl;
			tokens.push_back(std::string(1,s.at(i)));
		}else if(operatorPrec(s.at(i))){ //if char is an operator (function returns 0(I changed from -1) otherwise)
			if (s.at(i)=='-'){ //check if char denotes subtraction of negativity
				if (i==0){
					temp += s.at(i);
                                        i++; //increment i
					while (i<s.length()&&(isDigit(s.at(i))||s.at(i)=='.')){
						//std::cout<<"adding negative number at index "<<i<<": "<<s.at(i)<<std::endl;
                                                //i++;
                                                temp+=s.at(i); //add to temp string
                                                i++;//increment
					}
					i--; //while loop overincrements by 1
                                        //std::cout<<"pppPushing the negative operand "<<temp<<" to vector"<<std::endl;
                                        tokens.push_back(temp); //push_back temp to tokens
                                        if ((i+2)==s.length())
                                                break;
                                        temp = ""; //reset temp

				}else if ((s.at(i-1)=='(')||(operatorPrec(s.at(i-1)))){ //if char DOES denote negtivity
					temp += s.at(i);
					i++; //increment i
					while (i<s.length()&&(isDigit(s.at(i))||s.at(i)=='.')){
					//while (((isDigit(s.at(i)))||(s.at(i)=='.'))&&(i<s.length())){ //get all digits in number
						//std::cout<<"adding negative number at index "<<i<<": "<<s.at(i)<<std::endl;
						//i++;
						temp+=s.at(i); //add to temp string
						i++;//increment i
					}
					/*if ((i+1)==s.length()){
						//std::cout<<"breaking"<<std::endl;
						break;
					}*/
					i--; //while loop overincrements by 1
					//std::cout<<"Pushing the negative operand "<<temp<<" to vector"<<std::endl;
					tokens.push_back(temp); //push_back temp to tokens
					if ((i+2)==s.length())
						break;
					temp = ""; //reset temp
				}else{ //if char is an operator and not negative sign
					//std::cout<<"Pushing minus operator "<<std::string(1,s.at(i))<<" to vector"<<std::endl;
					tokens.push_back(std::string(1,s.at(i)));    
				}
			}else{ //if any other operator, push back normally
				//std::cout<<"Pushing operator "<<std::string(1,s.at(i))<<" to vector"<<std::endl;
				tokens.push_back(std::string(1,s.at(i)));
			}
		}else{
			std::cout<<"invalid character found in expression!"<<std::endl;
		}
	}
        // code ends
    }

    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens)
    {
        // code begins
	//std::cout<<"Inside infix to postfix func"<<std::endl;
	MyStack<std::string> stack;
	//MyStack digits; //create a stack to store digits
	//MyStack ops; //stack to store operators
	//int openParenthesis = 0; //stores number of open parenthesis
	for (int i = 0; i<infix_tokens.size(); i++){
		if (infix_tokens[i].size()!=1){ //if the string is a number, add to postfix_tokens
			postfix_tokens.push_back(infix_tokens[i]);
		}else{
			if (operatorPrec(infix_tokens[i][0])){ //if string is an operator
				if (operatorPrec(infix_tokens[i][0])==2){ //if operator is a * or /
					while ((!stack.empty())&&(stack.top()!="(")&&(operatorPrec(stack.top()[0])!=3)){
						postfix_tokens.push_back(stack.top());
						stack.pop();
					}
					stack.push(infix_tokens[i]);
				}else if(operatorPrec(infix_tokens[i][0])==3){
					while ((!stack.empty())&&(stack.top()!="(")){
						postfix_tokens.push_back(stack.top());
						stack.pop();
					}
					stack.push(infix_tokens[i]);
				}
			}else if(infix_tokens[i]=="("){
				stack.push(infix_tokens[i]);
			}else{
				while ((!stack.empty())&&(stack.top()!="(")){
					postfix_tokens.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
			}
		}
		/*if (infix_tokens[i].size()==1){
			std::cout<<"Running size 1 if loop for "<<infix_tokens[i][0]<<std::endl;
			if  (isValidParenthesis(infix_tokens[i][0])){ //if char is a parenthesis
				if (infix_tokens[i] == "("){ //if open parenthesis
					//std::cout<<infix_tokens[i]<<std::endl;
					std::cout<<"pushing open parenthesis "<<infix_tokens[i]<<" to stack"<<std::endl;
					stack.push(infix_tokens[i]); //push to stack
				//openParenthesis++;
				}else if(operatorPrec(infix_tokens[i][0])){ //if single char is an operator
					std::cout<<"pushing operator to stack: "<<infix_tokens[i]<<std::endl;
					stack.push(infix_tokens[i]);
				}else{//if closed parenthesis
			      		if ((i+1)==infix_tokens.size()){ //if we have reached the end of the expression
						std::cout<<"we are at the end of the expression: "<<(i+1)<<"=="<<infix_tokens.size()<<std::endl;
						while (!stack.empty()){ //while the stack is not empty
							//pop characters off stack
							if (isValidParenthesis(stack.top()[0])){//ignore parenthesis
								std::cout<<"Pop the parenthesis from the stack: "<<stack.top()<<std::endl;
								stack.pop(); //pop off parenthesis
							}else{ //otherwise
								std::cout<<"Non-parenthesis get pushed to vector: "<<stack.top()<<std::endl;
								postfix_tokens.push_back(stack.top()); //push character to vector
								stack.pop();//pop char
							}
						}
					}else if(operatorPrec(infix_tokens[i][0])){ //if single char is an operator
						std::cout<<"pushing operator to stack: "<<infix_tokens[i]<<std::endl;
						stack.push(infix_tokens[i]);
					}else{//closing parenthesis but not at the end
						while(stack.top() != "("){//while we haven't encountered another left parenthesis
							std::cout<<"push non-parenthesis operators from top of stack to vector: "<<stack.top()<<std::endl;
							postfix_tokens.push_back(stack.top()); //push top of stack to postfix_tokens
							stack.pop();
						}
						stack.pop(); //pop opening parenthesis	
				//openParenthesis--;
				//postfix_tokens.push_back(
					}
					//stack.pop(); //pop opening parenthesis
				}
			}else if(operatorPrec(infix_tokens[i][0])){ //if single char is an operator
				std::cout<<"pushing operator to stack: "<<infix_tokens[i]<<std::endl;
				stack.push(infix_tokens[i]);
			}
		}else if((isDigit(infix_tokens[i][0]))||(isDigit(infix_tokens[i][1]))){ //if char is a digit, add to postfix_tokens
			std::cout<<"pushing double to postfix vector: "<<infix_tokens[i]<<std::endl;
			postfix_tokens.push_back(infix_tokens[i]);
		}else if (operatorPrec(infix_tokens[i][0])){ //if char is an operator, push to stack
			std::cout<<"pushing operator to stack: "<<infix_tokens[i]<<std::endl;
			stack.push(infix_tokens[i]);
		}else{
			std::cout<<"There seems to be an unknown char"<<std::endl;
		}*/	
	}
	while (!stack.empty()){
		if (stack.top()=="("){
			stack.pop();
		}else{
			postfix_tokens.push_back(stack.top());
			stack.pop();
		}
	}
        // code ends
    }

    // calculates the final result from postfix tokens
    double calPostfix(const MyVector<std::string>& postfix_tokens) const
    {
        // code begins
	//std::cout<<"In func calPostfix"<<std::endl;
	MyStack<std::string> stack; //create stack
	std::string num1,num2,op,ans; //create vars to hold two numbers, an operator, and the answer
	double answer; //used to store expressions answer
	for (int i = 0; i<postfix_tokens.size(); i++){ //for every char in postfix_tokens
		if (postfix_tokens[i].size()!=1){//if it is a number
			stack.push(postfix_tokens[i]);//push number to stack
			//std::cout<<"Pushed "<<postfix_tokens[i]<<" to stack"<<std::endl;
		}else{//if it is an operator
			//std::cout<<"Operator: "<<postfix_tokens[i]<<std::endl;
			num2=stack.top();
			stack.pop();
			num1=stack.top();
			stack.pop();
			op = postfix_tokens[i];
			ans = std::to_string(computeBinaryOperation(num1,num2,op));
			//std::cout<<"answer: "<<ans<<std::endl;
			stack.push(ans);
			
		}
		/*if ((operatorPrec(postfix_tokens[i][0]))&&(postfix_tokens[1].size()==1)){ //if string is operator, perform arithmetic
			std::cout<<"The operator is: "<<postfix_tokens[i]<<std::endl;
			num1 = stack.top();
			stack.pop();
			num2 = stack.top();
			stack.pop();
			//std::cout<<"Num1: "<<num1<<"; Num2: "<<num2<<std::endl;
			ans = std::to_string(computeBinaryOperation(num1,num2,ans));
			stack.push(ans); //push answer back to stack

		}else{
			std::cout<<"Pushing "<<postfix_tokens[i]<<" to the stack. Size: "<<postfix_tokens[i].size()<<std::endl;
			stack.push(postfix_tokens[i]); //otherwise it is a number and push to stack
		}*/
	}
	//std::cout<<stack.top()<<std::endl;
	return std::stod(stack.top()); //return final number
        // code ends
    }
};

#endif // __MYINFIXCALCULATOR_H__
