#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//#define DEBUG


void dump_vec(vector<int> &n)
{
	for (auto it = n.begin(); it != n.end(); it++) {
		cout << *it << " ";
	}
}
/*
   [1,2],[1,2] = [1,1,2,2] = 1+2/2 = 1.5, pos_target = (n-1)/2 = 1

   begin = 0, end = 1, middle = 0, pos_a = 0, pos_b = 1,
   1[0] = 1, 2[1] = 2, first fail, begin = 1

   begin = 1, end = 1, middle = 1, pos_a = 1, pos_b = 0
   1[1] = 2, 2[0] = 1, 


   [1,2,3,4,6,7] [5]  n = 7, pos_target = 3

   begin = 3, end = 5, middle = 4, pos_a = 4, pos_b = 3-4 = -1

   first iteration: begin = 0, end = n-1, pos_target = (n-1)/2

   may find second first, then find first first.

   for each iteration(begin, end, pos_target)
   while (begin <= end)
       middle = (begin+end)/2
       pos_a = middle, pos_b = pos_target - pos_a
       if b < 0, dec middle
       if b==0, if 1[a] <= 2[0] then found it. else dec middle.
       if b>2.n, inc middle
       if b==2.n, if 1[a] < 2[max] then inc middle, else found it.
       if 1[a] <= 2[b-1], inc middle
       if [a] > 2[b], dec middle
       then (1[a] > 2[b-1] && 1[a] <= 2[b]). we found it.

   for same value, always on the left
      b<a <=b
   for same value, always on the right
      b<=a <b
*/
// lower_bound: first element that is not less than val
// upper_bound: first element that is great than val
typedef int (*func_t)(int, vector<int> &, int);
/*
      always left

      a <= bn-1,      return -1, mean a should be bigger
      bn-1 < a <= bn, return 0
      bn   < a,       return 1, means a should be smaller

      always right
      b1, b2, b3, ..., <= a < bn,  return 0
 */
	// true: [0] < x =< [index] < nums.size()
	// true:     x =< [0]
        // true: [n-1]  < x
	int check_x_is_inc_order_left(int x, vector<int> &nums, int index)
	{
		if (nums.size() == 0) {
			return 0; // always in order
		}
		if (index == 0) {
			// no one is on the left
			if (x <= nums[0])
				return 0;
			else
				return 1;
		} else if (index < 0) {
			return 1;
		} else if (index > nums.size()) {
			return -1;
		} else if (index == nums.size()) {
			if (x <= nums[index-1])
				return -1;
			else
				return 0;
		} else {
			// 0 < index < nums.size
			// [0] < x =< [index] < nums.size()
			if (x <= nums[index-1])
				return -1;
			if (x > nums[index])
				return 1;
			//if (x > nums[index-1] && x <= nums[index])
			return 0;
		}
	}

	// true: [index-1] =< x < [index] < nums.size()
	// true else 1:     x < [0]
        // true else -1: [n-1]  =< x
	int check_x_is_inc_order_right(int x, vector<int> &nums, int index)
	{
		if (nums.size() == 0) {
			return 0; // always in order
		}
		if (index == 0) {
			// no one is on the left
			if (x < nums[0])
				return 0;
			else
				return 1;
		} else if (index < 0) {
			return 1;
		} else if (index > nums.size()) {
			return -1;
		} else if (index == nums.size()) {
			if (x < nums[index-1])
				return -1;
			else
				return 0;
			
		} else {
			// 0 < index < nums.size()
			if (x < nums[index-1])
				return -1;
			if (x >= nums[index])
				return 1;
			//if (x >= nums[index-1] && x < nums[index])
			return 0;
		}
	}
class Solution {
public:

