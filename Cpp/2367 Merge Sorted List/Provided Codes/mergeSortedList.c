#include "mergeSortedList.h"
#include <malloc.h>
#include <stdlib.h>

void push_front(node** head, int val)
{

    node* add = (node *)malloc(sizeof(node));
    add->next = (*head);
    add->val = val;
    (*head) = add;
}

node* mergeSortedList(node* head1, node* head2)
{
    node* cur;
    node* pre;
    if(head1 == NULL)
    {
        cur = head2;
        int tmp;
        while((cur->next)->next != NULL)
        {
            pre = head2;
            while(pre->next != NULL)
            {
                if(pre->val > (pre->next)->val)
                {
                    tmp = pre->val;
                    pre->val = (pre->next)->val;
                    (pre->next)->val = tmp;
                }
                pre = pre->next;
            }
            cur = cur->next;
        }
        return head2;
    }
    else
    {
        cur = head1;
        while(cur->next != NULL)
            cur = cur->next;
        cur->next = head2;
        cur = head1;
        int tmp;
        while((cur->next)->next != NULL)
        {
            pre = head1;
            while(pre->next != NULL)
            {
                if(pre->val > (pre->next)->val)
                {
                    tmp = pre->val;
                    pre->val = (pre->next)->val;
                    (pre->next)->val = tmp;
                }
                pre = pre->next;
            }
        cur = cur->next;
        }
        return head1;
    }
}
