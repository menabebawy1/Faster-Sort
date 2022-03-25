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

Now this formula will produce a distinct value for each string, however, they will not be in order. We can't then sort the strings based on their number value. Ex: "apple" will be greater than the value for "z". So how do we fix this? What if we give the first letter the greatest value?

How do we do this? We can add the following to the number value:

```
pow(26, word.length() - i - 1)
```
Essentially, you are making the first letter be raised to the biggest power and the letters following that have a smaller and smaller power as we move forward. As a result, our new algorithm is as follows:

```
int order = 0;
in num = 0;
for (int i = 0; i < word.length(); i++){
    num = pow(26, word.length() - i - 1) * (word[i] - 'a' + 1);
    order = order + num;
}
return order;
```
Now credits to the remainder of the algorithm go to the user of the following post on stackoverflow: [Post](https://stackoverflow.com/questions/16521148/string-to-unique-integer-hashing)

Now we can have the following values:
```
"apple" = 749325
"z" = 19482450
```

This makes sense as 'z' is indeed lexicographically greater than 'apple'.

There is a hiccup though, an integer in c++ (32 bits), can only go up to 2147483647. This limits us to log27(2^32) letters. That is only 6 letters. What if we use a long int? a long long int? a __int128?

Well the max we can do with a __int128 is log27(2^128) which is 26. That is 26 letters which should be able to cover any word. Well, what about longer strings? We could definetly use a BigInt library for that, but for now, we're going to settle for a max size of 26 chrachters.







