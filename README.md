# Faster-Sort

Ever since I took my first Data Structures and Algorithms course, I became fascinated with sorting algorithms. And given that sorting algorithms are a dozen a dime, I thought to myself, "Why not create my own?". This project is exactly an attempt at that. If you want the final version of this algorithm scroll all the way to the bottom. But for now, let's start with the seed idea that sparked the new algorithm.

### IDEA #1: sorting numbers is faster than sorting strings. So, if we could come up with a way to convert strings to numbers, we could theoratically sort them much faster.

When comparing strings such as Apple and Application, we have to go all the way to the 5th letter to realize that 'e' is less than 'i' and therefore Apple is less than Application. However, if these words were converted to a number the comparison would be instant.

So how do we convert a string to a number, specifically to an integer?

Well let's start with an excel sheet, that's where I got the idea, that's right an excel sheet. In excel sheets you have columns that are ordered by letters A...Z, AA, AB, etc..

So how do we get there? Let's take a look at the examples:

```
A = 1
B = 2
C = 3
AA = 27
AB = 28
AAA = 677
```

If you notice the pattern here, we multiply by an order of 26 every time we add another letter, then we add the value of the new letter, and since we are starting at index 1, we add one to the result:

```
ABC
A = 0*26 + value of letter(0) + 1 = 1
B = 1*26 + value of letter(1) + 1 = 28
C = 28*26 + value of letter(2) + 1 = 731
```
As a result, we have the following formula:

```
int order = 0;
for (auto letter : word)
    order = order * 26 + letter - 'a' + 1;
return order;
```



