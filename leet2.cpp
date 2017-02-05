#include <iostream>
using namespace std;

struct ListNode;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x):val(x), next(NULL) {}
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    	int sum = 0;
    	int flag_carry = 0;
    	ListNode *p1, *p2, *p3, *ret;
    	sum = l1->val + l2->val;
    	flag_carry = sum/10;
    	ret = new ListNode(sum%10);
    	p1 = l1->next;
    	p2 = l2->next;
    	p3 = ret;
    	while (p1 != NULL || p2 != NULL) {
    		sum = 0;
    		if (p1) {
			sum += p1->val;
			p1 = p1->next;
		}
    		if (p2) {
			sum += p2->val;
			p2 = p2->next;
		}
		sum += flag_carry;
		flag_carry = sum /10;
		p3->next = new ListNode(sum%10);
		p3 = p3->next;
	}
    	if (flag_carry) {
		p3->next = new ListNode(1);
    	}
    	return ret;
    }
};

ListNode *cList(int num)
{
	int digit;
	ListNode *p, *ret;
	ret = p = new ListNode(num%10);
	num /= 10;
	while(num != 0) {
		p->next = new ListNode(num%10);
		num /= 10;
		p = p->next;
	}
	return ret;
}

void pList(ListNode *list)
{
	ListNode *p = list;
	while (p) {
		cout << "[" << p->val << "]" << " ";
		p = p->next;
	}
	cout << endl;
}

int main()
{
	ListNode *a, *b;
	Solution sol;
	a = cList(81); pList(a);
	b = cList(0); pList(b);
	a = sol.addTwoNumbers(a, b);
	pList(a);
}
