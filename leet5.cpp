#include <string>
#include <iostream>
using namespace std;
//#define DEBUG

class Solution {
public:
    int checkPalindrome(string s, int index)
    {
	    int i = 0;
	    int n = s.size();
	    int even_len, odd_len;

#ifdef DEBUG
	    cout << "checking " << index << "=" << s[index] << endl;
#endif
	    if (n == 1) {
		    return 1;
	    }
	    i = 1;

	    // check odd number
	    while ((index >= i) && ((index+i) < n)) {
		    if (s[index+i] != s[index-i]) {
#ifdef DEBUG
			    //cout << s[index+i] << " vs " << s[index-i] << endl;
#endif
			    break;
		    }
			    i++;
	    }
	    i--;
	    odd_len = 2*i + 1;
	    // check even number
	    i = 0;
	    while ((index >= i) && ((index+1+i) < n)) {
		    if (s[index+1+i] != s[index-i]) {
#ifdef DEBUG
			    //cout << s[index+1+i] << " vs " << s[index-i] << endl;
#endif
			    break;
		    }
			    i++;
	    }
	    even_len = 2*i;
#ifdef DEBUG
	    cout << odd_len << " vs " <<  even_len << endl;
#endif
	    return max(odd_len, even_len);
    }

    string genPalindrome(string s, int index, int len)
    {
	    int begin = index - (len-1) / 2;
	    return string(s.begin()+begin, s.begin()+begin+len);
    }

    string longestPalindrome(string s) {
	    int n = s.size();
	    int len, max_len = 0;
	    int max_id;

	    for (int i = 0; i < n; i++) {
		    len = checkPalindrome(s, i);
		    if (len > max_len) {
			    max_id = i;
			    max_len= len;
#ifdef DEBUG
			    cout << "max changed: " << max_len << endl;
#endif
		    }
	    }
	    return genPalindrome(s, max_id, max_len);
    }
};

void test1(string s)
{
	Solution solv;
	cout << s << endl;
	for (int i = 0; i < s.size(); i++) {
		cout << solv.checkPalindrome(s, i) << endl;
	}
}

void test2(string s, int index, int len)
{
	Solution solv;
	cout << s << "," << index << "," << len << " = "<< solv.genPalindrome(s, index, len) << endl;

}

void test(string s)
{
	Solution solv;
	cout << s << " = " << solv.longestPalindrome(s) << endl;
}

int main()
{
	//test1("a");
	//test1("abc");
	//test1("aba");

	//test2("abcdefg", 2, 5);

	test("a");
	test("aa");
	test("babab");
	test("babad");
	test("cbbd");
	test("cbbbbbd");
	return 0;
}
