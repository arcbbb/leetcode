#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define DEBUG

using namespace std;

template <class T>
void dumpx(T &x)
{
	cout << x << ", ";
}

template <typename T>
void dumpvecvec(T &x)
{
	for_each(x.begin(), x.end(), dumpx<typename T::value_type>);
	cout << endl;
}

template <typename T>
void dumpvec(string prefix, T &x)
{
	cout << prefix << " ";
	for_each(x.begin(), x.end(), dumpx<typename T::value_type>);
	cout << endl;
}

/*
 * a+b+c = 0
 * if 0 appears, find a == -b
 * for x in list
 *     begin, end = range  x > 0, -1 * x < [begin] < [end]  < 0
 *                         x < 0, 0 < [begin] < [end] < -1*x
 *     for e from begin ~ (begin+end)/2
 *           candidate = -1*x - e
 *           find_db(candidate)
 *           if found, ans.push_back({candidate,e,x})
 *  list_pos, list_neg
 *    find_l(list_pos, list_neg)
 *    find_l(list_neg, list_pos)
 */

void find_l(vector<vector<int> > &ans, vector<int> &target_list, vector<int> &candidate_list, bool target_is_pos, map<int, int> &db_dup)
{
	map<int,int> db;
	// create db
	for (int i = 0; i < candidate_list.size(); i++)
	{
		db[candidate_list[i]] = 1;
	}

	auto begin = candidate_list.begin();
	auto end = candidate_list.end();
	for (int i = 0; i < target_list.size(); i++) {
		int target = target_list[i];
		if (target == 0) {
			// 0 is candidate only
			continue;
		}
		//auto local_end = lower_bound(begin, end, target); // first item >= target
		auto local_end = upper_bound(begin, end, target/2); // first item >= target/2
		int range;
		//range = (local_end-begin+1)/2;
		range = (local_end-begin);

		// n = local_end -begin
		//1, n = 1, range = 1, id=0
		//1,1 n = 2, range = 1, id = 0 range 1 -> 2
		//1,2 n = 3, range = 2, id = 0,1
		//1,3 n = 4, range = 2, id = 0,1,2
		/*
		if (((local_end-begin) > 0) && (*begin == 0) && ((local_end-begin)%2 == 0))
			range ++;
			*/

#ifdef DEBUG
		cout << "target " << target << ", range: " << range << ", local_end = " << local_end-begin << endl;
#endif
		for (int j = 0; j < range; j++) {
			int candidate_1 = candidate_list[j];

			int candidate_2 = target - candidate_1;
#ifdef DEBUG
			cout << "candidate: " << candidate_1 << " " << candidate_2 << endl;
#endif
			if (candidate_2 == candidate_1) {
				int a = target;
				int b = candidate_2;
				int c = candidate_2;

				if (target_is_pos && (db_dup.find(candidate_2*-1) != db_dup.end())) {
					b *= -1;
					c *= -1;
					vector<int> tmp({a, b, c});
					sort(tmp.begin(), tmp.end());
					ans.push_back(tmp);
				} else if (!target_is_pos && db_dup.find(candidate_2) != db_dup.end()) {
					a *= -1;
					vector<int> tmp({a, b, c});
					sort(tmp.begin(), tmp.end());
					ans.push_back(tmp);
				}
			} else if (db.find(candidate_2) != db.end()) {
				int a = target;
				int b = candidate_1;
				int c = candidate_2;
				if (target_is_pos) {
					b *= -1;
					c *= -1;
				} else {
					a *= -1;
				}
				vector<int> tmp({a, b, c});
				sort(tmp.begin(), tmp.end());
				ans.push_back(tmp);
			}
		}
	}
}

void threeSum2(vector<vector<int> > &ans, vector<int> &list_pos, vector<int> &list_neg, map<int,int> &db_dup)
{
	find_l(ans, list_neg, list_pos, false, db_dup);
	find_l(ans, list_pos, list_neg, true, db_dup);
}

int op_abs(int x)
{
	return abs(x);
}

class Solution {
public:

