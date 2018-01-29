# Basic operation on string 2.0

# Description
We finished the assignment "basic operation on string " several weeks ago and learned some built-in functions strcmp, strncat… Today we continue to learn two more advanced operation s on string.
Split and strip are implemented as built-in functions in some programming languages, but C leaves the task to us. 
The function of split is to separate a given string into some words with a given character as delimiter. For example, if the string is ``"hello, world"`` and the delimiter is ``','``, the result will be two words ``"hello"`` and ``" world"``. if the delimiter is ``'o'``, the result will be three words ``"hell"``, ``", w"`` and ``"rld"``. And you should store the result words in an array of string (a two-dimensional array of char ).

The function of strip is to remove leading and trailing characters in a string with a given character as target. For example, if the string is ``"oohello, worldooo"`` and the given character is ``'o'``, the result will be ``"hello, world"``. You should also implement two similar functions lstrip and rstrip. They just deal with one side of a string, while strip deal with both sides. lstrip just removes the left side, and rstrip removes the right side.

For more details of the functions you need to implement, please read the comment in header file.

# Input
Input will be 6 lines. the first line is a string you need to split and the next line is a character which is the delimiter. The third line is a string that lstrip and rstrip should be applied to(actually, the input of rstrip is the result of lstrip). And the next line is the target character. The fifth line is a string that strip should be applied to. The last line is the target character.
The lengths of strings mentioned above are less than 100

# Output
The first n lines are n words produced by split.
The last three lines are the results of lstrip, rstrip and strip respectively.

# Sample Input 1
```
2016-11-12
-
~~~happy birthday~~~
~
!!!to SYSU!!!
!
```

# Sample Output 1
```
2016
11
12
happy birthday~~~
happy birthday
to SYSU
```
# Sample Input 2
```
www.vmatrix.org.cn
.
oooohello, matrixooooo
o
---hello, matrix---
-

```

# Sample Output 2
```
www
vmatrix
org
cn
hello, matrixooooo
hello, matrix
hello, matrix

```
# Further
In fact, the function of split and strip in other languages is more powerful than that of the functions we implement here. but for simplicity, we just complete the simple version. for more information, you can turn to this [website](https://docs.python.org/3/library/stdtypes.html?highlight=split#str.split) introducing these functions in python.

# 吸眼球的中文
这是本题唯一一段中文，应该能骗不少人来看。TA们希望大家能注意自己对代码缩进和大括号的处理，这是让别人看懂自己代码最基本的步骤，TA在帮你们debug的时候经常被某些缩进和大括号欺骗(此处略去成千上万个脏字)。请大家记住，虽然我们写不出诗一样的代码，但也别写的跟shǐ一样(ง •̀_•́)ง 。enjoy coding~