 #include "list.hpp"
#include <sstream>
#include <string>

list::list()
{
	_size = 0;
	head = -1;
	empty_head = 0;
}

list::list(const list& another)
{
	_size = another._size;
	head = another.head;
	empty_head = another.empty_head;
	int next = head;
	for(int i = 0; i < _size; i++)
	{
		storage[next].data = another.storage[next].data;
		storage[next].next = another.storage[next].next;
		next = storage[next].next;
	}
}

list& list::operator=(const list& another)
{
	_size = another._size;
	head = another.head;
	empty_head = another.empty_head;
	int next = head;
	for(int i = 0; i < _size; i++)
	{
		storage[next].data = another.storage[next].data;
		storage[next].next = another.storage[next].next;
		next = storage[next].next;
	}
	return *this;
}

list::~list(){}

bool list::empty(void) const
{
	if(_size == 0)
		return true;
	else
		return false;
}

list::size_type list::size(void) const
{
	return _size;
}

std::string list::toString(void) const
{
	int cur = head;
    std::stringstream tmp[_size];
    std::string result = "";
    std::string bri;
    for(int i = 0; i < _size; i++)
    {
        tmp[i] << storage[cur].data;
        tmp[i] >> bri;
        cur = storage[cur].next;
        result = result + bri + "->";
    }
    result += "NULL";
    return result;
}

void list::insert(int position, const int& data)
{
	if(position > _size || position < 0 || _size >= 1000)
        return;
    if(empty_head >= 1000)
    {
        int i;
        for(i = 0; i < 1000; i++)
        {
            if(storage[i].next == -1)
                break;
        }
        if(position == 0)
	    {
		    storage[i].data = data;
		    storage[i].next = head;
		    head = i;
		    _size++;
		    return;
	    }
	    else
        {
            storage[i].data = data;
	        _size++;
	        int cur = head;
	        for(int i = 0; i < position - 1; i++)
		        cur = storage[cur].next;
	        storage[i].next = storage[cur].next;
	        storage[cur].next = i;
            if(position == _size)
                storage[i].next = -2;
            return;
        }
    }
    if(position == 0 && head == -1)
	{
		head = 0;
		storage[0].data = data;
		empty_head++;
        storage[0].next = -2;    
		_size++;
		return; 
	}
	else if(position == 0)
	{
		storage[empty_head].data = data;
		storage[empty_head].next = head;
		head = empty_head;
		empty_head++;
		_size++;
		return;
	}
	storage[empty_head].data = data;
	_size++;
	int cur = head;
	for(int i = 0; i < position - 1; i++)
		cur = storage[cur].next;
	storage[empty_head].next = storage[cur].next;
	storage[cur].next = empty_head;
    if(position == _size)
        storage[empty_head].next = -2;
	empty_head++;
}

void list::erase(int position)
{
	if(position >= _size || position < 0)
        return;
    if(position == 0)
	{
		int del = head;
        head = storage[head].next;
		storage[del].next = -1;
        _size--;
		return;
	}
	int cur = head, del;
	for(int i = 0; i < position - 1; i++)
		cur = storage[cur].next;
    del = storage[cur].next;
	storage[cur].next = storage[storage[cur].next].next;
    storage[del].next = -1;
    if(position == _size - 1)
        storage[cur].next = -2;
	_size--;
}

void list::clear(void)
{
	_size = 0;
	head = -1;
	empty_head = 0;
}

list& list::sort(void)
{
	int cur, tmp, next;
	for(int i = 0; i < _size; i++)
	{
		cur = head;
        next = storage[cur].next;
        for(int j = 0; j < _size - i - 1; j++)
		{
			if(storage[cur].data > storage[next].data)
			{
				tmp = storage[cur].data;
				storage[cur].data = storage[next].data;
				storage[next].data = tmp;
			}
			cur = next;
			next = storage[next].next;
		}
	}
	return *this;
}