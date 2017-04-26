#include <iostream>
#include <fstream>
#include <string>
#include <vector>	
using namespace std;


vector<int> z_function (string s) {
	int n = (int) s.length();
	vector<int> z (n);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min (r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
	return z;
}


int main () {
  int N;
  string text, pattern;
  string textpluspatterns;
  ifstream input ("input.txt");
  ofstream output ("output.txt");
  vector<int> z;
  input >> N;
  input >> text;
  input >> pattern;
  //cout << N << '\n' << text << '\n' << pattern << '\n';
  textpluspatterns = text + '$' + pattern + pattern;
  z = z_function(textpluspatterns);
  int ans = -1;
   for (int i = N + 1; i <= 2 * N + 1; ++i) {
        if (z[i] >= N) {
            ans = 2 * N + 1 - i;
        }
   }
   output << ans;
}