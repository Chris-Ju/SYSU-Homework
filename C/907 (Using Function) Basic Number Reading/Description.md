# (Using Function) Basic Number Reading

## 注意：在开始看这次作业之前，请先完成 "Basic Number Reading" 这道题

# 描述

抽象出题目 "Basic Number Reading" 中读入整数的过程，将它封装为一个函数。

这次作业的目标是为你的**用户**（``main.c``）所使用的函数（``basicNumberReading``）进行声明和定义。所以建议你将题目 "Basic Number Reading" 中和读入整数有关的代码复制过来，稍加修改，以节省时间。

# 细节

这次的题目和以往不同。我们已经为你写好了 ``main.c``，而你的任务如下

1. **先**复习有关函数的声明、定义的内容，特别是**想清楚**在编译、链接过程中，函数的声明和定义各起什么作用
2. 了解用户的需求，观察 ``main.c`` 中是如何调用 ``basicNumberReading`` 这个函数的
3. 根据用户的调用情况，在 ``basicNumberReading.h`` 中，完成函数的声明
4. 在 ``basicNumberReading.c`` 中，完成函数的定义

与题目 "Basic Number Reading" 不同的是，这次只要求读入整数并输出它本身，不要求输出它的反转数，也就是说，将它本身作为函数的返回值返回就行了。

输入格式、具体要求与 "Basic Number Reading" 相同。

# Sample Input 1

```
2 10
12345
67890

```

# Sample Output 1

```
12345
67890

```

# Sample Input 2

```
9 2
1
011101
110110
10010
0
10101101
1
00
11010

```

# Sample Output 2

```
1
29
54
18
0
173
1
0
26

```

# 提示

## gcc 命令

首先在本地同一目录下应该有 ``main.c``、``basicNumberReading.h``、``basicNumberReading.c`` 三个文件

多文件编译时，将多个 ``.c`` 和 ``.o`` 文件（如果有）放入原来写 ``main.c`` 文件的地方，用空格隔开。``.h`` 文件 **不要放进去**

例如，以往的编译命令为：``gcc basicNumberReading.c -o ans -Wall -std=c99``

本题的编译命令为：``gcc main.c basicNumberReading.c -o ans -Wall -std=c99``。注意学习，模仿。

这样会生成 ``ans`` 这个可执行文件。 ``./ans`` 运行之。注意，能这样运行的是“可执行文件”，不是你写的 ``.c`` 文件。

## 编译和链接

之前说的“编译”，实际上可以细分。“编译”和“链接”就是其中的两个。这里只介绍几个细节

- 编译时是一个一个 ``.c`` 文件进行编译，各 ``.c`` 文件相互独立。在 ``main.c`` 进行 ``#include <stdio.h>``，将 ``getchar`` 的声明复制进来，并不代表在 ``basicNumberReading.c`` 里就能直接使用 ``getchar``。``basicNumberReading.c`` 里还得**再引入**一次 ``getchar`` 的声明。
- **函数的定义一般只存在一个**，可能定义在某个 ``.c``文件中（或其他地方）。如果函数的定义在不同文件或相同文件出现多次，可能会出问题。
- **要保证调用某函数的之前，已有该函数的声明**。考虑到定义的唯一性，最好使用声明。声明就像快捷方式，可以有很多个，但他们只能指向同一个本体。**链接**这一步骤里就有将函数调用和函数本体联系起来的过程。

结合以上几点，思考为什么要把声明放在 ``basicNumberReading.h``，把定义放在 ``basicNumberReading.c``里，而不是直接把定义放在 ``basicNumberReading.h``
