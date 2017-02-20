#include <iostream>
#include <string>
using namespace std;

/*
   I V  X  L   C    D      M
   1 5 10 50 100  500  1,000
   4   IV
   9   IX
   40  XL
   90  XC
   400 CD
   900 CM
 */

string n_100_s[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
string n_10_s[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
string n_1_s[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

int n_100_n[] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900};
int n_10_n[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
int n_1_n[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
class Solution {
	public:
		// 1 ~ 3999
		string intToRoman(int num) {
			string ret;
			if (num >= 1000) {
				int n = num/1000;
				if (n == 1) {
					ret += "M";
					num -= 1000;
				} else if (n == 2) {
					ret += "MM";
					num -= 2000;
				} else if (n == 3) {
					ret += "MMM";
					num -= 3000;
				}
			}
			if (num >= 100) {
				int n = num/100;
				ret += n_100_s[n];
				num -= n_100_n[n];
			}
			if (num >= 10) {
				int n = num/10;
				ret += n_10_s[n];
				num -= n_10_n[n];
			}
			ret += n_1_s[num];
			return ret;
		}
};

void test(int num, string ans)
{
	Solution solv;
	string ret;
	ret = solv.intToRoman(num);
	cout << num << " " << ret << " " << ((ret == ans) ? "Pass":"Fail") << endl;
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
	test(2014, "MMXIV");
	return 0;
}
