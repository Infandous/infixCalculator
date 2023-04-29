#ifndef __MYSTACK_H__
#define __MYSTACK_H__

#include <iostream>
#include <algorithm>

#include "MyVector.h"

template <typename DataType>
class MyStack : private MyVector<DataType>
{  
  public:

    // default constructor
    explicit MyStack(size_t initSize = 0) : MyVector<DataType>(initSize)
    {
        // code begins

        // code ends
    }

    // copy constructor
    MyStack(const MyStack & rhs) : MyVector<DataType>(rhs)
    {
        // code begins

        // code ends
    }

    // move constructor
    MyStack(MyStack && rhs) : MyVector<DataType>(std::move(rhs))
    {
        // code begins

        // code ends
    }

    // destructor
    ~MyStack()
    {
        ;    
    }

    // copy assignment
    MyStack & operator= (const MyStack & rhs)
    {
        // code begins
	MyVector<DataType>::operator = (rhs);
        // code ends
    }

    // move assignment
    MyStack & operator= (MyStack && rhs)
    {
        // code begins
	MyVector<DataType>::operator = (std::move(rhs));
        // code ends
    }

    // insert x to the stack
    void push(const DataType & x)
    {
        // code begins
	MyVector<DataType>::push_back(x);
	//std::cout<<"Push stack"<<std::endl;
        // code ends
    }

    // insert x to the stack
    void push(DataType && x)
    {
        // code begins
	MyVector<DataType>::push_back(std::move(x));
	//std::cout<<"Push stack"<<std::endl;
        // code ends
    }

    // remove the last element from the stack
    void pop(void)
    {
        // code begins
	    //std::cout<<"Pop stack"<<std::endl;
	MyVector<DataType>::pop_back();
        // code ends
    }

    // access the last element of the stack
    const DataType & top(void) const
    {
        // code begins
	//std::cout<<"At top func"<<std::endl;
	return this->data[this->theSize - 1];
        // code ends
    }

    // check if the stack is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        // code begins
	//std::cout<<MyVector<DataType>::empty()<<std::endl;
	return MyVector<DataType>::empty();
        // code ends
    }

    // access the size of the stack
    size_t size() const
    {
        // code begins
	//std::cout<<"At size stack"<<std::endl;
	return MyVector<DataType>::size();
        // code ends
    }

    // access the capacity of the stack
    size_t capacity(void) const 
    {
        // code begins
	    //std::cout<<"At stack capacity"<<std::endl;
	return MyVector<DataType>::capacity();
        // code ends
    }

};


#endif // __MYSTACK_H__