	vector<vector<int> > threeSum(vector<int>& nums) {
		vector<vector<int> > ans;
		map<int,int> db_dup;

		sort(nums.begin(), nums.end());

		int prev_num = 0;
		int count_zero = 0;
		for (auto it = nums.begin(); it != nums.end(); it++) {
			int num = *it;
			if (num == 0) {
				count_zero++;
			}
			if (num == prev_num) {
#ifdef DEBUG
				cout << "dup " << num <<endl;
#endif
				db_dup[num] = 1;
			}
			prev_num = num;
		}

		auto last = unique(nums.begin(), nums.end());
		nums.erase(last, nums.end());

		vector<int>::iterator first_pos = upper_bound(nums.begin(), nums.end(), 0);
		vector<int> list_pos(first_pos, nums.end());
		vector<int> list_neg(nums.begin(), first_pos);
		transform(list_neg.begin(), list_neg.end(), list_neg.begin(), op_abs);
		sort(list_pos.begin(), list_pos.end());
		sort(list_neg.begin(), list_neg.end());
#ifdef DEBUG
		dumpvec("list_pos:", list_pos);
		dumpvec("list_neg:", list_neg);
#endif

		threeSum2(ans, list_pos, list_neg, db_dup);
		if (count_zero >= 3) {
			ans.push_back({0,0,0});
		}
		return ans;
	}
};

void test(vector<int> nums, vector<vector<int> > ans)
{
	Solution solv;

	// debug dump
	dumpvec("input:", nums);

	vector<vector<int> > ret = solv.threeSum(nums);
	cout << "ret: ";
	for_each(ret.begin(), ret.end(), dumpvecvec<vector<int > >);
	cout << endl;
#if 1
	if (ret == ans) {
		cout << "Pass" << endl;
	} else {
		cout << "Fail" << endl;
	}
#endif
}

int main()
{
#if 1
	test({-9,-1,-8,-2,-7,-3,-6,-4,10},{
			{-9,-1,10}
			,{-8,-2,10}
			,{-7,-3,10}
			,{-6,-4,10}
			});

	test({-4,-3,-2,-1,3,4,5},{
			{-2,-1,3}
			,{-3,-1,4}
			,{-4,-1,5}
			,{-3, -2, 5,}
			});
	test({-2,-2,-2,-2,-2,4}, {{-2,-2,4}});
#endif

#if 1
	test({-1,-2,-3,0,3,2,1}, {
			{-3,1,2,}
			,{-1,0,1}
			,{-2,0,2}
			,{-3,0,3}
			,{-2,-1,3}
			});

	test({-1,0,1,2,-1,-4},{
			{-1,0,1}
			,{-1,-1,2}
			});
#endif

#if 1
	test({1,2,3,4,5,6,7},{});
	test({},{});
	test({1},{});
	test({0,0,0},{{0,0,0}});
	test({0,0,1,2,3,-4},{
			{-4,1,3}
			});
	test({-1,-2,-3,4,1,3,0,3,-2,1,-2,2,-1,1,-5,4,-3},{
			{-2, 1, 1}
			,{-3, 1, 2}
			,{-5, 1, 4}
			,{-5, 2, 3}
			,{-1, 0, 1}
			,{-2, 0, 2}
			,{-1, -1, 2}
			,{-3, 0, 3}
			,{-2, -1, 3}
			,{-3, -1, 4}
			,{-2, -2, 4}
			});
#endif
	test({3,2,-2,3,-2,-5,4,-1,-5,4},{
			{-5,2,3}
			,{-2,-1,3}
			,{-2,-2,4}
			});
	test({2,2,-1,-3,3,1,-2,1,-2,3,0,-5,0,4,-3,3},{
			{-2, 1, 1}
			,{-3, 1, 2}
			,{-5, 1, 4}
			,{-5, 2, 3}
			,{-1, 0, 1}
			,{-2, 0, 2}
			,{-3, 0, 3}
			,{-2, -1, 3}
			,{-3, -1, 4}
			,{-2, -2, 4}
			});
	return 0;
}
