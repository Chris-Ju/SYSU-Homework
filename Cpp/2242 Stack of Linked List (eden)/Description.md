# Stack of Linked List (eden)

## Descrption
The stack in this exercise is implemented with link list. You should implement
Three function push(), pop() and del().



Push: push a number in the stack.You should think about how to construct the
first node.

void push(Node **top, int n)



pop: pop the number witch is in the top of the stack, return it.If the stack
is empty return -1.And you should free the node of this number.

int pop(Node **top)



del:free the stack if it is not empty.

void del(Node **top)



Tips:

1.You should include stdio.h, malloc.h, Node.h in stack.h





format:You don't need to think about the output.

For example

\------------------------------------

[Input]

5  
1 2 3 4 5

6



[Output]

1 2 3 4 5

5 4 3 2 1 -1



\------------------------------------------



## Hint
函数参数用的是Node **top，上周的题目也有出现过。如果要使用可以表示为(*top)->next;(*top)->num。传入指针的地址目的是在子函数
内直接对main函数中的top指针变量直接修改，而不用将子函数内指针的值return给main函数的top指针。



需要注意的地方：

1.对于mallo分配内存(Node*)malloc(sizeof(Node));由于google
style检查时会要求强制类型转换写成static_cast C++的形式。因此要过google
style需要改成隐式类型转换malloc(sizeof(Node));，但平时建议写成显式类型转换，DEV只有显示转换能过编译。

2.push:注意第一个节点的构造

3.pop:要free被pop的节点

4.del:free剩余所有的节点，如果为空，不需要free。

5.（题目可能有些难度，所以大致说一下方法）关于栈的构造：

（1）用temp指向malloc的一个节点

（2）将temp指向的节点的next指向此时的top指向的节点

（3）top指向temp所指向的节点



如果存在一些比较坑的地方，请大家相互提醒。




*From : 何翔*
