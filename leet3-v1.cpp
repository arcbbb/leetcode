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
		void db_rm(char ch)
		{
			array[ch] = 0;
		}

		int lengthOfLongestSubstring(string s) {
			char ch;
			int begin = 0;
			int cur_len = 0;
			int max_len = 0;
			int index;
			int i;
			string::iterator it;
			db_reset();
			for(it = s.begin(), i = 0; it != s.end(); it++, i++) {
				ch = *it;
				index = db_set(ch, i);
				if (index == 0) {
					// no repetition
				} else {
					// repeat
					cur_len = i - begin;
					if (cur_len > max_len) {
						max_len = cur_len;
					}
					if (index == -1) {
						index = 0;
					}
					// clear hash table
					for(int j = begin; j < index; j++) {
						db_rm(s[j]);
					}
					begin = index+1;
				}
			}
			cur_len = i - begin;
			if (cur_len > max_len) {
				max_len = cur_len;
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
