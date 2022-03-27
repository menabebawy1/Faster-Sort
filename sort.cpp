//Mena Bebawy
//March 15, 2022
//Copy Right @Mena Bebawy

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <chrono> 
#include <cmath>
#include <unordered_map>
#include <list>
#include <climits>

using namespace std::chrono; 
using namespace std;


std::ostream& operator<<( std::ostream& dest, __int128_t value )
{
    std::ostream::sentry s( dest );
    if ( s ) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[ 128 ];
        char* d = std::end( buffer );
        do
        {
            -- d;
            *d = "0123456789"[ tmp % 10 ];
            tmp /= 10;
        } while ( tmp != 0 );
        if ( value < 0 ) {
            -- d;
            *d = '-';
        }
        int len = std::end( buffer ) - d;
        if ( dest.rdbuf()->sputn( d, len ) != len ) {
            dest.setstate( std::ios_base::badbit );
        }
    }
    return dest;
}

bool isSorted(const vector<string>& words){
	if(words.size() <= 1) return true;
	for(int i = 0; i < words.size()-1; i++){
		if(words[i] > words[i+1]){
			return false;
		}
	}
	return true;
}

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

//size 4 hash, linkedlist
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

//size 1 hash, vector
void bucketSort1v(vector<string> &strings){
	int size = 1;
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

//size 2 hash, vector
void bucketSort2v(vector<string> &strings){
	int size = 2;
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

//size 3 hash, vector
void bucketSort3v(vector<string> &strings){
	int size = 3;
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

//size 4 hash, vector
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

//size 5 hash, vector
void bucketSort5v(vector<string> &strings){
	int size = 5;
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

//size 6 hash, vector
void bucketSort6v(vector<string> &strings){
	int size = 6;
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

//size 4 hash, hashtable
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


//BurstSort --> numSort(limitation) --> Different sized buckets --> BucketSort with LL --> BucketSort with vector --> BucketSort with Hashmap

int main(){	
	//read file and create vector
	string myText;
	ifstream MyReadFile("words2.txt");
	vector<string> words;
	while (getline (MyReadFile, myText)) {
		words.push_back(myText);
	}
	MyReadFile.close();

	//generate vector
	//108,000,000 is when burstsort O(n * s) where s is the word size which comes out to be (7.21741) starts becoming faster than O(nlog(n))
	for(int j = 2000000; j <= 17000000; j += 3000000){
		srand(time(0));
		vector<string> unsorted1;
		int num;
		for(int i = 0; i < j; i++){
			num = rand() % words.size();
			unsorted1.push_back(words[num]);
		}
		vector<string> unsorted2 = unsorted1;
		/*
		vector<string> unsorted3 = unsorted1;
		vector<string> unsorted4 = unsorted1;
		vector<string> unsorted5 = unsorted1;
		vector<string> unsorted6 = unsorted1;
		*/
		

		cout << j << " ";
		
		auto start = high_resolution_clock::now();
		auto stop = high_resolution_clock::now();
		
		
		//regular sort (Quick Sort)
		start = high_resolution_clock::now(); 
		sort(unsorted1.begin(), unsorted1.end());
		stop = high_resolution_clock::now(); 
		cout << duration_cast<microseconds>(stop - start).count() << " ";
		
		

		//num sort
		
		start = high_resolution_clock::now(); 
		numSort(unsorted2);
		stop = high_resolution_clock::now(); 
		cout << duration_cast<microseconds>(stop - start).count() << endl;
		/*
		
		//hash4 sort
		
		start = high_resolution_clock::now(); 
		bucketSort1v(unsorted1);
		stop = high_resolution_clock::now();
		cout << duration_cast<microseconds>(stop - start).count() << " ";

		start = high_resolution_clock::now(); 
		bucketSort2v(unsorted2);
		stop = high_resolution_clock::now();
		cout << duration_cast<microseconds>(stop - start).count() << " ";

		start = high_resolution_clock::now(); 
		bucketSort3v(unsorted3);
		stop = high_resolution_clock::now();
		cout << duration_cast<microseconds>(stop - start).count() << " ";

		start = high_resolution_clock::now(); 
		bucketSort4v(unsorted4);
		stop = high_resolution_clock::now();
		cout << duration_cast<microseconds>(stop - start).count() << " ";

		start = high_resolution_clock::now(); 
		bucketSort5v(unsorted5);
		stop = high_resolution_clock::now();
		cout << duration_cast<microseconds>(stop - start).count() << " ";

		start = high_resolution_clock::now(); 
		bucketSort6v(unsorted6);
		stop = high_resolution_clock::now();
		cout << duration_cast<microseconds>(stop - start).count() << endl;
		
		*/
		
	}
	
	
}

