# Swap One Variable

# Swap One Variable

## Problem

Implement a function to swap two int.

### Detail

The function's declaration is `void mySwapInt(int *a, int *b);`.

## Hint

Last week, you have done a great job (or not?) in swapping array and matrix.

Try doing something more simple.

---

You have to know `pointer`(指针).

```c
int *a = NULL;  // declare a NULL pointer, meaning it points to nothing

int val = 5;
int *p_val = &val; // meaning it points to `val`

printf("%d == \%dn", val, *p_val);  // 5 == 5, `val` and `*p_val` are the same thing

*p_val = 4;

printf("%d == \%dn", val, *p_val);  // 4 == 4, the change to `*p_val` it the same to change to `val`

```

Refer to your book to find out what `*` and `&` actually is.

## Think

If I declare a function such that `void mySwapInt(int a, int b);`, can I swap them ?

> This problem is very simple, but learn more about pointer by yourself !
