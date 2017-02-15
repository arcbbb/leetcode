#include <iostream>
#include <vector>
using namespace std;

//#define DEBUG

/*
 * kn = kn-1 + stage
 * P(n,k) = (P(n-1,k-1) && check(n,k) | P(n-1, k) && check()...)
 * 1. calculate how many stages there are.
 * 2. assign each character to a stage.
 *    so it becomes 0 111 222 3333
 *     func(character, stage) = pass or not
 *     if pass, advance character and stages
 *     if not, back to previous stage
 *             and reset characters belong to that stage
 *   so we can make a table
 *   ch        0 1 2 3 4
 *   stage0 .* 1 1 1
 *   stage1 b*       1 1 1
 *   stage2 a*            
 *   stage3 
 *   correct answer would
 *   func(stage, index range)
 *   func(0, 0~n),
 *   func(1, n~n)
 *   func(2, n~n+1),
 *   func(3, y+1~)
 *     if check_stage(n, x,y) //table
 *            y = repick(n,x,y) //search
 *            if no candidate, n--, x = prev_x
 *     else   set_stage(n,x,y), n+=1, x = y, y = repick(n,x,y)
 *
 *  a b .*  vs "abcabc"
 *  stage 0 = a, stage 1 = b stage 2 = .*
 * P(2, 6-7) = P(1, 6-7) | P(1, 5-7) | P(1,4-7)
 * P(2, 5-6) = P(1, 5-6)
 *  
 *  .* a* b "ccaacb"
 *  stage 0 .* stage 1 a* stage 3 b
 *  0~ n-1 P(0, 0,n), P(1,n,n) P(2, n, n)
 *  0~n-2  P(0, 0, n-1), P(1,n-1,n-1) P(2,n-1,n)
 *  x~n-1
 *  [0] P0(0, n)= false P0(0, n-1)=?
 *  [1] P1(n,n)= false  P1(n-1,n) = false P1(n-1,n-1) = ?
 *  [2] P2(n,n) = false P2(n-1, n) = true
 *  P[0] = 4
 *  P[1] = 4
 *  P[2] = 5
 */

typedef struct {
	bool skipable;
	char ch;
} st_t;

class _sol {
	public:

		vector<st_t> st;
		void init_stages(string p)
		{
			char ch, prev_ch;
			for (auto it = p.begin(); it != p.end(); it++) {
				ch = *it;
				if (ch == '*') {
					st[st.size()-1].skipable = true;
				} else {
					st_t t;
					t.skipable = false;
					t.ch = ch;
					st.push_back(t);
				}
			}
		}

		void dump_stages()
		{
			for (auto it = st.begin(); it != st.end(); it++) {
				cout << "[" << it - st.begin() << "]" << it->ch << " " << it->skipable << endl;
			}
		}

		bool isMatch(string s, string p) {
			init_stages(p);
			int k = st.size();
			int n = s.size();
			P = new int[k*n];
			target = s;
			for (int i = 0; i < k*n; i++) {
				P[i] = -1;
			}
			if (check(k-1, n-1)) {
				return true;
			} else {
				return false;
			}
		}

		bool check(int stage, int ch_index)
		{
#ifdef DEBUG
			cout << "check [" << stage << "," << ch_index << "]" << endl;
#endif
			if ((stage < 0) || (ch_index < 0)) {
				if ((stage < 0) && (ch_index < 0)) {
					return true;
				} else {
					if ((stage >= 0) && st[stage].skipable)
						return check(stage-1, ch_index);
					else
						return false;
				}
			} else if (P[stage * target.size() + ch_index] == -1) {
				P[stage * target.size() + ch_index] = 1;
				if (target[ch_index] == st[stage].ch) {
					if (st[stage].skipable)
						// a*
						return check(stage, ch_index-1) 
							|| check(stage-1, ch_index-1) 
							|| check(stage-1, ch_index);
					else
						// a
						return check(stage-1, ch_index-1);
				} else {
					if (st[stage].ch == '.') {
						// .*
						if (st[stage].skipable)
							return check(stage, ch_index-1)
								|| check(stage-1, ch_index-1)
								|| check(stage-1, ch_index);
						else
							// .
							return check(stage-1, ch_index-1);
					} else if (st[stage].skipable) {
						return check(stage-1, ch_index);
					} else {
#ifdef DEBUG
						cout << "!= " << target[ch_index] << "," << st[stage].ch << endl;
#endif
						return false;
					}
				}
			} else {
#ifdef DEBUG
				cout << "-1 " << stage << "," << ch_index << endl;
#endif
				return false;
			}
		}
		int *P;
		string target;
};

class Solution {
	public:
		bool isMatch(string s, string p) {
			_sol sol;
			bool ret;
			ret = sol.isMatch(s, p);
			return ret;
		}
};

void test(string s, string p, bool ans)
{
	Solution solv;
	bool ret;
#if 0
	_sol sol;
	sol.init_stages(p);
	sol.dump_stages();
#endif
	ret = solv.isMatch(s, p);
	cout << s << "," << p << "= " << ret << ":" << ((ret == ans)?"Pass":"Fail") << endl;
}

void test1(string p)
{
	_sol solv;
	solv.init_stages(p);
	solv.dump_stages();
}

int main()
{
#if 0
	test1("a*b*.c");
	test1("aaa*b*.c");
#endif
#if 1
	test("a","", false);
	test("",".*", true);
	test("","a", false);
	test("aa","a", false);
	test("aa","aa", true);
	test("aaa","aa", false);
	test("aa","a*", true);
	test("aa",".*", true);
	test("ab",".*", true);
	test("aab","c*a*b", true);
	test("cccaabcb",".*a*b", true);
	test("cccaabcb",".*a*bc*", true);
	test("aaa","ab*ac*a", true);
	test("","c*c*", true);
#endif
	return 0;
}
