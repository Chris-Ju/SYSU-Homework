# Add Advance

# Description
如果之前没有做过题目``Add``, 可以查阅题目``Add``的描述。   
<span style="color:red; font-weight: bold">请不要抄``Add``的标准答案, 不然可能会被请去跟程设课老师喝茶</span>

实现函数``void add(char[], char[], char[])``, 其中第一个和第二个参数是加法的操作数，第三个参数是这两个参数的和，储存计算的结果。  
在函数``add``的基础上，实现函数``char* addTripleNum(char[], char[], char[])``，对三个数进行相加。

与题目``Add``类似的，三个数加法的操作数同样是以字符串的形式给出。  
这里与函数``add``不同的指出在于：  
1. 参数全为操作数
2. 返回值是和字符串

给定函数``freeSum``用于释放可能申请出来的内存，具体看``addTripleNum``函数实现方法, 如果返回值的指针指向动态申请的内存，可以通过``freeSum``释放  

``main``函数及数据的读取已经给定，只需``include``相应头文件，实现函数的定义即可。  

# Input
三个数字，位数不超过30，一行一个数字


# Output
和

# Sample Input
```
123
88
12

```

# Sample Output
```
233

```


# Hint
> If you're skilled in C programming or algorithm, you can pass this part.  
> Otherwise, please read it before you do it.

### 1. About bignum arithmetic
  The main idea of adding two big number is a simulation of the manual addition. For Example, `123` add `98` is `221`, where one simply adds the digits in sequence, carrying as necessary. Like:  


```
  1  2  3  
+    9  8  
------------- 
  1  11 11  
-------------  
  2  2  1 
```

It consists of three parts:  
  (1). From the lowest digits adding the digits one by one until there is no digit can be add.  
  (2). Appending the rest of the digsts in the longer number.  
  (3). Calculating the carry if it has.  
For Example, for ``a = 123`` and ``b = 98``,　calculating ``sum = a + b``.
  Firstly,
  ```c
   sum[3] = a[2] + b[1] // sum[3] = 11 = 3 + 8
   sum[2] = a[1] + b[0] // sum[2] = 11 = 2 + 9
  ```
  Secondly,
  ```c
   sum[1] = a[0]
  ```
  At last,
  ```c
   sum[2] += sum[3] / 10 // add the carry, sum[2] = 11 + 1
   sum[3] %= 10      // sum[3] = 1
   
   sum[1] += sum[2] / 10 // add the carry, sum[1] = 1 + 1
   sum[2] %= 10      // sum[2] = (11 + 1) % 10 = 2
  ```

&ensp;
&ensp;
> Why the length of sum is 4?  
> The maximum length of a and b is 3. if the highest digit of a or b create a carry, like `999 + 1`， the length of sum is 4.

### 2. return a pointer to the variable created in function
  We all know the variables will be distroyed after the end of the block. The code shown below is wrong and dangerous.
   
```
int *foo() {
  int a = 10;
  return &a;
}

int main() {
  int *p = foo();
}
```
There are three ways to return a pointer.
  1. declare the variable as global variable
  2. declare the variable as static variable
  3. use ``malloc`` or ``calloc`` to get a block of dynamic memory


The last one is recommended.   
However, if you allocate a block of memory, you must "free" it when you don't need it.
If you not, you will recieve a memory check error about memory leak.  
 
So, if you use ``malloc`` or ``calloc``, please use the function ``free`` to "free" the pointer, this step will be done in the function ``freeSum``.
 
### 3. add three number
  ``a + b + c`` can be regarded as ``(a + b) + c``
 
## Enjoy Coding