 #include "Set.hpp"

Set::Set()
{
	size = 0;
}

Set::Set(int* m, int s)
{
	size = s;
	for(int i = 0; i < size; i++)
		members[i] = m[i];
}

Set::Set(Set const &s)
{
	this->size = s.size;
    const int* tmp = s.members;
	for(int i = 0; i < size; i++)
	{
		this->members[i] = tmp[i];
	}
}

int* Set::getMembers () 
{
	return this->members;
}

int Set::getSize() 
{
	return size;
}

bool Set::append(int e)
{
	int i;
    for(i = 0; i < size; i++)
	{
		if(members[i] == e)
			return false;
	}
	members[i] = e;
	size++;
	return true;
}

bool Set::remove(int e)
{
	for(int i = 0; i < size; i++)
	{
		if(members[i] == e)
		{
			for(int j = i; j < size; j++)
				members[j] = members[j + 1];
			size--;
			return true;
		}
	}
	return false;
}

bool Set::isEmptySet()
{
	if(size == 0)
		return true;
	return false;
}

bool Set::isInSet(int e)
{
	for(int i = 0; i < size; i++)
	{
		if(members[i] == e)
			return true;
	}
	return false;
}

Set Set::operator&(const Set &s)
{
	Set tmp;
    for(int i = 0; i < s.size; i++)
    {
        if(isInSet(s.members[i]))
            tmp.append(s.members[i]);
    }
    return tmp;
}

Set Set::operator|(const Set &s)
{
    Set tmp;
    for(int i = 0; i < this->size; i++)
    {
        tmp.append(this->members[i]);
    }
    for(int i = 0; i < s.size; i++)
    {
        tmp.append(s.members[i]);
    }
    return tmp;
}

Set Set::operator-(const Set &s)
{
    Set tmp;
    for(int i = 0; i < size; i++)
    {
        int whether = 0;
        for(int j = 0; j < s.size; j++)
		{
			
            if(s.members[j] == members[i])
			{
                whether = 1;
                break;
			}
		}
        if(whether)    
            continue;
        tmp.append(members[i]);
    }
    return tmp;
}

Set Set::operator+(const Set &s)
{
    Set tmp;
    for(int i = 0; i < size; i++)
    {
        int whether = 0;
        for(int j = 0; j < s.size; j++)
		{
			
            if(s.members[j] == members[i])
			{
                whether = 1;
                break;
			}
		}
        if(whether)    
            continue;
        tmp.append(members[i]);
    }
    for(int i = 0; i < s.size; i++)
    {
        int whether = 0;
        for(int j = 0; j < size; j++)
		{
			
            if(s.members[i] == members[j])
			{
                whether = 1;
                break;
			}
		}
        if(whether == 1)    
            continue;
        tmp.append(s.members[i]);
    }
    return tmp;
}