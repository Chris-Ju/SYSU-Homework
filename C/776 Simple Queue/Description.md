# Simple Queue

# Simple Queue

## Problem

Implement a queue.

Input some number means `action`.(End with `EOF`)

+ `1` means **push** into the queue. Promise that another integer will follow it, meaning the value to push.
  + If the queue is full, print `Push Failed. The queue is full.`
  + If the queue is not full, push it into the queue. (Output nothing)
+ `0` means **pop** the front value of the queue. Print the value that was just popped out.
  + If the queue is empty, print `Pop Failed. The queue is empty.`
  + If the queue is not empty, print the value

In this assignment, a queue with a size of **10** is enough.

### Sample Input
```
0
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
0
0
0
0
0
0
0
0
0
0
0
```

### Sample Output
```
Pop Failed. The queue is empty.
Push Failed. The queue is full.
1
2
3
4
5
6
7
8
9
10
Pop Failed. The queue is empty.

```

## Hint (**Circular Queue**)

> If you don't want to see my BB, you can skip this part or just go to [wikipedia](https://en.wikipedia.org/wiki/Circular_buffer) to see a very nice gif explaining this.

Queue is a data structure that is FIFO(First In First Out), which means the data first to be pushed, will be first popped.

Generally, we use an array to implement **circular queue**.

For example, `int my_queue[11];`.

Then, we should know where the front/rear is. So we get two "pointer" to store the index of the the front/rear.

`int front_index = 0, rear_index = 0;`

Then with this, we know their position so we can modify it.

### How to push ?

`my_queue[rear_index++] = value;`
**Set** the value and **Move** the rear_index.

### How to pop ?

`front_index++;` 
**Move** the front_index.
Now we cannot access that value, so it seems we popped(delete) it.

### What is **Circular** ?

F for `front`, R for `rear`.

```
This queue is full. (Will explain why in the following part)

queue : [1,2,3,4,5,6,7,8,9,10]

1 2 3 4 5 6 7 8 9 10 N
^                    ^
F                    R

Pop 2 times, then we have

queue : [3,4,5,6,7,8,9,10]

1 2 3 4 5 6 7 8 9 10 N
    ^                ^
    F                R

Push 5 and 6

queue : [3,4,5,6,7,8,9,10,5,6]

6 2 3 4 5 6 7 8 9 10 5
^   ^
R   F

```

Then you see, `rear_index` reached the end but came out again from the other side. That's it, a circle indeed.

To implement this, when the index change, you should write `index %= 11;`.

### Why `11` but not `10` ?

Here, though the length of the array is `11`, only `10` spaces can be used.

We have to know if it is **full** or **empty**. Here, when `front_index == rear_index` we think it's empty, when `rear_index + 1 == front_index` we think it's full.

```
Empty

N N N N N N N N N N N
^         
F/R

Full

1 2 3 4 5 6 7 8 9 10 N
^                    ^
F                    R
```

In this way of implementation, `my_queue[rear_index]` is always unreachable. If it points to a position that has a data, then we cannot know if it is empty when `front_index == rear_index`.

(Certainly, there are some other ways to implement without this limitation)

This is why we can only use 10 spaces in a 11-long array.

If you still have no idea about this, search it yourself.
