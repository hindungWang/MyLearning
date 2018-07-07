/****
C++ 单链表数据结构  常用算法 


******/


#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
ListNode* swapPairs(ListNode* head)//链表前后位置调换：1->2->3->4  ==> 2->1->4->3 
{
        if(head == NULL)return NULL;
        if(head->next == NULL)return head;
        
        ListNode *p = head;
        ListNode *re = head->next;
        ListNode *temp;
        ListNode *link;
        ListNode *pre = head;
        while(p->next)
        {
        	if(p->next->next == NULL)
        	{
        		pre->next = p->next;
        		p->next->next = p;
        		p->next = NULL;
        		break;
			}
			else
			{
				//pre->next = p->next;
				if(pre->next != p->next)
				{
					link = pre->next;
					pre->next = p->next;
					pre = link;
				}
				temp = p->next->next;
				p->next->next = p;
		        p->next = temp;
		        p = temp;
		        temp = p->next;
			}
        }
        return re;
    }
    
ListNode* inverter(ListNode *head)
{
	ListNode *pre = head;
	ListNode *p = head->next;
	ListNode *temp;
	head->next = NULL;
	
	while(p)
	{
		temp = p->next;
		p->next = pre;
		pre = p;
		p = temp;
	}
	return pre;
} 
bool isloop(ListNode *head)
{
	ListNode *p = head;
	ListNode *q = head;
	
	while(q->next != NULL)
	{
		p = p->next;
		q = q->next->next;
		
		if(p == q)return 1;
	}
	return 0;
}
ListNode *loopEntry(ListNode *head)
{
	ListNode *p = head;
	ListNode *q = head;
	
	while(q->next != NULL)
	{
		p = p->next;
		q = q->next->next;
		
		if(p == q)break;
	}
	if(q->next == NULL)return NULL;
	
	p = head;
	while(p != q)
	{
		p = p->next;
		q = q->next;
	}
	return q;
}
void pt(ListNode *p)//打印单链表 
{
	while(p)
	{
		cout<<p->val<<"->";
		p = p->next;
	}
	cout<<"null"<<endl;
}
int main()
{
	ListNode head(1);
	ListNode p1(2);
	ListNode p2(3);
	ListNode p3(4);
	ListNode p4(5);
	ListNode p5(6);
	ListNode p6(7);
	ListNode p7(8);
	ListNode p8(9);
	head.next = &p1;
	p1.next = &p2;
	p2.next = &p3;
	p3.next = &p4;
	p4.next = &p5;
	p5.next = &p6;
	p6.next = &p7;
	
	pt(&head);
	//ListNode * re = swapPairs(&head); 
	//pt(re);
	ListNode *in = inverter(&head);
	pt(in);
	
	ListNode hasloop(1);
	ListNode l1(2);
	ListNode l2(3);
	ListNode l3(4);
	ListNode l4(5);
	hasloop.next = &l1;
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l4;
	//pt(&hasloop);
	cout<<isloop(&hasloop)<<endl;
	ListNode *loop = loopEntry(&hasloop);
	cout<<loop<<" "<<loop->val<<endl;
	return 0;
}
