# Fraction Multipe

# Description
Give you two fraction, and print their production.  
There are some points you should know:  
1. the production of two fractions is the production of their numerators\(分子\) divides the production of their denominators\(分母\).
2. the production should be simplify. That is the GCD of the numerator and the denominator must be 1.
3. if the numerator is 0, the production is zero.
3. if the denominator of the production is 1, the production is a integer.
4. if the denominator of the production is 0, the production is NAN\(Not A Number\).

# Input
The input contains two line.  
The first is the numerator and denominator of the first fraction.  
The second is the numerator and denominator of the second fraction.  


# Output
if the production is a fraction, print it like ``a/b``.
if the production is a integer, print it like ``a``.  
if the production is zero, print ``0``.  
if the production is not a number, print ``Not A Number``.  

# Sample Input
```
3 4
5 6

```

# Sample Output

```
5/8

```

# Hint
$$
\frac{3}{4} \\times \frac{5}{6} = \frac{3 \times 5}{4 \times 6} = \frac{15}{24} = \frac{5}{8}
$$