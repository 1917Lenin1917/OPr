#pragma once
#include <iostream>

class Stack
{
    int* data;
    int capacity;
    int top;

    uint64_t& nop;
public:
    Stack(uint64_t& nop, int size = 5000)
        :capacity(size), top(-1), nop(nop)
    {
        data = new int[capacity];
    }
    Stack (const Stack& other)
        :capacity(other.capacity), top(other.top), nop(other.nop)
    {
        data = new int[other.capacity];
        for (int i = 0; i <= top; i++)
        {
            data[i] = other.data[i];
        }
    }
    ~Stack()
    {
        delete[] data;
    }
    //3 + 6n
    void display() const 
    {
        std::cout << "Stack (top -> bottom): { ";
        nop += 3;
        for (int i = 0; i < top; i++)
        {
            nop += 6;
            std::cout << data[top - i] << ", ";
        }
        std::cout << data[0] << " }\n";
    }
    // 5
    void push(int element) 
    {
        nop += 3;
        top++;
        data[top] = element;
    }
    // 3
    int pop() 
    {
        nop += 3;
        const int element = data[top];
        top--;
        return element;
    }
    // 1
    int peek() const 
    {
        nop += 1;
        return data[top];
    }
    // 1
    int size() const 
    {
        nop += 1;
        return top + 1;
    }
    // 1
    bool isEmpty() const 
    {
        nop += 1;
        return top == -1;
    }
    // 2
    bool isFull() const 
    {
        nop += 2;
        return top == capacity - 1;
    }
};