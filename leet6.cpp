#include <iostream>
using namespace std;

//#define DEBUG
/*
 * given n rows
 *  n == 0, no string
 *  n == 1, origin string
 *  n == 2, m sets, m = size/2, put string i=0~[n-1], i==even [i], i == odd [m+i]
 *  n == 3, m sets size/(3+1)
 * Q: how to know in wich row a given position is?
 *    a cycle is  (n + (n - 2))
 *    0,    1,   2,   3,   4,   5, ..., n-1
 *       2n-3,  .., n+3, n+2, n+1,   n,
 *
 *    for n = 5, cycle = 8, rev = (n-1) - (id%n+1)
 *    0,1,2,3,4
 *      7,6,5,
 *    8,9
 *    pos_outer = index / cycle,  pos_inner = index % cycle
 *    pos_inner_r == (n-1) - (pos_inner%n+1)
 *    for pos_inner < n
 *        for pos_inner == 0
 *        1st ch -> pos_inner == 0,        output[pos_outer] = ch
 *        for pos_inner != 0 && pos_inner < n
 *        2nd ch -> pos_inner == 1,        output[total_cycles+pos_outer*2] = ch
 *        3rd ch -> pos_inner == 2,        output[total_cycles+total_cycles*2+pos_outer*2] = ch
 *        4rd ch -> pos_inner == 3,        output[total_cycles+total_cycles*4+pos_outer*2] = ch
 *        nth ch -> pos_inner == n-1,      output[total_cycles*(2*pos_inner-1)+pos_outer*2] = ch
 *    for n <= pos_inner < cycle
 *        (n+1)th ch -> pos_inner == n, pos_inner_r = n-2,  output[total_cycles+pos_outer*2+1] = ch;
 *        last ch ->pos_inner == cycle-1:  
 *
 * n = 3, cycle = 4:  0, 1, 2, 3, total_cycles = 12/4 = 3
 * 0, 1,2, 3,4,5,6,7, 8, 9,10,11,12,13
 * 0, 4,8, 1,3,5,7,9,11, 2, 6,10
 * 0, 4,8,12,1,3,5,7, 9,11,13, 2, 6,10
 *            0-0     0-0
 *  0,1,2     1-3     1-4
 *    3       2-9     2-11
 *  4,5,6     3-4     3-5
 *    7       4-1     4-1
 *  8,9,10    5-5     5-6
 *    11      6-10    6-12
 *  12,13     7-6     7-7
 *            8-2     8-2
 *            9-7     9-8
 *            10-11   10-13
 *            11-8    11-9
 *                    12-3
 *                    13-2
 *  1
 *  2
 *  3 7
 *  4 6
 *  5
 */
class Solution {
public:
	int _cycle;
	int _numRows;
	int total_cycles;
	int pos(int index)
	{
		int pos_outer = index / _cycle;
		int pos_inner = index % _cycle;
		if (pos_inner == 0) {
			return pos_outer;
		} else if (pos_inner == _numRows-1) {
			return total_cycles*(2*pos_inner-1) + pos_outer + rem[pos_inner];
		} else if (pos_inner < _numRows) {
			return total_cycles*(2*pos_inner-1) + pos_outer*2 + rem[pos_inner];
		} else {
			int pos_inner_r = (_numRows-1) - (pos_inner%_numRows+1);
			return total_cycles*(2*pos_inner_r-1) + pos_outer*2 + 1 + rem[pos_inner_r];
		}
	}

	int *rem;
	void dump_rem()
	{
		for (int i = 0; i < _numRows; i++) {
			cout << "rem" << i << "=" << rem[i] << endl;
		}
	}

	void remain_calc(int remain)
	{
		rem = new int[_numRows];
		for (int i = 0; i < _numRows; i++)
			rem[i] = 0;
		for (int i = 0; i < remain; i++) {

			if (i < _numRows)
				rem[i]++;
			else {
				int i_r = (_numRows-1) - (i % _numRows + 1);
				rem[i_r]++;
			}
		}
		int prev_sum = 0;
		int sum = 0;
		for (int i = 0; i < _numRows; i++) {
			sum += rem[i];
			rem[i] = prev_sum;
			prev_sum = sum;
		}
	}

	string trysolv(string s, int numRows)
	{
		char *ans = new char[s.size()+1];
		ans[s.size()] = '\0';
		_numRows = numRows;
		_cycle = 2*numRows - 2;
		total_cycles = s.size() / _cycle;
		int cycle_remain = s.size() % _cycle;
		remain_calc(cycle_remain);
#ifdef DEBUG
		dump_rem();
#endif
		for (int i = 0; i < s.size(); i++) {
			int id = pos(i);
#ifdef DEBUG
			cout << i << " to " << id << endl;
#endif
			ans[id] = s[i];
		}
		return ans;
	}

	string convert(string s, int numRows)
	{
		if (numRows <= 1) {
			return s;
		}

		return trysolv(s, numRows);
	}
};

void test(string s, int numRows, string ans)
{
	Solution solv;
	string ret;
	cout << s << "," << numRows << " : ";
	ret = solv.convert(s, numRows);
	cout << ret << ((ret == ans)? "pass":"fail") << endl;
}

int main()
{
	test("PAYPALISHIRING", 3, "PAHNAPLSIIGYIR");
	test("PAYPALISHIRI", 3, "PAHAPLSIIYIR");
	return 0;
}
