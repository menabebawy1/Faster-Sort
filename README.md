# Creating an algorithm 2x faster than the C++ STL QuickSort!

Ever since I took my first Data Structures and Algorithms course, I became fascinated with sorting algorithms. And given that sorting algorithms are a dime a dozen, I thought "Why not create my own?". This project is exactly an attempt at that. If you want the final version of this algorithm scroll all the way to the bottom. But for now, let's start with the seed idea that sparked the new algorithm.




### Version 1.0: sorting numbers is faster than sorting strings. So, if we could come up with a way to convert strings to numbers, we could theoratically sort them much faster.
---


When comparing strings such as Apple and Application, we have to go all the way to the 5th letter to realize that 'e' is less than 'i' and therefore Apple is less than Application. However, if these words were converted to a number, the comparison would be instant.

So how do we convert a string to a number, specifically to an integer?

Well let's start with an excel sheet; that's where I got the idea. That's right, an excel sheet. In excel sheets you have columns that are ordered by letters A...Z, AA, AB, etc..

What if they were numbers instead of letters? What would they look like? 
Let's take a look at the example:

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

Now this formula will produce a distinct value for each string, however, they will not be in order. We can't then sort the strings based on their number value. Ex: "apple" will be greater than the value for "z". So how do we fix this? 

What if we give the first letter the greatest value?

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

There is a hiccup though. An integer in C++ (32 bits), can only go up to 2147483647. This limits us to log27(2^32) letters. That is only 6 letters. A 7 letter word would not fit inside an int if we use our algorithm to convert it to a number. What if we use a long int? a long long int? a __int128?

Well, the max we can do with a __int128 is log27(2^128) which is 26. That is 26 letters which should be able to cover any word. Well, what about longer strings? We could definetly use a BigInt library for that, but for now, we're going to settle for a max size of 26 chrachters. Let's write an algorithm that is capable of sorting any real word, which should be less than 26 in length.

So now the algorithm should be as follows:
We should be deciding the biggest power for each word based on the size of the longest word. Otherwise, we will have inconsistent powers and the sorting will be off. So, for the first step:
1. Find the size of the biggest string

We also need to keep each number value attached to each string, so if we change the position of the number when sorting it, we will subsequently change the position of the string:
2. Create a vector of pairs with each pair having a string and the number value for that string
3. Calculate the number value for each string
4. Sort the numbers

The following is the algorithm:

```
bool sortbysec(const pair<string, __int128> &a, const pair<string, __int128> &b){
    return a.second < b.second;
}

void numSort(vector<string>& words){
	if(words.size() == 0) return;
	vector<pair<string, __int128>> copy;

	//find biggest string
	int maxSize = 0;
	for(auto word: words){
		if(word.length() > maxSize) maxSize = word.length();
	}
		
	//calculate the number for each word	
	string word;
	__int128 order;
	for(int i = 0; i < words.size(); i++){
		word = words[i];
		order = 0;
		__int128 num = 0;
		for (int j = 0; j < word.length(); j++){
			num = pow(27, maxSize - j - 1)*(word[j] - 'a' + 1);
			order = order + num;
		}
    	copy.push_back({word, order});
	}

	//sort the copy and put it in the original
	sort(copy.begin(), copy.end(), sortbysec);
	for(int i = 0; i < copy.size(); i++){
		words[i] = copy[i].first;
	}	
}
```

Note: for word generation, I downloaded a word file with every word in the dictionary and picked random words for each value of the vector to be sorted.

Now back to our algorithm. Is it faster? Well, let's run it against the state of the art C++ STL QuickSort.

But for how many words? Well, the fastest sorting algorithms for strings are QuickSort for a smaller set of data and BurstSort for a bigger set of data. QuickSort runs in O(nlog(n)) time; and BurstSort which uses a Trie data structure, runs in O(n*|S|) time where |S| is the size of the word. Now, I quickly computed the average size of a word in the dictionary to be 7.2 in length. Setting the 2 runtimes equal to each other, we can figure out that on average BurstSort starts becoming faster than QuickSort at n*7.2 = n*log(n) which is at about 17,000,000 strings. So we will only run our tests up until that value.

So what are the resutls?

![Data for NumSort](/images/numsortdata.png)

I ran the results for values up to 17 million and found our new NumSort to be much faster than QuickSort. When dividing the run time of QuickSort by NumSort we see that it takes about half the time on average! Which means our algorithm is twice as fast!

![Chart for NumSort](/images/numsortchart.png)

Now this ofcourse will only work for any string that is up to 26 charachters long, anything bigger than that and it won't fit into our __int128. That is great so far, but it can be improved.

So how can we uses this strategy to better sort strings without a limitation on its length? Answer: Instead of completely converting the string into an integer value, we can convert the first smaller part of it. This will give strings of similar length, a similar value. We can then put these strings together into buckets, and then sort these buckets. Once we do that, it should theoratically make the algorithm much faster. Instaed of the O(nlog(n)) run time, if the words are distributed well, we should have a run time of O(nlog(n)/k), where k is the number of buckets.



### Version 2.0: Instaed of completely converting the string to integers, we partially convert them and put them into buckets based on the resulting value.
--- 

So we use the same strategy as before to convert the first few letters of each string into a number.
If we only group the strings by their first charachter we will have 26 different buckets since we only have 26 charachers.
But how many letters is the first few, and how many buckets should we have?

Well, let's look at the following:

