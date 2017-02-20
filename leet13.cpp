#include <iostream>
#include <string>

using namespace std;

/*
   I V  X  L   C    D      M
   1 5 10 50 100  500  1,000
*/
int numS(char ch)
{
	int num;
	num = 0;
	switch (ch) {
		case 'I':
			num = 1;
			break;
		case 'V':
			num = 5;
			break;
		case 'X':
			num = 10;
			break;
		case 'L':
			num = 50;
			break;
		case 'C':
			num = 100;
			break;
		case 'D':
			num = 500;
			break;
		case 'M':
			num = 1000;
			break;
	}
	return num;
}

class Solution {
public:
    int romanToInt(string s)
    {
	    int num, prev_num;
	    int sum = 0;
	    prev_num = 0;
	    for (int i = 0; i < s.size(); i++) {
		    num = numS(s[i]);
		    if (prev_num >= num) {
			    // prev_num > num
			    sum += prev_num;
		    } else {
			    // prev_num < num
			    sum -= prev_num;
		    }
		    prev_num = num;
	    }
	    sum += prev_num;
	    return sum;
    }
};

void test(int ans, string s)
{
	Solution solv;
	int ret;
	ret = solv.romanToInt(s);
	cout << s << " " << ret << " " << ((ret == ans) ? "Pass":"Fail") << endl;
}

int main()
{
	test(1,"I");
	test(4,"IV");
	test(9,"IX");
	test(40,"XL");
	test(90,"XC");
	test(400,"CD");
	test(900, "CM");
	test(207, "CCVII");
	test(1066, "MLXVI");
	test(1954, "MCMLIV");
	test(1990, "MCMXC");
	test(3999, "MMMCMXCIX");
	return 0;
}
