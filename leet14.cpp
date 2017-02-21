#include <iostream>
#include <vector>

using namespace std;

/*
 * "ab", "abc" returns 2
 *
 */
int common_pre(string a, string b, int max_pre)
{
	int size = min(a.size(), b.size());
	size = min(max_pre, size);
	int i;
	for (i = 0; i < size; i++) {
		if (a[i] != b[i]) {
			break;
		}
	}
	return i;
}

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs)
    {
	    int num = strs.size();
	    if (num == 0) {
		    return "";
	    } else if (num == 1) {
		    return strs[0];
	    }

	    int max_pre = strs[0].size();
	    int target = 0;
	    for (int i = 1; i < strs.size(); i++) {
		    int size = strs[i].size();
		    if (size < max_pre) {
			    max_pre = size;
			    target = i;
		    }
	    }

	    for (int i = 0; i < strs.size(); i++) {
		    if (i != target)
			    max_pre = common_pre(strs[i], strs[target], max_pre);
	    }
	    return string(strs[0].begin(), strs[0].begin()+max_pre);
    }
};

void test(string a, string b, int ans)
{
	int ret = common_pre(a, b, a.size());

	if (ret == ans) 
		cout << a << " " << b << " " << "Pass" << endl;
	else 
		cout << a << " " << b << " " << "Fail" << endl;
}

void test2(vector<string> strs, string ans)
{
	Solution solv;
	string ret = solv.longestCommonPrefix(strs);
	if (ret == ans) {
		cout << ret << " Pass" << endl;
	} else {
		cout << ret << " != " << ans << " Fail" << endl;
	}
}

int main()
{
	test("ab", "abc", 2);
	test("b", "abc", 0);
	test2({"abcd","abce","abca"}, "abc");
	test2({"abcd","abe","abca"}, "ab");
	test2({"abcd","abe","dabca"}, "");
	test2({"abcd"}, "abcd");
	test2({""}, "");
	test2({}, "");
	return 0;
}
