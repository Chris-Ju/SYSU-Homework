 #include "List.hpp"
#include <sstream>
list::list()
{
    head = NULL;
    tail = NULL;
    _size = 0;
}

list::list(const data_type a[], int length)
{
    _size = length;
    if(length == 0)
    {
        head = NULL;
        tail = NULL;
        return;
    }
    head = new node(a[0], NULL, NULL);
    listPointer cur = head;
    listPointer curPre;
    int i = 1;
    while(i < length)
    {
        curPre = new node(a[i], NULL, cur);
        cur->next = curPre;
        cur = curPre;
        curPre = NULL;
        i++;
    }
    tail = cur;
}

list::list(const list& n)
{
    if(n.size() == 0)
    {
        head = NULL;
        tail = NULL;
        _size = 0;
        return;
    }
    head = new listNode(n.head->data, NULL, NULL);
    listPointer cur = head;
    listPointer curNext;
    listPointer find = n.head;
    int i = 1;
    _size = n.size();
    while(i < _size)
    {
        find = find->next;
        curNext = new listNode(find->data, NULL, cur);
        cur->next = curNext;
        cur = curNext;
        curNext = NULL; 
        i++;
    }
    tail = cur;
}

list& list::operator=(const list& n)
{
    if(!empty())
        clear();
    if(n.size() == 0)
        return *this;
    head = new listNode(n.head->data, NULL, NULL);
    listPointer cur = head;
    listPointer curPre;
    listPointer find = n.head;
    int i = 1;
    _size = n.size();
    while(i < _size)
    {
        find = find->next;
        curPre = new node(find->data, NULL, cur);
        cur->next = curPre;
        cur = curPre;
        curPre = NULL;
        i++;
    }
    tail = cur;
    return *this;
}

list::~list()
{
    clear();
}

bool list::empty(void) const
{
    if(_size == 0)
        return true;
    return false;
}

list::size_type list::size(void) const
{
    return _size;
}

list::data_type& list::front(void) const
{
    return head->data;
}

list::data_type& list::back(void) const
{
    return tail->data;
}

std::string list::toString(void) const
{
    if(_size == 0)
        return "NULL";
    std::stringstream add;
    std::string bri;
    add << head->data;
    add >> bri;
    std::string goal = "NULL<-" + bri;
    int i = 1;
    listPointer cur = head->next;
    while(i < _size)
    {
        add.clear();
        add.str("");
        add << cur->data;
        add >> bri;
        goal += "<->" + bri;
        cur = cur->next;
        i++;
    }
    goal += "->NULL";
    return goal;
}

void list::assign(const list& n)
{
    if(n.size() == 0)
    {
        clear();
        return;
    }
    if(!empty())
        clear();
    head = new listNode(n.head->data, NULL, NULL);
    listPointer cur = head;
    listPointer curPre;
    listPointer find = n.head;
    int i = 1;
    _size = n.size();
    while(i < _size)
    {
        find = find->next;
		curPre = new listNode(find->data, NULL, cur);
        cur->next = curPre;
        cur = curPre;
        curPre = NULL;
        i++;
    }
    tail = cur;
}

void list::assign(const data_type datas[], int length)
{
    if(length == 0)
    {
        clear();
        return;
    }
    if(!empty())
        clear();
    _size = length;
    head = new listNode(datas[0], NULL, NULL);
    listPointer cur = head;
    listPointer curPre;
    int i = 1;
    while(i < length)
    {
        curPre = new listNode(datas[i], NULL, cur);
        cur->next = curPre;
        cur = curPre;
        curPre = NULL;
        i++;
    }
    tail = cur;
}

void list::push_front(const data_type& goal)
{
    if(empty())
    {
        head = new listNode(goal, NULL, NULL);
        tail = head;
        _size++;
        return;
    }
    listPointer add = new listNode(goal, head, NULL);
    head->prev = add;
    head = add;
    _size++;
}

