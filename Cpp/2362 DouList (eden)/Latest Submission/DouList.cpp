#include "DouList.h"
#include <sstream>
#include <string>

int DouList::_error_sign = 0;

DouList::DouList()
{
    m_head = NULL;
    m_tail = NULL;
}

DouList::DouList(const DouList& n)
{
    if(n.m_head == NULL)
    {
        m_head = NULL;
        m_tail = NULL;
        return;
    }
    m_head = new DouListNode(n.m_head->elem, NULL, NULL);
    DouListNode* cur = m_head;
    DouListNode* curNext;
    DouListNode* find = n.m_head;
    while(find->next != NULL)
    {
        find = find->next;
        curNext = new DouListNode(find->elem, cur, NULL);
        cur->next = curNext;
        cur = curNext;
        curNext = NULL; 
    }
    m_tail = cur;
}

DouList& DouList::operator=(const DouList& n)
{
    if(n.m_head == m_head)
    	return *this;
    clear();
    if(n.m_head == NULL)
        return *this;
    m_head = new DouListNode(n.m_head->elem, NULL, NULL);
    DouListNode* cur = m_head;
    DouListNode* curPre;
    DouListNode* find = n.m_head;
    while(find->next != NULL)
    {
        find = find->next;
        curPre = new DouListNode(find->elem, cur, NULL);
        cur->next = curPre;
        cur = curPre;
        curPre = NULL;
    }
    m_tail = cur;
    return *this;
}

DouList::~DouList()
{
    clear();
}

bool DouList::empty() const
{
    if(m_head == NULL || m_tail == NULL)
        return true;
    return false;
}

int DouList::front() const
{
    return m_head->elem;
}

int DouList::back() const
{
    return m_tail->elem;
}

void DouList::push_front(const int& goal)
{
    if(empty())
    {
        m_head = new DouListNode(goal, NULL, NULL);
        m_tail = m_head;
        return;
    }
    DouListNode* add = new DouListNode(goal, NULL, m_head);
    m_head->prev = add;
    m_head = add;
}

void DouList::push_back(const int& goal)
{
    if(empty())
    {
    	push_front(goal);
    	return;
    }
    DouListNode* add = new DouListNode(goal, m_tail, NULL);
    m_tail->next = add;
    m_tail = add;
}

void DouList::pop_front()
{
    if(empty())
    {
        _error_sign++;
        return;
    }
    DouListNode* cur = m_head;
    m_head = m_head->next;
    m_head->prev = NULL;
    delete cur;
    if(empty())
    {
        m_tail = NULL;
        m_head = NULL;
    }
}

void DouList::pop_back()
{
    if(empty())
    {
        _error_sign++;
        return;
    }
    DouListNode* cur = m_tail;
    m_tail = m_tail->prev;
    if(m_tail != NULL)
    	m_tail->next = NULL;
    delete cur;
    if(empty())
    {
        m_head = NULL;
        m_tail = NULL;
    }
}

void DouList::clear()
{
    if(empty())
    	return;
    DouListNode* cur = m_head;
    while(cur != NULL)
    {
        m_head = m_head->next;
        delete cur;
        cur = m_head;
    }
    m_head = NULL;
    m_tail = NULL;
}

std::ostream& operator<<(std::ostream& os, const DouList& li)
{
    os << li.to_str();
    return os;
}

std::string DouList::to_str() const
{
    if(empty())
        return "[]";
    std::stringstream add;
    std::string bri;
    DouListNode* cur = m_head;
    add << cur->elem;
    add >> bri;
    std::string goal = "[" + bri;
    cur = cur->next;
    while(cur != NULL)
    {
        add.clear();
        add.str("");
        add << cur->elem;
        add >> bri;
        goal += ", " + bri;
        cur = cur->next;
    }
    goal += "]";
    return goal;
}


