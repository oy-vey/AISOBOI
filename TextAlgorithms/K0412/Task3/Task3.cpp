#include <iostream>
#include <fstream>
#include <string>
#include <vector>	
#include <algorithm>
#include <sstream>
using namespace std;

struct compare {
    bool operator()(const string& first, const string& second) {
        return first.size() < second.size();
    }
};


vector<int> PrefixFunction(string pattern){
	int N = (int) pattern.length();
	int border = 0;
	vector<int> s (N);
	for (int i = 1; i < N; i++){
		while (border > 0 && (pattern[i] != pattern[border])){
			border = s[border - 1];
		}
		if (pattern[i] == pattern[border]){
			border += 1;
		}
		else{
			border = 0;
		}
		s[i] = border;
	};
	return s;
};


vector<int>  kmp(string P, string T){
	int Plen = (int) P.length();
	string Str = P + '$' + T;
	int Strlen = (int) Str.length();
	vector<int> s = PrefixFunction(Str);
	vector<int> result;
	for (int i = Plen + 1; i < Strlen; i++){
		if (s[i] == Plen) {
			result.push_back(i - 2 * Plen);
			break;
		}
	};
	return result;
};

int main () {
int N;
compare c;
string ans = "NO"; 
ifstream input ("input.txt");
ofstream output ("output.txt");
input >> N;
vector<string> patterns (N);
for (int i = 0; i < N; i++) {
	 input >> patterns[i];
}
// cout << N << '\n';
// for (int i = 0; i < N; i++) {
// 	cout << patterns[i] << '\n';
// }
// cout << "Sorted" << '\n';
sort(patterns.begin(), patterns.end(), c);
string pattern;
string text;
ostringstream ss;
vector<int> result;
for (int i = 0; i < N; i++){
	pattern = patterns[0];
	patterns.erase(patterns.begin());
	for(size_t j = 0; j < patterns.size(); ++j){
  		if(j != 0)
    		ss << "$";
  		ss << patterns[j];
	}
	text = ss.str();
	result = kmp(pattern, text);
	if (!result.empty()){
		ans = "YES";
		break;
	};
		

};
output << ans;
}