void list::push_back(const data_type& goal)
{
    listPointer add = new listNode(goal, NULL, tail);
    if(_size != 0)
        tail->next = add;
    tail = add;
    _size++;
    if(_size == 1)
        head = tail;
}

void list::pop_front(void)
{
    if(empty())
        return;
    listPointer cur = head;
    head = head->next;
    head->prev = NULL;
    delete cur;
    _size--;
    if(_size == 0)
    {
        tail = NULL;
        head = NULL;
    }
}

void list::pop_back(void)
{
    if(empty())
        return;
    listPointer cur = tail;
    if(tail->prev != NULL)
        tail = tail->prev;
    tail->next = NULL;
    delete cur;
    _size--;
    if(_size == 0)
    {
        head = NULL;
        tail = NULL;
    }
}

void list::insert(int position, const data_type& data)
{
    if(position == 0)
        push_front(data);
    else if(position > _size || position < -1)
        return;
    else if(position == _size)
        push_back(data);
    else
    {
        listPointer site = at(position);
        listPointer add = new listNode(data, site, site->prev);
        (site->prev)->next = add;
        site->prev = add;
        _size++;
    }
    //std::cout << *this << std::endl;
}

void list::erase(int position)
{
    if(position == _size - 1)
    {
        pop_back();
        return;
    }
    else if(position == 0)
    {
        pop_front();
        return;
    }
    listPointer site = at(position);
    if(site == NULL)
        return;
    (site->next)->prev = site->prev;
    (site->prev)->next = site->next;
    delete site;
    _size--;
}

void list::clear(void)
{
    int i = 0;
    listPointer cur;
    while(i < _size)
    {
        cur = head;
        head = head->next;
        delete cur;
        i++;
    }
    head = NULL;
    tail = NULL;
    _size = 0;
}

void list::split(int position, list* dest1, list* dest2)
{
    dest1->clear();
    dest2->clear();
    listPointer cur = head;
    for(int i = 0; i < _size; i++)
    {
        if(i < position)
            dest1->push_back(cur->data);
        else
            dest2->push_back(cur->data);
        cur = cur->next;
    }
}

list& list::merge(const list& src1, const list& src2)
{
    list l = *this;
    l.clear();
    int n = src1.size();
    listPointer find = src1.head;
    for(int i = 0; i < n; i++)
    {
		l.push_back(find->data);
        find = find->next;
	}
    n = src2.size();
    find = src2.head;
    for(int i = 0; i < n; i++)
    {
        l.push_back(find->data);
        find = find->next;
	}
    clear();
    *this = l;
    return *this;
}

list& list::remove_if(bool (*condition)(listPointer))
{
    if(_size == 0)
    {
        clear();
        return *this;
    }
    listPointer cur = head;
    int n = _size;
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        if(condition(cur))
        {
            cur = cur->next;
            erase(i - count);
            count++;
        }
        else
            cur = cur->next;
    }
    return *this;
}

list& list::unique(void)
{
	listPointer cur = head;
    listPointer del;
    int count, n;
    for(int i = 0; i < _size; i++, cur = cur->next)
    {
        n = _size;
        count = 0;
        del = cur->next;
        for(int j = i + 1; del != NULL; j++)
        {
            if(cur->data == del->data)
            {
                del = del->next;
                erase(j - count);
                count++;
            }
            else
                del = del->next;
        }   
    }
}

list& list::reverse(void)
{
    for(int i = 0; i < _size; i++)
    {
        push_front(tail->data);
        pop_back();
    }
    return *this;

}

list::data_type& list::operator[](int index)
{
    int i = 0;
    listPointer cur = head;
    while(i < index)
    {
        i++;
        cur = cur->next;
    }
    return cur->data;
}


list& list::operator+=(const list& n)
{
    int m = n.size();
    listPointer cur = n.head;
    for(int i = 0; i < m; i++)
    {
        push_back(cur->data);
        cur = cur->next;
    }
    return *this;
}


std::ostream& operator<<(std::ostream& os, const list& li)
{
    os << li.toString();
    return os;
}


