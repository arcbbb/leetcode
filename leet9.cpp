#include <iostream>
using namespace std;

class Solution {
public:
	bool isPalindrome(int x) {
		int sum = 0;
		int prev_sum;
		if (x < 0) {
			//x *= -1;
			return false;
		}
		int back = x;
		while (x > 0) {
			prev_sum = sum;
			sum = x % 10 + sum*10;
			if (sum < prev_sum) {
				//overflow
				//cout << "overflow" << endl;
				return false;
			}
			x /= 10;
		}
		if (sum == back) {
			return true;
		} else {
			return false;
		}
	}
};

void test(int num, bool ans)
{
	Solution solv;
	bool ret;
	ret = solv.isPalindrome(num);
	cout << num << "," << ret << ":" << ((ret == ans)?"Pass":"Fail") << endl;
}

int main()
{
	test(121,true);
	test(123,false);
	test(2147483647,false);

	test(-1,false);
	test(-121,false);
	test(-2147447412,false); 
	return 0;
}
