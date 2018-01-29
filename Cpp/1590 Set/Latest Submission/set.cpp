 #include "set.hpp"

Set::Set()
{
    this->size = 0;
}

Set::Set(int* m, int s)
{
    int i;
    this->size = 0;
    for(i = 0; i < s; i++)
        this->append(m[i]);
}

int Set::getSize()
{
    return this->size;
}

int* Set::getMembers()
{
    return this->members;
}

bool Set::isEmptySet()
{
    if(this->size == 0)
        return true;
    return false;
}

bool Set::isInSet(int e)
{
    int *node = this->getMembers();
    int length = this->getSize();
    int i;
    for(i = 0; i < length; i++)
    {
        if(node[i] == e)
            break;
    }
    if(i == length)
        return false;
    return true;
}

bool Set::append(int e)
{
    if(this->size == MAX_MEMBERS)
        return false;
    if(this->isInSet(e))
        return false;
    this->members[this->size] = e;
    this->size++;
    return true;
}

bool Set::remove(int e)
{
    if(this->isEmptySet())
        return false;
    if(this->isInSet(e))
    {
        int i;
        for(i = 0; i < this->size; i++)
        {
            if(this->members[i] == e)
            {
                this->members[i] = this->members[this->size - 1];
                break;
            }
        }
        this->size--;
        return true;
    }
    return false;
}