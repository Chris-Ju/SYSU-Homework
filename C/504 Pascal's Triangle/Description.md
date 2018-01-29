# Pascal's Triangle

# description

In mathematics, Pascal's triangle \(which we call it Yang Hui's triangle\[杨辉三角\]\) is a triangular array of the binomial coefficients.  
The Pascal's Triangle has these properties:
1. the top of triangle and the numbers on both of left and right edges are 1.
2. a number can be calculate by adding two numbers above it.

A Pascal's triangle which has five rows:

```
          1
          
        1   1
         \ /
      1   2   1
       \ / \ /
    1   3   3   1
     \ / \ / \ /
  1   4   6   4   1

```

Now provide your with a number denoted by R (2 <= R <= 32), and your task is printing a Pascal's triangle which has R rows.  
The triangle you print must like the sample given below, have one space between any two numbers, several spaces at the begin and no space at the end of each line.

# Sample Input

```
4
```
# Sample Output

```
   1
  1 1
 1 2 1
1 3 3 1

```
# Sample Input

```
5
```

# Sample Output

```
    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1

```

# Hint

You can calculate the number of the Rth row, the Cth column (start from 0) by two way:
1.
$$
N_{(R, C)} = N_{(R - 1, C)} * （C - R + 1）/ C
$$
2. sum of the number above:  
  if C = 0 or C = R:
$$
N_{(R, C)} = 1
$$

  otherwise:
$$
N_{(R, C)} = N_{(R - 1, C)} + N_{(R - 1, C - 1)}
$$

3. 
$$
N_{(R, C)} = C^{ R}_C
$$

The numbers in a triangle with 30 rows aren't not larger than $2^{31}$, so `int` is enough.

More detail about Pascal's triangle. [https://en.wikipedia.org/wiki/Pascal%27s_triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle) 