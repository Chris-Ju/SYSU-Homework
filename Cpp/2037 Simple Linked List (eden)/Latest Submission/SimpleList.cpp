 #include "SimpleList.hpp"
#include <sstream>

list::list()
{
    head = NULL;
    _size = 0;
}

list::list(const list& father)
{
    _size = 0;
    node* current = father.head;
    head = NULL;
    for(int i = 0; i < father._size; i++)
    {
        insert(i, current->data);
        current = current->next;
    }
}

list& list::operator=(const list& father)
{
    clear();
    node* current = father.head;
    head = NULL;
    for(int i = 0; i < father._size; i++)
    {
        this->insert(i, current->data);
        current = current->next;
    } 
    return *this;
}

list::~list()
{
    clear();
}


bool list::empty(void) const
{
    if(_size)
        return true;
    return false;
}

int list::size(void) const
{
    return _size;
}

std::string list::toString(void) const
{
    node* current = head;
    std::stringstream tmp[_size];
    std::string result = "";
    std::string bri;
    for(int i = 0; i < _size; i++)
    {
        tmp[i] << current->data;
        tmp[i] >> bri;
        current = current->next;
        result = result + bri + "->";
    }
    result += "NULL";
    return result;
}

void list::insert(int position, const int& data)
{
    if(position > _size || position < 0)
        return;
    if(position == 0)
    {
        node* add = new node(data, head);
        this->head = add;
        this->_size++;
        return;
    }
    node* current = head;
    for(int i = 0; i < position - 1; i++)
        current = current->next;
    node* add = new node(data, current->next);
    current->next = add;
    this->_size++;
    return;
}

void list::erase(int position)
{
    if(position >= _size)
        return;
    if(position == 0)
    {
        node* current = head;
        head = head->next;
        delete current;
        _size--;
        return;
    }
    node* current = head;
    for(int i = 0; i < position - 1; i++)
    {
        current = current->next;
    }
    node* sub = current->next;
    current->next = sub->next;
    delete sub;
    _size--;
    return;
}

list& list::sort(void)
{
    int tmp;
    int array[_size];
    node* current = head;
    for(int i = 0; i < _size; i++)
    {
        array[i] = current->data;
        current = current->next;
    }
    current = head;
    for(int i = 0; i < _size; i++)
    {
        for(int j = _size - 1; j > i ; j--)
        {
            if(array[j] < array[j - 1])
            {
                tmp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = tmp;
            }
        }
        current->data = array[i];
        current = current->next;
    }
    return *this;
}

