#include "array.hpp"

array::array(array::size_t size)
{
	this->_size = size;
	this->_data = new data_type[size];
}

array::~array()
{
	delete []this->_data;
}

array::size_t array::max_size(void)
{
	return _size;
}

array::data_type& array::at(const array::data_type& i)
{
	return _data[i];
}

array::data_type& array::front()
{
	return _data[0];
}

array::data_type& array::back()
{
	return _data[_size - 1];
}

void array::fill(const array::data_type& value)
{
	int i;
	for(i = 0; i <= _size - 1; i++)
	{
		_data[i] = value;
	}
}

void array::resize(int newSize)
{
	pointer data = new data_type[newSize];
	int i;
	for(i = 0; i < _size; i++)
		data[i] = _data[i];
	delete[] _data;
	_data = data;
	_size = newSize;
}

void array::sort(int from, int to)
{
	int i,j;
	int tmp;
	if(_size == 1)
		return;
	for(i = from; i < to; i++)
	{
		for(j = to - 1; j > i ; j--)
		{
			if(_data[j] < _data[j - 1])
			{
				tmp = _data[j];
				_data[j] = _data[j - 1];
				_data[j - 1] = tmp;
			}
		}
	}
}

array::pointer array::data()
{
	return _data;
}