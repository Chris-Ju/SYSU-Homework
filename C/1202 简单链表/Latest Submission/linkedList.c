#include<stdlib.h>
#include"linkedList.h"
bool insert(int position,int value)
{
    if(position<0||position>size)
        return false;
    int i=0;
    node *current=(node *)malloc(sizeof(node));
    node *pre=(node *)malloc(sizeof(node));
    if(head==NULL)
    {
        current->next=NULL;
        current->value=value;
        head=current;
    }
    else if(position!=0)    
    {
        for(pre=head;i<position-1;i++)
            pre=pre->next;
        current->value=value;
        current->next=pre->next;
        pre->next=current;
    }
    else
    {
        current->value=value;
        current->next=head;
        head=current;
    }
    if(position==size)
        current->next=NULL;
    ++size;
    return true;
}

int get(int position)
{
    node *current=head;
    for(int i=0;i<position;i++)
        current=current->next;
    return current->value;
}

void clear()
{
    node *current=head;
    while(size--)
    {
        current=head->next;
        free(head);
        head=current;
    }
}