# Using Macro (eden)

## Descrption

### 所需知识

在C和C++中有个东西叫预处理，其实就是拷贝粘贴。优势就是并不会占用运行时间，只是会占用编译时间。

[维基百科](https://zh.wikipedia.org/wiki/预处理器)

[官方文档](https://gcc.gnu.org/onlinedocs/cpp/Macros.html#Macros)

1. Object-like Macros: 将宏作为一个标识符，替换掉代码片段。可以用它来解决Magic Number问题。

2. Macro Arguments: 带参数的宏。可以将参数传入，来标识某一段代码的含义。

3. Stringification: 将内容转化为string

4. Concatenation: 将参数连接起来（因为在参数替换的时候，如 (a,b) 要替换成ab直接写是不会替换的，必须通过a##b）

### 任务：（所有任务都应该用宏完成）

1. 两个宏定义来表示最大值（100）和最小值（-100）

2. max(a,b)表示取出两者中较大的一个

3. square(a)表示得到a的平方

4. e(a,b)表示得到a*10^b，如e（2，3）得到的是2000

5. mstr(a)表示替换宏内容到string

     如一个宏为#define foo 4

     mstr(foo)会得到一个为"4"的字符串

6. str(a)表示将a作为string内容，得到一个字符串

7. WARN_IF(a)表示当a成立时，输出"Warning: （a内容）n"。如果不明白请看标准输出

8. 对于头文件（.h文件）而言，应当怎么定义一个宏来保证重复include而不出错

*出题人：李天培*