```
1st charachter = 26^1 = 26 buckets
2nd charachter = 26^2 = 676 buckets
3rd charachter = 26^3 = 17576 buckets
4th charachter = 26^4 = 456976 buckets
5th charachter = 26^5 = 11881376 buckets
6th charachter = 26^6 = 308915776 buckets
```
As we increase the number of charachters used to calculate our integer, we exponentially increase the number of buckets. So how many buckets should we have? well let's test all bucket sizes and see which is the fastest and which uses the most reasonable amount of space. I am going to increase the word number to a 100,000,000 this time to get a more accurate picture since this algorithm should be able to sort strings of any size.

First let's figure out our algorithm:
1. Create out buckets (vector of linkedlists), I am using linkedlists as to avoid extra memory usage
2. Partially compute the integer value for each string and add them into their proper bucket
3. Sort the buckets
4. Copy the results into the original vector


Here is the algorithm using the first 4 charachters of each string:

```
void bucketSort4l(vector<string> &strings){
	int size = 4;
	vector<list<string>> buckets(pow(26,size));
	int num;
	for(auto string: strings){
		num = 0;
		for(int i = 0; i < string.length() && i < size; i++){
			num += (string[i]-'a')*pow(26, size-i-1);
		}
		buckets[num].push_back(string);
	}
	int index = 0;
	for(auto list: buckets){
		list.sort();
		for(auto itr = list.begin(); itr != list.end(); itr++){
			strings[index] = *itr;
			index++;
		}
	}
}
```

So what are the results for each char value? Here:

![Data for Char](/images/chardata.png)

![Chart for Char](/images/charchart.png)

As we can be seen, based on this data, chars 3, 4, & 5 seem to be optimal with char 4 having the best performance out of all of them. So I will choose this size to continue to experiment with.

Now before testing this algorithm, against the C++ STL QuickSort, I want to experiment further with it. I feel that it should have performed faster. But why is it slower? I believe sorting a linkedlist takes more time due to the cost of traversing the list. This takes us to the next improvement!




### Version 3.0: Instaed of having linkedlist buckets, we will have vector buckets to see if speed improves.
---

This is a very simple change, substitute the linkedlists with vectors and see how it changes the time. We should get the following algorithm:

```
void bucketSort4v(vector<string> &strings){
	int size = 4;
	vector<vector<string>> buckets(pow(26,size));
	int num;
	for(auto string: strings){
		num = 0;
		for(int i = 0; i < string.length() && i < size; i++){
			num += (string[i]-'a')*pow(26, size-i-1);
		}
		buckets[num].push_back(string);
	}
	int index = 0;
	for(auto list: buckets){
		sort(list.begin(), list.end());
		for(auto num: list){
			strings[index] = num;
			index++;
		}
	}
}
```

Now, let's look at the run time with a vector vs a linkedlist:

![Data for Char](/images/vectorlistdata.png)

![Chart for Char](/images/vectorlistchart.png)

Based on this data, having vectors for buckets is much faster than linkedlists, especially as the number of words increase.

We will stick with the implementation of a vector of vectors. Let's now compare the speed of this algorithm to the C++ STL QuickSort:

![Data for Char](/images/hashdata.png)

![Chart for Char](/images/hashchart.png)

Based on this data and the graph, we can see that the algorithm is almost twice as fast and it works for all strings, not just ones that are up to 26 charachters!

And now for one final tweak: If you look at our algorithm, it uses (26^4) = 456,976 buckets. So many of our buckets such as bucket 'zzzz' or bucket 'fwbe' will be unused. Although the number of buckets is a constant, it can be greatly decreased.




### Version 4.0: By changing our buckets container to a hashmap we can greatly decrease the number of buckets.
---

This is another very simple change. We have optimized so much for run time and not as much for space. We can change this here. Just change our container to a hashmap. Calculate the integer value for each string. If it already exists in the hashmap, then insert it into the proper bucket. If not, then create a new bucket.

This leads us to our final algorithm:

```
void bucketSort4h(vector<string> &strings){
	int size = 4;
	unordered_map<int, vector<string>> buckets;
	int num;
	int min_ = INT_MAX;
	int max_ = INT_MIN;
	for(auto string: strings){
		num = 0;
		for(int i = 0; i < string.length() && i < size; i++){
			num += (string[i]-'a')*pow(26, size-i-1);
		}
		buckets[num].push_back(string);
		min_ = min(min_, num);
		max_ = max(max_, num);
	}
	int index = 0;
	for(int i = min_; i <= max_; i++){
		auto it = buckets.find(i);
		if(it != buckets.end()){
			sort(it->second.begin(), it->second.end());
			for(auto num: it->second){
				strings[index] = num;
				index++;
			}
		}
	}
}
```
Now, how is the run time?

![Data for Char](/images/mapdata.png)

![Chart for Char](/images/mapchart.png)

Admittedly the algorithm is about 20% slower than the vector container due to accessing the hashmap. Although, it is theoratically O(1) same as a vector O(1). In practice, it is slightly slower. However, our number of buckets for each data point has gone down to about 10,000 buckets every time we run it. That's about 46x less buckets.

This is great! I created an algorithm that is twice as fast!

Final thoughts:
Is QuickSort now disposable? Ofcourse not! The answer is, "It depends". What is the user looking for?

- If the user is constrained by space, they can use QuickSort which is quite fast and uses only O(log(n)) space.
- But, if the user is looking for maximum speed, they can use version 3.0 of this algorithm and achieve maximum speed with a space complexity of O(n).
- Finally if the user is looking for something in between, they can use version 4.0 which is faster than QuickSort and uses less space than Version 3.0 of the algorithm.

Overall, I'd say this was quiet a nice tunrnout :)
