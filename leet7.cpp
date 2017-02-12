#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
 * 0x0 0x7FFF-FFFF 0x8000-0000 0xFFFF-FFFF
 *   0      max pos  min neg       -1
 * 2147483647 rev overflow
 * 2147487412 rev overflow
 * 2147447412 rev y
 * 2147483641 rev y 

 * MAX_POS 0x7FFFFFFF //  2147483647 -> 7463847412
 * MIN_NEG 0x80000000 // -2147483648 -> 8463847412
 *
 * -2147483648
 * -2147483412
 * 2147483412
 * 2143847412
 */

static const int max_input[] = {2,1,4,7,4,8,3,6,4,7};
static const int min_input[] = {2,1,4,7,4,8,3,6,4,8};
class Solution {
public:
	bool check_10(vector<int> n, bool is_neg)
	{
		bool flag_pass = false;
		if (n.size() == 10) {
			if (is_neg) {
				for(int i = 0; i < 10; i++) {
					if (n[i] < min_input[i]) {
						flag_pass = true;
						break;
					} else if (min_input[i] < n[i]) {
						flag_pass = false;
						break;
					}
				}
			} else {
				for(int i = 0; i < 10; i++) {
					if (n[i] < min_input[i]) {
						flag_pass = true;
						break;
					} else if (min_input[i] < n[i]) {
						flag_pass = false;
						break;
					}
				}
			}
			if (!flag_pass)
				return false;
		}
		return true;
	}

	vector<int> do_num_2_10(int x, bool is_neg)
	{
		vector<int> ret;
		while (x > 0) {
			int digit = x % 10;
			ret.push_back(digit);
			x /= 10;
		}
		if (check_10(ret, is_neg))
			return ret;
		else
			return vector<int>({0});
	}

	int do_10_2_num(vector<int> &n)
	{
		int ret = 0;
		for (int i = 0; i < n.size(); i++) {
			int digit = n[i];
			ret = digit + ret * 10;
		}
		return ret;
	}

	int reverse(int x)
	{
		bool flag_neg = false;

		if (x < 0) {
			x = -x;
			flag_neg = true;
		}

		vector<int> t = do_num_2_10(x, flag_neg);
		//reverse(n.begin(), n.end());
		if (flag_neg)
			return -1*do_10_2_num(t);
		else
			return do_10_2_num(t);
	}
};

void test(int num, int ans)
{
	Solution solv;
	int ret;
	ret = solv.reverse(num);
	cout << num << " " << ret << ":" << ((ret == ans)?"Pass":"Fail") << endl;
}

void test2(int x)
{
	Solution solv;
	vector<int> ret= solv.do_num_2_10(x, ((x > 0)?false:true));
	cout << "test num to 10: " << x << " : ";
	for(auto it=ret.begin(); it != ret.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void test3(vector<int> n)
{
	Solution solv;
	int ret = solv.do_10_2_num(n);
	cout << "test 10 to num " ;
	for(auto it=n.begin(); it != n.end(); it++) {
		cout << *it << " ";
	}
	cout << ": " << ret << endl;
}

void test_range()
{
	Solution solv;
	int ret;
	for (int i = 100; i < 2000; i++) {
		int num = i;
		ret = solv.reverse(i);
		cout << num << " " << ret << endl;
	}
}

int main()
{
	test(123,321);
	test(-123,-321);
	test(1534236469,0);
	test(-2147483412,-2143847412);
	//test_range();
	//test2(190);
	//test3({0,9,1});
	return 0;
}