	// return -1 if not found in nums1, otherwise return pos in nums1
	void find_median(vector<int>& nums1, vector<int>& nums2, vector<int>&ans, func_t check_x_is_inc_order)
	{
		int begin, middle, end;
		int ret = -1;
		int x;
		int pos_a, pos_b;
		begin = 0;
		end = nums1.size()-1;
		bool flag_even;
		int n = nums1.size() + nums2.size();
		int pos_target = (n - 1) / 2;

		flag_even = ((n % 2) == 0)? true:false;

		while((begin >= 0) && (begin < end)) {
			middle = (begin+end)/2;
			x = nums1[middle];

#ifdef DEBUG
			cout << "middle " << "[" << begin << " + " << end <<  "]=" << "[" << middle << "]" << x << endl;
#endif

			pos_a = middle;
			pos_b = pos_target - pos_a;
			if ( check_x_is_inc_order(nums1[pos_a], nums2, pos_b) == 0) {
				// find answer
				ret = pos_a;
				ans.push_back(nums1[pos_a]);
#ifdef DEBUG
				cout << "first = " << pos_a << "," << ans[ans.size()-1] << endl;
#endif
				if (flag_even) {
					pos_a += 1;
					pos_b = pos_target + 1 - pos_a;
					if (check_x_is_inc_order(nums1[pos_a], nums2, pos_b) == 0) {
						// find answer
						ret = pos_a;
						ans.push_back(nums1[pos_a]);
#ifdef DEBUG
						cout << "second = " << pos_a << "," << ans[ans.size()-1] << endl;
#endif
					}
				}
				break;
			}

			pos_b = pos_target + 1 - pos_a;
			if (flag_even && (check_x_is_inc_order(nums1[pos_a], nums2, pos_b) == 0)) {
				// find answer
				ret = pos_a;
				ans.push_back(nums1[pos_a]);
#ifdef DEBUG
				cout << "second = " << pos_a << "," << ans[ans.size()-1] << endl;
#endif
				//break;
				end = middle - 1;
				continue;
			}
			// wrong
			pos_b = pos_target - pos_a;
			if (check_x_is_inc_order(nums1[pos_a], nums2, pos_b) < 0) {
#ifdef DEBUG
				cout << "increase middle" << endl;
#endif
				begin = middle+1;
			} else {
#ifdef DEBUG
				cout << "decrease middle" << endl;
#endif
				end = middle-1;
			}
#ifdef DEBUG
			cout << "next: begin=" << begin << ", end= " << end << endl;
#endif
		}
		if (begin == end) {
#ifdef DEBUG
			cout << "final check " <<  begin << endl;
#endif
			middle = end;
			x = nums1[middle];
			pos_a = middle;
			pos_b = pos_target - pos_a;
			if (check_x_is_inc_order(nums1[pos_a], nums2, pos_b) == 0) {
				// find answer
				ret = pos_a;
				ans.push_back(nums1[pos_a]);
#ifdef DEBUG
				cout << "first = " << pos_a << "," << ans[ans.size()-1] << endl;
#endif
				return;
			}

			pos_b = pos_target + 1 - pos_a;
			if (flag_even && (check_x_is_inc_order(nums1[pos_a], nums2, pos_b) == 0)) {
				// find answer
				ret = pos_a;
				ans.push_back(nums1[pos_a]);
#ifdef DEBUG
				cout << "second = " << pos_a << "," << ans[ans.size()-1] << endl;
#endif
				return;
			}
		}
		return;
	}

	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		// check nums1 & nums2 are in increasing order,or reverse it
		if ((nums1.size() > 1) && (nums1[0] > nums1[1]))
			reverse(nums1.begin(), nums1.end());
		if ((nums2.size() > 1) && (nums2[0] > nums2[1]))
			reverse(nums2.begin(), nums2.end());
		return solv(nums1, nums2);
	}

	void test()
	{
		/*
		 * stage1. 
		 *     for even, find both then done.
		 *     for odd, find one then done.
		 * stage2.
		 *     for even, 
		 */
	}

	double solv(vector<int>& nums1, vector<int>& nums2) {
		int median_index_1, median_index_2;
		double ret = 0;
		bool flag_even;
		vector<int> ans;

		int n = nums1.size() + nums2.size();
		flag_even = ((n % 2) == 0)? true:false;

#ifdef DEBUG
		cout << "find nums1" << endl;
#endif
		find_median(nums1, nums2, ans, check_x_is_inc_order_left);
#ifdef DEBUG
		cout << "find nums2" << endl;
#endif
		find_median(nums2, nums1, ans, check_x_is_inc_order_right);

		if (flag_even && (ans.size() != 2)) {
#ifdef DEBUG
			cout << "WA:";
			dump_vec(ans);
			cout << endl;
#endif
			return 0;
		} else if (ans.size() == 0) {
#ifdef DEBUG
			cout << "no ans" << endl;
#endif
			return 0;
		}
		if (flag_even) {
			ret = ans[0] + ans[1];
			ret /= 2;
		} else {
			ret = ans[0];
		}

		return ret;
	}
};

void test(vector<int> a, vector<int> b)
{
	Solution solv;

	//cout << solv.find_median(a,b) << endl;
	cout << "a: ";
	dump_vec(a);
	cout << "b: ";
	dump_vec(b);
	cout << endl;
	cout << solv.findMedianSortedArrays(a,b) << endl;
}

int main()
{
	vector<int> a({1,2,3,4,5});
	test({},{1});
	test({1,2},{1,2});
	test({3},{1,2});
	test({1},{2,3,4});
	test({1,3},{2});
	test({1,2},{3,4});
	test({1},{2,3,4,5,6});
	test({5},{1,2,3,4,6,7});
	return 0;
}
