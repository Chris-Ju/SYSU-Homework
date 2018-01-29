 #include "stack.hpp"

void stack::push(int node)
{
	if(this->isFull())
		return;
	else
		this->storage[++this->top] = node;
}

void stack::pop()
{
	if(this->isEmpty())
		return;
	else
		--this->top;
}

int stack::peek()
{
	if(!isEmpty())
		return this->storage[this->top];
	else
		return 0; 
}

bool stack::isEmpty()
{
	if(this->top >= 0)
		return false;
 return true;
}

bool stack::isFull()
{
	if(this->top == this->max_size - 1)
		return true;
	return false;
}

void stack::clear()
{
	this->~stack();
 this->storage = new int[MAX_SIZE]();
 this->top = -1;
}



