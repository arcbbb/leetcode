#include <iostream>
#include <vector>

//#define DEBUG
using namespace std;

const int i_max = 2147483647;
const int i_min = -2147483648;
static const int max_input[] = {2,1,4,7,4,8,3,6,4,7};
static const int min_input[] = {2,1,4,7,4,8,3,6,4,8};
typedef struct {
	vector<int> array;
	bool is_neg;
} num_t;

class Solution {
public:
	int check_overflow(num_t n)
	{
		int size = n.array.size();
		if (size > 10) {
			if (n.is_neg)
				return -1;
			else
				return 1;
		} else if (size == 10) {
			if (n.is_neg) {
				for(int i = 0; i < 10; i++) {
					if (n.array[i] < min_input[i]) {
						return 0;
					} else if (min_input[i] < n.array[i]) {
						return -1;
					}
				}
			} else {
				for(int i = 0; i < 10; i++) {
					if (n.array[i] < max_input[i]) {
						return 0;
					} else if (max_input[i] < n.array[i]) {
						return 1;
					}
				}
			}
		}
		return 0;
	}

	num_t first_int_str(string str)
	{
		num_t n;
		bool flag_sign = false;
		n.is_neg = false;
		for (auto i = str.begin(); i != str.end(); i++) {
			char ch = *i;
			if (!flag_sign) {
				if (ch == '+') {
					n.is_neg = false;
					flag_sign = true;
					continue;
				} else if (ch == '-') {
					n.is_neg = true;
					flag_sign = true;
					continue;
				} else if (ch == ' ') {
					continue;
				}
			}
			if (ch >= '0' && ch <= '9') {
				flag_sign = true;
				n.array.push_back(ch - '0');
			} else {
				break;
			}
			// if flag_sign is false, check sign & '0'-'9'
			// if flag_sign is true, check '0' - '9'
		}
		if (n.array.size() == 0) {
			n.array.push_back(0);
			n.is_neg = false;
		}
#ifdef DEBUG
		cout << "dump vec: ";
		for(auto i = n.array.begin(); i != n.array.end(); i++) {
			cout << *i << " ";
		}
		cout << endl;
#endif
		return n;
	}

	int do_10_2_num(num_t &n)
	{
		int ret = 0;
		for (auto i = n.array.begin(); i != n.array.end(); i++) {
			int digit = *i;
			ret = digit + ret * 10;
		}
		if (n.is_neg)
			return -1*ret;
		else
			return ret;
	}

	int myAtoi(string str)
	{
		int r;
		// return "0" if no valid
		num_t n = first_int_str(str);
		r = check_overflow(n);
		if (r > 0) {
			r = i_max;
		} else if (r < 0) {
			r = i_min;
		} else {
			r = do_10_2_num(n);
		}
		return r;
	}
};

void test(string str, int ans)
{
	Solution solv;
	int ret;
	ret = solv.myAtoi(str);
	cout << str << " vs " << ret << ((ret == ans)?", Pass":", Fail") << endl;
}

int main()
{
	test("123", 123);
	test("+123", 123);
	test("-123", -123);
	test("  123  abc", 123);
	test("  12 3  abc", 12);
	test("2147483647", 2147483647);
	test("2147483648", i_max);
	test("-2147483648", -2147483648);
	test("-2147483649", i_min);
	test("abc 123", 0);
	test("      -11919730356x", -2147483648);
	return 0;
}
