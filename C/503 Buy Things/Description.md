# Buy Things

## Story

>This story is fiction

Cirno(⑨) earned some money by selling ice, so she want to buy something.

She comes to Kourindou, a store selling interesting things.

Suppose that you are the owner of the store, and you know she is ⑨ (means she is not very smart), so you have to tell her how much money she has, after she buys something.

## Problem

+ **Input**
  + How much Cirno has.
  + How many items you sell. (1 <= n <= 10)
  + The price of each items.
  + **Note: the number of item starts from `0`, and the max is `9`** (Because it is too difficult for Cirno to count to `10`, she's not smart enough.)
  + Following is some numbers. (Denote it as `cirno_say`)
    + if `cirno_say` is `-1`, it means she will not buy anything and leave.
    + if `cirno_say` is `0-9`, it means the item she wants. Take her money.
    + if `cirno_say` is `10`, it is a very abnormal phenomenon. You think it is a **Ihen(異変)**.

+ **Output**
  + If Cirno buy something and she has enough money, output `You have %d yen now.`. %d means the money she has, now. But if she doesn't have enough money, output `BAKA!` and **end the trade**.
  + If Cirno say `-1`, **end the trade**.
  + If Cirno say `10`, output `Ihen!` and **end the trade**.
  + When you **end the trade**, you should output `Bye.`.

### Sample Input 1

```
9536
10
852 766 302 495 403 469 839 233 671 461 
-1
```

### Sample Output 1

```
Bye.

```

---

### Sample Input 2

```
3331
6
412 785 893 458 270 190 
0
4
-1
```

### Sample Output 2

```
You have 2919 yen now.
You have 2649 yen now.
Bye.

```

---

### Sample Input 3

```
7006
4
600 947 537 638 
10
```

### Sample Output 3
```
Ihen!
Bye.

```

---

### Sample Input 4
```
1552
8
943 953 725 451 723 173 637 247 
3
5
6
0
1
5
0
6
-1
```

### Sample Output 4

```
You have 1101 yen now.
You have 928 yen now.
You have 291 yen now.
BAKA!
Bye.

```