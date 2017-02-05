#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

typedef struct {int val; int pos;} map_t;
bool map_cmp(map_t a, map_t b)
{
	return a.val < b.val;
}

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    	vector<int> ans;
    	int begin, end, tmp;
    	vector<map_t> map;

    	for(auto it = nums.begin(); it != nums.end(); ++it) {
    		map_t tmp;
    		tmp.val = *it;
    		tmp.pos = it - nums.begin();
    		map.push_back(tmp);
    	}
    	sort(map.begin(), map.end(), map_cmp);

    	// sort nums increasing order
    	sort(nums.begin(), nums.end());
    	// end =  find last(target)
	//end = bisearch(nums, target);
	end = nums.size() - 1;
    	begin = 0;
    	while (begin != end) {
		//printf("%d %d\n", begin, end);
		tmp = nums[begin]+nums[end];
		if (tmp > target) {
			//cout << tmp << " > " << target << endl;
			--end;
		} else if (tmp < target) {
			++begin;
			//cout << tmp << " < " << target << endl;
		} else {
			ans.push_back(map[begin].pos);
			ans.push_back(map[end].pos);
			break;
		}
	}

    	return ans;
    }
};

int main()
{
	vector<int> in;
	vector<int> ans;
	Solution solv;
	int target;
	in.push_back(3);
	in.push_back(2);
	in.push_back(4);
	target = 6;
	ans = solv.twoSum(in, target);
	if (ans.size() == 2)
		cout << "answer: " << ans[0] << ", " << ans[1] << endl;
	else
		cout << "answer not found: " << ans.size() << endl;
	//cout << bisearch(in, target) << endl;
	return 0;
}
