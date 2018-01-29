# 字符串基本操作

# description
1. 输入两个字符串str1, str2，两个字符串长度均在[1, 20]中，按字典顺序(lexicographical order)对这两个字符串进行比较并按照特定格式输出结果。
2. 将str2的前n个字符添加到str1后面，若n大于str2长度，则将str2整体接在str1后面。将str1第x个至第y个字符中所有小写字母转换为大写并按照特定格式输出str1及其长度(x, y保证在字符串合法范围内, 并且字符串从0开始计数)。
3. 将str1复制到str2（即此时二者相等），将str2中所有字母转换为小写，并按照1.中的格式输出此时二者的比较结果
4. 判断str1的长度除以2（整除）再减去10是否大于0，若是则输出str1，否则输出str2

# input
输入为3行。前两行分别为str1, str2。第三行为正整数n。第四行为正整数x, y。

# output
* 第一行为比较结果，格式为: str1 ? str2, 其中?为>, < 或 ＝，str1及str2均为具体内容
* 第二行为操作后的str1及长度,格式为： the length of "str1" is xxx, 其中str1为具体内容，xxx为str1长* 度，引号不可省略。
* 第三行为比较结果，格式同第一行。
* 第四行为str1或str2

# sample input
```
abc
aa
2
3 4
```
# sample output
```
abc > aa
the length of "abcAA" is 5
abcAA < abcaa
abcaa
```
# hint
可能会用的函数有：strlen, strcmp, strncat……，这些函数均在string.h中；以及在ctype.h中的tolower, toupper等等。