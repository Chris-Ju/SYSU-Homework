 #include "queue.hpp"

int con(int num);

void queue::push(int node)
{
	if(this->isFull())
		return;
	else
	{
		this->storage[this->head] = node;
 	this->head = con(this->head + 1);
	}
				
}

void queue::pop()
{
	if(this->isEmpty())
		return;
	else
		this->rear++;
}

int queue::front()
{
	if(this->isEmpty())
		return 0;
	else
		return this->storage[this->rear];
}

int queue::back()
{
	if(this->isEmpty())
		return 0;
	else
		return this->storage[con(this->head - 1)];
}

bool queue::isFull()
{
	if(con(this->head + 1) == this->rear)
		return true;
	else
		return false;
}

bool queue::isEmpty()
{
	if(this->head == this->rear)
		return true;

		return false;
}

void queue::clear(void)
{
	this->~queue();
 this->storage = new int[MAX_SIZE+1]();
 this->head = 0;
 this->rear = 0;
}

int con(int num)
{
		 if(num == -1)
     return 10;
  return num % 11;
}


