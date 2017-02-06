#include <iostream>
#include <string>
using namespace std;

class Solution {
	public:
		int array[256];
		
		void db_reset(void)
		{
			memset(array, 0, sizeof(array));
		}

		int db_set(char ch, int index)
		{
			int old_index;
			if (index == 0)
				index = -1;
			old_index = array[ch];
			array[ch] = index;
			return old_index;
		}

		int lengthOfLongestSubstring(string s) {
			int begin = 0;
			int end = s.size();
			char ch;
			int cur_len, max_len = 0;
			int index;
			int i;
			while(begin < end) {
				db_reset();
				for(i = begin; i < end; i++) {
					ch = s[i];
					index = db_set(ch, i);
					if (index == 0) {
					} else {
						// repeat
						cur_len = i - begin;
						if (cur_len > max_len) {
							max_len = cur_len;
						}
						if (index == -1)
							index = 0;
						begin = index+1;
						break;
					}

				}
				if (i!=end) {
					continue;
				} else {
					cur_len = i - begin;
					if (cur_len > max_len) {
						max_len = cur_len;
					}
					break;
				}
			}
			return max_len;
		}
};

void test(string s)
{
	Solution solv;
	cout << s << ":" << solv.lengthOfLongestSubstring(s) << endl;
}

int main()
{
	test("abcabcbb");
	test("bbbbb");
	test("pwwkew");
	test("dfda");
	test("abba");
	test("a1b1c1d1e1f1g");
	return 0;
}
