int *stack_constructor(void)
{
    int *arr=malloc(sizeof(int)*6);
    int i;
    for(i=0;i<6;i++)
        arr[i]=-1;
    return arr;
}
void stack_destructor(int *stack)
{
    free(stack);
}
int stack_top(int *stack, int *ret)
{
    int i;
    for(i=0;i<6&&stack[i]!=-1;i++);
    if(i==0)
        return 0;
    else 
    {
        *ret=stack[i-1];
        return 1;
    }
}
int stack_pop(int *stack)
{
    int i;
    for(i=0;i<6&&stack[i]!=-1;i++);
    if(i==0)
        return 0;
    else
    {
        stack[i-1]=-1;
        return 1;
    }
}
int stack_push(int *stack, int num)
{
    int i;
    for(i=0;i<6&&stack[i]!=-1;i++);
    if(i==6)
        return 0;
    else
    {    
        stack[i]=num;
        return 1;
    }
}