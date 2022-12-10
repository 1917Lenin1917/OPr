#pragma once
#include "Stack.h"

class Adapter
{
	Stack stack;
	int capacity;
	uint64_t& nop;
public:
	Adapter(uint64_t& nop, int capacity = 5000)
	    :stack(nop, capacity), capacity(capacity), nop(nop) {}
	// 1
    int size() const 
    {
		return stack.size();
	}
	// 1
	bool isEmpty() const 
    {
		return stack.isEmpty();              
	}
	// 2
	bool isFull() const 
    {
		return stack.isFull();    
	}
	// 10n + 6
	int getElement(int ind) 
	{
		int size = stack.size(); // 1
		nop += 4;
		if (!(ind >= 0 && ind < size)) 
			return -1;

		Stack* tmp = new Stack(nop, capacity);
		// 10n + 5
		nop += 2;
		nop += 2 * size;
		for (int i = 0; i < ind; i++) // 1 + 2n
		{
			tmp->push(stack.pop()); // 8n
			
		}
		
		int element = stack.pop(); // 3
		for (int i = 0; i < ind; i++)
		{
			stack.push(tmp->pop()); 
			
		}
		//
	    delete tmp;
		return element;
		
	}
	// 10n + 4
	int peekElement(int ind)
	{
		int size = stack.size(); // 1
		nop += 4;
		if (!(ind >= 0 && ind < size)) 
			return -1;

		Stack* tmp = new Stack(nop, capacity);
		// 10n + 1
		nop += 2;
		nop += 2 * size;
		for (int i = 0; i < ind; i++)
		{
			tmp->push(stack.pop());
		}
		
		const int element = stack.peek();
		
		for (int i = 0; i < ind; i++)
		{
			stack.push(tmp->pop());
		}
		//
		delete tmp;
		return element;
	}
	// 16n
	bool setElement(int ind, int element) 
	{
		nop += 4;
	    int size = stack.size(); // 4
		if (!(ind >= 0 && ind <= size)) 
			return false;


		Stack* tmp = new Stack(nop, capacity);
		// 16n 
		for (int i = 0; i < ind; i++) 
			tmp->push(stack.pop());
		
		tmp->push(element);
		for (int i = ind + 1; i < size; i++) 
			tmp->push(stack.pop());
		
		for (int i = 0; i < size; i++)
			stack.push(tmp->pop());
		
		delete tmp;
		return true;	
	}
	
	void push(int x) // 5
	{
		stack.push(x);
	}
	void display() const // 3 + 6n
    {
		stack.display();
	}
};